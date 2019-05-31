/**
 *	@file	binary_expression.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_DEBUG_DETAIL_BINARY_EXPRESSION_HPP
#define BKSGE_DEBUG_DETAIL_BINARY_EXPRESSION_HPP

#include <bksge/debug/detail/binary_expression_fwd.hpp>
#include <bksge/debug/detail/expression_base.hpp>
#include <bksge/utility/forward.hpp>
#include <bksge/config.hpp>
#include <ostream>

namespace bksge
{

namespace debug
{

namespace detail
{

template <typename Lhs, typename Rhs, typename OP>
class binary_expression : public expression_base<binary_expression<Lhs, Rhs, OP>, typename OP::result_type>
{
public:
	using result_type = typename OP::result_type;

	BKSGE_CONSTEXPR binary_expression(binary_expression const& be)
		: m_lhs(be.m_lhs)
		, m_rhs(be.m_rhs)
	{
	}

	BKSGE_CONSTEXPR binary_expression(binary_expression&& be)
		: m_lhs(bksge::forward<Lhs>(be.m_lhs))
		, m_rhs(bksge::forward<Rhs>(be.m_rhs))
	{
	}

	BKSGE_CONSTEXPR binary_expression(Lhs&& lhs, Rhs&& rhs)
		: m_lhs(bksge::forward<Lhs>(lhs))
		, m_rhs(bksge::forward<Rhs>(rhs))
	{
	}

	BKSGE_CONSTEXPR binary_expression(Lhs const& lhs, Rhs const& rhs)
		: m_lhs(lhs)
		, m_rhs(rhs)
	{
	}

	BKSGE_CONSTEXPR char const* label(void) const
	{
		return OP::label();
	}

	BKSGE_CONSTEXPR Lhs const& lhs(void) const { return m_lhs; }
	BKSGE_CONSTEXPR Rhs const& rhs(void) const { return m_rhs; }

private:
	Lhs		m_lhs;
	Rhs		m_rhs;
};

template <typename CharT, typename Traits, typename Lhs, typename Rhs, typename OP>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, binary_expression<Lhs, Rhs, OP> const& rhs)
{
	return os << "(" << rhs.lhs() << " " << rhs.label() << " " << rhs.rhs() << ")";
}

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_DEBUG_DETAIL_BINARY_EXPRESSION_HPP
