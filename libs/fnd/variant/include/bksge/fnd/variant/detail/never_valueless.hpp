/**
 *	@file	never_valueless.hpp
 *
 *	@brief	NeverValueless の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_NEVER_VALUELESS_HPP
#define BKSGE_FND_VARIANT_DETAIL_NEVER_VALUELESS_HPP

#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/variant/detail/never_valueless_alt.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>

namespace bksge
{

namespace variant_detail
{

// True if every alternative in Types... can be emplaced in a variant
// without it becoming valueless. If this is true, variant<Types...>
// can never be valueless, which enables some minor optimizations.
template <typename... Types>
struct NeverValueless
	: public bksge::bool_constant<
		variant_detail::VariantTraits<Types...>::s_move_assign &&
		bksge::conjunction<variant_detail::NeverValuelessAlt<Types>...>::value
	>
{};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_NEVER_VALUELESS_HPP
