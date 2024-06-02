#ifndef JACKTOKENIZER_H
#define JACKTOKENIZER_H

#include <string>
#include <queue>
#include <map>

enum TokenType{
    KEYWORD = 0,
    SYMBOL,
    IDENTIFIER,
    INT_CONST,
    STRING_CONST
};

enum KeywordType{
    CLASS=0,
    METHOD,
    FUNCTION,
    CONSTRUCTOR,
    INT,
    BOOLEAN,
    CHAR,
    VOID,
    VAR,
    STATIC,
    FIELD,
    LET,
    DO,
    IF,
    ELSE,
    WHILE,
    RETURN,
    TRUE,
    FALSE,
    NULLSTR,
    THIS
};

const std::map<std::string,KeywordType> KEYWORD_REFLECTION = 
{
    {"class",KeywordType::CLASS},
    {"method",KeywordType::METHOD},
    {"function",KeywordType::FUNCTION},
    {"constructor",KeywordType::CONSTRUCTOR},
    {"int",KeywordType::INT},
    {"boolean",KeywordType::BOOLEAN},
    {"char",KeywordType::CHAR},
    {"void",KeywordType::VOID},
    {"var",KeywordType::VAR},
    {"static",KeywordType::STATIC},
    {"field",KeywordType::FIELD},
    {"let",KeywordType::LET},
    {"do",KeywordType::DO},
    {"if",KeywordType::IF},
    {"else",KeywordType::ELSE},
    {"while",KeywordType::WHILE},
    {"return",KeywordType::RETURN},
    {"true",KeywordType::TRUE},
    {"false",KeywordType::FALSE},
    {"null",KeywordType::NULLSTR},
    {"this",KeywordType::THIS}
};

/**
 * @brief 字元转换器模块
*/
class JackTokenizer
{

public:
    JackTokenizer(/* args */);
    ~JackTokenizer();

    /**
     * @brief 将m_curToken转为对应的xml格式
    */
    std::string generateXmlstr();

    std::string xmlLine(std::string type,std::string contents);
    /**
     * @brief 返回去除双引号的string-const
    */
    std::string stringVal();

    /**
     * @brief 返回m_currtoken的所属类型
    */
   TokenType Type();

    /**
     * @brief 返回m_currtoken的具体类型
    */
   KeywordType keyWord()
   {
        return KEYWORD_REFLECTION.at(m_curToken);
   }
   /**
    * @brief 设置当前token值
   */
  void SetCurToken(const std::string &tokenValue){m_curToken = tokenValue;}

  /**
   * @brief 是否还存在待解析的token
  */
  bool hasMoreToken()
  {
    return !m_tokenQue.empty();
  }

  /**
   * @brief 读取下一个token（hasMoreToken为true）
  */
 std::string advance();

    /**
     * @brief 获取下下一个token
    */
 std::string getNextToken(){return  m_nextToken;}

 /**
  * @brief 获取上一个token
 */
 std::string getLastToken(){return m_lastToken;}

public:
    std::queue<std::string> m_tokenQue; // 存储token

private:
    std::string m_lastToken; // 上一个token
    std::string m_curToken; // 当前token
    std::string m_nextToken; // 下一个token
    bool m_firstQuote; // 是否为""中的第一个",目前仅用来判断string const类型
    bool m_secondQuote; // 是否为""中的第二个",目前仅用来判断string const类型
    std::string m_constStrValue;
    
};




#endif