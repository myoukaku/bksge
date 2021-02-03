/**
 *	@file	do_message.hpp
 *
 *	@brief	do_message の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_DETAIL_DO_MESSAGE_HPP
#define BKSGE_FND_SYSTEM_ERROR_DETAIL_DO_MESSAGE_HPP

#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/string.hpp>

namespace bksge
{

namespace detail
{

class do_message
	: public error_category
{
public:
	virtual bksge::string message(int ev) const;
};

}	// namespace detail

}	// namespace bksge

#include <bksge/fnd/system_error/detail/do_message_inl.hpp>

#endif // BKSGE_FND_SYSTEM_ERROR_DETAIL_DO_MESSAGE_HPP
