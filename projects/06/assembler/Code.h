#if !defined(CODE_H)
#define CODE_H

#include <string>
#include <map>
/**
 * @date 2023-4-16
 * @brief 将对应域翻译成二进制码
*/
class Code
{
private:
    std::map<std::string,std::string> m_destMap;
    std::map<std::string,std::string> m_jumpMap;
    std::map<std::string,std::string> m_compMap;
    
public:
    Code(/* args */);
    ~Code();
    std::string dest(std::string mnemonic_dest);
    std::string jump(std::string mnemonic_jump);
    std::string comp(std::string mnemonic_comp);
};





#endif // CODE_H
