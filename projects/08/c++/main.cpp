#include "Parser.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <dirent.h>
#include <sys/stat.h>


using namespace std;


int main(int argc,char* argv[])
{
    
    string file = argv[1];
    DIR *vmFolder = opendir(file.c_str());
    struct dirent *entry;

    if (vmFolder==nullptr)
    {
        cout<<"unable to read folder: "<<file;
        return 1;
    }

    int Lastfolder_pos = file.find_last_of("\\");
    string asmFileName = file.substr(Lastfolder_pos)+".asm";
    ofstream outF(file+ asmFileName ,ios_base::trunc);
    if(!outF.is_open()) 
    {
        cout<<"out file is not open"<<endl;
        return 1;
    }
    
    
    Parser parser;

    //写入启动代码
    string targetStr=parser.writeHead();
    // string targetStr = "";
    outF.write(targetStr.c_str(),targetStr.size());

    while ((entry=readdir(vmFolder)))
    {
        string tmp = entry->d_name;
        if (tmp.find("vm")==string::npos)
        {
            continue;
        }
        
        string fileName = file + "\\"+ entry->d_name;
        ifstream f(fileName,std::ios_base::in);

        if(f.is_open())
        {
            parser.setFile(tmp);
            string line="";

            int endPos=0;

            while (getline(f,line))
            {
                if(line.substr(0,1)=="/" || line.empty()) continue;
                //line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());//去除空格

                //去除命令行内的注释
                endPos = line.find('/');
                if(endPos!=string::npos)
                {
                    line = line.substr(0,endPos);
                }
                
                parser.setCurComand(line);
                targetStr = parser.parse();
                if(!targetStr.empty())
                {
                    outF.write(targetStr.c_str(),targetStr.size());/**.write("\n",1)**/
                }
            }
        }

    }
    
    
    // ifstream f(fileName,std::ios_base::in);

    // string outFileName = ".asm";
    // int dotPos = fileName.find_last_of(".");
    // int LastSlashPos = fileName.find_last_of("/");

    // outFileName = fileName.substr(0,dotPos) + outFileName;
    
    // ofstream outF(outFileName,ios_base::trunc);
    // if(!outF.is_open()) cout<<"out file is not open"<<endl;

    // string pureFileName = fileName.substr(LastSlashPos+1,dotPos-LastSlashPos-1);
    // Parser parser(pureFileName);
    // if(f.is_open())
    // {
    //     string line="";
    //     // string targetStr=parser.writeHead();
    //     string targetStr = "";
    //     outF.write(targetStr.c_str(),targetStr.size());
    //     int endPos=0;

    //     while (getline(f,line))
    //     {
    //         if(line.substr(0,1)=="/" || line.empty()) continue;
    //         //line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());//去除空格

    //         //去除命令行内的注释
    //         endPos = line.find('/');
    //         if(endPos!=string::npos)
    //         {
    //             line = line.substr(0,endPos);
    //         }
            
    //         parser.setCurComand(line);
    //         targetStr = parser.parse();
    //         if(!targetStr.empty())
    //         {
    //             outF.write(targetStr.c_str(),targetStr.size());/**.write("\n",1)**/
    //         }
    //     }
    // }
    return 0;
}