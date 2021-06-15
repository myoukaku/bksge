/**
 *	@file	error_category_inl.hpp
 *
 *	@brief	error_category の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CATEGORY_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CATEGORY_INL_HPP

#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/system_error/error_condition.hpp>
#include <bksge/fnd/system_error/error_code.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/compare/compare_three_way.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline
error_category::~error_category() BKSGE_NOEXCEPT
{
}

inline error_condition
error_category::default_error_condition(int ev) const BKSGE_NOEXCEPT
{
	return error_condition(ev, *this);
}

inline bool
error_category::equivalent(int code, error_condition const& condition) const BKSGE_NOEXCEPT
{
	return default_error_condition(code) == condition;
}

inline bool
error_category::equivalent(error_code const& code, int condition) const BKSGE_NOEXCEPT
{
	return *this == code.category() && code.value() == condition;
}

inline bool
error_category::operator==(error_category const& rhs) const BKSGE_NOEXCEPT
{
	return this == &rhs;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
inline bksge::strong_ordering
error_category::operator<=>(error_category const& rhs) const BKSGE_NOEXCEPT
{
	return bksge::compare_three_way()(this, &rhs);
}
#else
inline bool
error_category::operator!=(error_category const& rhs) const BKSGE_NOEXCEPT
{
	return !(*this == rhs);
}

inline bool
error_category::operator<(error_category const& rhs) const BKSGE_NOEXCEPT
{
	return bksge::less<error_category const*>()(this, &rhs);
}
#endif

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_INL_ERROR_CATEGORY_INL_HPP
