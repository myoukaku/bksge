/**
 *	@file	system_error_inl.hpp
 *
 *	@brief	system_error の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_INL_SYSTEM_ERROR_INL_HPP
#define BKSGE_FND_SYSTEM_ERROR_INL_SYSTEM_ERROR_INL_HPP

#include <bksge/fnd/system_error/system_error.hpp>
#include <bksge/fnd/system_error/system_category.hpp>
#include <bksge/fnd/system_error/error_code.hpp>
#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

inline bksge::string
system_error::init(error_code const& ec, bksge::string what_arg)
{
	if (ec)
	{
		if (!what_arg.empty())
		{
			what_arg += ": ";
		}

		what_arg += ec.message();
	}

	return what_arg;
}

inline
system_error::system_error(error_code ec, bksge::string const& what_arg)
	: runtime_error(init(ec, what_arg))
	, m_ec(ec)
{
}

inline
system_error::system_error(error_code ec, char const* what_arg)
	: runtime_error(init(ec, what_arg))
	, m_ec(ec)
{
}

inline
system_error::system_error(error_code ec)
	: runtime_error(init(ec, ""))
	, m_ec(ec)
{
}

inline
system_error::system_error(int ev, error_category const& ecat, bksge::string const& what_arg)
	: runtime_error(init(error_code(ev, ecat), what_arg))
	, m_ec(error_code(ev, ecat))
{
}

inline
system_error::system_error(int ev, error_category const& ecat, char const* what_arg)
	: runtime_error(init(error_code(ev, ecat), what_arg))
	, m_ec(error_code(ev, ecat))
{
}

inline
system_error::system_error(int ev, error_category const& ecat)
	: runtime_error(init(error_code(ev, ecat), ""))
	, m_ec(error_code(ev, ecat))
{
}

inline
system_error::~system_error() BKSGE_NOEXCEPT
{
}

inline void
throw_system_error(int ev, char const* what_arg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw system_error(error_code(ev, system_category()), what_arg);
#else
	(void)ev;
	(void)what_arg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_SYSTEM_ERROR_INL_SYSTEM_ERROR_INL_HPP
