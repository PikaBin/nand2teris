#ifndef PARSER_H
#define PARSER_H

/**
 * @date 2023-4-16
 * @brief 解析编译文件，返回编译命令的内在含义
*/

#include <string>
#include "Code.h"
#include <map>

enum CommandType{
    A_COMMAND=0,
    C_COMMAND,
    L_COMMAND
};

class Parser
{
private:

    CommandType commandType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();



public:
    Parser(/* args */);
    ~Parser();
    void setCurInstruction(const std::string & newInstru){ m_curInstruction = newInstru;}
    void initSymbolTable();
    std::string parse();


private:
    std::string m_curInstruction;
    Code m_pCode;
    std::map<std::string,int> m_sysmbolTable;
    unsigned int m_curInstructionNum;//当前命令的行号（实质时ROM的内存地址）
    unsigned int m_curVarNum; //下一个变量存放的地址
};

#endif






