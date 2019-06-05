﻿/**
 *	@file	hash_combine_inl.hpp
 *
 *	@brief	hash_combine 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FUNCTIONAL_INL_HASH_COMBINE_INL_HPP
#define BKSGE_FUNCTIONAL_INL_HASH_COMBINE_INL_HPP

#include <bksge/functional/hash_combine.hpp>
#include <bksge/config.hpp>
#include <cstddef>		// size_t
#include <functional>	// hash

namespace bksge
{

namespace detail
{

template <typename T>
inline std::size_t do_hash_combine(std::size_t seed, T const& v) BKSGE_NOEXCEPT
{
	return seed ^ (std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

inline std::size_t hash_combine_impl(std::size_t seed) BKSGE_NOEXCEPT
{
	return seed;
}

template <typename T, typename... Rest>
inline std::size_t hash_combine_impl(std::size_t seed, T const& v, Rest const&... rest) BKSGE_NOEXCEPT
{
	return hash_combine_impl(do_hash_combine(seed, v), rest...);
}

}	// namespace detail

template <typename RT, typename... T>
inline RT hash_combine(T const&... args) BKSGE_NOEXCEPT
{
	return detail::hash_combine_impl(0, args...);
}

}	// namespace bksge

#endif // BKSGE_FUNCTIONAL_INL_HASH_COMBINE_INL_HPP