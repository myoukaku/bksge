/**
 *	@file	furlong.hpp
 *
 *	@brief	furlong の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_FURLONG_HPP
#define BKSGE_FND_UNITS_FURLONG_HPP

#include <bksge/fnd/units/foot.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 国際ハロン = 660フィート (正確に201.168m)
template <typename T> using furlong  = decltype(foot<T>() * std::ratio<660>());
template <typename T> using furlongs = furlong<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_FURLONG_HPP
