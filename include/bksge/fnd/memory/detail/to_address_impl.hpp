/**
 *	@file	to_address_impl.hpp
 *
 *	@brief	to_address_impl を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP
#define BKSGE_FND_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP

#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_function.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <memory>	// pointer_traits

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace bksge
{

namespace detail
{

namespace to_address_detail
{

template <typename T, typename = void>
struct pointer_traits_to_address
	: bksge::false_type {};

template <typename T>
struct pointer_traits_to_address<T,
	bksge::void_t<
		decltype(std::pointer_traits<T>::to_address(bksge::declval<T const&>()))
	>
> : bksge::true_type {};

template <typename T, typename = void>
struct has_operator_arrow
	: bksge::false_type {};

template <typename T>
struct has_operator_arrow<T,
	bksge::void_t<
		decltype(bksge::declval<T const&>().operator->())
	>
> : bksge::true_type {};

struct to_address_fn
{
private:
	template <typename T, typename = bksge::enable_if_t<!bksge::is_function<T>::value>>
	static BKSGE_CONSTEXPR T*
	impl(bksge::detail::overload_priority<3>, T* p) BKSGE_NOEXCEPT
	{
		return p;
	}

	template <typename Ptr, typename = bksge::enable_if_t<pointer_traits_to_address<Ptr>::value>>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<2>, const Ptr& p) BKSGE_NOEXCEPT
	->decltype(std::pointer_traits<Ptr>::to_address(p))
	{
		return std::pointer_traits<Ptr>::to_address(p);
	}

	template <typename Ptr, typename = bksge::enable_if_t<has_operator_arrow<Ptr>::value>>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<0>, const Ptr& p) BKSGE_NOEXCEPT
	->decltype(impl(bksge::detail::overload_priority<3>{}, p.operator->()))
	{
		return impl(bksge::detail::overload_priority<3>{}, p.operator->());
	}

	template <typename Ptr, typename = bksge::enable_if_t<has_operator_arrow<Ptr>::value>>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, const Ptr& p) BKSGE_NOEXCEPT
	->decltype(impl(bksge::detail::overload_priority<0>{}, p.operator->()))
	{
		return impl(bksge::detail::overload_priority<0>{}, p.operator->());
	}

public:
	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T const& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			impl(bksge::detail::overload_priority<3>{}, t))
};

}	// namespace to_address_detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
to_address_detail::to_address_fn to_address_impl{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP
