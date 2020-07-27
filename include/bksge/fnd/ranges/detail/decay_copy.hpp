/**
 *	@file	decay_copy.hpp
 *
 *	@brief	decay_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_DECAY_COPY_HPP
#define BKSGE_FND_RANGES_DETAIL_DECAY_COPY_HPP

#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/is_nothrow_convertible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename T>
BKSGE_CONSTEXPR bksge::decay_t<T>
decay_copy(T&& t)
BKSGE_NOEXCEPT_IF((bksge::is_nothrow_convertible<T, bksge::decay_t<T>>::value))
{
	return bksge::forward<T>(t);
}

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_DECAY_COPY_HPP
