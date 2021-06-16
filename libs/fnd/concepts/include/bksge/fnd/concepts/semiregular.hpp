/**
 *	@file	semiregular.hpp
 *
 *	@brief	semiregular の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_SEMIREGULAR_HPP
#define BKSGE_FND_CONCEPTS_SEMIREGULAR_HPP

#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/default_initializable.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept semiregular =
	bksge::copyable<T> &&
	bksge::default_initializable<T>;

template <typename T>
using is_semiregular = bksge::bool_constant<semiregular<T>>;

#else

template <typename T>
using semiregular =
	bksge::conjunction<
		bksge::copyable<T>,
		bksge::default_initializable<T>
	>;

template <typename T>
using is_semiregular = semiregular<T>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_SEMIREGULAR_HPP
