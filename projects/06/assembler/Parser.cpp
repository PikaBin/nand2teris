
#include "Parser.h"
#include <bitset>

using namespace std;

Parser::Parser(/* args */)
{
    m_sysmbolTable = {
        {"SP", 0},
        {"LCL", 1},
        {"ARG", 2},
        {"THIS", 3},
        {"THAT", 4},
        {"R0", 0},
        {"R1", 1},
        {"R2", 2},
        {"R3", 3},
        {"R4", 4},
        {"R5", 5},
        {"R6", 6},
        {"R7", 7},
        {"R8", 8},
        {"R9", 9},
        {"R10", 10},
        {"R11", 11},
        {"R12", 12},
        {"R13", 13},
        {"R14", 14},
        {"R15", 15},
        {"SCREEN", 16384},
        {"KBD", 24576},
    };
    m_curInstructionNum = 0;
    m_curVarNum = 16;
}

Parser::~Parser()
{
}

/// @brief 第一遍读取，填充符号表
void Parser::initSymbolTable()
{
    if (commandType()==L_COMMAND)
    {
        string mnemonic = symbol();
        if (m_sysmbolTable.find(mnemonic) == m_sysmbolTable.end())
        {
            m_sysmbolTable[mnemonic] = m_curInstructionNum;
            
        }
    }else if (commandType()==A_COMMAND || commandType()==C_COMMAND)
    {
        m_curInstructionNum++;
    }
    
}

std::string Parser::parse()
{
    std::string binaryStr = "";
    if (commandType() == A_COMMAND)
    {
        binaryStr = "0" + binaryStr;
        string strSymbol = symbol();
        if (isdigit(strSymbol[0]))
        {
            std::bitset<15> resBit(atoi(symbol().c_str()));
            binaryStr += resBit.to_string();
        }else
        {
            auto it_find = m_sysmbolTable.find(strSymbol);
            if(it_find==m_sysmbolTable.end())
            {
                m_sysmbolTable[strSymbol] = m_curVarNum;
                std::bitset<15> resBit(m_curVarNum);
                binaryStr += resBit.to_string();
                m_curVarNum++;
                
            }else
            {
                // strSymbol = it_find->second;

                std::bitset<15> resBit(it_find->second);
                binaryStr += resBit.to_string();
            }
            
        }
        
    }

    if (commandType() == C_COMMAND)
    {
        binaryStr = "111" + binaryStr;
        binaryStr += m_pCode.comp(comp());
        binaryStr += m_pCode.dest(dest());
        binaryStr += m_pCode.jump(jump());
    }

    return binaryStr;
}

CommandType Parser::commandType()
{
    if (m_curInstruction[0] == '@')
    {
        return A_COMMAND;
    }else if(m_curInstruction[0] == '(' && m_curInstruction.back() == ')')
    {
        return  L_COMMAND;
    }

    return C_COMMAND;
}

std::string Parser::symbol()
{
    if (commandType() == A_COMMAND)
    {
        return m_curInstruction.substr(1);
    }else if (commandType()==L_COMMAND)
    {
       return m_curInstruction.substr(1, m_curInstruction.size() - 2);
    }
    
    return "";
}

std::string Parser::dest()
{
    if (commandType() == C_COMMAND)
    {
        int equalPos = m_curInstruction.find('=');
        return m_curInstruction.substr(0, equalPos - 0);
    }
    return std::string(); // 如果不含等号，那么dest=null
}

std::string Parser::comp()
{
    if (commandType() == C_COMMAND)
    {
        int equalPos = m_curInstruction.find('=');
        int semicolonPos = m_curInstruction.find(';');
        if (equalPos != std::string::npos)
        {
            return m_curInstruction.substr(equalPos + 1);
        }

        if (semicolonPos != std::string::npos)
        {
            return m_curInstruction.substr(0, semicolonPos - 0);
        }
    }
    return std::string();
}

// how to whether to jump
std::string Parser::jump()
{
    if (commandType() == C_COMMAND)
    {
        int semicolonPos = m_curInstruction.find(';');
        return m_curInstruction.substr(semicolonPos + 1);
    }
    return std::string();
}
