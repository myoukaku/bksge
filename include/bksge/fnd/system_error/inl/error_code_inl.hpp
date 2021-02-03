/**
 *	@file	error_code_inl.hpp
 *
 *	@brief	error_code の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CODE_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CODE_INL_HPP

#include <bksge/fnd/system_error/error_code.hpp>
#include <bksge/fnd/system_error/error_condition.hpp>
#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/system_error/system_category.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline
error_code::error_code() BKSGE_NOEXCEPT
	: m_val(0)
	, m_cat(&system_category())
{}

inline
error_code::error_code(int val, error_category const& cat) BKSGE_NOEXCEPT
	: m_val(val)
	, m_cat(&cat)
{}

template <typename E, typename>
inline
error_code::error_code(E e) BKSGE_NOEXCEPT
{
	*this = make_error_code(e);
}

inline void
error_code::assign(int val, error_category const& cat) BKSGE_NOEXCEPT
{
	m_val = val;
	m_cat = &cat;
}

template <typename E, typename>
inline error_code&
error_code::operator=(E e) BKSGE_NOEXCEPT
{
	*this = make_error_code(e);
	return *this;
}

inline void
error_code::clear() BKSGE_NOEXCEPT
{
	m_val = 0;
	m_cat = &system_category();
}

inline int
error_code::value() const BKSGE_NOEXCEPT
{
	return m_val;
}

inline error_category const&
error_code::category() const BKSGE_NOEXCEPT
{
	return *m_cat;
}

inline error_condition
error_code::default_error_condition() const BKSGE_NOEXCEPT
{
	return m_cat->default_error_condition(m_val);
}

inline bksge::string
error_code::message() const
{
	return m_cat->message(m_val);
}

inline
error_code::operator bool() const BKSGE_NOEXCEPT
{
	return m_val != 0;
}

inline bool
operator==(error_code const& lhs, error_code const& rhs) BKSGE_NOEXCEPT
{
	return
		lhs.category() == rhs.category() &&
		lhs.value() == rhs.value();
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
inline bksge::strong_ordering
operator<=>(error_code const& lhs, error_code const& rhs) BKSGE_NOEXCEPT
{
	if (auto c = lhs.category() <=> rhs.category(); c != 0)
	{
		return c;
	}
	return lhs.value() <=> rhs.value();
}
#else
inline bool
operator!=(error_code const& lhs, error_code const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

inline bool
operator<(error_code const& lhs, error_code const& rhs) BKSGE_NOEXCEPT
{
    return (lhs.category() < rhs.category()
	    || (lhs.category() == rhs.category()
		&& lhs.value() < rhs.value()));
}
#endif

inline bool
operator==(error_code const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT
{
	return
		lhs.category().equivalent(lhs.value(), rhs) ||
		rhs.category().equivalent(lhs, rhs.value());
}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
inline bool
operator!=(error_code const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

inline bool
operator==(error_condition const& lhs, error_code const& rhs) BKSGE_NOEXCEPT
{
	return rhs == lhs;
}

inline bool
operator!=(error_condition const& lhs, error_code const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}
#endif

template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(
	bksge::basic_ostream<CharT, Traits>& os,
	bksge::error_code const& ec)
{
	return os << ec.category().name() << ':' << ec.value();
}

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CODE_INL_HPP
