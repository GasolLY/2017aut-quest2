/**
 * Created by kylerky, adapted to cxx api by recolic.
 */

#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "test_utils.hpp"


std::default_random_engine rand_eng(810);
std::uniform_real_distribution<double> distribution(0, 100);
double rand() {return distribution(rand_eng);}

void timed_func(std::function<void()> f, const std::string &info = "")
{
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << info << std::to_string((end - start).count()) << 's' << std::endl;
}

template<typename... args_t, Callable func_t>
auto repeat(size_t count, func_t f, args_t... args)
{
    for(size_t cter = 0; cter < count; ++cter)
    {
        if(cter + 1 == count) return f(args ...);
        f(args ...);
    }
    return nullptr;
}

int main()
{
    auto a_randomed_push_back = [](auto bufa, auto bufb, size_t count){
        auto val = rand();
        bufa.push_back(val);
        bufb.push_back(val);
    };

    auto a_pop_back = [](auto bufa, auto bufb, size_t count){
        bufa.pop_back();
        bufb.pop_back();
    }





}


TEST(randomPush, timing) {
    // initializations
    const unsigned elem_cnt = 1000000;
    // generate the elements to be pushed
    std::array<double, elem_cnt> elems;
    for (auto i = 0; i != elem_cnt; ++i) {
        elems[i] = distribution(rand_eng);
    }

    // loads of pushing & timing
    std::vector<std::pair<unsigned, double>> data_points;
    for (unsigned count = 100; count <= elem_cnt; count *= 10) {
        auto m_vec = Lab::vector();
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i != count; ++i) {
            m_vec.push_back(elems[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        data_points.push_back(std::make_pair(count, diff.count()));
    }
    // for (unsigned count = 100; count <= elem_cnt; count *= 10) {
    //     std::vector<double> vec;
    //     auto start = std::chrono::high_resolution_clock::now();
    //     for (unsigned i = 0; i != count; ++i) {
    //         vec.push_back(elems[i]);
    //     }
    //     auto end = std::chrono::high_resolution_clock::now();
    //     std::chrono::duration<double> diff = end - start;
    //     data_points.push_back(std::make_pair(count, diff.count()));
    // }

    // print the result
    std::cout << "N\tduration" << std::endl;
    for (auto data : data_points)
        std::cout << data.first << "\t" << data.second << std::endl;
}

void random_push(Lab::vector &m_vec, std::vector<double> &std_vec,
                 size_t count);

#define TRAVERSE_CHECK() do {    /* validation*/\
    /* size */\
    ASSERT_EQ(m_vec.size(), std_vec.size()) << "wrong size";\
    /* get the iterators */\
    auto curr = m_vec.begin();\
    auto end = m_vec.end();\
    for (const auto &elem : std_vec) {\
        ASSERT_DOUBLE_EQ(*curr, elem) << "found unmatched element";\
        ++curr;\
    }\
    ASSERT_EQ(curr, end) << "end iterator not functioning";\
} while(0)

TEST_F(VectorTest, iterator) {
    // constructions
    std::vector<double> std_vec;

    // random push
    random_push(m_vec, std_vec, 2333);

    TRAVERSE_CHECK();
}

TEST_F(VectorTest, randomPop) {
    // constructions
    std::vector<double> std_vec;

    // random push
    random_push(m_vec, std_vec, 233);
    m_vec.pop_back();
    std_vec.pop_back();

    random_push(m_vec, std_vec, 132);
    for (unsigned i = 0; i != 10; ++i) {
        m_vec.pop_back();
        std_vec.pop_back();
    }

    random_push(m_vec, std_vec, 112);
    for (unsigned i = 0; i != 20; ++i) {
        m_vec.pop_back();
        std_vec.pop_back();
    }

    TRAVERSE_CHECK();
}

TEST_F(VectorTest, randomErase) {
    // constructions
    std::vector<double> std_vec;

    // random push
    random_push(m_vec, std_vec, 233);
    auto iter = vector.begin(&m_vec);
    vector.erase(&m_vec, iter);
    std_vec.erase(std_vec.begin());

    random_push(m_vec, std_vec, 233);
    iter = vector.begin(&m_vec);
    iter = vector.iter_move(iter, 10);
    vector.erase(&m_vec, iter);
    std_vec.erase(std_vec.begin()+10);


    random_push(m_vec, std_vec, 233);
    for (unsigned i = 0; i != 23; ++i) {
        iter = vector.begin(&m_vec);
        iter = vector.iter_move(iter, 5);
        vector.erase(&m_vec, iter);
        std_vec.erase(std_vec.begin()+5);
    }

    TRAVERSE_CHECK();
}

TEST_F(VectorTest, clear) {
    std::default_random_engine rand_eng(810);
    std::uniform_real_distribution<double> distribution(0, 100);
    for (unsigned i = 0; i != 1000; ++i) {
        for (unsigned j = 0; j != 20000; ++j) {
            double real = distribution(rand_eng);
            vector.push_back(&m_vec, &real, sizeof(double));
        }
        vector.clear(&m_vec);
    }

    std::vector<double> std_vec;
    random_push(m_vec, std_vec, 1000);
    
    TRAVERSE_CHECK();
}

TEST_F(VectorTest, shrink) {
    std::default_random_engine rand_eng(810);
    std::uniform_real_distribution<double> distribution(0, 100);
    for (unsigned j = 0; j != 20000; ++j) {
        double real = distribution(rand_eng);
        vector.push_back(&m_vec, &real, sizeof(double));
    }
    for (unsigned i = 0; i != 1000; ++i) {
        for (unsigned j = 0; j != 10000; ++j) {
            double real = distribution(rand_eng);
            vector.push_back(&m_vec, &real, sizeof(double));
        }
        for (unsigned j = 0; j != 10000; ++j) {
            vector.pop_back(&m_vec);
        }
        vector.shrink_to_fit(&m_vec);
    }
    std::vector<double> std_vec;
    random_push(m_vec, std_vec, 1000);
    
    TRAVERSE_CHECK();
}
TEST_F(VectorTest, reserve) {
    std::default_random_engine rand_eng(810);
    std::uniform_real_distribution<double> distribution(0, 100);
    for (unsigned j = 0; j != 20000; ++j) {
        double real = distribution(rand_eng);
        vector.push_back(&m_vec, &real, sizeof(double));
    }
    for (unsigned i = 0; i != 1000; ++i) {
        vector.reserve(&m_vec, 30000);
        vector.shrink_to_fit(&m_vec);
    }
    std::vector<double> std_vec;
    random_push(m_vec, std_vec, 1000);
    
    TRAVERSE_CHECK();
}
void random_push(VectorDescriptor &m_vec, std::vector<double> &std_vec,
                 size_t count) {
    std::default_random_engine rand_eng(810);
    std::uniform_real_distribution<double> distribution(0, 100);
    for (unsigned i = 0; i != count; ++i) {
        double real = distribution(rand_eng);
        vector.push_back(&m_vec, &real, sizeof(double));
        std_vec.push_back(real);
    }
}
