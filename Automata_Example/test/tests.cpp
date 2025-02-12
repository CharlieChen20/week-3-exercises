#include <catch2/catch_test_macros.hpp>
#include "automaton.h"
#include <vector>
#include <map>
#include <memory>

using std::vector;
using std::map;

TEST_CASE("Check that a simple automaton accepts", "[simple accept]")
{
    vector<vector<unsigned int>> M{{0,1}, {0,1}};
    vector<uint> S_A{0}; // accept state
    vector<char> A{'a','b'};
    Automaton only_As(A, M, S_A);

    REQUIRE_THROWS(only_As.Read("abbca")); //检查是否抛出异常
}

TEST_CASE("Check matrix formatting", "[exceptions]") //! 第一个string是测试用例的名字； 第二个string是标签。
//! 有几个状态转移矩阵就有几行;
{
    vector<vector<uint>> M_long_row{{0,1,1}, {1,1}};
    vector<vector<uint>> M_short_row{{0,1}, {1}};
    vector<vector<uint>> M_invalid_transition{{0,2}, {1,1}};
    vector<vector<uint>> M_correct{{0,1},{1,1}};

    vector<uint> S_A{0};
    vector<char> A{'a', 'b'};
    std::unique_ptr<Automaton> only_As; //! 这里之所以用指针，是因为如果在构造过程中抛出异常，忘记释放内存，程序会出现泄露。
    REQUIRE_NOTHROW(only_As = std::make_unique<Automaton>(A, M_correct, S_A));
    REQUIRE_THROWS(only_As = std::make_unique<Automaton>(A, M_long_row, S_A));
    REQUIRE_THROWS(only_As = std::make_unique<Automaton>(A, M_short_row, S_A));
    REQUIRE_THROWS(only_As = std::make_unique<Automaton>(A, M_invalid_transition, S_A));
}

TEST_CASE("Test accept states", "[exceptions]")
{
    vector<vector<uint>> M_2states{{0,1}, {1,1}};
    vector<vector<uint>> M_3states{{2,1}, {0,2},{1,0}}; 

    vector<char> A{'a', 'b'};
    std::unique_ptr<Automaton> automaton;
    REQUIRE_NOTHROW(automaton = std::make_unique<Automaton>(A, M_2states, std::vector<uint> {0} )); //! 这里{0}是向量， 如果写0则是int，参数不匹配。
    REQUIRE_NOTHROW(automaton = std::make_unique<Automaton>(A, M_2states, std::vector<uint>{1}));
    REQUIRE_NOTHROW(automaton = std::make_unique<Automaton>(A, M_2states, std::vector<uint>{0, 1}));
    REQUIRE_NOTHROW(automaton = std::make_unique<Automaton>(A, M_3states, std::vector<uint>{0}));
    REQUIRE_NOTHROW(automaton = std::make_unique<Automaton>(A, M_3states, std::vector<uint>{1}));
    REQUIRE_NOTHROW(automaton = std::make_unique<Automaton>(A, M_3states, std::vector<uint>{2}));
    REQUIRE_NOTHROW(automaton = std::make_unique<Automaton>(A, M_3states, std::vector<uint>{0,1,2}));

    // 下面四行代码会报错，因为M_2states只有0，1两个状态，但接收状态出现了2，3。
    REQUIRE_THROWS(automaton = std::make_unique<Automaton>(A, M_2states, std::vector<uint>{2}));
    REQUIRE_THROWS(automaton = std::make_unique<Automaton>(A, M_2states, std::vector<uint>{0,1,3}));
    REQUIRE_THROWS(automaton = std::make_unique<Automaton>(A, M_2states, std::vector<uint>{3}));
    REQUIRE_THROWS(automaton = std::make_unique<Automaton>(A, M_2states, std::vector<uint>{0,4,2}));
}

TEST_CASE("Test strip function", "[strip]")
{
    map<char, uint> A{{'a', 0}, {'b', 1}}; // 构建字母表
    string s1 = "aaaa";
    string s2 = "abbaab";
    string s3 = "aeabcab";
    string s4 = "cchdefj";

    REQUIRE(strip(A,s1) == s1);
    REQUIRE(strip(A,s2) == s2);
    REQUIRE(strip(A,s3) == "aabab");
    REQUIRE(strip(A,s4).empty());
    REQUIRE(strip(A,"").empty());
}

TEST_CASE("Multiple Sequential Reads", "[multi-read]")
{
    // Define automaton that accepts strings with odd number of 'b's
    vector<char> A{'a','b'};
    vector<vector<uint>> M{{0,1}, {0,1}};
    vector<uint> S{1};
    Automaton odd_num_b(A,M,S);

    // This is successful so final state is 1
    REQUIRE(odd_num_b.Read("ababab")); // ababab会返回1,接收状态是1，所以结果为True，符合require
    REQUIRE(odd_num_b.Read("bbb")); // bbb也会返回1，true。

}

// 如何测试？ 
//! 重要，首先在顶级cmakelist中，添加了第14行，否则cmake无法找到catch2.
// 然后cd到automata_example/build, 运行cmake ..
// ! 由于顶级cmakelist中有这一行：set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
// ! 所以我们的可执行文件在build/bin文件夹下。
// 执行： ./bin/Automata 或者 TestAutomata