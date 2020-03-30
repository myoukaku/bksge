/**
 *	@file	max.hpp
 *
 *	@brief	max クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_MAX_HPP
#define BKSGE_FND_TMP_MAX_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T lhs, T rhs>
struct max
{
	static T const value = (lhs < rhs) ? rhs : lhs;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_MAX_HPP
