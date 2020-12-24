/**
 *	@file	unit_test_fnd_iterator_concepts_weakly_incrementable.cpp
 *
 *	@brief	weakly_incrementable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <vector>
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_WEAKLY_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == bksge::weakly_incrementable<__VA_ARGS__>, "")
#else
#  define BKSGE_WEAKLY_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == bksge::weakly_incrementable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace weakly_incrementable_test
{

BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int               *);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int const         *);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int       volatile*);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int const volatile*);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int               * const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int const         * const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int       volatile* const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int const volatile* const);

BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int               **);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int const         **);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int       volatile**);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  int const volatile**);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int               ** const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int const         ** const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int       volatile** const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int const volatile** const);

BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void               *);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void const         *);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void       volatile*);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void const volatile*);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void               * const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void const         * const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void       volatile* const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void const volatile* const);

BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  void               **);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  void const         **);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  void       volatile**);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  void const volatile**);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void               ** const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void const         ** const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void       volatile** const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, void const volatile** const);

BKSGE_WEAKLY_INCREMENTABLE_TEST(false, bksge::unique_ptr<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, std::shared_ptr<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, std::vector<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  std::vector<int>::iterator);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  std::vector<int>::const_iterator);

BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int[]);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int[2]);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, int&&);

struct X
{
	friend auto operator++(X&)->X&;
	friend auto operator++(X&, int)->X&;
	using difference_type = int;
};
struct Y
{
	friend auto operator++(Y&)->Y;		// 前置インクリメントは参照を返さないといけない
	friend auto operator++(Y&, int)->Y&;
	using difference_type = int;
};
struct Z
{
	friend auto operator++(Z&)->Z&;
	friend auto operator++(Z&, int)->void;	// 後置インクリメントは何を返しても良い
	using difference_type = int;
};
struct W
{
	friend auto operator++(W&)->W&;
	friend auto operator++(W&, int)->W&;
//	using difference_type = int;		// difference_type が定義されてないといけない
};

BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  X);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, X&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, X const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, X const&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, Y);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, Y&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, Y const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, Y const&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  Z);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, Z&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, Z const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, Z const&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, W);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, W&);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, W const);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, W const&);

BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  weakly_incrementable_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  incrementable_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, indirectly_readable_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(false, indirectly_writable_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  input_or_output_iterator_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  input_iterator_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  output_iterator_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  forward_iterator_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  bidirectional_iterator_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  random_access_iterator_wrapper<int>);
BKSGE_WEAKLY_INCREMENTABLE_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace weakly_incrementable_test

}	// namespace bksge_iterator_test

#undef BKSGE_WEAKLY_INCREMENTABLE_TEST
