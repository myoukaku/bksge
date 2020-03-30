/**
 *	@file	minus.hpp
 *
 *	@brief	minus クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_MINUS_HPP
#define BKSGE_FND_TMP_MINUS_HPP

namespace bksge
{

namespace tmp
{

template <typename T, T lhs, T rhs>
struct minus
{
	static T const value = lhs - rhs;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_MINUS_HPP
