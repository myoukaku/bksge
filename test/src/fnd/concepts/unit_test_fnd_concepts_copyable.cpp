/**
 *	@file	unit_test_fnd_concepts_copyable.cpp
 *
 *	@brief	copyable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_COPYABLE_TEST(B, T)	\
	static_assert(B == bksge::copyable<T>, "")
#else
#  define BKSGE_COPYABLE_TEST(B, T)	\
	static_assert(B == bksge::copyable<T>::value, "")
#endif

namespace bksge_concepts_test
{

namespace copyable_test
{

BKSGE_COPYABLE_TEST(true,  int);
BKSGE_COPYABLE_TEST(true,  int*);
BKSGE_COPYABLE_TEST(false, int&);
BKSGE_COPYABLE_TEST(false, void);
BKSGE_COPYABLE_TEST(false, void());
BKSGE_COPYABLE_TEST(false, void() noexcept);
BKSGE_COPYABLE_TEST(false, void() const);

struct Trivial { };
BKSGE_COPYABLE_TEST(true,  Trivial);

struct NotTrivial
{
	NotTrivial(int) { }
	NotTrivial(const NotTrivial&) { }
	NotTrivial& operator=(const NotTrivial&) { return *this; }
	~NotTrivial() { }
};
BKSGE_COPYABLE_TEST(true,  NotTrivial);

namespace N1
{
struct Immovable
{
	Immovable() = default;
	Immovable(Immovable&&) = delete;
};
}
BKSGE_COPYABLE_TEST(false, N1::Immovable);

struct Movable
{
	Movable() = default;
	Movable(Movable&&) = default;
	Movable& operator=(Movable&&) = default;
};
BKSGE_COPYABLE_TEST(false, Movable);

struct MovableAndCopyAssignable
{
	MovableAndCopyAssignable() = default;
	MovableAndCopyAssignable(MovableAndCopyAssignable&&) = default;
	MovableAndCopyAssignable& operator=(MovableAndCopyAssignable&&) = default;
	MovableAndCopyAssignable& operator=(const MovableAndCopyAssignable&) = default;
};
BKSGE_COPYABLE_TEST(false, MovableAndCopyAssignable);

struct MovableAndCopyConstructible
{
	MovableAndCopyConstructible() = default;
	MovableAndCopyConstructible(MovableAndCopyConstructible&&) = default;
	MovableAndCopyConstructible(const MovableAndCopyConstructible&) = default;
	MovableAndCopyConstructible& operator=(MovableAndCopyConstructible&&) = default;
};
BKSGE_COPYABLE_TEST(false, MovableAndCopyConstructible);

namespace N2
{
struct Swappable
{
	Swappable() = default;
	Swappable(Swappable&&) = default;
	friend void swap(Swappable&, Swappable&) { }
};
}
BKSGE_COPYABLE_TEST(false, N2::Swappable);

struct NotAssignable
{
	NotAssignable() = default;
	NotAssignable(NotAssignable&&) = default;
	NotAssignable& operator=(NotAssignable&&) = default;
	NotAssignable(const NotAssignable&) = default;
	NotAssignable& operator=(const NotAssignable&) = delete;
	friend void swap(NotAssignable&, NotAssignable&) { }
};
BKSGE_COPYABLE_TEST(false, NotAssignable);

struct NotSwappable
{
	NotSwappable() = default;
	NotSwappable(const NotSwappable&) = default;
	NotSwappable& operator=(const NotSwappable&) = default;
};
void swap(NotSwappable&, NotSwappable&) = delete;
BKSGE_COPYABLE_TEST(true,  NotSwappable); // ranges::swap still works!

}	// namespace copyable_test

}	// namespace bksge_concepts_test

#undef BKSGE_COPYABLE_TEST
