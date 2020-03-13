/**
 *	@file	type_traits_test_utility.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_TYPE_TRAITS_TYPE_TRAITS_TEST_UTILITY_HPP
#define UNIT_TEST_FND_TYPE_TRAITS_TYPE_TRAITS_TEST_UTILITY_HPP

#include <bksge/fnd/config.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <cstddef>

namespace
{

//
// define some test types:
//
enum enum_UDT{ one, two, three };

enum enum_uint32_t_UDT : std::uint32_t { four, five, six };
enum enum_uint16_t_UDT : std::uint16_t { seven, eight };
enum enum_uint8_t_UDT  : std::uint8_t { nine };
enum enum_int32_t_UDT  : std::int32_t { ten};
enum enum_int16_t_UDT  : std::int16_t { eleven };
enum enum_int8_t_UDT   : std::int8_t { twelve };

enum class enum_class_UDT { one, two, three };

enum class enum_class_uint32_t_UDT : std::uint32_t { one, two, three };
enum class enum_class_uint16_t_UDT : std::uint16_t { one, two, three };
enum class enum_class_uint8_t_UDT  : std::uint8_t { one, two, three };
enum class enum_class_int32_t_UDT  : std::int32_t { one, two, three };
enum class enum_class_int16_t_UDT  : std::int16_t { one, two, three };
enum class enum_class_int8_t_UDT   : std::int8_t { one, two, three };

struct UDT
{
	UDT(){}
	~UDT() BKSGE_NOEXCEPT_OR_NOTHROW{}
	UDT(const UDT&){}
	UDT& operator=(const UDT&){return *this;}

	int i;

	void f1();
	int f2();
	int f3(int);
	int f4(int,float);
};

typedef void(*f1)();
typedef int(*f2)(int);
typedef int(*f3)(int, bool);
typedef void (UDT::*mf1)();
typedef int (UDT::*mf2)();
typedef int (UDT::*mf3)(int);
typedef int (UDT::*mf4)(int, float);
typedef int (UDT::*mp);
typedef int (UDT::*cmf)(int) const;

// cv-qualifiers applied to reference types should have no effect
// declare these here for later use with is_reference and remove_reference:
# ifdef BKSGE_MSVC
#  pragma warning(push)
#  pragma warning(disable: 4181)
# elif defined(BKSGE_INTEL)
#  pragma warning(push)
#  pragma warning(disable: 21)
# elif defined(BKSGE_CLANG)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wignored-qualifiers"
# endif
//
// This is intentional:
// r_type and cr_type should be the same type
// but some compilers wrongly apply cv-qualifiers
// to reference types (this may generate a warning
// on some compilers):
//
typedef int& r_type;
#ifndef BKSGE_INTEL
typedef const r_type cr_type;
#else
// recent Intel compilers generate a hard error on the above:
typedef r_type cr_type;
#endif
# ifdef BKSGE_MSVC
#  pragma warning(pop)
# elif defined(BKSGE_INTEL)
#  pragma warning(pop)
#  pragma warning(disable: 985) // identifier truncated in debug information
# elif defined(BKSGE_CLANG)
#  pragma clang diagnostic pop
# endif

struct POD_UDT { int x; };
struct empty_UDT
{
   empty_UDT();
   empty_UDT(const empty_UDT&);
   ~empty_UDT() BKSGE_NOEXCEPT_OR_NOTHROW;
   empty_UDT& operator=(const empty_UDT&);
   bool operator==(const empty_UDT&)const;
};
struct empty_POD_UDT
{
   bool operator==(const empty_POD_UDT&)const
   { return true; }
};
union union_UDT
{
  int x;
  double y;
  ~union_UDT() BKSGE_NOEXCEPT_OR_NOTHROW {}
};
union POD_union_UDT
{
  int x;
  double y;
};
union empty_union_UDT
{
   ~empty_union_UDT() BKSGE_NOEXCEPT_OR_NOTHROW {}
};
union empty_POD_union_UDT{};

#define BKSGE_DECLARE_NOTHROW_UDT(T, E1, E2, E3, E4, E5, E6)	\
	struct T									\
	{											\
		T() E1;									\
		~T() E2;								\
		T(T const&) E3;							\
		T& operator=(T const&) E4;				\
		T(T&&) E5;								\
		T& operator=(T&&) E6;					\
	}

BKSGE_DECLARE_NOTHROW_UDT(
	nothrow_default_ctor_UDT,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/,
	/**/,
	/**/,
	/**/);

BKSGE_DECLARE_NOTHROW_UDT(
	nothrow_dtor_UDT,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/,
	/**/,
	/**/,
	/**/);

BKSGE_DECLARE_NOTHROW_UDT(
	nothrow_copy_ctor_UDT,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/,
	/**/,
	/**/);

BKSGE_DECLARE_NOTHROW_UDT(
	nothrow_copy_assign_UDT,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/,
	/**/);

BKSGE_DECLARE_NOTHROW_UDT(
	nothrow_move_ctor_UDT,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/);

BKSGE_DECLARE_NOTHROW_UDT(
	nothrow_move_assign_UDT,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW,
	/**/,
	/**/,
	/**/,
	BKSGE_NOEXCEPT_OR_NOTHROW);

#undef BKSGE_DECLARE_NOTHROW_UDT


class Base { };

class Derived : public Base { };
class Derived2 : public Base { };
class MultiBase : public Derived, public Derived2 {};
class PrivateBase : private Base {};

class NonDerived { };

#if defined(BKSGE_HAS_CXX11_FINAL)
struct final_UDT final {};
class final_Derived_UDT final : public Base {};
union final_union_UDT final {};
#endif


enum enum1
{
   one_,two_
};

enum enum2
{
   three_,four_
};

struct VB
{
   virtual ~VB() BKSGE_NOEXCEPT_OR_NOTHROW {};
};

struct VD : public VB
{
   ~VD() BKSGE_NOEXCEPT_OR_NOTHROW {};
};
//
// struct non_pointer:
// used to verify that is_pointer does not return
// true for class types that implement operator void*()
//
struct non_pointer
{
   operator void*(){return this;}
};
struct non_int_pointer
{
   int i;
   operator int*(){return &i;}
};
struct int_constructible
{
   int_constructible(int);
};
struct int_convertible
{
   operator int() const volatile;
};

// abstract base classes:
struct test_abc1
{
   test_abc1();
   virtual ~test_abc1() BKSGE_NOEXCEPT_OR_NOTHROW {}
   test_abc1(const test_abc1&);
   test_abc1& operator=(const test_abc1&);
   virtual void foo() = 0;
   virtual void foo2() = 0;
};

struct test_abc2
{
   virtual void foo() = 0;
   virtual void foo2() = 0;
   int x;
};

struct test_abc3 : public test_abc1
{
   virtual void foo3() = 0;
};

struct test_concrete1 : public test_abc2
{
	virtual void foo() {}
	virtual void foo2() {}
};

struct test_concrete2 : public test_abc3
{
	virtual void foo() {}
	virtual void foo2() {}
	virtual void foo3() {}
};

struct incomplete_type;

struct polymorphic_base
{
	virtual ~polymorphic_base() BKSGE_NOEXCEPT_OR_NOTHROW {}
	virtual void method() {}
};

struct polymorphic_derived1 : public polymorphic_base
{
};

struct polymorphic_derived2 : public polymorphic_base
{
	virtual void method(){}
};

struct virtual_inherit1 : public virtual Base { };
struct virtual_inherit2 : public virtual_inherit1 { };
struct virtual_inherit3 : private virtual Base {};
//struct virtual_inherit4 : public virtual noncopyable {};
struct virtual_inherit5 : public virtual int_convertible {};
struct virtual_inherit6 : public virtual Base { virtual ~virtual_inherit6()throw(){} };

typedef void foo0_t();
typedef void foo1_t(int);
typedef void foo2_t(int&, double);
typedef void foo3_t(int&, bool, int, int);
typedef void foo4_t(int, bool, int*, int[], int, int, int, int, int);

struct trivial_except_construct
{
	trivial_except_construct();
	int i;
};

struct trivial_except_destroy
{
	~trivial_except_destroy() BKSGE_NOEXCEPT_OR_NOTHROW;
	int i;
};

struct trivial_except_copy_ctor
{
	trivial_except_copy_ctor(const trivial_except_copy_ctor&);
	int i;
};

struct trivial_except_copy_assign
{
	trivial_except_copy_assign& operator=(const trivial_except_copy_assign&);
	int i;
};

struct trivial_except_move_ctor
{
	trivial_except_move_ctor(trivial_except_move_ctor&&);
	int i;
};

struct trivial_except_move_assign
{
	trivial_except_move_assign& operator=(trivial_except_move_assign&&);
	int i;
};

template <typename T>
struct wrap
{
   T t;
   int j;
protected:
   wrap();
   wrap(const wrap&);
   wrap& operator=(const wrap&);
};

template <typename T, typename T::value_type b>
void IntegralConstantTest()
{
	static_assert(T::value == b, "");

#if defined(BKSGE_HAS_CXX11_CONSTEXPR)
	static_assert(T() == b, "");
	static_assert(T()() == b, "");
#endif

	EXPECT_EQ(b, T());
	EXPECT_EQ(b, T()());
}

}	// namespace

#define BKSGE_TRANSFORM_TEST_SUB(t, name, from_suffix, to_suffix)	\
	static_assert(bksge::is_same<t to_suffix, name<t from_suffix>::type>::value, "");	\
	static_assert(bksge::is_same<t to_suffix, name##_t<t from_suffix>>::value, "")

#define BKSGE_TRANSFORM_TEST(name, from, to)	\
	BKSGE_TRANSFORM_TEST_SUB(bool, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(char, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(wchar_t, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(signed char, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(unsigned char, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(short, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(unsigned short, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(int, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(unsigned int, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(long, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(unsigned long, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(std::size_t, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(float, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(double, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(long double, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(UDT, name, from, to);	\
	BKSGE_TRANSFORM_TEST_SUB(enum1, name, from, to)	\
	/**/

#endif // UNIT_TEST_FND_TYPE_TRAITS_TYPE_TRAITS_TEST_UTILITY_HPP
