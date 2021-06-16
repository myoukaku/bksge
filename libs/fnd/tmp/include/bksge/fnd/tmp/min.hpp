/**
 *	@file	min.hpp
 *
 *	@brief	min クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_MIN_HPP
#define BKSGE_FND_TMP_MIN_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T lhs, T rhs>
struct min
{
	static T const value = (lhs < rhs) ? lhs : rhs;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_MIN_HPP
