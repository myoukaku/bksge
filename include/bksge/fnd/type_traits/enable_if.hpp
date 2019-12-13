/**
 *	@file	enable_if.hpp
 *
 *	@brief	enable_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ENABLE_IF_HPP
#define BKSGE_FND_TYPE_TRAITS_ENABLE_IF_HPP

#include <type_traits>

namespace bksge
{

using std::enable_if;

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B,T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ENABLE_IF_HPP
