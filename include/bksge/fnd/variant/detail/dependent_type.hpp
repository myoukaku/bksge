/**
 *	@file	dependent_type.hpp
 *
 *	@brief	dependent_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_DEPENDENT_TYPE_HPP
#define BKSGE_FND_VARIANT_DETAIL_DEPENDENT_TYPE_HPP

namespace bksge
{

namespace variant_detail
{

template <typename T, bool>
struct dependent_type : public T {};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_DEPENDENT_TYPE_HPP
