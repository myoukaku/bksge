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

namespace bksge
{

namespace variant_detail
{

template <typename ResultType, typename Visitor, typename... Variants>
constexpr decltype(auto)
do_visit(Visitor&& visitor, Variants&&... variants)
{
	constexpr auto& vtable = variant_detail::GenVtable<
		ResultType, Visitor&&, Variants&&...>::s_vtable;

	auto func_ptr = vtable.access(variants.index()...);
	return (*func_ptr)(bksge::forward<Visitor>(visitor), bksge::forward<Variants>(variants)...);
}

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_DO_VISIT_HPP
