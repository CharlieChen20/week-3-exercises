#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map> 
#include <algorithm> 
#include <stdexcept>

using std::vector;
using std::map;
using std::string;

//首先带来wrong版本
// class Automaton
// {
//     public: 
//     Automaton(map<char, int> A, vector<vector<int>> M, vector<int> S_A) : alphabet(A), transition_matrix(M), accepting_states(S_A){}

//     bool Read(string word)
//     {
//         for (auto &c : word)
//         {
//             /* code */
//             int j = alphabet.find(c)->second; // second是返回迭代器指向的键值对的值，first则是键
//             state = transition_matrix[state][j]; // 表示第state行第j列
//         }
//         return std::find(accepting_states.begin(), accepting_states.end(), state); // !起始迭代器，结束迭代器，要查找的值。
//         // !如果没找到，返回accepting_states.end(),指向容器最后一个元素之后的位置
        
//     }


//     private:
//     int state = 0;
//     map<char, int> alphabet;
//     // We can use a vector of vectors as a 2D array or matrix
//     vector<vector<int>> transition_matrix;
//     vector<int> accepting_states;
// };
//! 补一枪函数的声明。
std::string strip(const map<char, unsigned int>& A, std::string s);
//接下来开始修改后的版本
//1. 为什么都使用unsigned int?
class Automaton
{
    public:
    Automaton(const vector<char> &A, const vector<vector<unsigned int>> &M, const vector<unsigned int> &S) : transition_matrix(M), 
    accepting_states(S), alphabet(setup_alphabet(A))
    {
        // Check matrix form and content
        unsigned int num_states = transition_matrix.size(); // transition_matrix是M, vector<vector>, 这里返回的应该是里面有多少个
        for (auto &row : transition_matrix)
        {
            /* code */
            if (row.size() != A.size())
            {
                /* code */
                throw std::logic_error("Each row in transition matrix must have one entry per character.");
            }
            for(auto &element : row)
            {
                if (element >= num_states) // 这个判断表示，状态转移矩阵中的元素指向了不存在的状态，例如一共只有4个状态，但指向了5。
                {
                    /* code */
                    throw std::logic_error("Element found in transition matrix pointing to non existent state.");
                }
                
            }
            
        }
        // Check accepting states
        for (auto s:accepting_states)
        {
            if (s >= num_states)
            {
                /* code */
                throw std::logic_error("Invalid accepting state found.");
            }
        }
        if (accepting_states.size() > num_states) 
        {
            /* code */
            throw std::logic_error("Size of accepting state vector should be less than or equal to the number of states.");
        }   
    }

    static map<char, unsigned int> setup_alphabet(const vector<char> &A)
    {
        // Setup alphabet map
        map<char, unsigned  int> temp_alphabet;
        for (unsigned int i = 0; i < A.size(); i++)
        {
            /* code */
            temp_alphabet[A[i]] = i; //将A种的字符映射到它的索引i
        }
        return temp_alphabet;
        
    }
    
    bool Read(string word)
    {
        for(auto &c : word)
        {
            auto it = alphabet.find(c);
            if (it == alphabet.end())
            {
                /* code */
                throw std::domain_error("Invalid character found in input string. You can try: " + strip(alphabet,word));
            }
            unsigned int j = it->second; // 对应到值，例如字母"a"可能映射到index 0
            state = transition_matrix[state][j];
        }
        bool accept = std::find(accepting_states.begin(),accepting_states.end(), state) != accepting_states.end();
        state = 0;
        return accept;
    }

    private:
    unsigned int state = 0;
    const map<char, unsigned int> alphabet;
    const vector<vector<unsigned int>> transition_matrix;
    const vector<unsigned int> accepting_states;
};

    
    

