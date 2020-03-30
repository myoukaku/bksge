/**
 *	@file	any_of.hpp
 *
 *	@brief	any_of クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TMP_ANY_OF_HPP
#define BKSGE_FND_TMP_ANY_OF_HPP

namespace bksge
{

namespace tmp
{

template <bool... Bs>
struct any_of;

template <>
struct any_of<>
{
	static bool const value = false;
};

template <bool B0, bool... Bs>
struct any_of<B0, Bs...>
{
	static bool const value = B0 || any_of<Bs...>::value;
};

}	// namespace tmp

}	// namespace bksge

#endif // BKSGE_FND_TMP_ANY_OF_HPP
