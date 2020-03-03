/**
 *	@file	addressof_inl.hpp
 *
 *	@brief	addressofの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_INL_ADDRESSOF_INL_HPP
#define BKSGE_FND_MEMORY_INL_ADDRESSOF_INL_HPP

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
struct is_member_address_op_overloaded
{
	template <typename U>
	static auto test(int, bksge::type_identity<decltype(bksge::declval<U>().operator&())>* = nullptr) -> bksge::true_type;
	template <typename...>
	static auto test(...) -> bksge::false_type;

	static bool const value = bksge::type_identity<decltype(test<T>(0))>::type::value;
};

template <typename T>
struct is_nonmember_address_op_overloaded
{
	template <typename U>
	static auto test(int, bksge::type_identity<decltype(operator&(bksge::declval<U>()))>* = nullptr) -> bksge::true_type;
	template <typename...>
	static auto test(...) -> bksge::false_type;

	static bool const value = bksge::type_identity<decltype(test<T>(0))>::type::value;
};

template <typename T>
struct is_address_op_overloaded
	: public bksge::bool_constant<
		  is_member_address_op_overloaded<T>::value ||
		  is_nonmember_address_op_overloaded<T>::value
	  >
{};

template <typename T, bool = is_address_op_overloaded<T>::value>
struct addressof_impl;

template <typename T>
struct addressof_impl<T, true>
{
	template <typename U>
	static U* get(U& t) BKSGE_NOEXCEPT
	{
		return reinterpret_cast<U*>(
			&const_cast<char&>(
				reinterpret_cast<char const volatile&>(t)));
	}
};

template <typename T>
struct addressof_impl<T, false>
{
	template <typename U>
	static BKSGE_CONSTEXPR U* get(U& t) BKSGE_NOEXCEPT
	{
		return &t;
	}
};

}	// namespace detail

template <typename T>
BKSGE_CONSTEXPR T* addressof(T& r) BKSGE_NOEXCEPT
{
	return detail::addressof_impl<bksge::remove_cv_t<T>>::get(r);
}

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_INL_ADDRESSOF_INL_HPP
