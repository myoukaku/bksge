/**
 *	@file	iostream_category.hpp
 *
 *	@brief	iostream_category の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_IOS_IOSTREAM_CATEGORY_HPP
#define BKSGE_FND_IOS_IOSTREAM_CATEGORY_HPP

#include <bksge/fnd/system_error/config.hpp>

#if defined(BKSGE_USE_STD_SYSTEM_ERROR)

#include <ios>

namespace bksge
{

using std::iostream_category;

}	// namespace bksge

#else

#include <bksge/fnd/ios/io_errc.hpp>
#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/system_error/detail/do_message.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

class iostream_category_impl
	: public detail::do_message
{
public:
	virtual char const* name() const BKSGE_NOEXCEPT
	{
		return "iostream";
	}

	virtual bksge::string message(int ev) const
	{
		if (ev != static_cast<int>(bksge::io_errc::stream)
#ifdef _LIBCPP_ELAST
			&& ev <= _LIBCPP_ELAST
#endif  // _LIBCPP_ELAST
			)
		{
			return detail::do_message::message(ev);
		}

		return bksge::string("unspecified iostream_category error");
	}
};

}	// namespace detail

inline bksge::error_category const&
iostream_category() BKSGE_NOEXCEPT
{
	static detail::iostream_category_impl s;
	return s;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_IOS_IOSTREAM_CATEGORY_HPP
