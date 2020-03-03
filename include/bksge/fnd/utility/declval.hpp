/**
 *	@file	declval.hpp
 *
 *	@brief	declval を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_DECLVAL_HPP
#define BKSGE_FND_UTILITY_DECLVAL_HPP

#include <bksge/fnd/type_traits/add_rvalue_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T>
bksge::add_rvalue_reference_t<T>
declval() BKSGE_NOEXCEPT;

}	// namespace bksge

#endif // BKSGE_FND_UTILITY_DECLVAL_HPP
