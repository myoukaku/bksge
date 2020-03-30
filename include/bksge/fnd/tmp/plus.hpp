/**
 *	@file	plus.hpp
 *
 *	@brief	plus クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_PLUS_HPP
#define BKSGE_FND_TMP_PLUS_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T lhs, T rhs>
struct plus
{
	static T const value = lhs + rhs;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_PLUS_HPP
