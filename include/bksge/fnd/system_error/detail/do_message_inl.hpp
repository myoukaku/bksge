/**
 *	@file	do_message_inl.hpp
 *
 *	@brief	do_message の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_DETAIL_DO_MESSAGE_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_DETAIL_DO_MESSAGE_INL_HPP

#include <bksge/fnd/system_error/detail/do_message.hpp>
//#include <bksge/fnd/cstdio/snprintf.hpp>
#include <cstdio>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if !defined(BKSGE_NO_THREADS)

namespace
{

//  GLIBC also uses 1024 as the maximum buffer size internally.
constexpr bksge::size_t strerror_buff_size = 1024;

bksge::string do_strerror_r(int ev);

#if 1//defined(_MSC_VER)

inline bksge::string do_strerror_r(int ev)
{
	char buffer[strerror_buff_size];

	if (::strerror_s(buffer, strerror_buff_size, ev) == 0)
	{
		return bksge::string(buffer);
	}
	
	std::snprintf(buffer, strerror_buff_size, "unknown error %d", ev);
	return bksge::string(buffer);
}

#else

// Only one of the two following functions will be used, depending on
// the return type of strerror_r:

// For the GNU variant, a char* return value:
__attribute__((unused)) char const*
handle_strerror_r_return(char *strerror_return, char* buffer)
{
	// GNU always returns a bksge::string pointer in its return value. The
	// bksge::string might point to either the input buffer, or a static
	// buffer, but we don't care which.
	return strerror_return;
}

// For the POSIX variant: an int return value.
__attribute__((unused)) char const*
handle_strerror_r_return(int strerror_return, char* buffer)
{
	// The POSIX variant either:
	// - fills in the provided buffer and returns 0
	// - returns a positive error value, or
	// - returns -1 and fills in errno with an error value.
	if (strerror_return == 0)
	{
		return buffer;
	}

	// Only handle EINVAL. Other errors abort.
	int new_errno = strerror_return == -1 ? errno : strerror_return;
	if (new_errno == EINVAL)
	{
		return "";
	}

	BKSGE_ASSERT(new_errno == ERANGE, "unexpected error from ::strerror_r");
	// FIXME maybe? 'strerror_buff_size' is likely to exceed the
	// maximum error size so ERANGE shouldn't be returned.
	bksge::abort();
}

// This function handles both GNU and POSIX variants, dispatching to
// one of the two above functions.
bksge::string do_strerror_r(int ev)
{
	char buffer[strerror_buff_size];
	// Preserve errno around the call. (The C++ standard requires that
	// system_error functions not modify errno).
	const int old_errno = errno;
	char const* error_message = handle_strerror_r_return(
		::strerror_r(ev, buffer, strerror_buff_size), buffer);

	// If we didn't get any message, print one now.
	if (!error_message[0])
	{
		bksge::snprintf(buffer, strerror_buff_size, "Unknown error %d", ev);
		error_message = buffer;
	}

	errno = old_errno;
	return bksge::string(error_message);
}

#endif

}	// namespace

#endif

inline bksge::string
do_message::message(int ev) const
{
#if defined(BKSGE_NO_THREADS)
	return bksge::string(::strerror(ev));
#else
	return do_strerror_r(ev);
#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_DETAIL_DO_MESSAGE_INL_HPP
