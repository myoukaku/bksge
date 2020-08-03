/**
 *	@file	totally_ordered.hpp
 *
 *	@brief	totally_ordered の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_TOTALLY_ORDERED_HPP
#define BKSGE_FND_CONCEPTS_TOTALLY_ORDERED_HPP

#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/detail/partially_ordered_with.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept totally_ordered =
	bksge::equality_comparable<T> &&
	detail::partially_ordered_with<T, T>;

#else

template <typename T>
using totally_ordered =
	bksge::conjunction<
		bksge::equality_comparable<T>,
		detail::partially_ordered_with<T, T>
	>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_TOTALLY_ORDERED_HPP
