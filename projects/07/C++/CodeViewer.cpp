#include "CodeViewer.h"
#include <iostream>
#include <assert.h>

using namespace std;

int CodeViewer::m_labelId = 0;
int CodeViewer::m_labelNextId = 0;

CodeViewer::CodeViewer(/* args */)
{
}

CodeViewer::~CodeViewer()
{
}

void CodeViewer::setFileName(std::string fileName)
{
    this->m_filename = fileName;
}

std::string CodeViewer::writeArithmetic(const vector<string> &arithmeticCommandVec)
{
    if (arithmeticCommandVec[0] == "not" || arithmeticCommandVec[0] == "neg")
    {
        return monadicOperation(arithmeticCommandVec);
    }else if (arithmeticCommandVec[0] == "eq" || arithmeticCommandVec[0] == "lt" || arithmeticCommandVec[0] == "gt")
    {
        return compare(arithmeticCommandVec);
    }
    
    return binaryOperation(arithmeticCommandVec);
}

std::string CodeViewer::writePushPop(const vector<string> &accessCommandVec)
{
    int pushPopValue=atoi(accessCommandVec[2].c_str());;
    string pushFrom = "";
    if (accessCommandVec[0] == "push")
    {
        if( accessCommandVec[1] == "constant")
        {
            return "@"+accessCommandVec[2]+"\n" "D=A\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n";  
                    
        }else if (accessCommandVec[1] == "local")
        {
            pushFrom = "LCL";
            
        }else if (accessCommandVec[1] == "argument")
        {
            pushFrom = "ARG";
        }else if (accessCommandVec[1] == "this")
        {
            pushFrom = "THIS";
        }else if (accessCommandVec[1] == "that")
        {
            pushFrom = "THAT";
        }else if (accessCommandVec[1] == "temp")
        {
            pushFrom = "5";
            return "@"+pushFrom+"\n" "D=A\n" "@"+accessCommandVec[2]+"\n" "D=D+A\n A=D\n D=M\n"  "@SP\n A=M\n M=D\n " "@SP\n M=M+1\n";
        }else if (accessCommandVec[1] == "pointer")
        {
            pushFrom = "3";
            return "@"+pushFrom+"\n" "D=A\n" "@"+accessCommandVec[2]+"\n" "D=D+A\n A=D\n D=M\n"  "@SP\n A=M\n M=D\n " "@SP\n M=M+1\n";
        }else if (accessCommandVec[1]=="static")
        {
            pushFrom = m_filename+"."+ accessCommandVec[2];
        }
        
        return "@"+pushFrom+"\n" "D=M\n" "@"+accessCommandVec[2]+"\n" "D=D+A\n A=D\n D=M\n"  "@SP\n A=M\n M=D\n " "@SP\n M=M+1\n";
        
    }

        /**处理pop操作*/
        string localtion="";
        int pos = atoi(accessCommandVec[2].c_str());
        if (accessCommandVec[1] == "local")
        {
            localtion = "LCL";
            
        }else if (accessCommandVec[1] == "argument")
        {
            localtion = "ARG";
        }else if (accessCommandVec[1] == "this")
        {
            localtion = "THIS";

        }else if (accessCommandVec[1] == "that")
        {
            localtion = "THAT";

        }else if (accessCommandVec[1] == "temp")
        {
            localtion = "5";
            return "@SP\n AM=M-1\n D=M\n" "@13\n M=D\n" "@"+accessCommandVec[2]+"\n D=A\n" "@"+localtion+"\n D=D+A\n "
                    "@14\n M=D\n" "@13\n D=M\n" "@14\n A=M\n M=D\n" ;

        }else if (accessCommandVec[1] == "pointer")
        {
            localtion = "3";
            return "@SP\n AM=M-1\n D=M\n" "@13\n M=D\n" "@"+accessCommandVec[2]+"\n D=A\n" "@"+localtion+"\n D=D+A\n "
                    "@14\n M=D\n" "@13\n D=M\n" "@14\n A=M\n M=D\n" ;
        }else if(accessCommandVec[1]=="static")
        {
            localtion = m_filename+"."+ to_string(pos);
        }
        
        return "@SP\n AM=M-1\n D=M\n" "@13\n M=D\n" "@"+accessCommandVec[2]+"\n D=A\n" "@"+localtion+"\n D=D+M\n "
         "@14\n M=D\n" "@13\n D=M\n" "@14\n A=M\n M=D\n" ;        
}

std::string CodeViewer::init()
{
    string head = "@256\n"
                  "D=A\n"
                  "@SP\n"
                  "M = D\n";

    return head;
}

std::string CodeViewer::binaryOperation(const vector<string> &command)
{
    string differentPart = "";
    if (command[0] == "add")
    {
        differentPart = "D=M+D\n";
    }

    if (command[0] == "sub")
    {
        differentPart = "D=M-D\n";
    }

    if (command[0] == "and")
    {
        differentPart = "D=D&M\n";
    }

    if (command[0] == "or")
    {
        differentPart ="D=D|M\n";
    }
       
    return "@SP\n M=M-1\n A=M\n D=M\n"  "@SP\n M=M-1\n A=M\n"+differentPart+ "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n";
}

std::string CodeViewer::monadicOperation(const std::vector<std::string> &vec)
{

    if (vec[0] == "neg")
    {
        return "@SP\n M=M-1\n A=M\n D=-M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n" ;
    }else if (vec[0] == "not")
    {
        return "@SP\n M=M-1\n A=M\n D=!M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n" ;
    }
    
    cout<<"monadicOperation get wrong cal instruction:"<<vec[0];
    return "";
}

std::string CodeViewer::compare(const std::vector<std::string> &command)
{
    string label_true = "(label_true_" +to_string(m_labelId)+ ")\n" "@SP\n A=M\n M=-1\n" "@SP\n M=M+1\n";
    string label_next = "label_next_" +to_string(m_labelNextId);
    string label_true_name =  "label_true_" +to_string(m_labelId)+"\n";
    string differentPart = "";
    if (command[0] == "eq")
    {
        differentPart = "D;JEQ\n";
    }else if (command[0] == "lt")
    {
        differentPart = "D;JLT\n";

    }else if (command[0] == "gt"){
        differentPart = "D;JGT\n";

    }
    m_labelId++;
    m_labelNextId++;
    return "@SP\n M=M-1\n A=M\n D=M\n"  "@SP\n M=M-1\n A=M\n D=M-D\n" "@"+label_true_name+ differentPart+ "@SP\n A=M\n M=0\n"  "@SP\n M=M+1\n"
            "@"+label_next+"\n"+"0;JMP\n"+label_true+"("+label_next+")\n"; 
}


