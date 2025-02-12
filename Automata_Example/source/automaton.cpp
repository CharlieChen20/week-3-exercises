#include "automaton.h"
#include <string>

using std::vector;
using std::map;
using std::string;

std::string strip(const map<char, unsigned int> &A, std::string s)
{
    auto new_end = std::remove_if(s.begin(),s.end(), [&A](char a){return A.find(a) == A.end();});
    //! remove_if不直接删除元素，而是把需要删除的元素移动到末尾。
    s.erase(new_end, s.end()); //! 两个参数代表开始删除的位置和删除到此位置（不包括）
    return s;
}

int main()
{
    vector<vector<unsigned int>> M{{0,1},{0,1}};
    vector<char> A{'a', 'b'};
    vector<unsigned int> S{1}; //这里表示，接受状态为1
    Automaton ends_with_one(A, M, S);

    std::cout <<"Enter a string of characters from the alphabet {a,b}:" << std::endl;
    std::string s;
    std::cin >> s; //! 表示键盘的输入赋值给s
    try
    {
        /* code */
        std::cout << "Accepted?" << ends_with_one.Read(s) << std::endl; //! recall, Automaton类的read方法会返回一个bool表示接受与否。

    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl; // what是返回异常的说明。
    }
    catch(...)
    {
        std::cout << "Unanticipated exception!" << std::endl;
    }
    
    return 0;

}