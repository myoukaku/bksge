/**
 *	@file	unit_test_fnd_iterator_concepts_indirect_binary_predicate.cpp
 *
 *	@brief	indirect_binary_predicate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirect_binary_predicate.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECT_BINARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == bksge::indirect_binary_predicate<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECT_BINARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == bksge::indirect_binary_predicate<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirect_binary_predicate_test
{

struct Pred1
{
	bool operator()(int, int) const;
};
struct Pred2
{
	bool operator()(int) const;
};
struct Pred3
{
	Pred3(Pred3 const&) = delete;
	bool operator()(int, int) const;
};
struct X
{
	using value_type = int;
	int const& operator*() const;
};
struct Y
{
	//using value_type = int;
	int const& operator*() const;
};
struct Z
{
	using value_type = int;
	//int const& operator*() const;
};

BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int      *, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int const*, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int      *, int const*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int const*, int const*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, float*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, char*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int&);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int&&);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int[]);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int[2]);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, void*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, bksge::unique_ptr<int>);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, bksge::shared_ptr<int>);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, bksge::vector<int>::iterator,       int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, bksge::vector<int>::iterator,       bksge::vector<int>::iterator);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, bksge::vector<int>::iterator,       bksge::vector<int>::const_iterator);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, bksge::vector<int>::const_iterator, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, bksge::vector<int>::const_iterator, bksge::vector<int>::iterator);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, bksge::vector<int>::const_iterator, bksge::vector<int>::const_iterator);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, X, X);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, X, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Y, Y);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Y, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Z, Z);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Z, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred2, int*, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred2, bksge::vector<int>::iterator, bksge::vector<int>::iterator);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred2, X, X);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred3, int*, int*);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred3, bksge::vector<int>::iterator, bksge::vector<int>::iterator);
BKSGE_INDIRECT_BINARY_PREDICATE_TEST(false, Pred3, X, X);

}	// namespace indirect_binary_predicate_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECT_BINARY_PREDICATE_TEST
