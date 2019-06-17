/**
 *	@file	abs.hpp
 *
 *	@brief	abs クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TMP_ABS_HPP
#define BKSGE_TMP_ABS_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T x>
struct abs
{
	static T const value = x < 0 ? -x : x;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_TMP_ABS_HPP
