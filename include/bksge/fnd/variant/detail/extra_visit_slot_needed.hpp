/**
 *	@file	extra_visit_slot_needed.hpp
 *
 *	@brief	extra_visit_slot_needed の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_EXTRA_VISIT_SLOT_NEEDED_HPP
#define BKSGE_FND_VARIANT_DETAIL_EXTRA_VISIT_SLOT_NEEDED_HPP

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/variant/detail/never_valueless.hpp>
#include <bksge/fnd/variant/detail/variant_cookie.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename>
struct VariantNeverValueless;

template <typename... Types>
struct VariantNeverValueless<variant<Types...>>
	: public variant_detail::NeverValueless<Types...> {};

template <typename MaybeVariantCookie, typename Variant>
struct extra_visit_slot_needed
	: public bksge::bool_constant<
		(bksge::is_same<MaybeVariantCookie, variant_detail::VariantCookie>::value ||
		 bksge::is_same<MaybeVariantCookie, variant_detail::VariantIdxCookie>::value) &&
		!VariantNeverValueless<bksge::remove_cvref_t<Variant>>::value
	>
{};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_EXTRA_VISIT_SLOT_NEEDED_HPP
