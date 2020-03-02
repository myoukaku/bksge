﻿/**
 *	@file	color_hsv.hpp
 *
 *	@brief	ColorHSV の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_COLOR_HSV_HPP
#define BKSGE_CORE_MATH_COLOR_HSV_HPP

#include <bksge/core/math/fwd/color_hsv_fwd.hpp>
#include <bksge/core/math/fwd/color3_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/def_helper_macros.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <tuple>

namespace bksge
{

namespace math
{

template <typename T>
class ColorHSV
	: public detail::VectorBase<T, 3>
{
private:
	using BaseType = detail::VectorBase<T, 3>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	// デフォルトコンストラクタ
	BKSGE_CONSTEXPR
	ColorHSV() BKSGE_NOEXCEPT_OR_NOTHROW
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
	ColorHSV(ColorHSV<U> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	RGB から HSV への変換
	 */
	template <typename U>
	BKSGE_CXX14_CONSTEXPR
	explicit ColorHSV(Color3<U> const& rgb);

	/**
	 *	@brief	ゼロ初期化されたColorHSVを作成します
	 */
	static BKSGE_CONSTEXPR ColorHSV
	Zero() BKSGE_NOEXCEPT;

	BKSGE_CORE_MATH_NAMED_ACCESS(h, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(s, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(v, 2);
};

/**
 *	@brief	正規化されたColorHSVを作成します
 */
template <typename T>
BKSGE_CONSTEXPR ColorHSV<T>
Normalized(ColorHSV<T> const& hsv);

/**
 *	@brief	RGB から HSV への変換
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR ColorHSV<T>
RGBtoHSV(Color3<T> const& rgb);

/**
 *	@brief	HSV から RGB への変換
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR Color3<T>
HSVtoRGB(ColorHSV<T> const& hsv);

}	// namespace math

}	// namespace bksge

#include <functional>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T>
struct tuple_size<bksge::math::ColorHSV<T>>
	: public bksge::integral_constant<bksge::size_t, 3>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T>
struct tuple_element<I, bksge::math::ColorHSV<T>>
{
	static_assert(I < 3, "ColorHSV index out of bounds");
	using type = T;
};

/**
 *	@brief	hash
 */
template <typename T>
struct hash<bksge::math::ColorHSV<T>>
{
	bksge::size_t operator()(bksge::math::ColorHSV<T> const& arg) const
	{
		return bksge::hash_combine(arg.as_array());
	}
};

}	// namespace std

#include <bksge/core/math/inl/color_hsv_inl.hpp>
#include <bksge/core/math/detail/undef_helper_macros.hpp>

#endif // BKSGE_CORE_MATH_COLOR_HSV_HPP
