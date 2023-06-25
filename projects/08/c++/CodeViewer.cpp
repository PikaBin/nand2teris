#include "CodeViewer.h"
#include <iostream>
#include <assert.h>


/**
 * @date 5.14 需要重新设计，运行BasicLoop发现，push arg 0 中的arg[0]是会在汇编
 * 程序中变化的，而此时仍然@原有的arg[0],因为生成的语句是定死的，而不是一个变量。
 * @date 5.28 完成了program flow部分并验证通过
*/
using namespace std;

int CodeViewer::m_labelId = 0;
int CodeViewer::m_labelNextId = 0;

CodeViewer::CodeViewer(/* args */)
{
    m_functionName = "null";
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
    string initSP = "@256\n"
                  "D=A\n"
                  "@SP\n"
                  "M = D\n";

    //translate call Sys.init 0            
    std::string return_adress ="Sys.init" "_returnAdress_";
    string CallSysinit = "@"+return_adress+"\n" "D=A\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@LCL\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@ARG\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@THIS\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@THAT\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@SP\n" "D=M\n" "@LCL\n" "M=D\n"
                    "@5\n D=D-A\n" "@ARG\n" "M=D\n"
                    "@Sys.init\n" "0;JMP\n"
                    "("+return_adress+")\n";
    return initSP+CallSysinit;
}

std::string CodeViewer::writeLabel(const std::string& label)
{

    return "(" +m_functionName+"$"+label+ ")\n";
}

std::string CodeViewer::writeGoto(const std::string &label)
{
    
    return "@"+m_functionName+"$"+label+"\n"
          +"0;JMP\n";
}

std::string CodeViewer::writeIf(const std::string &label)
{
    
    return "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "@"+m_functionName+"$"+label+"\n"
            + "D;JNE \n";
}

std::string CodeViewer::writeFunction(const std::string& functionName,int numLocals)
{
    m_functionName = functionName;
    if (functionName.empty())
    {
        std::cout<<"获取function name 出错"<<endl;
        return "";
    }
    if (numLocals<=0)
    {
        return "("+functionName+")\n";
    }
    // 难道一定要初始化吗？
    std::string push0LabelName = functionName+"push0"; 
    std::string push0Label = "("+functionName+"push0)\n";
    return "("+functionName+")\n"+
            "@"+to_string(numLocals)+"\n"+"D=A\n"+"@i\n M=D\n "+"@loc\n M=0\n"
            +push0Label+
            "@0\n" "D=A\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n" // push 0
            "@SP\n A=M-1\n D=M\n" "@13\n M=D\n" "@loc\n D=M\n" "@LCL\n" "D=D+M\n" 
            "@14\n M=D\n" "@13\n D=M\n" "@14\n A=M\n M=D\n" //pop local
            "@loc\n M=M+1\n" 
            "@i\n MD=M-1\n"+
            "@"+push0LabelName+"\n"+"D;JGT\n";
    /**
     * (fun)
     * @k
     * D=K
     * @i
     * M = D
     * @loc
     * M=0
     * (LOOP)
     * PUSH 0
     * pop local loc
     * @loc
     * M=M+1
     * @i
     * M=M-1
     * D=M
     * @loop
     * D;JGT
     * 
    */
}

//调用时，通过numArgs可以计算出当前函数的arg base在哪
//返回地址的标签命名没有考虑到递归函数类型，如果出现递归，则会出现不同层次的调用栈而返回地址相同的问题
//通过加上一个id值（m_functionId）来解决
std::string CodeViewer::writeCall(const std::string &functionName, int numArgs)
{
    static int m_functionId=0; //区分同名函数的不同层次递归调用
    std::string return_adress =functionName+"_returnAdress_"+to_string(m_functionId);
    string retStr = "@"+return_adress+"\n" "D=A\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@LCL\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@ARG\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@THIS\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@THAT\n" "D=M\n" "@SP\n A=M\n M=D\n" "@SP\n M=M+1\n"
                    "@SP\n" "D=M\n" "@LCL\n" "M=D\n"
                    "@5\n D=D-A\n" "@"+to_string(numArgs)+"\n" "D=D-A\n" "@ARG\n" "M=D\n"
                    "@"+functionName+"\n" "0;JMP\n"
                    "("+return_adress+")\n";
    m_functionId++;
    return retStr;
}


//出现问题与writeCall相同，解决方法也相同
std::string CodeViewer::writeReturn()
{
    static int retId = 0;
    static int frameId = 0;
    frameId++;
    retId++;  
    return "@LCL\n D=M\n" "@FRAME"+to_string(frameId)+"\n" " M=D\n" "@5\n D=D-A\n A=D\n D=M\n" "@ret"+to_string(retId)+ "\n M=D\n"  //?
           "@SP\n AM=M-1\n D=M\n" "@13\n M=D\n" "@0\n D=A\n" "@ARG\n D=D+M\n "
           "@14\n M=D\n" "@13\n D=M\n" "@14\n A=M\n M=D\n"
           "@ARG\n D=M\n" "@SP\n M=D+1\n"
           "@FRAME"+to_string(frameId)+"\n" " A=M-1\n D=M\n" "@THAT\n M=D\n"
           "@FRAME"+to_string(frameId)+"\n" " D=M\n @2\n D=D-A\n A=D\n D=M\n" "@THIS\n M=D\n"          
           "@FRAME"+to_string(frameId)+"\n" " D=M\n @3\n D=D-A\n A=D\n D=M\n" "@ARG\n M=D\n" 
           "@FRAME"+to_string(frameId)+"\n" " D=M\n @4\n D=D-A\n A=D\n D=M\n" "@LCL\n M=D\n" 
           "@ret"+to_string(retId)+  "\n A=M\n 0;JMP\n";  //这里返回地址时，应该要返回指针指向的值，而不是指针本身        

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
