﻿/**
 *	@file	matrix4x3.hpp
 *
 *	@brief	Matrix4x3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_MATRIX4X3_HPP
#define BKSGE_CORE_MATH_MATRIX4X3_HPP

#include <bksge/core/math/fwd/matrix4x3_fwd.hpp>
#include <bksge/core/math/matrix.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Matrix<T, 4, 3> : public Vector<Vector<T, 3>, 4>
{
private:
	using BaseType = Vector<Vector<T, 3>, 4>;
	using VectorType = Vector<T, 3>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	Matrix(T const& x) BKSGE_NOEXCEPT
		: BaseType{VectorType{x}}
	{}

	/**
	 *	@brief	Vector3 4つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix(VectorType const& v1, VectorType const& v2, VectorType const& v3, VectorType const& v4) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3, v4}
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
	Matrix(Matrix<U, 4, 3> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<VectorType>(rhs[0]),
			static_cast<VectorType>(rhs[1]),
			static_cast<VectorType>(rhs[2]),
			static_cast<VectorType>(rhs[3]),
		}
	{}

	/**
	 *	@brief	ゼロ行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix4x3<T>
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	/**
	 *	@brief	単位行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix4x3<T>
	Identity() BKSGE_NOEXCEPT
	{
		return
		{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1},
			{0, 0, 0},
		};
	}
};

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_MATRIX4X3_HPP
