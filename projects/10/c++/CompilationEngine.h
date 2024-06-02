#ifndef COMPILATIONENGINE_H
#define COMPILATIONENGINE_H

/**
 * @brief 自顶向下的递归语法分析器
*/
#include <string>
#include "JackTokenizer.h"
#include <fstream>

class CompilationEngine
{

public:
    CompilationEngine(JackTokenizer tokenizer,const std::string& outfilePath);
    ~CompilationEngine();

    /**
     * @brief token type 为keyword时的处理函数
     * @return 生成的xml内容
    */
    std::string processKeyword();

    void CompileClass();

    /**
     * @brief compile a static var declaration or a field
     * @return xml contents
    */
    std::string CompileClassVarDec();

    /**
     * @brief compile function,method or constructor
    */
   std::string CompileSubroutine();

   /**
    * @brief compile subroutine body
   */
   std::string CompileSubroutineBody();

    /**
     * @brief compile var
     * @return related xml contents
    */
   std::string CompileVarDec();

    /**
     * @brief compile a sequence of statements
     * @return related xml contents
    */
   std::string CompileStatements();

   /**
    * @brief compile a if statement
    * @return related xml contents
   */
    std::string CompileIfStatment();

   /**
    * @brief compile a else statement
    * @return related xml contents
   */
    std::string CompileElseStatement();


   /**
    * @brief compile a let statement
    * @return related xml contents
   */
    std::string CompileLetStatement();


   /**
    * @brief compile a while statement
    * @return related xml contents
   */
    std::string CompileWhileStatement();


   /**
    * @brief compile a return statement
    * @return related xml contents
   */
    std::string CompileReturnStatement();

   /**
    * @brief compile a do statement
    * @return related xml contents
   */
    std::string CompileDoStatement();


    /**
     * @brief helper routine:gengerate xml and advance next token
    */
   std::string Process(const std::string & str);

   /**
    * @brief compile a term
   */
  std::string CompileTerm();

  /**
   * @brief compile a expression
  */
  std::string CompileExpression();

  /**
   * @brief compile a expressionlist
  */
  std::string CompileExpressionList();

private:
    JackTokenizer m_tokenizer;
    std::string curToken;
    std::string m_outFilePath;
};



#endif