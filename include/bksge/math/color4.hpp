/**
 *	@file	color4.hpp
 *
 *	@brief	Color4 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_COLOR4_HPP
#define BKSGE_MATH_COLOR4_HPP

#include <bksge/math/fwd/color4_fwd.hpp>
#include <bksge/math/color.hpp>

#if 0
namespace bksge
{

namespace math
{

template <typename T>
class Color<T, 4>
	: public detail::VectorRGBA<T, 4>
{
private:
	using BaseType = detail::VectorRGBA<T, 4>;

public:
	// デフォルトコンストラクタ
	BKSGE_CONSTEXPR
	Color() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	template <typename U1, typename U2, typename U3, typename U4>
	BKSGE_CONSTEXPR
	Color(U1 const& r, U2 const& g, U3 const& b, U4 const& a) BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType(r, g, b, a)
	{}

	template <typename U>
	BKSGE_CONSTEXPR
	Color(Color<U, 4> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType(rhs.r(), rhs.g(), rhs.b(), rhs.a())
	{}

	/**
	 *	@brief	ゼロ初期化されたColorを作成します
	 */
	static BKSGE_CONSTEXPR Color
	Zero() BKSGE_NOEXCEPT
	{
		return Color{};
	}
};

}	// namespace math

}	// namespace bksge
#endif

#endif // BKSGE_MATH_COLOR4_HPP
