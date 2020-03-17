/**
 *	@file	visit.hpp
 *
 *	@brief	visit の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_VISIT_HPP
#define BKSGE_FND_VARIANT_VISIT_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::visit;

}	// namespace bksge

#else

#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

inline BKSGE_CONSTEXPR bool visit_valueless_check(void)
{
	return true;
}

template <typename Variant, typename... Vs>
inline BKSGE_CONSTEXPR bool visit_valueless_check(Variant&& v, Vs&&... vs)
{
	return v.valueless_by_exception() ?
		(throw_bad_variant_access(), false) :
		visit_valueless_check(bksge::forward<Vs>(vs)...);
}

}	// namespace variant_detail

/**
 *	@brief	variant に 処理を適用する
 */
template <typename Visitor, typename... Vs>
inline BKSGE_CONSTEXPR auto visit(Visitor&& visitor, Vs&&... vs)
->decltype(variant_detail::visitation::variant_t::visit_value(
			bksge::forward<Visitor>(visitor),
			bksge::forward<Vs>(vs)...))
{
	return
		variant_detail::visit_valueless_check(
			bksge::forward<Vs>(vs)...),
		variant_detail::visitation::variant_t::visit_value(
			bksge::forward<Visitor>(visitor),
			bksge::forward<Vs>(vs)...);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_VARIANT_VISIT_HPP
