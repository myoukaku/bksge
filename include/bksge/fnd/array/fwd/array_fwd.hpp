/**
 *	@file	array_fwd.hpp
 *
 *	@brief	array クラステンプレートの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ARRAY_FWD_ARRAY_FWD_HPP
#define BKSGE_FND_ARRAY_FWD_ARRAY_FWD_HPP

#include <bksge/fnd/array/config.hpp>

#if defined(BKSGE_USE_STD_ARRAY)

#include <array>

namespace bksge
{

using std::array;

}	// namespace bksge

#else

#include <cstddef>

namespace bksge
{

template <typename T, std::size_t N>
struct array;

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_ARRAY)

#endif // BKSGE_FND_ARRAY_FWD_ARRAY_FWD_HPP
