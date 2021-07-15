/**
 *	@file	static_string.hpp
 *
 *	@brief	static_string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_STRING_STATIC_STRING_HPP
#define BKSGE_FND_STATIC_STRING_STATIC_STRING_HPP

#include <bksge/fnd/static_string/basic_static_string.hpp>
#include <cstddef>

namespace bksge
{

template <std::size_t Capacity>
using static_string = bksge::basic_static_string<char, Capacity>;

}	// namespace bksge

#endif // BKSGE_FND_STATIC_STRING_STATIC_STRING_HPP
