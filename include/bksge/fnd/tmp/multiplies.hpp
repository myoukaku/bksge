/**
 *	@file	multiplies.hpp
 *
 *	@brief	multiplies クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_MULTIPLIES_HPP
#define BKSGE_FND_TMP_MULTIPLIES_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T lhs, T rhs>
struct multiplies
{
	static T const value = lhs * rhs;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_MULTIPLIES_HPP
