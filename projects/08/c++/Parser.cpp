#include "Parser.h"
#include <sstream>
#include <iostream>


using namespace std;

set<string> Parser::arithmeticCommand = {
    "add",
    "sub",
    "neg",
    "eq",
    "gt",
    "lt",
    "and",
    "or",
    "not"
};

Parser::Parser(/* args */)
{
    m_splitedCommandVec = {};
}

Parser::Parser(std::string filename)
{
    m_splitedCommandVec = {};
    m_codeViewr.setFileName(filename);
}

Parser::~Parser()
{

}

void Parser::VMsplit()
{
    stringstream sstream(m_curComand);
    
    string tmpstr;
    while (getline(sstream,tmpstr,' '))
    {
        m_splitedCommandVec.push_back(tmpstr);
    }
}

VMCommandType Parser::commandType()
{

    if(m_splitedCommandVec.empty())
    {
        cout<<"命令分割失败"<<endl;
    }

    string firstStrOfCommand = m_splitedCommandVec[0];
    if(arithmeticCommand.find(firstStrOfCommand)!=arithmeticCommand.end())
    {
        return C_ARITHMETTIC;
    }

    if(firstStrOfCommand=="push") return C_PUSH;
    if(firstStrOfCommand=="pop") return C_POP;
    if(firstStrOfCommand=="label") return C_LABEL;
    if(firstStrOfCommand=="goto") return C_GOTO;
    if(firstStrOfCommand=="if-goto") return  C_IF;
    if(firstStrOfCommand=="function") return C_FUNCTION;
    if(firstStrOfCommand=="return") return C_RETURN;
    return C_CALL;
}

std::string Parser::arg1()
{
    switch (commandType())
    {
    case C_ARITHMETTIC:
        return m_curComand;
        break;
    
    default:
        return m_splitedCommandVec.at(1);
        break;
    }

    cout<<"返回arg1有误 当前指令为："<<m_curComand<<endl;
    return std::string();
    
}

std::string Parser::args2()
{
    switch (commandType())
    {
    case C_POP:
    case C_PUSH:
    case C_FUNCTION:
    case C_CALL:
        return m_splitedCommandVec[2];
        break;
    
    default:
        cout<<"获取arg2的类型有误"<<endl;
        break;
    }
    return "";
}

std::string Parser::parse()
{

    switch (commandType())
    {
    case C_PUSH:
    case C_POP:
        return m_codeViewr.writePushPop(m_splitedCommandVec);
        break;
    case C_ARITHMETTIC:
    {
        return m_codeViewr.writeArithmetic(m_splitedCommandVec);
        break;
    }
    case C_LABEL:
    {
        return m_codeViewr.writeLabel(arg1());
        break;
    }
    case C_GOTO:
    {
        return m_codeViewr.writeGoto(arg1());
        break;
    }
    case C_IF:
    {
        return m_codeViewr.writeIf(arg1());
        break;
    }
    case C_FUNCTION:
    {
        return m_codeViewr.writeFunction(arg1(),stoi(args2()));
        break;
    }
    case C_CALL:
    {
        return m_codeViewr.writeCall(arg1(),stoi(args2()));
        break;
    }
    case C_RETURN:
    {
        return m_codeViewr.writeReturn();
        break;
    }
    default:
        std::cout<<"判断命令类型出错"<<std::endl;
        break;
    }
    
    
    cout<<"parse 函数出错误"<<endl;
    return std::string();
}

void Parser::setCurComand(std::string command)
{
    m_curComand = command;
    m_splitedCommandVec.clear();
    VMsplit();
}

std::string Parser::writeHead()
{
    return m_codeViewr.init();
}

void Parser::setFile(std::string filename)
{
    m_codeViewr.setFileName(filename);
}
