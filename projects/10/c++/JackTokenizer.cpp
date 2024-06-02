#include "JackTokenizer.h"
#include <iostream>
#include <set>

using namespace std;

const std::set<string> keywordSet = 
{
    "class","method","int","function","boolean","constructor","char","void","var",
    "static","field","let","do","if","else","while","return","true","false","null",
    "this"
};

JackTokenizer::JackTokenizer(/* args */)
{
    m_firstQuote = m_secondQuote = false;
}

JackTokenizer::~JackTokenizer()
{
}

std::string JackTokenizer::generateXmlstr()
{
    string res;
    switch (Type())
    {
    case TokenType::KEYWORD:
        {
            res = xmlLine("keyword",m_curToken);
            break;
        }
    case TokenType::IDENTIFIER:
        {
            res = xmlLine("identifier",m_curToken);
            break;
        }
    case TokenType::INT_CONST:
        {
            res = xmlLine("integerConstant",m_curToken);
            break;
        }
    case TokenType::STRING_CONST:
        {
            string strVal = stringVal();
            if (strVal.empty())
            {
                return string();
            }
    
            res = xmlLine("stringConstant",strVal);
            break;
        }
    case TokenType::SYMBOL:
        {
            if (m_curToken==">" )
            {
                m_curToken = "&gt;";

            }else if (m_curToken=="<")
            {
                m_curToken = "&lt;";
            }else if (m_curToken=="&")
            {
                m_curToken="&amp;";
            }
                   
            res = xmlLine("symbol",m_curToken);
            break;
        }
    default:
        {
            std::cout<<"wrong token type"<<std::endl;
        }     
    } 
    return res;
}

std::string JackTokenizer::xmlLine(std::string type, std::string contents)
{
   return "<" + type + "> " + contents + " " + "</" + type + ">\n";
}

std::string JackTokenizer::stringVal()
{
    int pos = m_curToken.find_last_of("\"");
    if (m_firstQuote && !m_secondQuote && pos == string::npos)
    {//已经遇到了第一个"但还没有遇到第二个"
       m_constStrValue += " ";
       m_constStrValue += m_curToken;
       return string();
    }else if (m_firstQuote && m_secondQuote)
    {//遇到了第二个"
        string tmpRes = m_constStrValue;
        m_constStrValue = "";
        m_firstQuote = m_secondQuote = false;       
        return tmpRes;
    }
    
    return string();
}

TokenType JackTokenizer::Type()
{
    if (keywordSet.find(m_curToken) != keywordSet.end())
    {
        return TokenType::KEYWORD;
    }else if (isdigit(m_curToken[0]))
    {
        return TokenType::INT_CONST;
    }else if (m_curToken.find("\"")!= string::npos || m_firstQuote)
    {
        if (!m_firstQuote)
        {
            m_firstQuote = true;
        }   
        else if (m_firstQuote && m_curToken=="\"")
        {
            m_secondQuote = true;
        }
        
        return TokenType::STRING_CONST;
    }   
    else if (ispunct(m_curToken[0]))
    {
        return TokenType::SYMBOL;
    }
    

    return TokenType::IDENTIFIER;
}

std::string JackTokenizer::advance()
 {
    if (hasMoreToken())
    {
        string res =  m_tokenQue.front();
        m_lastToken = m_curToken;
        m_curToken = res;
        m_tokenQue.pop();
        if(hasMoreToken())
        {
            m_nextToken = m_tokenQue.front();
        }else
        {
            m_nextToken = "";
        }
        
        
        return res;
    }

    std::cout << "some error in function advance"<<std::endl;
    return std::string();
    
 }
