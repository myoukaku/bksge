/**
 *	@file	vector4.hpp
 *
 *	@brief	Vector4 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_VECTOR4_HPP
#define BKSGE_CORE_MATH_VECTOR4_HPP

#include <bksge/core/math/fwd/vector4_fwd.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/core/math/vector3.hpp>
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
class Vector<T, 4> : public detail::VectorBase<T, 4>
{
private:
	using BaseType = detail::VectorBase<T, 4>;

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
		: BaseType{x, x, x, x}
	{}

	/**
	 *	@brief	値4つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Vector(T const& v1, T const& v2, T const& v3, T const& v4) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3, v4}
	{}

	/**
	 *	@brief	Vector3と値1つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Vector(Vector<T, 3> const& v1, T const& v2) BKSGE_NOEXCEPT
		: BaseType{v1[0], v1[1], v1[2], v2}
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
	Vector(Vector<U, 4> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0]),
			static_cast<T>(rhs[1]),
			static_cast<T>(rhs[2]),
			static_cast<T>(rhs[3]),
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
	BKSGE_CORE_MATH_NAMED_ACCESS(z, 2);
	BKSGE_CORE_MATH_NAMED_ACCESS(w, 3);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y)(z)(w));
};

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_VECTOR4_HPP
