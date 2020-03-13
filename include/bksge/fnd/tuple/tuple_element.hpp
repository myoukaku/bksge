/**
 *	@file	tuple_element.hpp
 *
 *	@brief	tuple_element の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_ELEMENT_HPP
#define BKSGE_FND_TUPLE_TUPLE_ELEMENT_HPP

#include <cstddef>
#include <tuple>

namespace bksge
{

using std::tuple_element;

template <std::size_t I, typename T>
using tuple_element_t = typename tuple_element<I, T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_TUPLE_ELEMENT_HPP
