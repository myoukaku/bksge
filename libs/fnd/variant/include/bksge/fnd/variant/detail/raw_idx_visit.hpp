/**
 *	@file	raw_idx_visit.hpp
 *
 *	@brief	raw_idx_visit の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_RAW_IDX_VISIT_HPP
#define BKSGE_FND_VARIANT_DETAIL_RAW_IDX_VISIT_HPP

#include <bksge/fnd/variant/detail/do_visit.hpp>
#include <bksge/fnd/variant/detail/variant_cookie.hpp>
#include <bksge/fnd/utility/forward.hpp>

namespace bksge
{

namespace variant_detail
{

// Visit variants that might be valueless, passing indices to the visitor.
template <typename Visitor, typename... Variants>
inline BKSGE_CXX14_CONSTEXPR void
raw_idx_visit(Visitor&& visitor, Variants&&... variants)
{
	variant_detail::do_visit<variant_detail::VariantIdxCookie>(
		bksge::forward<Visitor>(visitor),
		bksge::forward<Variants>(variants)...);
}

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_RAW_IDX_VISIT_HPP
