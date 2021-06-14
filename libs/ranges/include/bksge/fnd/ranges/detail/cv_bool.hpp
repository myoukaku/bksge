/**
 *	@file	cv_bool.hpp
 *
 *	@brief	cv_bool の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_CV_BOOL_HPP
#define BKSGE_FND_RANGES_DETAIL_CV_BOOL_HPP

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept cv_bool = bksge::same_as<const volatile T, const volatile bool>;

#else

template <typename T>
using cv_bool = bksge::same_as<const volatile T, const volatile bool>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_CV_BOOL_HPP
