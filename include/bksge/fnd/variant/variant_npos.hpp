/**
 *	@file	variant_npos.hpp
 *
 *	@brief	variant_npos の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_VARIANT_NPOS_HPP
#define BKSGE_FND_VARIANT_VARIANT_NPOS_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::variant_npos;

}	// namespace bksge

#else

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	variantの無効なインデックスを表す
 */
BKSGE_INLINE_VAR BKSGE_CONSTEXPR bksge::size_t
	variant_npos = static_cast<bksge::size_t>(-1);

}	// namespace bksge

#endif

#endif // BKSGE_FND_VARIANT_VARIANT_NPOS_HPP
