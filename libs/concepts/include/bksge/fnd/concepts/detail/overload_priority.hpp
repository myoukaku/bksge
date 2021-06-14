/**
 *	@file	overload_priority.hpp
 *
 *	@brief	overload_priority の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_OVERLOAD_PRIORITY_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_OVERLOAD_PRIORITY_HPP

#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace detail
{

template <bksge::size_t N>
struct overload_priority : public overload_priority<N - 1>
{};

template <>
struct overload_priority<0>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DETAIL_OVERLOAD_PRIORITY_HPP
