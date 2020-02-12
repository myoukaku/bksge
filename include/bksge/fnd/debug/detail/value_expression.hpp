/**
 *	@file	value_expression.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEBUG_DETAIL_VALUE_EXPRESSION_HPP
#define BKSGE_FND_DEBUG_DETAIL_VALUE_EXPRESSION_HPP

#include <bksge/fnd/debug/detail/value_expression_fwd.hpp>
#include <bksge/fnd/debug/detail/expression_base.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <ostream>

namespace bksge
{

namespace debug
{

namespace detail
{

template <typename T>
class value_expression : public expression_base<value_expression<T>, bksge::remove_reference_t<T>>
{
public:
	BKSGE_CONSTEXPR value_expression(value_expression&& ve)
		: m_value(bksge::forward<T>(ve.m_value))
	{
	}

	BKSGE_CONSTEXPR value_expression(value_expression const& ve)
		: m_value(ve.m_value)
	{
	}

	explicit BKSGE_CONSTEXPR value_expression(T&& val)
		: m_value(bksge::forward<T>(val))
	{
	}

	value_expression& operator=(value_expression const&) = delete;

	BKSGE_CONSTEXPR T const& value(void) const { return m_value; }

private:
	T		m_value;
};

template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, value_expression<T> const& rhs)
{
	return os << rhs.value();
}

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, value_expression<std::nullptr_t> const& /*rhs*/)
{
	return os << "nullptr";
}

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_FND_DEBUG_DETAIL_VALUE_EXPRESSION_HPP
