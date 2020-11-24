/**
 *	@file	never_valueless_alt.hpp
 *
 *	@brief	NeverValuelessAlt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_NEVER_VALUELESS_ALT_HPP
#define BKSGE_FND_VARIANT_DETAIL_NEVER_VALUELESS_ALT_HPP

#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>

namespace bksge
{

namespace variant_detail
{

// NeverValuelessAlt is true for variant alternatives that can
// always be placed in a variant without it becoming valueless.

// For suitably-small, trivially copyable types we can create temporaries
// on the stack and then memcpy them into place.
template <typename T>
struct NeverValuelessAlt
	: public bksge::conjunction<
		bksge::bool_constant<(sizeof(T) <= 256)>,
		bksge::is_trivially_copyable<T>
	>
{};

// Specialize NeverValuelessAlt for other types which have a
// non-throwing and cheap move construction and move assignment operator,
// so that emplacing the type will provide the strong exception-safety
// guarantee, by creating and moving a temporary.
// Whether NeverValuelessAlt<T> is true or not affects the ABI of a
// variant using that alternative, so we can't change the value later!

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_NEVER_VALUELESS_ALT_HPP
