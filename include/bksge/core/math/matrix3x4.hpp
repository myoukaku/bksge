/**
 *	@file	matrix3x4.hpp
 *
 *	@brief	Matrix3x4 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_MATRIX3X4_HPP
#define BKSGE_CORE_MATH_MATRIX3X4_HPP

#include <bksge/core/math/fwd/matrix3x4_fwd.hpp>
#include <bksge/core/math/matrix.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Matrix<T, 3, 4> : public Vector<Vector<T, 4>, 3>
{
private:
	using BaseType = Vector<Vector<T, 4>, 3>;
	using VectorType = Vector<T, 4>;

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
	 *	@brief	Vector4 3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix(VectorType const& v1, VectorType const& v2, VectorType const& v3) BKSGE_NOEXCEPT
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
	Matrix(Matrix<U, 3, 4> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<VectorType>(rhs[0]),
			static_cast<VectorType>(rhs[1]),
			static_cast<VectorType>(rhs[2]),
		}
	{}

	/**
	 *	@brief	ゼロ行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix3x4<T>
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	/**
	 *	@brief	単位行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix3x4<T>
	Identity() BKSGE_NOEXCEPT
	{
		return
		{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
		};
	}
};

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_MATRIX3X4_HPP
