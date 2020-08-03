/**
 *	@file	regular.hpp
 *
 *	@brief	regular の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_REGULAR_HPP
#define BKSGE_FND_CONCEPTS_REGULAR_HPP

#include <bksge/fnd/concepts/semiregular.hpp>
#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept regular =
	bksge::semiregular<T> &&
	bksge::equality_comparable<T>;

#else

template <typename T>
using regular =
	bksge::conjunction<
		bksge::semiregular<T>,
		bksge::equality_comparable<T>
	>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_REGULAR_HPP
