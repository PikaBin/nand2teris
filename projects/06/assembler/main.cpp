#include "Parser.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

/**
 * 含符号编译思路：第一步读取，将所有的（xxx）的xxx以及相关联的地址写进符号表中（地址是从0开始，每有一条命令就+1，
 * 而xxx的地址就是下一条命令对应的数字），第二遍扫描时即开始翻译成二进制码，当A_command的是变量，而又在符号表中
 * 找不到，那么直接加入到符号表及其地址（其地址是从RAM的16开始），下一次遇到时就可以直接替换。比较棘手的是 如何
 * 实现 “读取两遍”，难道真的要读两遍文件吗
*/

bool isErased(char c)
{
    return c==' ' || c=='/';
};

int main(int argc,char* argv[])
{
    cout<<argv[1]<<endl;
    string fileName = argv[1];
    ifstream f(fileName,std::ios_base::in);

    //
    // string outFileName = "E:\\nand2tetris\\projects\\06\test.hack";
    string outFileName = "test.hack";
    // int pos = outFileName.find_last_of('.');
    // outFileName.replace(pos,3,"hack");

    ofstream outF(outFileName,ios_base::trunc);
    if(!outF.is_open()) cout<<"out file is not open"<<endl;
    Parser parser;
    if(f.is_open())
    {
        string line="";
        string targetStr="";
        int endPos=0;
        //第一遍读取，构建符号表
        while (getline(f,line))
        {
            if(line.substr(0,1)=="/" || line.empty()) continue;
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());//去除空格

            //去除命令行内的注释
            endPos = line.find('/');
            if(endPos!=string::npos)
            {
                line = line.substr(0,endPos);
            }
            
            parser.setCurInstruction(line);
            parser.initSymbolTable();
        }
        


        f.clear();
        f.seekg(0,ios::beg);


        //第二遍读取
        while(getline(f,line))
        {
            if(line.substr(0,1)=="/" || line.empty()) continue;
            line.erase(std::remove_if(line.begin(), line.end(),::isspace), line.end());

            //去除命令行内的注释
            endPos = line.find('/');
            if(endPos!=string::npos)
            {
                line = line.substr(0,endPos);
            }

            parser.setCurInstruction(line);
            targetStr = parser.parse();
            if(!targetStr.empty())
            {
                outF.write(targetStr.c_str(),targetStr.size()).write("\n",1);
            }
            
        }

        f.close();
        outF.close();

    }else
    {
        cout<<"can not open file"<<fileName;
    }



    
}