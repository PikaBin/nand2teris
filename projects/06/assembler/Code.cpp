#include "Code.h"
#include <iostream>

Code::Code(/* args */)
{
    m_destMap = {
        // {"","000"},
        {"M","001"},
        {"D","010"},
        {"MD","011"},
        {"A","100"},
        {"AM","101"},
        {"AD","110"},
        {"AMD","111"}
    };
    
    m_jumpMap = {
        // {"","000"},
        {"JGT","001"},
        {"JEQ","010"},
        {"JGE","011"},
        {"JLT","100"},
        {"JNE","101"},
        {"JLE","110"},
        {"JMP","111"}
    };

    m_compMap = {
        {"0","0101010"},
        {"1","0111111"},
        {"-1","0111010"},
        {"D","0001100"},
        {"A","0110000"},
        {"!D","0001101"},
        {"!A","0110001"},
        {"-D","0001111"},
        {"-A","0110011"},
        {"D+1","0011111"},
        {"A+1","0110111"},
        {"D-1","0001110"},
        {"A-1","0110010"},
        {"D+A","0000010"},
        {"D-A","0010011"},
        {"A-D","0000111"},
        {"D&A","0000000"},
        {"D|A","0010101"},
        {"M","1110000"},
        {"!M","1110001"},
        {"-M","1110011"},
        {"M+1","1110111"},
        {"M-1","1110010"},
        {"D+M","1000010"},
        {"M+D","1000010"},
        {"D-M","1010011"},
        {"M-D","1000111"},
        {"D&M","1000000"},
        {"D|M","1010101"},      
    };

}

Code::~Code()
{
}

std::string Code::dest(std::string mnemonic_dest)
{
    if(m_destMap.find(mnemonic_dest)!=m_destMap.end())
    {
        return m_destMap[mnemonic_dest];
    }
    std::cout<<"can not find mnemonic_dest"<<std::endl;
    return std::string("000");
}

std::string Code::jump(std::string mnemonic_jump)
{
    if(m_jumpMap.find(mnemonic_jump)!=m_jumpMap.end())
    {
        return m_jumpMap[mnemonic_jump];
    }
    std::cout<<"can not find mnemonic_jump"<<std::endl;
    return std::string("000");
}

std::string Code::comp(std::string mnemonic_comp)
{
    if(m_compMap.find(mnemonic_comp)!=m_compMap.end())
    {
        return m_compMap[mnemonic_comp];
    }
    std::cout<<"can not find mnemonic_comp"<<std::endl;
    return std::string();
}
