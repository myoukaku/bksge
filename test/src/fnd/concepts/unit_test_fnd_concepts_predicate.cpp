/**
 *	@file	unit_test_fnd_concepts_predicate.cpp
 *
 *	@brief	predicate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/predicate.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_PREDICATE_TEST(B, ...)	\
	static_assert(B == bksge::predicate<__VA_ARGS__>, "predicate ");	\
	static_assert(B == bksge::predicate_t<__VA_ARGS__>::value, "predicate_t ")
#else
#  define BKSGE_PREDICATE_TEST(B, ...) \
	static_assert(B == bksge::predicate_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace predicate_test
{

bool func1(int);
int  func2();
int* func3(int, int);
void func4(int);
auto lambda1 = [](int a) { return a < 10; };

BKSGE_PREDICATE_TEST(false, decltype(func1));
BKSGE_PREDICATE_TEST(true,  decltype(func1), int);
BKSGE_PREDICATE_TEST(true,  decltype(func1), float);
BKSGE_PREDICATE_TEST(false, decltype(func1), int, int);

BKSGE_PREDICATE_TEST(true,  decltype(func2));
BKSGE_PREDICATE_TEST(false, decltype(func2), int);
BKSGE_PREDICATE_TEST(false, decltype(func2), float);
BKSGE_PREDICATE_TEST(false, decltype(func2), int, int);

BKSGE_PREDICATE_TEST(false, decltype(func3));
BKSGE_PREDICATE_TEST(false, decltype(func3), int);
BKSGE_PREDICATE_TEST(false, decltype(func3), float);
BKSGE_PREDICATE_TEST(true,  decltype(func3), int, int);

BKSGE_PREDICATE_TEST(false, decltype(func4));
BKSGE_PREDICATE_TEST(false, decltype(func4), int);
BKSGE_PREDICATE_TEST(false, decltype(func4), float);
BKSGE_PREDICATE_TEST(false, decltype(func4), int, int);

BKSGE_PREDICATE_TEST(false, decltype(lambda1));
BKSGE_PREDICATE_TEST(true,  decltype(lambda1), int);
BKSGE_PREDICATE_TEST(true,  decltype(lambda1), float);
BKSGE_PREDICATE_TEST(false, decltype(lambda1), int, int);

BKSGE_PREDICATE_TEST(true,  bool(*)());
BKSGE_PREDICATE_TEST(false, bool(*)(), int);
BKSGE_PREDICATE_TEST(false, bool(*)(), int, int);
BKSGE_PREDICATE_TEST(false, bool(*)(int));
BKSGE_PREDICATE_TEST(true,  bool(*)(int), int);
BKSGE_PREDICATE_TEST(false, bool(*)(int), int, int);
BKSGE_PREDICATE_TEST(false, bool(*)(int, int));
BKSGE_PREDICATE_TEST(false, bool(*)(int, int), int);
BKSGE_PREDICATE_TEST(true,  bool(*)(int, int), int, int);

struct A
{
	operator bool() const;
};
struct B
{
	explicit operator bool() const;
};
struct C
{
	operator bool() const;
	bool operator!() const;
};
struct D
{
	operator bool() const = delete;
	bool operator!() const;
};
struct E
{
	operator bool() const;
	bool operator!() const = delete;
};

BKSGE_PREDICATE_TEST(true,  A(*)());
BKSGE_PREDICATE_TEST(false, B(*)());
BKSGE_PREDICATE_TEST(true,  C(*)());
BKSGE_PREDICATE_TEST(false, D(*)());
BKSGE_PREDICATE_TEST(false, E(*)());

struct Predicate0
{
	bool operator()() const { return true;}
};
struct Predicate1
{
	bool operator()(int n) const { return n < 10;}
};
struct Predicate2
{
	bool operator()(int n, int) const { return n < 10;}
};

struct NotPredicate
{
	void operator()(int) {}
	void operator()(int, int) {}
};

BKSGE_PREDICATE_TEST(true,  Predicate0);
BKSGE_PREDICATE_TEST(false, Predicate0, int);
BKSGE_PREDICATE_TEST(false, Predicate0, float);
BKSGE_PREDICATE_TEST(false, Predicate0, int, int);

BKSGE_PREDICATE_TEST(false, Predicate1);
BKSGE_PREDICATE_TEST(true,  Predicate1, int);
BKSGE_PREDICATE_TEST(true,  Predicate1, float);
BKSGE_PREDICATE_TEST(false, Predicate1, int, int);

BKSGE_PREDICATE_TEST(false, Predicate2);
BKSGE_PREDICATE_TEST(false, Predicate2, int);
BKSGE_PREDICATE_TEST(false, Predicate2, float);
BKSGE_PREDICATE_TEST(true,  Predicate2, int, int);

BKSGE_PREDICATE_TEST(false, NotPredicate);
BKSGE_PREDICATE_TEST(false, NotPredicate, int);
BKSGE_PREDICATE_TEST(false, NotPredicate, float);
BKSGE_PREDICATE_TEST(false, NotPredicate, int, int);

}	// namespace predicate_test

}	// namespace bksge_concepts_test

#undef BKSGE_PREDICATE_TEST
