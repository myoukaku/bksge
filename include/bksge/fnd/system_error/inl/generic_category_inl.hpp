/**
 *	@file	generic_category_inl.hpp
 *
 *	@brief	generic_category の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_INL_GENERIC_CATEGORY_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_INL_GENERIC_CATEGORY_INL_HPP

#include <bksge/fnd/system_error/generic_category.hpp>
#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/system_error/detail/do_message.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

class generic_error_category
	: public do_message
{
public:
	virtual char const*
	name() const BKSGE_NOEXCEPT
	{
		return "generic";
	}

	virtual bksge::string
	message(int ev) const
	{
		return do_message::message(ev);
	}
};

}	// namespace detail

inline error_category const&
generic_category() BKSGE_NOEXCEPT
{
	static detail::generic_error_category s;
	return s;
}

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_INL_GENERIC_CATEGORY_INL_HPP
