/**
 *	@file	bad_optional_access.hpp
 *
 *	@brief	bad_optional_access の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
#define BKSGE_FND_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP

#include <bksge/fnd/optional/config.hpp>

#if defined(BKSGE_USE_STD_OPTIONAL)

#include <optional>

namespace bksge
{

using std::bad_optional_access;

}	// namespace bksge

#else

#include <exception>

namespace bksge
{

/**
 *  @brief Exception class thrown when a disengaged optional object is
 *  dereferenced.
 *  @ingroup exceptions
 */
class bad_optional_access : public std::exception
{
public:
	bad_optional_access() = default;
	virtual ~bad_optional_access() = default;

	char const* what() const BKSGE_NOEXCEPT override
	{
		return "bad optional access";
	}
};

}	// namespace bksge

#endif

#if defined(BKSGE_NO_EXCEPTIONS)
#include <bksge/fnd/cstdlib/abort.hpp>
#endif

namespace bksge
{

BKSGE_NORETURN inline
void throw_bad_optional_access()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::bad_optional_access();
#else
	bksge::abort();
#endif
}

}	// namespace bksge
#endif // BKSGE_FND_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
