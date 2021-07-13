/**
 *	@file	do_visit.hpp
 *
 *	@brief	do_visit の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_DO_VISIT_HPP
#define BKSGE_FND_VARIANT_DETAIL_DO_VISIT_HPP

#include <bksge/fnd/variant/detail/gen_vtable.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename ResultType, typename Visitor, typename... Variants>
struct do_visit_t
{
	using vtable_type = decltype(variant_detail::GenVtable<
		ResultType, Visitor&&, Variants&&...>::s_vtable);

	using func_type = decltype(
		bksge::declval<vtable_type>().access(bksge::declval<Variants>().index()...));

	using result_type = decltype(
		(*bksge::declval<func_type>())(
			bksge::declval<Visitor>(),
			bksge::declval<Variants>()...));

	constexpr result_type operator()(Visitor&& visitor, Variants&&... variants) const
	{
		constexpr auto& vtable = variant_detail::GenVtable<
			ResultType, Visitor&&, Variants&&...>::s_vtable;
		auto func_ptr = vtable.access(variants.index()...);
		return (*func_ptr)(
			bksge::forward<Visitor>(visitor),
			bksge::forward<Variants>(variants)...);
	}
};

template <typename ResultType, typename Visitor, typename... Variants>
constexpr typename do_visit_t<ResultType, Visitor, Variants...>::result_type
do_visit(Visitor&& visitor, Variants&&... variants)
{
	return do_visit_t<ResultType, Visitor, Variants...>{}(
		bksge::forward<Visitor>(visitor),
		bksge::forward<Variants>(variants)...);
}

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_DO_VISIT_HPP
