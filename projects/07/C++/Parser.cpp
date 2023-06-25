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
    if(firstStrOfCommand=="if") return  C_IF;
    if(firstStrOfCommand=="function") return C_FUNCTION;
    if(firstStrOfCommand=="return") return C_RETURN;
    return C_CALL;
}

std::string Parser::arg1()
{
    // int startPos = m_curComand.find(" ");
    // int endPos = m_curComand.find_first_not_of(" ");
    // if(endPos!= string::npos)
    // {
    //     return m_curComand.substr(0,endPos);
    // }
    // return m_curComand;


    switch (commandType())
    {
    case C_ARITHMETTIC:
        return m_curComand;
        break;
    
    default:
        return m_splitedCommandVec.at(1);
        break;
    }
    
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
    if(commandType()==C_PUSH || commandType()==C_POP)
    {
        return m_codeViewr.writePushPop(m_splitedCommandVec);
        
    }

    if(commandType()==C_ARITHMETTIC)
    {
        return m_codeViewr.writeArithmetic(m_splitedCommandVec);
    }

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
