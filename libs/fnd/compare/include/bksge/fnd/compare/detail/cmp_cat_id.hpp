/**
 *	@file	cmp_cat_id.hpp
 *
 *	@brief	cmp_cat_id の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_CMP_CAT_ID_HPP
#define BKSGE_FND_COMPARE_DETAIL_CMP_CAT_ID_HPP

#include <bksge/fnd/compare/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
struct cmp_cat_id
{
	static constexpr unsigned value = 1;
};

template <> struct cmp_cat_id<bksge::partial_ordering> { static constexpr unsigned value = 2; };
template <> struct cmp_cat_id<bksge::weak_ordering>    { static constexpr unsigned value = 4; };
template <> struct cmp_cat_id<bksge::strong_ordering>  { static constexpr unsigned value = 8; };

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
// * extension *
template <> struct cmp_cat_id<std::partial_ordering> { static constexpr unsigned value = 2; };
template <> struct cmp_cat_id<std::weak_ordering>    { static constexpr unsigned value = 4; };
template <> struct cmp_cat_id<std::strong_ordering>  { static constexpr unsigned value = 8; };
#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_CMP_CAT_ID_HPP
