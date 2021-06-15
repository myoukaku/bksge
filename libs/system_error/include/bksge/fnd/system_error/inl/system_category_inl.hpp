/**
 *	@file	system_category_inl.hpp
 *
 *	@brief	system_category の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_INL_SYSTEM_CATEGORY_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_INL_SYSTEM_CATEGORY_INL_HPP

#include <bksge/fnd/system_error/system_category.hpp>
#include <bksge/fnd/system_error/generic_category.hpp>
#include <bksge/fnd/system_error/error_condition.hpp>
#include <bksge/fnd/system_error/detail/do_message.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

class system_error_category
	: public do_message
{
public:
	virtual char const*
	name() const BKSGE_NOEXCEPT
	{
		return "system";
	}

	virtual bksge::string
	message(int ev) const
	{
		return do_message::message(ev);
	}

	virtual error_condition
	default_error_condition(int ev) const BKSGE_NOEXCEPT
	{
		return error_condition(ev, system_category());
	}
};

}	// namespace detail

inline error_category const&
system_category() BKSGE_NOEXCEPT
{
	static detail::system_error_category s;
	return s;
}

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_INL_SYSTEM_CATEGORY_INL_HPP
