/**
 *	@file	color3.hpp
 *
 *	@brief	Color3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_COLOR3_HPP
#define BKSGE_CORE_MATH_COLOR3_HPP

#include <bksge/core/math/fwd/color3_fwd.hpp>
#include <bksge/core/math/fwd/color_hsv_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/vector_rgba.hpp>
#include <bksge/core/math/color.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

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
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, U>::value
		>
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

#include <bksge/core/math/inl/color3_inl.hpp>

#endif // BKSGE_CORE_MATH_COLOR3_HPP
