/**
 *	@file	vector2.hpp
 *
 *	@brief	Vector2 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_VECTOR2_HPP
#define BKSGE_CORE_MATH_VECTOR2_HPP

#include <bksge/core/math/fwd/vector2_fwd.hpp>
#include <bksge/core/math/vector.hpp>
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
class Vector<T, 2> : public detail::VectorBase<T, 2>
{
private:
	using BaseType = detail::VectorBase<T, 2>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Vector() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	Vector(T const& x) BKSGE_NOEXCEPT
		: BaseType{x, x}
	{}

	/**
	 *	@brief	値2つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Vector(T const& v1, T const& v2) BKSGE_NOEXCEPT
		: BaseType{v1, v2}
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
	Vector(Vector<U, 2> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0]),
			static_cast<T>(rhs[1]),
		}
	{}

	/**
	 *	@brief	ゼロベクトルを作成します
	 */
	static BKSGE_CONSTEXPR Vector
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	BKSGE_CORE_MATH_NAMED_ACCESS(x, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(y, 1);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y));
};

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_VECTOR2_HPP
