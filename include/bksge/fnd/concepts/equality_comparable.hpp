/**
 *	@file	equality_comparable.hpp
 *
 *	@brief	equality_comparable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_EQUALITY_COMPARABLE_HPP
#define BKSGE_FND_CONCEPTS_EQUALITY_COMPARABLE_HPP

#include <bksge/fnd/concepts/detail/weakly_eq_cmp_with.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept equality_comparable = detail::weakly_eq_cmp_with<T, T>;

#else

template <typename T>
using equality_comparable = detail::weakly_eq_cmp_with<T, T>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_EQUALITY_COMPARABLE_HPP
