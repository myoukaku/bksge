/**
 *	@file	unit_test_fnd_type_traits_void_t.cpp
 *
 *	@brief	void_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

namespace bksge_type_traits_test
{

namespace void_t_test
{

// 型Tが ::type メンバを持っているかを取得する、has_type_memberを定義します
template <typename, typename = bksge::void_t<>>
struct has_type_member : std::false_type {};
 
template <typename T>
struct has_type_member<T, bksge::void_t<typename T::type>> : std::true_type {};

struct A
{
};

struct B
{
	using type = int;
};

static_assert(!has_type_member<A>::value, "");
static_assert( has_type_member<B>::value, "");

// 型Tが f1 メンバ関数を持っているか取得する
struct C
{
	int f1();
};

struct D
{
	int f2();
};

template <typename, typename = bksge::void_t<>>
struct has_f1_memfun : std::false_type {};

template <typename T>
struct has_f1_memfun<T, bksge::void_t<decltype(std::declval<T>().f1())>> : std::true_type {};

static_assert( has_f1_memfun<C>::value, "");
static_assert(!has_f1_memfun<D>::value, "");

// 型Tが f(int, float) メンバ関数を持っているか取得する
struct E
{
	void f(int);
};

struct F
{
	void f(int, float);
};

template <typename, typename = bksge::void_t<>>
struct has_f_memfun : std::false_type {};

template <typename T>
struct has_f_memfun<T, bksge::void_t<
	decltype(std::declval<T>().f(std::declval<int>(), std::declval<float>()))>> : std::true_type {};

static_assert(!has_f_memfun<E>::value, "");
static_assert( has_f_memfun<F>::value, "");

// 型Tが fun(int, T, char) と呼び出せるか取得する
struct G
{
};

struct H
{
};

int fun(int, const G&, char);

template <typename, typename = bksge::void_t<>>
struct fun_callable : std::false_type {};

template <typename T>
struct fun_callable<T, bksge::void_t<
	decltype(fun(std::declval<int>(), std::declval<T>(), std::declval<char>()))>> : std::true_type {};

static_assert( fun_callable<G>::value, "");
static_assert(!fun_callable<H>::value, "");
static_assert(!fun_callable<int>::value, "");

}	// namespace void_t_test

}	// namespace bksge_type_traits_test
