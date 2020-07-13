﻿/**
 *	@file	iter_common_reference_t.hpp
 *
 *	@brief	iter_common_reference_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_COMMON_REFERENCE_T_HPP
#define BKSGE_FND_ITERATOR_ITER_COMMON_REFERENCE_T_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::indirectly_readable T
#else
	typename T,
	typename = bksge::enable_if_t<bksge::indirectly_readable_t<T>::value>
#endif
>
using iter_common_reference_t =
	bksge::common_reference_t<bksge::iter_reference_t<T>, bksge::iter_value_t<T>&>;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_COMMON_REFERENCE_T_HPP
