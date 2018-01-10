#include "header.h"
#include "read_file.h"
#include "data.h"
ifstream fin;
string ReadFile;
long filelen=0;
char   Read_Flag=0;
void File_readInitial()
{
    ReadFile= "/home/zyx/manipulator/code_project/manipulator_line/data_trajectory/joint_line.txt";
    fin.open(ReadFile.c_str(), ios::in );
    fin.seekg(0,ios::end);
    //seekg是对输入文件定位，它有两个参数：第一个参数是偏移量，第二个参数是基地址。
    //ios::beg //相对于文件开头的偏移量
    //ios::cur //相当于当前位置的偏移量
    //ios::end //相当于文件结尾的偏移量
    filelen = fin.tellg() ;      //获取文件长度  tellg（）函数不需要带参数，它返回当前定位指针的位置，也代表着输入流的大小
    filelen=filelen-1;
    fin.seekg(0,ios::beg) ;  //指针指向文件开头

//	fin.close();
}
void FileData_Copy()
{
    for(int i=0;i<6;i++)
           {
                if((fin.tellg() == filelen)||(fin.tellg() ==-1))
                {
                    Read_Flag=1;
                }
                else
                {
                    fin>>Joint_AngleSet[i];            //fin从数据流（已经在内存中）中提取数据，cin只有在键盘按下enter键时才会吧数据放
   //                 cout <<Joint_AngleSet[i]<<endl;                                                             // 冲区中被数据流调用置内存缓
                }
           }
}

