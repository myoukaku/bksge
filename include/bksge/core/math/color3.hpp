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
#include <bksge/core/math/color.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/swizzle_operator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Color<T, 3> : public detail::VectorBase<T, 3>
{
private:
	using BaseType = detail::VectorBase<T, 3>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Color() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	Color(T const& x) BKSGE_NOEXCEPT
		: BaseType{x, x, x}
	{}

	/**
	 *	@brief	値3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Color(T const& v1, T const& v2, T const& v3) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3}
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
	Color(Color<U, 3> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0] * detail::color_scale<T>::get() / detail::color_scale<U>::get()),
			static_cast<T>(rhs[1] * detail::color_scale<T>::get() / detail::color_scale<U>::get()),
			static_cast<T>(rhs[2] * detail::color_scale<T>::get() / detail::color_scale<U>::get()),
		}
	{}

	/**
	 *	@brief	ゼロ初期化されたColorを作成します
	 */
	static BKSGE_CONSTEXPR Color
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	BKSGE_CORE_MATH_NAMED_ACCESS(r, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(g, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(b, 2);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((r)(g)(b));
};

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_COLOR3_HPP
