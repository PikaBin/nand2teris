#if !defined(CODEVIWER_H)
#define CODEVIWER_H

/**
 * @date 2023-5-14
*/
#include <string>
#include <stack>
#include <vector>

class CodeViewer
{
private:
    /* data */
public:
    CodeViewer(/* args */);
    ~CodeViewer();

    void setFileName(std::string fileName);
    std::string writeArithmetic(const std::vector<std::string> &vec);
    std::string writePushPop(const std::vector<std::string> &vec);

    std::string init();
    std::string writeLabel(const std::string& label);
    std::string writeGoto(const std::string& label );
    std::string writeIf(const std::string& label);
    std::string writeFunction(const std::string& functionName,int numLocals);
    std::string writeCall(const std::string& label,int numArgs);
    std::string writeReturn();
    
private:
    std::string binaryOperation(const std::vector<std::string>& vec);
    std::string monadicOperation(const std::vector<std::string>& vec);
    std::string compare(const std::vector<std::string>& vec);
    std::string m_filename;
    std::string m_functionName;
    static int m_labelId; //区分因为比较运算符产生的label
    static int m_labelNextId; //label next id
    
};




#endif // CODEVIWER_H
