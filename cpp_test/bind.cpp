#include "bind.h"

#include <iostream>
#include <string>
#include <functional>
#include <utility>

//////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#   define TEST_FUNC_NAME __FUNCSIG__
#elif defined(__GNUC__)
#   define TEST_FUNC_NAME __PRETTY_FUNCTION__
#else
#   define TEST_FUNC_NAME __func__
#endif

#define TEST_CASE(...) \
    std::cout << std::endl \
              << "----------------------------------" << std::endl \
              << TEST_FUNC_NAME << " ->: " __VA_ARGS__ << std::endl \
              << "----------------------------------" << std::endl

//////////////////////////////////////////////////////////////////////////

namespace test_bind_np
{
    using namespace simple;

    void func0_0(void)
    {
        std::cout << TEST_FUNC_NAME << std::endl;
    }

    int func0_1(void)
    {
        std::cout << TEST_FUNC_NAME << " ->: ";
        return 0;
    }

    int func1(long a)
    {
        std::cout << TEST_FUNC_NAME << "(" << a << ")" << " ->: ";
        return 1;
    }

    static int func2(int a, int b)
    {
        std::cout << TEST_FUNC_NAME << "(" << a << ", " << b << ")" << " ->: ";
        return 2;
    }

    static int func2_s(long a, int b)
    {
        std::cout << TEST_FUNC_NAME << "(" << a << ", " << b << ")" << " ->: ";
        return 2;
    }

    class A
    {
    public:
        virtual int func(long a, int b, long c, int d)
        {
            std::cout << TEST_FUNC_NAME << "(" << a << ", "
                << b << ", "
                << c << ", "
                << d << ")" << " ->: ";
            return 4;
        }
    };

    class B : public A
    {
    public:
        int func(long a, int b, long c, int d)
        {
            std::cout << TEST_FUNC_NAME << "(" << a << ", "
                << b << ", "
                << c << ", "
                << d << ")" << " ->: ";
            return 4;
        }

        int func_const(long a) const
        {
            std::cout << TEST_FUNC_NAME << "(" << a << ")" << " ->: ";
            return 1;
        }

        static int funcS(long a)
        {
            std::cout << TEST_FUNC_NAME << "(" << a << ")" << " ->: ";
            return 1;
        }
    };

    class C
    {
    public:
        template <typename T>
        T operator()(T a)
        {
            std::cout << TEST_FUNC_NAME << "(" << a << ")" << " ->: ";
            return a;
        }
    };

    class Func
    {
    public:
        int operator()(int a, double b)
        {
            std::cout << TEST_FUNC_NAME << "(" << a << ", " << b << ")" << std::endl;
            return 0;
        }
    };

    class Func0
    {
    public:
        int operator()(void)
        {
            std::cout << TEST_FUNC_NAME << " ->: ";
            return 0;
        }
    };

    class Foo
    {
    public:
        Foo(void) = default;
        Foo(const Foo&) { std::cout << "Foo copy" << std::endl; }
    };

    class Func1
    {
    public:
        std::string& operator()(std::string& s, Foo&&)
        {
            std::cout << TEST_FUNC_NAME << "(" << s << ")" << " ->: ";
            return s;
        }
    };

    class Func2
    {
    public:
        int operator()(void) const volatile
        {
            std::cout << TEST_FUNC_NAME << " ->: ";
            return 0;
        }
    };

    class UncopyableFunc
    {
    public:
        UncopyableFunc(void) {}
        UncopyableFunc(UncopyableFunc&&) {}
        UncopyableFunc(const UncopyableFunc&) = delete;

        int operator()(void)
        {
            std::cout << TEST_FUNC_NAME << " ->: ";
            return 0;
        }
    };
}

void test_bind(void)
{
    TEST_CASE();
    using namespace test_bind_np;
    {
        bind(func0_0)();
        std::cout << bind(func0_1)() << std::endl;
        std::cout << bind(func1, _1)(123) << std::endl;
        std::cout << bind(func2, _1, _2)(1, 2) << std::endl;
        std::cout << bind(func2_s, _1, _1)(321) << std::endl;
    }
    std::cout << std::endl;
    {
        B a;
        std::cout << bind(&B::func, a, 1, _1, 3, 4)(2) << std::endl;
        std::cout << bind(&B::func_const, &a, 123)() << std::endl;
        A* pa = &a;
        std::cout << bind(&A::func, pa, _4, _3, _2, _1)(1, 2, 3, 4) << std::endl;
        std::cout << bind(B::funcS, 123)() << std::endl;
        std::cout << bind(C(), _1)(123) << std::endl;
    }
    std::cout << std::endl;
    {
        Func f;
        std::cout << bind(f, _2, _1)(123, 321) << std::endl;
        Func0 f0;
        std::cout << bind(&f0)() << std::endl;
        Func1 f1;
        std::string s("Hello Bind!");
        std::cout << bind(f1, _1, _2)(s, Foo()) << std::endl;
        Func2 f2;
        std::cout << bind(f2)() << std::endl;
    }
    std::cout << std::endl;
    {
        UncopyableFunc ff;
        std::cout << bind(std::move(ff))() << std::endl;
        auto fr = bind(std::move(ff));
        std::cout << fr() << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////

int main(void)
{
    test_bind();

    TEST_CASE(<< "Finished!");
    return 0;
}

