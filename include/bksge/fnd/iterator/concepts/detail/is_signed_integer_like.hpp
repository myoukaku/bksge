/**
 *	@file	is_signed_integer_like.hpp
 *
 *	@brief	is_signed_integer_like の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP

#include <bksge/fnd/concepts/signed_integral.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept is_signed_integer_like = bksge::signed_integral<T>;

#else

template <typename T>
using is_signed_integer_like = bksge::signed_integral<T>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP
