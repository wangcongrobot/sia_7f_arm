#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#include<pthread.h>
#include<string.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>  // // io 流控制头文件, 主要是一些操纵用法如setw(int n),setprecision(int n),setbase(int   n),setfill(char c)的


#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long
using namespace std;

extern  int fd;
void UART_initial();
void set_speed(int fd, int speed);
int set_Parity(int fd,int databits,int stopbits,int parity);
void writeSerial(unsigned char *buf,unsigned char len);
void Parse( ) ;
void receiveSerial( unsigned char length) ;
uchar CheckRecvData() ;
void sInit();//从手初始化，开始执行时被调用一次即可
void Run();//周期性执行
void ParseCmd( );
void MoveCtrl();
void Timer_initial();
void signalHandler(int signo);      //定时器函数
void SendCtrl();
void File_Create ();
void Data_Record();
void FileData_Copy();
extern uchar uart0_receive_ok;
extern uchar len_receive;
extern volatile unsigned char SendEN;
extern volatile int TIMER_FLAG;
extern unsigned char com0RecvBuf[64];
extern unsigned char com0SendBuf[64];///接收与发送缓冲区
extern  char   Read_Flag;
extern double Joint_AngleSet[7];
#endif // HEADER_H_INCLUDED
