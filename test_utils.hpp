#include <type_traits>
namespace rlib {
    template<typename T>
    struct is_callable_helper {
    private:
        typedef char(&yes)[1];
        typedef char(&no)[2];

        struct Fallback { void operator()(); };
        struct Derived : T, Fallback { };

        template<typename U, U> struct Check;

        template<typename>
        static yes test(...);

        template<typename C>
        static no test(Check<void (Fallback::*)(), &C::operator()>*);

    public:
        static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
    };
    template<typename T>
    struct is_callable
        : std::conditional<
            std::is_class<T>::value,
            is_callable_helper<T>,
            std::false_type>::type
    {};
}

//operation must be a templated callable object, usually templated lambda.
#define ASSERT_EQUIVALENCE(bufA, bufB, operation, equal_checker) \
    do { \
        static_assert(rlib::is_callable(equal_checker), \
                    "equal_checker is not callable"); \
        static_assert(equal_checker(bufA, bufB), "given buf is not equal.") \
        operation(bufA); \
        operation(bufB); \
        static_assert(equal_checker(bufA, bufB), "operation failed."); \
    } while(false)

/* Operation() can not accept two type.
template <Container bufa_t, Container bufb_t, Callable operation_t>
void equivalence_assert(bufa_t &bufA, bufb_t &bufB, operation_t operation, 
    std::function<bool(bufa_t, bufb_t)> equal_checker = std::equal<bufa_t, bufb_t>)
{
    static_assert(equal_checker(bufA, bufB), "given buf is not equal.");
    operation(bufA);
    operation(bufB);
    static_assert(equal_checker(bufA, bufB), "given buf is not equal.");
}
*/

//vector
#include "lab_vector.hpp"
#include <vector>

template<typename data_t>
bool vector_equal(const Lab::vector<data_t> &vcta, const std::vector<data_t> &vctb)
{
    if(vcta.size() != vctb.size()) return false;
    for(auto ia = vcta.begin(), ib = vctb.begin();
        ia != vcta.end() && ib != vctb.end();
        ++ia, ++ib)
        {
            if(*ia != *ib) return false;
        }
    return true;
}
#define VECTOR_ASSERT_EQUIVALENCE(bufA, bufB, operation) ASSERT_EQUIVALENCE(bufA, bufB, operation, vector_equal)



