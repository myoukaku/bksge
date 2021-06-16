/**
 *	@file	divides.hpp
 *
 *	@brief	divides クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_DIVIDES_HPP
#define BKSGE_FND_TMP_DIVIDES_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T lhs, T rhs>
struct divides
{
	static T const value = lhs / rhs;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_DIVIDES_HPP
