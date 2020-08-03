/**
 *	@file	unit_test_fnd_concepts_movable.cpp
 *
 *	@brief	movable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/movable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_MOVABLE_TEST(B, T)	\
	static_assert(B == bksge::movable<T>, "")
#else
#  define BKSGE_MOVABLE_TEST(B, T)	\
	static_assert(B == bksge::movable<T>::value, "")
#endif

namespace bksge_concepts_test
{

namespace movable_test
{

BKSGE_MOVABLE_TEST(true,  int);
BKSGE_MOVABLE_TEST(true,  int*);
BKSGE_MOVABLE_TEST(false, int&);
BKSGE_MOVABLE_TEST(false, void);
BKSGE_MOVABLE_TEST(false, void());
BKSGE_MOVABLE_TEST(false, void() noexcept);
BKSGE_MOVABLE_TEST(false, void() const);

struct Trivial { };
BKSGE_MOVABLE_TEST(true,  Trivial);

struct NotTrivial
{
	NotTrivial(int) { }
	NotTrivial(NotTrivial&&) { }
	NotTrivial& operator=(NotTrivial&&) { return *this; }
	~NotTrivial() { }
};
BKSGE_MOVABLE_TEST(true,  NotTrivial);

namespace N1
{
struct Immovable
{
	Immovable() = default;
	Immovable(Immovable&&) = delete;
};
}
BKSGE_MOVABLE_TEST(false, N1::Immovable);

namespace N2
{
struct Swappable
{
	Swappable() = default;
	Swappable(Swappable&&) = delete;
	Swappable& operator=(Swappable&&) = default;
	friend void swap(Swappable&, Swappable&) { }
};
}
BKSGE_MOVABLE_TEST(false, N2::Swappable);

struct NotAssignable
{
	NotAssignable() = default;
	NotAssignable(NotAssignable&&) = default;
	NotAssignable& operator=(NotAssignable&&) = delete;
	friend void swap(NotAssignable&, NotAssignable&) { }
};
BKSGE_MOVABLE_TEST(false, NotAssignable);

struct NotSwappable
{
	NotSwappable() = default;
	NotSwappable(NotSwappable&&) = default;
	NotSwappable& operator=(NotSwappable&&) = default;
};
void swap(NotSwappable&, NotSwappable&) = delete;
BKSGE_MOVABLE_TEST(true,  NotSwappable); // ranges::swap still works!

}	// namespace movable_test

}	// namespace bksge_concepts_test

#undef BKSGE_MOVABLE_TEST
