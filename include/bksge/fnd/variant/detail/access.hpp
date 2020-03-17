/**
 *	@file	access.hpp
 *
 *	@brief	access の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_ACCESS_HPP
#define BKSGE_FND_VARIANT_DETAIL_ACCESS_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

namespace access
{

template <std::size_t I>
struct get_alt_impl
{
	template <typename V>
	static BKSGE_CONSTEXPR auto get(V&& v)
	->decltype(get_alt_impl<I - 1>::get(bksge::forward<V>(v).m_tail))
	{
		return get_alt_impl<I - 1>::get(bksge::forward<V>(v).m_tail);
	}
};

template <>
struct get_alt_impl<0>
{
	template <typename V>
	static BKSGE_CONSTEXPR auto get(V&& v)
	->decltype((bksge::forward<V>(v).m_head))
	{
		return bksge::forward<V>(v).m_head;
	}
};

struct union_t
{
	template <typename V, std::size_t I>
	static BKSGE_CONSTEXPR auto
	get_alt(V&& v, bksge::in_place_index_t<I>)
	->decltype(get_alt_impl<I>::get(bksge::forward<V>(v)))
	{
		return get_alt_impl<I>::get(bksge::forward<V>(v));
	}
};

struct base_t
{
	template <std::size_t I, typename V>
	static BKSGE_CONSTEXPR auto get_alt(V&& v)
	->decltype(union_t::get_alt(bksge::forward<V>(v).m_data, bksge::in_place_index_t<I>{}))
	{
		return union_t::get_alt(bksge::forward<V>(v).m_data, bksge::in_place_index_t<I>{});
	}
};

struct variant_t
{
	template <std::size_t I, typename V>
	static BKSGE_CONSTEXPR auto get_alt(V&& v)
	->decltype(base_t::get_alt<I>(bksge::forward<V>(v).m_impl))
	{
		return base_t::get_alt<I>(bksge::forward<V>(v).m_impl);
	}
};

}	// namespace access

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_ACCESS_HPP
