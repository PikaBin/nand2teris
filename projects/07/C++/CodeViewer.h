#if !defined(CODEVIWER_H)
#define CODEVIWER_H

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

    
private:
    std::string binaryOperation(const std::vector<std::string>& vec);
    std::string monadicOperation(const std::vector<std::string>& vec);
    std::string compare(const std::vector<std::string>& vec);
    std::string m_filename;
    static int m_labelId; //区分因为比较运算符产生的label
    static int m_labelNextId; //label next id
};




#endif // CODEVIWER_H
