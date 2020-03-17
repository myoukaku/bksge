/**
 *	@file	variant_index_t.hpp
 *
 *	@brief	variant_index_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_INDEX_T_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_INDEX_T_HPP

#include <bksge/fnd/type_traits/conditional.hpp>
#include <cstddef>
#include <limits>

namespace bksge
{

namespace variant_detail
{

template <std::size_t NumAlts>
using variant_index_t =
	bksge::conditional_t<(NumAlts < std::numeric_limits<unsigned char>::max()),  unsigned char,
	bksge::conditional_t<(NumAlts < std::numeric_limits<unsigned short>::max()), unsigned short,
	bksge::conditional_t<(NumAlts < std::numeric_limits<unsigned int>::max()),   unsigned int,
	                                                                             unsigned long long
>>>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_INDEX_T_HPP
