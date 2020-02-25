/**
 *	@file	bad_optional_access.hpp
 *
 *	@brief	bad_optional_access の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
#define BKSGE_FND_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<optional>)
#include <optional>
#endif

#if defined(__cpp_lib_optional) && (__cpp_lib_optional >= 201606)

namespace bksge
{

using std::bad_optional_access;

}	// namespace bksge

#else

#include <exception>

namespace bksge
{

class bad_optional_access : public std::exception
{
public:
	bad_optional_access() BKSGE_NOEXCEPT
	{}

	char const* what() const BKSGE_NOEXCEPT override
	{
		return "bad optional access";
	}
};

}	// namespace bksge

#endif

#include <cstdlib>		// abort

namespace bksge
{

BKSGE_NORETURN inline
void throw_bad_optional_access()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::bad_optional_access();
#else
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
