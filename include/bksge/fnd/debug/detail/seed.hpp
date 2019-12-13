/**
 *	@file	seed.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEBUG_DETAIL_SEED_HPP
#define BKSGE_FND_DEBUG_DETAIL_SEED_HPP

#include <bksge/fnd/debug/detail/value_expression.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace debug
{

namespace detail
{

class seed
{
public:
	// ->* is highest precedence left to right operator
	template <typename T>
	BKSGE_CONSTEXPR value_expression<T>
	operator->*(T&& v) const
	{
		return value_expression<T>(bksge::forward<T>(v));
	}
};

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_FND_DEBUG_DETAIL_SEED_HPP
