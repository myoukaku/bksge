/**
 *	@file	variant_cookie.hpp
 *
 *	@brief	VariantCookie の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_COOKIE_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_COOKIE_HPP

namespace bksge
{

namespace variant_detail
{

// used for raw visitation
struct VariantCookie {};

// used for raw visitation with indices passed in
struct VariantIdxCookie { using type = VariantIdxCookie; };

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_COOKIE_HPP
