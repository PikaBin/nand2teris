#include "CompilationEngine.h"
#include <iostream>
#include <set>

using namespace std;


CompilationEngine::CompilationEngine(JackTokenizer tokenizer,const string& outfilePath)
{
    m_tokenizer = tokenizer;
    m_outFilePath = outfilePath;
}

CompilationEngine::~CompilationEngine()
{
}

std::string CompilationEngine::processKeyword()
{
    KeywordType curType = m_tokenizer.keyWord();
    string res;
    switch (curType)
    {
    case CLASS:
        {
            res = "<class>\n"+ m_tokenizer.generateXmlstr();//<keyword>class</>
            curToken = m_tokenizer.advance(); //className
            // res += m_tokenizer.generateXmlstr();
            
        };
        break;
    case FIELD:
    case STATIC:
        {//类变量声明
            res = CompileClassVarDec();
            break;
        };
    case METHOD:
    case FUNCTION:
    case CONSTRUCTOR:
        {//类成员函数的声明
            res = CompileSubroutine();
            break;
        }
    default:
        {
            res = m_tokenizer.generateXmlstr();
            curToken = m_tokenizer.advance();
            break;    
        }
    }

    return res;
}

void CompilationEngine::CompileClass()
{
    ofstream outStream(m_outFilePath,ios_base::trunc);
    if (!outStream.is_open())
    {
        std::cout<<"the output file can't open: "<<m_outFilePath<<std::endl;
        return;
    }

    //不断从队列中取出token,并生成xml内容
    while (m_tokenizer.hasMoreToken())
    {
        // 第一次进入while时curToken为空
        if (curToken.empty())
        {
           curToken = m_tokenizer.advance(); 
        }
        
        string contents;
        switch (m_tokenizer.Type())
        {
        case KEYWORD:
            {
                contents = processKeyword();         
            }
            break;
        
        default:
        {
            contents = m_tokenizer.generateXmlstr();
            curToken = m_tokenizer.advance();
            break;     
        }
            
        }

        outStream.write(contents.c_str(),contents.length());

    } // end of while
    // outStream.write("}\n",2);
    string lastBrackt = m_tokenizer.xmlLine("symbol","}");
    outStream.write(lastBrackt.c_str(),lastBrackt.length());
    outStream.write("</class>",8);
    outStream.close();
}

std::string CompilationEngine::CompileClassVarDec()
{
    string contents = "<classVarDec>\n";
    if (curToken!="static" && curToken!="field")
    {
        std::cerr<< "syntax error in CompileClassVarDec"<<endl;
        return string();
    }
    
    contents += Process(curToken); // keyword static | field
    contents += Process(curToken); // var type like int,double
    while (m_tokenizer.Type()==IDENTIFIER || curToken==",")
    {
        contents += Process(curToken);
    }
    
    contents += Process(";");
    contents += "</classVarDec>\n";

    return contents;

}

std::string CompilationEngine::CompileSubroutine()
{
    string contents = "<subroutineDec>\n";
    contents += Process(curToken); // keyword：method,functuon,constructor
    contents += Process(curToken); // type:int boolean classname void
    contents += Process(curToken); // subroutine name
    contents += Process("(");
    contents += "<parameterList>\n";

    while (curToken != ")")
    {
        contents += Process(curToken);
    }

    contents += "</parameterList>\n";
    contents += Process(")");

    contents += CompileSubroutineBody();
    contents += " </subroutineDec>\n";
    return contents;
    
}

std::string CompilationEngine::CompileSubroutineBody()
{
    string routineBody = "<subroutineBody>\n";
    routineBody += Process("{");

    while (curToken != "}")
    {
        switch (m_tokenizer.keyWord())
        {
        case VAR:
            routineBody += CompileVarDec();
            break;
        
        default:
            routineBody += CompileStatements();
            //routineBody += "</statements>\n";
            break;
        }
    }
    
    routineBody += Process("}");
    routineBody += "</subroutineBody>\n";
    return routineBody;
}

std::string CompilationEngine::CompileVarDec()
{
    string contents = "<varDec>\n";
    contents += Process("var");
    contents += Process(curToken); // type like int boolean etc
    while (curToken!=";")
    {
        contents += Process(curToken);
    }
    
    contents += Process(";");
    contents += "</varDec>\n";
    
    return contents;
}

std::string CompilationEngine::CompileStatements()
{
    string contents = "<statements>\n";

    // 解析连续的 statment
    while (curToken != "}")
    { 
        switch (m_tokenizer.keyWord())
        {
        case IF:
            contents += CompileIfStatment();
            break;
        case DO:
            contents += CompileDoStatement();
            break;
        case WHILE:
            contents += CompileWhileStatement();
            break;
        case RETURN:
            contents += CompileReturnStatement();
            break;
        case LET:
            contents += CompileLetStatement();
            break;
        // case VAR:
        //     contents += CompileVarDec();
        //     break;
        default:
            std::cerr<< "parse error at function CompileStatements: "<<curToken<<endl;
            break;
        }

    }
    contents += "</statements>\n";
    return contents;
}

std::string CompilationEngine::CompileIfStatment()
{
    string ifcontent = "<ifStatement>\n";
    ifcontent += Process("if");
    ifcontent += Process("(");
    //ifcontent += Process(curToken); //expression less version
    ifcontent += CompileExpression();
    ifcontent += Process(")");
    ifcontent += Process("{");
    ifcontent += CompileStatements();
    //ifcontent += "</statements>\n";
    ifcontent += Process("}");
    
    if (m_tokenizer.keyWord() == ELSE)
    {
        ifcontent += Process("else");
        ifcontent += Process("{");
        ifcontent += CompileStatements();
        //ifcontent += "</statements>\n";
        ifcontent += Process("}");
    }
    
    ifcontent += "</ifStatement>\n";
    return ifcontent;
}

std::string CompilationEngine::CompileElseStatement()
{
    return std::string();
}

std::string CompilationEngine::CompileLetStatement()
{
    string letXml = "<letStatement>\n";
    letXml += Process(curToken); // keyword: let 
    letXml += Process(curToken); // varname
    if (curToken=="[")
    {
        letXml += Process("[");
        letXml += CompileExpression();
        letXml += Process("]");
    }
    
    letXml += Process("=");
    letXml += CompileExpression();
    letXml += Process(";");
    letXml += "</letStatement>\n";

    return letXml;
}

std::string CompilationEngine::CompileWhileStatement()
{
    string whileXml = "<whileStatement>\n";
    whileXml += Process("while"); // keyword
    whileXml += Process("(");
    whileXml += CompileExpression();
    whileXml += Process(")");
    whileXml += Process("{");
    whileXml += CompileStatements();
    //whileXml += "</statements>\n";
    whileXml += Process("}");
    whileXml += "</whileStatement>\n";

    return whileXml;
}

std::string CompilationEngine::CompileReturnStatement()
{
    string retXml = "<returnStatement>\n";
    retXml += Process(curToken); // keyword:return
    if (curToken != ";")
    {
        retXml+= CompileExpression();
    }
        
    retXml += Process(";"); // return 语句必定跟一个;
    retXml += "</returnStatement>\n";
    
    return retXml;
}

std::string CompilationEngine::CompileDoStatement()
{
    string doxmlContents = "<doStatement>\n";
    while (curToken != "(")
    {
        doxmlContents += Process(curToken);
    }

    doxmlContents += Process("(");
    doxmlContents += CompileExpressionList();
    doxmlContents += Process(")");
    doxmlContents += Process(";");
    doxmlContents += "</doStatement>\n";
    return doxmlContents;
}

std::string CompilationEngine::Process(const string &str)
{
    string processxml;
    if (str == curToken)
    {
        processxml = m_tokenizer.generateXmlstr();
        curToken = m_tokenizer.advance();
    }else
    {
        std::cerr<<"syntax error at process function: "<<curToken<<endl;
    }

    return processxml;
}

const std::set<char> opSet = {'+','-','*','/','<','>','=','&','|'};
const std::set<char> unaryOpset = {'-','~'};

std::string CompilationEngine::CompileTerm()
{
    
    string termXml;
    
    if (curToken!="," && curToken != ")" && curToken!= ";")
    {
        termXml = "<term>\n";
        
        if (!ispunct(curToken[0]) &&  m_tokenizer.getNextToken() =="[")
        { // let  a = b[i]; term ----> arrname[]
            termXml += Process(curToken); // arrName
            termXml += Process(curToken); // "["
            termXml += CompileExpression();
            termXml += Process(curToken); //  ']'
        }else if (!ispunct(curToken[0]) &&  m_tokenizer.getNextToken() =="(")
        {//subroutinue call:  subroutinueName(expressionList) 
            termXml += Process(curToken); //  subroutinueName
            termXml += Process("("); // "("
            termXml += CompileExpressionList();
            termXml += Process(")"); // ")"
            //termXml += Process(";");
            
        }else if (!ispunct(curToken[0]) &&  m_tokenizer.getNextToken() ==".")
        { // subroutinue call: className.subroutineName()
            termXml += Process(curToken); // className
            termXml += Process(".");
            termXml += Process(curToken); //  subroutinueName
            termXml += Process("("); // "("
            termXml += CompileExpressionList();
            termXml += Process(")"); // ")"
            //termXml += Process(";");
            
        }else if(curToken == "(" || curToken == "[")
        {// term = (expression) || [expression]

           termXml += Process(curToken); // '(' || '['
           termXml += CompileExpression();
           termXml += Process(curToken); // ')' || ']'
        }
        else if (unaryOpset.count(curToken[0]) && ispunct(m_tokenizer.getLastToken()[0]))
        { // (unaryop term)
            termXml += Process(curToken); // '-' | '~'
            termXml += CompileTerm();
        }
        else
        {
           string tmpRes = Process(curToken);
           if (tmpRes.empty())
           {
              return "";
           }else
           {
              termXml += tmpRes;
           }
           
        }

        termXml += "</term>\n";
        
    }
    
    return termXml;
}


std::string CompilationEngine::CompileExpression()
{
    string expressionXml = "<expression>\n";
    
    /**
     * , -> subroutinueName(expression,expression)
     * ; -> let x = y + 1;
     * ) -> subroutinueName(expression)
    */
    while (curToken!="," && curToken!= ";" && curToken!=")" &&curToken != "]")
    {

        expressionXml += CompileTerm();
        if (opSet.count(curToken[0]))
        {// (op term)*
           expressionXml +=  Process(curToken);
        }
    }
    
    
    expressionXml += "</expression>\n";
    return expressionXml;
}

std::string CompilationEngine::CompileExpressionList()
{
    string expressionListXml = "<expressionList>\n";
    while (curToken != ")")
    {
        expressionListXml += CompileExpression();
        if (curToken == ",")
        {
            expressionListXml += Process(",");
        }
   
    }

    expressionListXml += "</expressionList>\n";
    
    return expressionListXml;
}
