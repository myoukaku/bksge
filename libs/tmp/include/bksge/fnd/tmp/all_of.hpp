/**
 *	@file	all_of.hpp
 *
 *	@brief	all_of クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_ALL_OF_HPP
#define BKSGE_FND_TMP_ALL_OF_HPP

namespace bksge
{

namespace tmp
{

template <bool... Bs>
struct all_of;

template <>
struct all_of<>
{
	static bool const value = true;
};

template <bool B0, bool... Bs>
struct all_of<B0, Bs...>
{
	static bool const value = B0 && all_of<Bs...>::value;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_ALL_OF_HPP
