/**
 *	@file	unit_test_fnd_concepts_swappable_with.cpp
 *
 *	@brief	swappable_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/swappable_with.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SWAPPABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::swappable_with<T1, T2>, "")
#else
#  define BKSGE_SWAPPABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::swappable_with<T1, T2>::value, "")
#endif

namespace bksge_concepts_test
{

namespace swappable_with_test
{

BKSGE_SWAPPABLE_WITH_TEST(true,  int&, int&);
BKSGE_SWAPPABLE_WITH_TEST(false, int, int);
BKSGE_SWAPPABLE_WITH_TEST(false, int*, int*);
BKSGE_SWAPPABLE_WITH_TEST(false, int&, const int&);
BKSGE_SWAPPABLE_WITH_TEST(false, const int&, const int&);
BKSGE_SWAPPABLE_WITH_TEST(false, int&, long&);
BKSGE_SWAPPABLE_WITH_TEST(true,  int(&)[2], int(&)[2]);
BKSGE_SWAPPABLE_WITH_TEST(false, int(&)[2], int(&)[3]);
BKSGE_SWAPPABLE_WITH_TEST(false, const int(&)[2], const int(&)[2]);
#if (defined(_MSC_VER) && (_MSC_VER < 1920))
BKSGE_SWAPPABLE_WITH_TEST(true,  int[2], int[2]);	// TODO
#else
BKSGE_SWAPPABLE_WITH_TEST(false, int[2], int[2]);
#endif

namespace N1
{
struct Immovable
{
	Immovable() = default;
	Immovable(Immovable&&) = delete;
};
}
BKSGE_SWAPPABLE_WITH_TEST(false, N1::Immovable&, N1::Immovable&);
BKSGE_SWAPPABLE_WITH_TEST(false, N1::Immovable(&)[2], N1::Immovable(&)[2]);

namespace N2
{
struct Swappable
{
	Swappable() = default;
	Swappable(Swappable&&) = delete;
	friend void swap(Swappable&, Swappable&) { }
};
}
BKSGE_SWAPPABLE_WITH_TEST(true,  N2::Swappable&, N2::Swappable&);
BKSGE_SWAPPABLE_WITH_TEST(true,  N2::Swappable(&)[3], N2::Swappable(&)[3]);

namespace N3
{
struct A { };
struct Proxy {
	Proxy(A&) { }
	friend void swap(Proxy, Proxy) { }
};
}

BKSGE_SWAPPABLE_WITH_TEST(true,  N3::A&, N3::A&);
BKSGE_SWAPPABLE_WITH_TEST(true,  N3::A&, N3::Proxy);
BKSGE_SWAPPABLE_WITH_TEST(true,  N3::Proxy, N3::A&);
BKSGE_SWAPPABLE_WITH_TEST(true,  N3::Proxy, N3::Proxy);

struct C { C(int&) { } };
void swap(int&, C&) { } // not symmetrical
BKSGE_SWAPPABLE_WITH_TEST(false, int, C);
BKSGE_SWAPPABLE_WITH_TEST(false, C, int);

struct D { D(int&) { } };
void swap(int&, D&) { }
void swap(D&&, int&) { } // only accepts rvalues
BKSGE_SWAPPABLE_WITH_TEST(false, int, D);
BKSGE_SWAPPABLE_WITH_TEST(false, D, int);

struct E { E(int&) { } };
void swap(int, E&&) { } // only accepts rvalues
void swap(E&, int) { }
BKSGE_SWAPPABLE_WITH_TEST(false, int, E);
BKSGE_SWAPPABLE_WITH_TEST(false, E, int);

}	// namespace swappable_with_test

}	// namespace bksge_concepts_test

#undef BKSGE_SWAPPABLE_WITH_TEST
