/**
 *	@file	tuple_cmp.hpp
 *
 *	@brief	tuple_cmp_eq, tuple_cmp_3way, tuple_cmp_less の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_TUPLE_CMP_HPP
#define BKSGE_FND_TUPLE_DETAIL_TUPLE_CMP_HPP

#include <bksge/fnd/compare/detail/synth3way.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace tuple_detail
{

template <typename T, typename U>
inline BKSGE_CONSTEXPR bool
tuple_cmp_eq(T const&, U const&, bksge::index_sequence<>)
{
	return true;
}

template <typename T, typename U,
	std::size_t I, std::size_t... Indices>
inline BKSGE_CONSTEXPR bool
tuple_cmp_eq(T const& t, U const& u, bksge::index_sequence<I, Indices...>)
{
	return bool(bksge::get<I>(t) == bksge::get<I>(u)) &&
		tuple_cmp_eq(t, u, bksge::index_sequence<Indices...>());
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename Cat, typename T, typename U>
inline BKSGE_CONSTEXPR Cat
tuple_cmp_3way(T const&, U const&, bksge::index_sequence<>)
{
	return Cat::equivalent;
}

template <typename Cat, typename T, typename U,
	std::size_t I, std::size_t... Indices>
inline BKSGE_CONSTEXPR Cat
tuple_cmp_3way(T const& t, U const& u, bksge::index_sequence<I, Indices...>)
{
	auto c = bksge::detail::synth3way(bksge::get<I>(t), bksge::get<I>(u));
	if (c != 0)
	{
		return c;
	}
	return tuple_cmp_3way<Cat>(t, u, bksge::index_sequence<Indices...>());
}

#else

template <typename T, typename U>
inline BKSGE_CONSTEXPR bool
tuple_cmp_less(T const&, U const&, bksge::index_sequence<>)
{
	return false;
}

template <typename T, typename U,
	std::size_t I, std::size_t... Indices>
inline BKSGE_CONSTEXPR bool
tuple_cmp_less(T const& t, U const& u, bksge::index_sequence<I, Indices...>)
{
	return
		  bool(bksge::get<I>(t) < bksge::get<I>(u)) ||
		(!bool(bksge::get<I>(u) < bksge::get<I>(t)) &&
		tuple_cmp_less(t, u, bksge::index_sequence<Indices...>()));
}

#endif

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_TUPLE_CMP_HPP
