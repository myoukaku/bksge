/**
 *	@file	nan.hpp
 *
 *	@brief	nan 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_NAN_HPP
#define BKSGE_FND_CMATH_NAN_HPP

#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

/**
 *	@brief	文字列から quiet NaN へ変換する。
 *
 *	@param	arg		NaNの中身を判別するための文字列
 *
 *	@return	シグナルを発生させないNaNを返す。利用可能であれば、argを通じた内容を付加する。
 */
inline float
nanf(const char* arg) BKSGE_NOEXCEPT
{
	return std::nanf(arg);
}

inline double
nan(const char* arg) BKSGE_NOEXCEPT
{
	return std::nan(arg);
}

inline long double
nanl(const char* arg) BKSGE_NOEXCEPT
{
	return std::nanl(arg);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_NAN_HPP
