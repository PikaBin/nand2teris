#ifndef JACKANALYZER_H
#define JACKANALYZER_H

/**
 * @brief 建立和调用其他模块的顶层驱动模块
 * @details 获取命令行参数，得到jack文件路径，并调用
 * 
*/
#include <string>
#include <memory>
#include <fstream>
#include "CompilationEngine.h"
#include "JackTokenizer.h"

class JackAnalyzer
{
private:
    /* data */
public:
    JackAnalyzer(const std::string& sourceFilePath);
    ~JackAnalyzer();

    /**
     * @brief 获取Jack文件路径，调用相关模块，输出xml
    */
    void parse();
private:
    std::string OutFileName();
private:
    std::string source;
    //std::unique_ptr<JackTokenizer> pTokenizer;
    //std::unique_ptr<CompilationEngine> pComplieEngine;
};




#endif