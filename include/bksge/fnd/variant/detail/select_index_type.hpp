/**
 *	@file	select_index_type.hpp
 *
 *	@brief	select_index_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_SELECT_INDEX_TYPE_HPP
#define BKSGE_FND_VARIANT_DETAIL_SELECT_INDEX_TYPE_HPP

namespace bksge
{

namespace variant_detail
{

#if 1
template <typename... Types>
using select_index_type = unsigned short;
#else
template <typename... Types>
using select_index_type =
typename __select_int::_Select_int_base<sizeof...(Types),
	unsigned char,
	unsigned short>::type::value_type;
#endif

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_SELECT_INDEX_TYPE_HPP
