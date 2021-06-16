/**
 *	@file	tie.hpp
 *
 *	@brief	tie の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TIE_HPP
#define BKSGE_FND_TUPLE_TIE_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE)

namespace bksge
{

using std::tie;
using std::ignore;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename... Types>
inline BKSGE_CONSTEXPR bksge::tuple<Types&...>
tie(Types&... args) BKSGE_NOEXCEPT
{
	return bksge::tuple<Types&...>(args...);
}

namespace tuple_detail
{

struct swallow_assign
{
	template <typename T>
	BKSGE_CONSTEXPR swallow_assign const&
	operator=(T const&) const
	{
		return *this;
	}
};

}	// namespace tuple_detail

// ignore
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
tuple_detail::swallow_assign ignore{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TUPLE_TIE_HPP
