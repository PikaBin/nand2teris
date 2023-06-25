#if !defined(PARSER_H)
#define PARSER_H

/**
 * @date 2023-4-30
*/
#include <string>
#include <set>
#include <vector>
#include <stack>
#include "./CodeViewer.h"

enum VMCommandType
{
    C_ARITHMETTIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL

};

class Parser
{
    
public:
    Parser(/* args */);
    Parser(std::string filename);
    ~Parser();

void VMsplit();
VMCommandType commandType();
std::string arg1();
std::string args2();
std::string parse();
void setCurComand(std::string command);
std::string writeHead();
void setFile(std::string filename);

private:
    std::string m_curComand;//当前vm命令
    std::vector<std::string> m_splitedCommandVec;//当前vm命令根据空格split的对应
    static std::set<std::string> arithmeticCommand;
    std::stack<int> m_stack;//模拟堆栈
    CodeViewer m_codeViewr;
};






#endif // PARSER_H
