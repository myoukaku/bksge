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
#include <bksge/math/fwd/color_hsv_fwd.hpp>
#include <bksge/math/detail/vector_base.hpp>
#include <bksge/math/detail/vector_rgba.hpp>
#include <bksge/math/color.hpp>
#include <bksge/config.hpp>
#include <type_traits>

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
	// 継承コンストラクタ
	using BaseType::BaseType;

	// デフォルトコンストラクタ
	BKSGE_CONSTEXPR
	Color() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	/**
	 *	@brief	変換コンストラクタ
	 */
	template <
		typename U,
		typename = typename std::enable_if<
			std::is_constructible<T, U>::value
		>::type
	>
	BKSGE_CONSTEXPR
	Color(Color<U, 3> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	HSV から RGB への変換
	 */
	template <typename U>
	BKSGE_CXX14_CONSTEXPR
	explicit Color(ColorHSV<U> const& hsv);

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

#include <bksge/math/inl/color3_inl.hpp>

#endif // BKSGE_MATH_COLOR3_HPP
