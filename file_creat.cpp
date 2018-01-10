#include "header.h"
#include "file_create.h"
#include "data.h"
char  Timer[20]= {0};
unsigned int sum=0;

void File_Create ()
{
    time_t now_time= time(NULL);
    strftime(Timer, 20, "%F %H:%M:%S", localtime(&now_time)); //该函数可以设定时间的格式
    FileName="/home/zyx/manipulator/code_project/manipulator_line/data/"+(string)Timer+".txt";
    fout.open(FileName.c_str(), ios::out | ios::app); //创建的对象关联到文件，文件只追加
//  ofstream fout ("text.txt", ios::out | ios::app) ;//打开文件写入数据，只追加
}

/*void Data_Record()   //发送数据整体记录
{
    unsigned char *buff_fout;
    char str[27]= {0};
    gettimeofday(&tv,NULL);   //获得相对1970年时间：分、秒
    fout <<dec<<tv.tv_sec <<"."<<setfill('0')<<setw(6)<< tv.tv_usec;
    fout <<": ";
    for(buff_fout=com0RecvBuf; buff_fout<(com0RecvBuf+24); buff_fout++)
    {
        sprintf(str, "%02X ", *buff_fout);
        fout  << str;
//        fout << " 0x"<<hex <<setfill('0')<<setw(2)<< (unsigned short) *buff_fout ; //cout自己可以知道要输出的是整数还是字符串（根据要打印的内容判断出）。字符的话，原样输出
        //整数的话自己把数据转换为字符串的形式（0x34----“0x34”），printf需要根据内容，再设定输出格式（输出内容跟设定格式要一一对应）
    }
    fout <<"\n";
    fout.flush();        //刷新内存,实时更新
}*/
void Data_Record()    //收到的数据只记录角度设定值和关节实际值
{
        gettimeofday(&tv,NULL);   //获得相对1970年时间：分、秒
        fout <<dec<<tv.tv_sec <<"."<<setfill('0')<<setw(6)<< tv.tv_usec;
        fout <<": ";
        for (int i=0;i<7;i++)  //向文件写7次，共有28个字节
        {
            fout<<" "<<hex<<setfill('0')<<setw(4)<<sPos.scmdPos[i];     //向文件写入关节角度设定值
            fout<<" "<<hex<<setfill('0')<<setw(4)<<spos->scmdPos[i]; //向文件写入关节角度实际值
        }
        fout <<"\n";
        fout.flush();                                       //刷新内存,实时更新
}


