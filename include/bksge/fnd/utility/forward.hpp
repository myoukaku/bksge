/**
 *	@file	forward.hpp
 *
 *	@brief	forward を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_FORWARD_HPP
#define BKSGE_FND_UTILITY_FORWARD_HPP

#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	forward
 *
 *	std::forwardはC++14以降でないとconstexpr指定されていないが、
 *	C++11の範囲内でconstexpr関数の要件を満たすことができる。
 *	規格上での非constexpr関数を、標準ライブラリの実装がconstexpr関数とすることは
 *	規格違反なので、自前で実装する必要がある。
 *	参照： http://boleros.hateblo.jp/entry/20131019/1382192721
 */
template <typename T>
inline BKSGE_CONSTEXPR T&&
forward(bksge::remove_reference_t<T>& t) BKSGE_NOEXCEPT
{
	return static_cast<T&&>(t);
}

/**
 *	@brief	forward
 *
 *	規格上のforwardではrvalueを取る形も定義されるが、
 *	通常のPerfect Forwardに使う限りでは必要ないので、明示的にdeleted指定する。
 *	参照： http://d.hatena.ne.jp/gintenlabo/20120226/1330273493
 *
 *	sprout::forwardでもrvalueを取る形はdeleted指定されている。
 *	https://github.com/bolero-MURAKAMI/Sprout/blob/master/sprout/utility/forward.hpp
 */
template <typename T>
inline BKSGE_CONSTEXPR T&&
forward(bksge::remove_reference_t<T>&& t) BKSGE_NOEXCEPT = delete;

}	// namespace bksge

#endif // BKSGE_FND_UTILITY_FORWARD_HPP
