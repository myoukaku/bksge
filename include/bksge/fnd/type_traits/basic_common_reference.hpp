/**
 *	@file	basic_common_reference.hpp
 *
 *	@brief	basic_common_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP


namespace bksge
{

template <
	typename T,
	typename U,
	template <typename> class TQual,
	template <typename> class UQual
>
struct basic_common_reference
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
