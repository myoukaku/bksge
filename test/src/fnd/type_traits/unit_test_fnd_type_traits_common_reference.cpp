/**
 *	@file	unit_test_fnd_type_traits_common_reference.cpp
 *
 *	@brief	common_reference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>

namespace bksge_type_traits_test
{

namespace common_reference_test
{

template <typename T, typename = void>
struct has_type : bksge::false_type { };

template <typename T>
struct has_type<T, bksge::void_t<typename T::type>>: bksge::true_type { };

template <typename... T>
constexpr bool
has_common_ref()
{
	return has_type<bksge::common_reference<T...>>::value;
}

struct A { };
struct B { };
struct C { };

struct D { };
struct E { };
struct F { };

}	// namespace common_reference_test

}	// namespace bksge_type_traits_test

namespace bksge
{

template <template <typename> class AQual, template <typename> class BQual>
struct basic_common_reference<
	bksge_type_traits_test::common_reference_test::A,
	bksge_type_traits_test::common_reference_test::B,
	AQual, BQual>
{
	using type = BQual<AQual<bksge_type_traits_test::common_reference_test::C>>;
};

template <>
struct common_type<
	bksge_type_traits_test::common_reference_test::D,
	bksge_type_traits_test::common_reference_test::E>
{
	using type = bksge_type_traits_test::common_reference_test::F;
};

}	// namespace bksge

namespace bksge_type_traits_test
{

namespace common_reference_test
{

static_assert(!has_common_ref<>(), "");
static_assert(!has_common_ref<char(*)(), int(*)()>(), "");
static_assert(!has_common_ref<void*, int>(), "");
static_assert( has_common_ref<int, int, int>(), "");
static_assert(!has_common_ref<void*, int, int>(), "");
static_assert(!has_common_ref<int, int, void*>(), "");

#define BKSGE_COMMON_REFERENCE_TEST(T, ...)	\
	static_assert(bksge::is_same<T, bksge::common_reference_t<__VA_ARGS__>>::value, "")

BKSGE_COMMON_REFERENCE_TEST(int, int);
BKSGE_COMMON_REFERENCE_TEST(int&, int&);
BKSGE_COMMON_REFERENCE_TEST(void, void);
BKSGE_COMMON_REFERENCE_TEST(const void, const void);
BKSGE_COMMON_REFERENCE_TEST(void, const void, void);
BKSGE_COMMON_REFERENCE_TEST(void(*)(), void(* const)(), void(*)());
BKSGE_COMMON_REFERENCE_TEST(int, int, int);
BKSGE_COMMON_REFERENCE_TEST(int, int&, int);
BKSGE_COMMON_REFERENCE_TEST(int, int&, int);
BKSGE_COMMON_REFERENCE_TEST(int, int&&, int);
BKSGE_COMMON_REFERENCE_TEST(int&, int&, int&);
BKSGE_COMMON_REFERENCE_TEST(const int&, int&, int&&);
BKSGE_COMMON_REFERENCE_TEST(const int&, int&&, int&);
BKSGE_COMMON_REFERENCE_TEST(int&&, int&&, int&&);
BKSGE_COMMON_REFERENCE_TEST(const int&&, int&&, const int&&);
BKSGE_COMMON_REFERENCE_TEST(const int&, int&, int&, int&&);
BKSGE_COMMON_REFERENCE_TEST(const int&, int&&, int&, int&);
BKSGE_COMMON_REFERENCE_TEST(int, char&, int&);
BKSGE_COMMON_REFERENCE_TEST(long, long&, int&);

BKSGE_COMMON_REFERENCE_TEST(C, A, B);
BKSGE_COMMON_REFERENCE_TEST(C&, A&, B);
BKSGE_COMMON_REFERENCE_TEST(C&, A&, const B);
BKSGE_COMMON_REFERENCE_TEST(const C&, const A, B&);
BKSGE_COMMON_REFERENCE_TEST(const C&, const A&, B&&);
BKSGE_COMMON_REFERENCE_TEST(const C&&, const A, B&&);

BKSGE_COMMON_REFERENCE_TEST(F, D, E);
BKSGE_COMMON_REFERENCE_TEST(F, D&, E);
BKSGE_COMMON_REFERENCE_TEST(F, D&, E&&);

#undef BKSGE_COMMON_REFERENCE_TEST

}	// namespace common_reference_test

}	// namespace bksge_type_traits_test
