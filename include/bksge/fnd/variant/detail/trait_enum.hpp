/**
 *	@file	trait_enum.hpp
 *
 *	@brief	trait_enum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_TRAIT_ENUM_HPP
#define BKSGE_FND_VARIANT_DETAIL_TRAIT_ENUM_HPP

namespace bksge
{

namespace variant_detail
{

enum class trait_enum
{
	TriviallyAvailable,
	Available,
	Unavailable
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_TRAIT_ENUM_HPP
