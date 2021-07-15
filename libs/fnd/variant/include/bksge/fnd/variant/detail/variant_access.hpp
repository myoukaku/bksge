/**
 *	@file	variant_access.hpp
 *
 *	@brief	variant_access の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_ACCESS_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_ACCESS_HPP

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

class variant_access
{
private:
	template <typename... Types, typename T, typename = bksge::enable_if_t<!bksge::is_lvalue_reference<T>::value>>
	static variant<Types...>&&
	variant_cast_impl(T&& rhs, bksge::detail::overload_priority<2>)
	{
		return static_cast<variant<Types...>&&>(rhs);
	}

	template <typename... Types, typename T, typename = bksge::enable_if_t<bksge::is_const<bksge::remove_reference_t<T>>::value>>
	static variant<Types...> const&
	variant_cast_impl(T&& rhs, bksge::detail::overload_priority<1>)
	{
		return static_cast<variant<Types...> const&>(rhs);
	}

	template <typename... Types, typename T>
	static variant<Types...>&
	variant_cast_impl(T&& rhs, bksge::detail::overload_priority<0>)
	{
		return static_cast<variant<Types...>&>(rhs);
	}

public:
	template <typename... Types, typename T>
	static auto
	variant_cast(T&& rhs)
	->decltype(variant_cast_impl<Types...>(bksge::forward<T>(rhs), bksge::detail::overload_priority<2>{}))
	{
		return variant_cast_impl<Types...>(bksge::forward<T>(rhs), bksge::detail::overload_priority<2>{});
	}

private:
	template <std::size_t N, typename Dummy = void> // Dummy for avoid explicit specialization in class scope
	struct get_impl_t
	{
		template <typename Union>
		constexpr auto
		operator()(Union&& u) const noexcept
		->decltype(get_impl_t<N-1>{}(bksge::forward<Union>(u).m_rest))
		{
			return get_impl_t<N-1>{}(bksge::forward<Union>(u).m_rest);
		}
	};

	template <typename Dummy>
	struct get_impl_t<0, Dummy>
	{
		template <typename Union>
		constexpr auto
		operator()(Union&& u) const noexcept
		->decltype(bksge::forward<Union>(u).m_first.get())
		{
			return bksge::forward<Union>(u).m_first.get();
		}
	};

public:
	// Returns the typed storage for v.
	template <std::size_t N, typename Variant>
	static constexpr auto
	get_impl(Variant&& v) noexcept
	->decltype(get_impl_t<N>{}(bksge::forward<Variant>(v).m_u))
	{
		return get_impl_t<N>{}(bksge::forward<Variant>(v).m_u);
	}

	template <std::size_t N, typename Variant, typename... Args>
	static void
	variant_construct_by_index(Variant& v, Args&&... args)
	{
		v.m_index = N;
		auto&& storage = get_impl<N>(v);
		::new ((void*)bksge::addressof(storage))
			bksge::remove_reference_t<decltype(storage)>(bksge::forward<Args>(args)...);
	}
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_ACCESS_HPP
