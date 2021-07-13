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
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>

namespace bksge
{

namespace variant_detail
{

class variant_access
{
private:
	template <typename... Types, typename T, typename = bksge::enable_if_t<!bksge::is_lvalue_reference<T>::value>>
	static decltype(auto)
	variant_cast_impl(T&& rhs, bksge::detail::overload_priority<2>)
	{
		return static_cast<variant<Types...>&&>(rhs);
	}

	template <typename... Types, typename T, typename = bksge::enable_if_t<bksge::is_const<bksge::remove_reference_t<T>>::value>>
	static decltype(auto)
	variant_cast_impl(T&& rhs, bksge::detail::overload_priority<1>)
	{
		return static_cast<variant<Types...> const&>(rhs);
	}

	template <typename... Types, typename T>
	static decltype(auto)
	variant_cast_impl(T&& rhs, bksge::detail::overload_priority<0>)
	{
		return static_cast<variant<Types...>&>(rhs);
	}

public:
	template <typename... Types, typename T>
	static decltype(auto)
	variant_cast(T&& rhs)
	{
		return variant_cast_impl<Types...>(bksge::forward<T>(rhs), bksge::detail::overload_priority<2>{});
	}

	template <typename Union>
	static constexpr decltype(auto)
	get_impl(bksge::in_place_index_t<0>, Union&& u) noexcept
	{
		return bksge::forward<Union>(u).m_first.get();
	}

	template <bksge::size_t N, typename Union>
	static constexpr decltype(auto)
	get_impl(bksge::in_place_index_t<N>, Union&& u) noexcept
	{
		return get_impl(bksge::in_place_index_t<N-1>{}, bksge::forward<Union>(u).m_rest);
	}

	// Returns the typed storage for v.
	template <bksge::size_t N, typename Variant>
	static constexpr decltype(auto)
	get_impl(Variant&& v) noexcept
	{
		return get_impl(bksge::in_place_index_t<N>{}, bksge::forward<Variant>(v).m_u);
	}

	template <bksge::size_t N, typename Variant, typename... Args>
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
