/**
 *	@file	matrix3x3.hpp
 *
 *	@brief	Matrix3x3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_MATRIX3X3_HPP
#define BKSGE_CORE_MATH_MATRIX3X3_HPP

#include <bksge/core/math/fwd/matrix3x3_fwd.hpp>
#include <bksge/core/math/fwd/quaternion_fwd.hpp>
#include <bksge/core/math/fwd/scale_fwd.hpp>
#include <bksge/core/math/matrix.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Matrix<T, 3, 3>
	: public Vector<Vector<T, 3>, 3>
{
private:
	using BaseType = Vector<Vector<T, 3>, 3>;

public:
	// 継承コンストラクタ
	using BaseType::BaseType;

	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Matrix() BKSGE_NOEXCEPT_OR_NOTHROW
		: BaseType()
	{}

	/**
	 *	@brief	Quaternionからのコンストラクタ
	 */
	template <typename U>
	explicit BKSGE_CONSTEXPR
	Matrix(Quaternion<U> const& q) BKSGE_NOEXCEPT;

	/**
	 *	@brief	ゼロ行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix
	Zero() BKSGE_NOEXCEPT;

	/**
	 *	@brief	単位行列を作成します
	 */
	static BKSGE_CONSTEXPR Matrix
	Identity() BKSGE_NOEXCEPT;

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	trans	平行移動
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeTranslation(Vector<T, 2> const& trans) BKSGE_NOEXCEPT;

	/**
	 *	@brief	平行移動行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeTranslation(T x, T y) BKSGE_NOEXCEPT;

	/**
	 *	@brief	スケーリング行列を作成します
	 *
	 *	@param	s	スケール
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeScale(Scale<T, 3> const& s) BKSGE_NOEXCEPT;

	/**
	 *	@brief	スケーリング行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	z
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeScale(T x, T y, T z) BKSGE_NOEXCEPT;

	/**
	 *	@brief	X軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix
	MakeRotationX(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	Y軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix
	MakeRotationY(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	Z軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CONSTEXPR Matrix
	MakeRotationZ(AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	任意のベクトルを回転軸にして回転する行列を作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	static BKSGE_CXX14_CONSTEXPR Matrix
	MakeRotation(Vector<T, 3> const& axis, AngleType const& angle) BKSGE_NOEXCEPT;

	/**
	 *	@brief	せん断行列を作成します
	 *
	 *	@param	x	X方向のせん断係数
	 *	@param	y	Y方向のせん断係数
	 *	@param	z	Z方向のせん断係数
	 */
	static BKSGE_CONSTEXPR Matrix
	MakeShear(T x, T y, T z) BKSGE_NOEXCEPT;
};

}	// namespace math

}	// namespace bksge

#include <bksge/core/math/inl/matrix3x3_inl.hpp>

#endif // BKSGE_CORE_MATH_MATRIX3X3_HPP
