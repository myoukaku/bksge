/**
 *	@file	color_hsv.hpp
 *
 *	@brief	ColorHSV の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_COLOR_HSV_HPP
#define BKSGE_CORE_MATH_COLOR_HSV_HPP

#include <bksge/core/math/fwd/color_hsv_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/swizzle_operator.hpp>
#include <bksge/core/math/detail/rgb_to_hsv.hpp>
#include <bksge/core/math/detail/hsv_to_rgb.hpp>
#include <bksge/core/math/color3.hpp>
#include <bksge/fnd/cmath/clamp.hpp>
#include <bksge/fnd/cmath/fmod.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class ColorHSV : public detail::VectorBase<T, 3>
{
private:
	using BaseType = detail::VectorBase<T, 3>;
	
public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	ColorHSV() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	ColorHSV(T const& h, T const& s, T const& v) BKSGE_NOEXCEPT
		: BaseType{h, s, v}
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
	ColorHSV(ColorHSV<U> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0]),
			static_cast<T>(rhs[1]),
			static_cast<T>(rhs[2]),
		}
	{}

	/**
	 *	@brief	RGB から HSV への変換
	 */
	BKSGE_CXX14_CONSTEXPR
	explicit ColorHSV(Color3<T> const& rgb)
		: ColorHSV(detail::rgb_to_hsv(rgb))
	{}

	/**
	 *	@brief	HSV から RGB への変換
	 */
	BKSGE_CXX14_CONSTEXPR
	explicit operator Color3<T>() const
	{
		return detail::hsv_to_rgb(*this);
	}

	/**
	 *	@brief	ゼロ初期化されたColorHSVを作成します
	 */
	static BKSGE_CONSTEXPR ColorHSV
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	BKSGE_CORE_MATH_NAMED_ACCESS(h, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(s, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(v, 2);
};

/**
 *	@brief	正規化されたColorHSVを作成します
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR ColorHSV<T>
Normalized(ColorHSV<T> const& hsv)
{
	auto const h = bksge::fmod(hsv.h(), T(1));
	return
	{
		h < 0 ? h + T(1) : h,
		bksge::clamp(hsv.s(), T(0), T(1)),
		bksge::clamp(hsv.v(), T(0), T(1)),
	};
}

}	// namespace math

}	// namespace bksge

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <cstddef>

namespace BKSGE_TUPLE_NAMESPACE
{

/**
 *	@brief	tuple_size
 */
template <typename T>
struct tuple_size<bksge::math::ColorHSV<T>>
	: public tuple_size<bksge::math::detail::VectorBase<T, 3>>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T>
struct tuple_element<I, bksge::math::ColorHSV<T>>
	: public tuple_element<I, bksge::math::detail::VectorBase<T, 3>>
{};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <functional>

namespace std
{

/**
 *	@brief	hash
 */
template <typename T>
struct hash<bksge::math::ColorHSV<T>>
	: public hash<bksge::math::detail::VectorBase<T, 3>>
{};

}	// namespace std

#endif // BKSGE_CORE_MATH_COLOR_HSV_HPP
