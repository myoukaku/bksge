/**
 *	@file	vector.hpp
 *
 *	@brief	Vector の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_VECTOR_HPP
#define BKSGE_CORE_MATH_VECTOR_HPP

#include <bksge/core/math/fwd/vector_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/numeric/ranges/inner_product.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N>
class Vector : public detail::VectorBase<T, N>
{
private:
	using BaseType = detail::VectorBase<T, N>;

public:
	using BaseType::BaseType;
};

/**
 *	@brief	内積
 *
 *	@param	v1	ベクトルその１
 *	@param	v2	ベクトルその２
 *	@return	v1とv2の内積
 */
template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR T
Dot(Vector<T, N> const& v1, Vector<T, N> const& v2)
{
	return bksge::ranges::inner_product(v1, v2, T{});
}

/**
 *	@brief	ベクトルの長さの２乗を取得.
 *
 *	@param	v	対象となるベクトル
 *	@return	vの長さの２乗
 */
template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR T
SquaredLength(Vector<T, N> const& v)
{
	return Dot(v, v);
}

/**
 *	@brief	ベクトルの長さを取得.
 *
 *	@param	v	対象となるベクトル
 *	@return	vの長さ
 */
template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
Length(Vector<T, N> const& v)
{
	return bksge::sqrt(SquaredLength(v));
}

/**
 *	@brief	ベクトルを正規化.
 *
 *	引数vは変更しません。
 *	vがゼロベクトルの時はゼロベクトルを返します。
 *
 *	@param	v	対象となるベクトル
 *	@return	vを正規化したベクトル
 */
template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N>
Normalized(Vector<T, N> const& v)
{
	return
		SquaredLength(v) == 0 ?
			Vector<T, N>{} :
		v / Length(v);
}

}	// namespace math

}	// namespace bksge

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>

namespace BKSGE_TUPLE_NAMESPACE
{

/**
 *	@brief	tuple_size
 */
template <typename T, bksge::size_t N>
struct tuple_size<bksge::math::Vector<T, N>>
	: public tuple_size<bksge::math::detail::VectorBase<T, N>>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T, bksge::size_t N>
struct tuple_element<I, bksge::math::Vector<T, N>>
	: public tuple_element<I, bksge::math::detail::VectorBase<T, N>>
{};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <bksge/fnd/functional/hash.hpp>

namespace BKSGE_HASH_NAMESPACE
{

/**
 *	@brief	hash
 */
template <typename T, bksge::size_t N>
struct hash<bksge::math::Vector<T, N>>
	: public hash<bksge::math::detail::VectorBase<T, N>>
{};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CORE_MATH_VECTOR_HPP
