/**
 *	@file	modulus.hpp
 *
 *	@brief	modulus クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_MODULUS_HPP
#define BKSGE_FND_TMP_MODULUS_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T lhs, T rhs>
struct modulus
{
	static T const value = lhs % rhs;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_MODULUS_HPP
