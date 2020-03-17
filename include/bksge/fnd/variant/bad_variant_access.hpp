/**
 *	@file	bad_variant_access.hpp
 *
 *	@brief	bad_variant_access の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_BAD_VARIANT_ACCESS_HPP
#define BKSGE_FND_VARIANT_BAD_VARIANT_ACCESS_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::bad_variant_access;

}	// namespace bksge

#else

#include <bksge/fnd/exception/exception.hpp>

namespace bksge
{

/**
 *	@brief	variantの無効な値にアクセスしたときに投げられる例外
 *
 *	bad_variant_access は以下の状況の時に投げられる例外である
 *	・get(variant)を有効でないインデックスや型で呼び出した
 *	・valueless_by_exception が true の variant に対して visit を呼び出した
 */
class bad_variant_access : public bksge::exception
{
public:
	virtual char const* what() const BKSGE_NOEXCEPT
	{
		return "bad_variant_access";
	}
};

}	// namespace bksge

#endif

#if defined(BKSGE_NO_EXCEPTIONS)
#include <cstdlib>	// abort
#endif

namespace bksge
{

BKSGE_NORETURN inline void
throw_bad_variant_access()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::bad_variant_access();
#else
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_BAD_VARIANT_ACCESS_HPP
