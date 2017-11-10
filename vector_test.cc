/**
 * Created by kylerky, adapted to cxx api by recolic.
 */

#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <functional>


#include "test_utils.hpp"
using rlib::println;

std::default_random_engine rand_eng(810);
std::uniform_real_distribution<double> distribution(0, 100);
double m_rand() {return distribution(rand_eng);}

void timed_func(std::function<void(void)> f, const std::string &info)
{
    println(info, "launched.");
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    println(info, "used", std::to_string((end-start).count()), 's');
}

void repeat(size_t count, std::function<void(void)> f)
{
    for(size_t cter = 0; cter < count; ++cter)
        f();
}

int main()
{
    Lab::vector<double> bufa;
    std::vector<double> bufb;

    auto co_push_back = [&]{
        auto val = m_rand();
        bufa.push_back(val);
        bufb.push_back(val);
    };

    auto co_pop_back = [&]{
        bufa.pop_back();
        bufb.pop_back();
    };

    auto co_erase = [&]{
        bufa.erase(bufa.begin() + 10);
        bufb.erase(bufb.begin() + 10);
    };

    auto co_clear = [&]{
        bufa.clear();
        bufb.clear();
    };

    auto co_shrink = [&]{
        bufa.shrink_to_fit();
        bufb.shrink_to_fit();
    };

    auto co_reserve = [&]{
        bufa.reserve(10000);
        bufb.reserve(10000);
    };

    #define TEST(count, operation, desc) VECTOR_ASSERT_EQUIVALENCE(bufa, bufb, std::bind(timed_func, \
                                            std::function<void(void)>(std::bind(repeat, count, operation)), desc))
    //VECTOR_ASSERT_EQUIVALENCE(bufa, bufb, timed_func(std::bind(repeat, 1000000, co_push_back), "randomPush"));
    //VECTOR_ASSERT_EQUIVALENCE(bufa, bufb, timed_func(std::bind(repeat, 2333, co_push_back), "randomPush2"));
    TEST(1000, co_push_back, "push1");
    TEST(1000000, co_push_back, "push2");
    TEST(9999, co_pop_back, "pop1");
    TEST(5432, co_push_back, "push3");
    TEST(123, co_pop_back, "pop2");
    TEST(777, co_erase, "erase1");
    TEST(66, co_push_back, "push4");
    TEST(543, co_erase, "erase2");
    TEST(2, co_clear, "clear1");
    TEST(3456, co_push_back, "push5");
    TEST(2, co_shrink, "shrink1");
    TEST(233, co_push_back, "push6");
    TEST(2, co_reserve, "reserve1");
    TEST(666, co_push_back, "push7");
    TEST(2, co_shrink, "shrink2");
    return 0;
}