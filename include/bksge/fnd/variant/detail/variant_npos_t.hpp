/**
 *	@file	variant_npos_t.hpp
 *
 *	@brief	variant_npos_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_NPOS_T_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_NPOS_T_HPP

namespace bksge
{

namespace variant_detail
{

template <typename IndexType>
struct variant_npos_t
{
	static auto const value = static_cast<IndexType>(-1);
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_NPOS_T_HPP
