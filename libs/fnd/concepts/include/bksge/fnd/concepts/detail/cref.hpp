/**
 *	@file	cref.hpp
 *
 *	@brief	cref の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_CREF_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_CREF_HPP

#include <bksge/fnd/type_traits/remove_reference.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
using cref = const bksge::remove_reference_t<T>&;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DETAIL_CREF_HPP
