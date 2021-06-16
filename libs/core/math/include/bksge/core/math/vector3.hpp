/**
 *	@file	vector3.hpp
 *
 *	@brief	Vector3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_VECTOR3_HPP
#define BKSGE_CORE_MATH_VECTOR3_HPP

#include <bksge/core/math/fwd/vector3_fwd.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/core/math/vector2.hpp>
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
class Vector<T, 3> : public detail::VectorBase<T, 3>
{
private:
	using BaseType = detail::VectorBase<T, 3>;

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
		: BaseType{x, x, x}
	{}

	/**
	 *	@brief	値3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Vector(T const& v1, T const& v2, T const& v3) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3}
	{}

	/**
	 *	@brief	Vector2と値1つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Vector(Vector<T, 2> const& v1, T const& v2) BKSGE_NOEXCEPT
		: BaseType{v1[0], v1[1], v2}
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
	Vector(Vector<U, 3> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0]),
			static_cast<T>(rhs[1]),
			static_cast<T>(rhs[2]),
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
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y)(z));
};

/**
 *	@brief	外積
 */
template <typename T>
inline BKSGE_CONSTEXPR Vector3<T>
Cross(Vector3<T> const& v1, Vector3<T> const& v2) BKSGE_NOEXCEPT
{
	return
	{
		(v1.y() * v2.z()) - (v1.z() * v2.y()),
		(v1.z() * v2.x()) - (v1.x() * v2.z()),
		(v1.x() * v2.y()) - (v1.y() * v2.x()),
	};
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_VECTOR3_HPP
