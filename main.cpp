/*
 是否熟悉POSIX多线程编程技术？如熟悉，编写程序完成如下功能：
  1）有一int型全局变量g_Flag初始值为0；
  2）在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1
  3）在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2
  4）线程序1需要在线程2退出后才能退出
  5）主线程在检测到g_Flag从1变为2，或者从2变为1的时候退出
   */
#include "header.h"
#include "data.h"
#include "read_file.h"
unsigned char com0RecvBuf[64];
unsigned char com0SendBuf[64];  //接收与发送缓冲区
typedef  void*  (*fun)(void*);   //指向函数的指针
int g_Flag=0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void* thread1(void*);                   //thread1为指向函数thread1()的指针
void* thread2(void*);
void signalHandler(int signo);      //定时器函数
/*
 *  when program is started, a single thread is created, called the initial thread or main thread.
 *  Additional threads are created by pthread_create.
 *  So we just need to create two thread in main().
 */
int main(int argc, char** argv)
{
    UART_initial();
    Timer_initial();    //启动定时器
    File_Create ();    //创建文件
    File_readInitial();  //读取文件初始化
    pthread_t tid1, tid2;
    int rc1=0, rc2=0;
    rc2 =   pthread_create(&tid2, NULL, thread2, NULL);
    usleep(10000);    //休眠10毫秒，保证线程2 开始运行
    if(rc2 != 0)
        printf("pthread_create thread2 error！\n ");

    rc1 = pthread_create(&tid1, NULL, thread1, &tid2);     //线程2的地址作为参数传给线程1
    usleep(10000);    //休眠10毫秒，保证线程1 开始运行
    if(rc1 != 0)
        printf("pthread_create thread1 error！\n ");

    printf("enter main\n");
    sInit();
    // writeSerial(com0SendBuf ,sizeof(com0RecvBuf)) ;
    usleep(15000);
    while(1)
    {
      Run();
    }
//	pthread_cond_wait(&cond, &mutex);    //等待条件变量为真为什么条件变量始终与互斥锁一起使用，对条件的测试是在互斥锁（互斥）的保护下进行的呢？
    //因为“某个特性条件”通常是在多个线程之间共享的某个变量。互斥锁允许这个变量可以在不同的线程中设置和检测。
    printf("leave main\n");
    exit(0);
}
void* thread1(void* arg)
{
    printf("enter thread1\n");
    printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());

    /*pthread_mutex_lock(&mutex);
    if(g_Flag == 2)
    	pthread_cond_signal(&cond);   //特定信号为真
    g_Flag = 1;
    pthread_mutex_unlock(&mutex);
    */
    while(1)
    {
        //       pthread_mutex_lock(&mutex);    //对多线程更改的数据要进行互斥访问，因串口数据只会在本线程中修改，不需加锁
        ParseCmd( );
        //       pthread_mutex_unlock(&mutex);  //

    }
//	pthread_join(*(pthread_t*)arg, NULL);       //等待线程结束，成功返回0，否则返回Exxx（为正数），*(pthread_t*)arg：把arg转换为pthread_t型指针，然后后取出
    printf("leave thread1\n");
    pthread_exit(0);
}

/*
 * thread2() will be execute by thread2, after pthread_create()
 * it will set g_Flag = 2;
 */
void* thread2(void* arg)     //线程2暂时不用
{
    printf("enter thread2\n");
    printf("this is thread2, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());  //打印自己的线程ID
    pthread_mutex_lock(&mutex);
    if(g_Flag == 1)
        pthread_cond_signal(&cond);
    g_Flag = 2;
    pthread_mutex_unlock(&mutex);
    printf("leave thread2\n");
    pthread_exit(0);
}
void signalHandler(int signo)
{
    switch (signo)
    {
    case SIGALRM:
//              printf("Caught the SIGALRM signal!\n");
        SendCtrl();
 //        cout << "hello";
        break;
    }
}
