/**
 *	@file	hash_combine_inl.hpp
 *
 *	@brief	hash_combine 関数テンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_INL_HASH_COMBINE_INL_HPP
#define BKSGE_FND_FUNCTIONAL_INL_HASH_COMBINE_INL_HPP

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline bksge::size_t
do_hash_combine(bksge::size_t seed, T const& v) BKSGE_NOEXCEPT
{
	return seed ^ (bksge::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

inline bksge::size_t
hash_combine_impl(bksge::size_t seed) BKSGE_NOEXCEPT
{
	return seed;
}

template <typename T, typename... Rest>
inline bksge::size_t
hash_combine_impl(bksge::size_t seed, T const& v, Rest const&... rest) BKSGE_NOEXCEPT
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

#endif // BKSGE_FND_FUNCTIONAL_INL_HASH_COMBINE_INL_HPP
