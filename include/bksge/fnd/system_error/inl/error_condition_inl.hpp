/**
 *	@file	error_condition_inl.hpp
 *
 *	@brief	error_condition の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CONDITION_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CONDITION_INL_HPP

#include <bksge/fnd/system_error/error_condition.hpp>
#include <bksge/fnd/system_error/error_code.hpp>
#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/system_error/generic_category.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline
error_condition::error_condition() BKSGE_NOEXCEPT
	: m_val(0)
	, m_cat(&generic_category())
{}

inline
error_condition::error_condition(int val, error_category const& cat) BKSGE_NOEXCEPT
	: m_val(val)
	, m_cat(&cat)
{}

template <typename E, typename>
inline
error_condition::error_condition(E e) BKSGE_NOEXCEPT
{
	*this = make_error_condition(e);
}

inline void
error_condition::assign(int val, error_category const& cat) BKSGE_NOEXCEPT
{
	m_val = val;
	m_cat = &cat;
}

template <typename E, typename>
inline error_condition&
error_condition::operator=(E e) BKSGE_NOEXCEPT
{
	*this = make_error_condition(e);
	return *this;
}

inline void
error_condition::clear() BKSGE_NOEXCEPT
{
	m_val = 0;
	m_cat = &generic_category();
}

inline int
error_condition::value() const BKSGE_NOEXCEPT
{
	return m_val;
}

inline error_category const&
error_condition::category() const BKSGE_NOEXCEPT
{
	return *m_cat;
}

inline bksge::string
error_condition::message() const
{
	return m_cat->message(m_val);
}

inline
error_condition::operator bool() const BKSGE_NOEXCEPT
{
	return m_val != 0;
}

inline bool
operator==(error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT
{
	return lhs.category() == rhs.category() &&
		lhs.value() == rhs.value();
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
inline bksge::strong_ordering
operator<=>(error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT
{
	if (auto c = lhs.category() <=> rhs.category(); c != 0)
	{
		return c;
	}
	return lhs.value() <=> rhs.value();
}
#else
inline bool
operator!=(error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

inline bool
operator<(error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT
{
	return lhs.category() < rhs.category() ||
		(lhs.category() == rhs.category() && lhs.value() < rhs.value());
}
#endif

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CONDITION_INL_HPP
