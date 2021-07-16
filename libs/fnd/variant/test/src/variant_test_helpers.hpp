/**
 *	@file	variant_test_helpers.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_VARIANT_VARIANT_TEST_HELPERS_HPP
#define UNIT_TEST_FND_VARIANT_VARIANT_TEST_HELPERS_HPP

#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <cassert>
#include <utility>

namespace bksge_variant_test
{

#define TEST_VARIANT_HAS_NO_REFERENCES

#if defined(BKSGE_ENABLE_NARROWING_CONVERSIONS_IN_VARIANT)
# define TEST_VARIANT_ALLOWS_NARROWING_CONVERSIONS
#endif

#if defined(TEST_VARIANT_ALLOWS_NARROWING_CONVERSIONS)
constexpr bool VariantAllowsNarrowingConversions = true;
#else
constexpr bool VariantAllowsNarrowingConversions = false;
#endif

#if !defined(BKSGE_NO_EXCEPTIONS)

template <typename>
struct TMakeEmptyT
{
	static int alive;

	TMakeEmptyT()
	{
		++alive;
	}

	TMakeEmptyT(TMakeEmptyT const&)
	{
		++alive;
		// Don't throw from the copy constructor since variant's assignment
		// operator performs a copy before committing to the assignment.
	}

	TMakeEmptyT(TMakeEmptyT&&)
	{
		throw 42;
	}

	TMakeEmptyT& operator=(TMakeEmptyT const&)
	{
		throw 42;
	}

	TMakeEmptyT& operator=(TMakeEmptyT&&)
	{
		throw 42;
	}

	~TMakeEmptyT()
	{
		--alive;
	}
};

template <typename T>
int TMakeEmptyT<T>::alive = 0;

using MakeEmptyT = TMakeEmptyT<void>;

static_assert(bksge::is_swappable<MakeEmptyT>::value, ""); // required for test

template <class Variant>
void makeEmpty(Variant& v)
{
	Variant v2(bksge::in_place_type_t<MakeEmptyT>{});
	try
	{
		v = std::move(v2);
		assert(false);
	}
	catch (...)
	{
		assert(v.valueless_by_exception());
	}
}

#endif

}	// namespace bksge_variant_test

#endif // UNIT_TEST_FND_VARIANT_VARIANT_TEST_HELPERS_HPP
