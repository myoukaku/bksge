/**
 *	@file	color3.hpp
 *
 *	@brief	Color3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_COLOR3_HPP
#define BKSGE_MATH_COLOR3_HPP

#include <bksge/math/fwd/color3_fwd.hpp>
#include <bksge/math/color.hpp>

#if 0
namespace bksge
{

namespace math
{

template <typename T>
class Color<T, 3>
	: public detail::VectorRGBA<T, 3>
{
private:
	using BaseType = detail::VectorRGBA<T, 3>;

public:
	// デフォルトコンストラクタ
	BKSGE_CONSTEXPR
	Color() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	template <typename U1, typename U2, typename U3>
	BKSGE_CONSTEXPR
	Color(U1 const& r, U2 const& g, U3 const& b) BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType(r, g, b)
	{}

	template <typename U>
	BKSGE_CONSTEXPR
	Color(Color<U, 3> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType(rhs.r(), rhs.g(), rhs.b())
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

#endif // BKSGE_MATH_COLOR3_HPP
