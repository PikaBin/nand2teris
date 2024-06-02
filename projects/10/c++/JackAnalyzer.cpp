
#include "JackAnalyzer.h"
#include "CompilationEngine.h"
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

bool isOperatorOrParen(char c)
{
    
    return std::ispunct(c);
}

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

// compile command line: g++ .\c++\JackTokenizer.cpp .\c++\JackAnalyzer.cpp -o analyzer
JackAnalyzer::JackAnalyzer(const std::string &sourceFilePath)
{
    // pTokenizer =  std::make_unique<JackTokenizer>(sourceFilePath);
    source = sourceFilePath;
}

JackAnalyzer::~JackAnalyzer()
{
}

void JackAnalyzer::parse()
{
    ifstream inputStream(source, std::ios_base::in);
    
    string outFile = OutFileName();
    // ofstream outputStream(outFile, ios_base::trunc);

    if (!inputStream.is_open())
    {
        std::cerr << "the input file can't open,file: " << source<<endl;
        return;
    }

    // if (!outputStream.is_open())
    // {
    //     std::cerr<<"the output file can't open: "<<outFile<<std::endl;
    // }

    //outputStream.write("<tokens>\n",9);
    

    JackTokenizer tokenizer;
    std::string elememt;
    while (inputStream >> elememt)
    {
        // 去除注释
        if (elememt == "//")
        {                                       // line comment
            inputStream.ignore(max_size, '\n'); // skip comment input
        }
        else if (elememt == "/*" || elememt == "/**")
        { // block comment
            //inputStream.ignore(max_size, '/'); //当comment中存在/字符时就会误判
            while (inputStream>>elememt)
            {
                if (elememt =="*/")
                {
                    break;
                }
                
            }
            
        }
        else
        {
            // 可能会出现 square.moveRight(); 这种identifer + symbol 的字符串，所以要处理
            // 处理思路：缓存identifer值直到遇到symbol类型的char时，先把之前的缓存推入vector并清空缓存，
            //然后将symbol char 单独 推入vector；
            std::vector<std::string> tokens;
            std::string currentToken;
            for (char c : elememt)
            {
                if (isOperatorOrParen(c))
                {
                    if (!currentToken.empty())
                    {//将之前的identifer存入队列
                        tokens.push_back(currentToken);
                        currentToken.clear();
                    }
                    tokens.push_back(std::string(1, c));
                }
                // else if(c == '"')
                // {//处理 string-const
                //     currentToken += elememt;
                //     while (inputStream>>elememt)
                //     {
                //         if (elememt.find("\"")!= string::npos)
                //         {
                //             currentToken += " ";
                //             currentToken += elememt;
                //             break;
                //         }else{
                //             currentToken += " ";
                //             currentToken += elememt;
                //         }
                        
                //     }
                //     break; //get out loop for       
                // }
                else
                {
                    currentToken  += c;
                }
                
            }
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
            }

            for (const std::string &token : tokens)
            {
                //std::cout<<token<<endl;
                // tokenizer.SetCurToken(token);
                // string contents= tokenizer.generateXmlstr();
                // outputStream.write(contents.c_str(),contents.length());
                tokenizer.m_tokenQue.push(token);
            }
        }
    }

    //编译整个类
    CompilationEngine cEngine(tokenizer,outFile);
    cEngine.CompileClass();

    // 关闭读取文件流
    inputStream.close();
    // outputStream.close();
}
std::string JackAnalyzer::OutFileName()
{
    string fileName;
    if (!source.empty())
    {
        int pos1 = source.find_last_of("\\");
        int pos2 = source.find_last_of(".");
        fileName = source.substr(pos1+1,pos2 - pos1);
        string folder = source.substr(0,pos1+1);
        fileName = folder+"T_"+fileName+"xml";
    }
    
    return fileName;
}
/**
 * @brief 建立并调用其他模块的顶层驱动模块
 */
int main(int args, char *argv[])
{
    std::string dirPath = argv[1];
    JackAnalyzer analyzer_first(dirPath);

    analyzer_first.parse();

    return 0;
}