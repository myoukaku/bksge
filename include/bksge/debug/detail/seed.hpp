/**
 *	@file	seed.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_DEBUG_DETAIL_SEED_HPP
#define BKSGE_DEBUG_DETAIL_SEED_HPP

#include <bksge/debug/detail/value_expression.hpp>
#include <bksge/config.hpp>
#include <utility>

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
		return value_expression<T>(std::forward<T>(v));
	}
};

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_DEBUG_DETAIL_SEED_HPP
