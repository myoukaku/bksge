/**
 *	@file	to_address_impl.hpp
 *
 *	@brief	to_address_impl を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP
#define BKSGE_FND_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP

#include <bksge/fnd/type_traits/is_function.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <memory>	// pointer_traits

namespace bksge
{

namespace detail
{

template <typename T, typename = void>
struct to_address_result
{
	using type = typename to_address_result<decltype(bksge::declval<T const&>().operator->())>::type;
};

template <typename T>
struct to_address_result<T*>
{
	using type = T*;
};

template <typename T>
struct to_address_result<T,
	bksge::void_t<decltype(std::pointer_traits<T>::to_address(bksge::declval<T const&>()))>>
{
	using type = decltype(std::pointer_traits<T>::to_address(bksge::declval<T const&>()));
};

template <typename T>
BKSGE_CONSTEXPR T*
to_address_impl(T* p) BKSGE_NOEXCEPT
{
	static_assert(!bksge::is_function<T>::value, "not a function pointer");
	return p;
}

template <typename Ptr>
BKSGE_CONSTEXPR auto
to_address_impl(const Ptr& p) BKSGE_NOEXCEPT
->decltype(std::pointer_traits<Ptr>::to_address(p))
{
	return std::pointer_traits<Ptr>::to_address(p);
}

template <typename Ptr, typename... None>
BKSGE_CONSTEXPR typename to_address_result<Ptr>::type
to_address_impl(const Ptr& p, None...) BKSGE_NOEXCEPT
{
	return to_address_impl(p.operator->());
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP
