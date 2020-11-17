/**
 *	@file	extent3.hpp
 *
 *	@brief	Extent3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_EXTENT3_HPP
#define BKSGE_CORE_MATH_EXTENT3_HPP

#include <bksge/core/math/fwd/extent3_fwd.hpp>
#include <bksge/core/math/extent.hpp>
#include <bksge/core/math/extent2.hpp>
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
class Extent<T, 3> : public detail::VectorBase<T, 3>
{
private:
	using BaseType = detail::VectorBase<T, 3>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Extent() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	Extent(T const& x) BKSGE_NOEXCEPT
		: BaseType{x, x, x}
	{}

	/**
	 *	@brief	値3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Extent(T const& v1, T const& v2, T const& v3) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3}
	{}

	/**
	 *	@brief	Extent2と値1つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Extent(Extent<T, 2> const& v1, T const& v2) BKSGE_NOEXCEPT
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
	Extent(Extent<U, 3> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0]),
			static_cast<T>(rhs[1]),
			static_cast<T>(rhs[2]),
		}
	{}

	/**
	 *	@brief	ゼロ初期化されたExtentを作成します
	 */
	static BKSGE_CONSTEXPR Extent
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	BKSGE_CORE_MATH_NAMED_ACCESS(w, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(h, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(d, 2);
	BKSGE_CORE_MATH_NAMED_ACCESS(width,  0);
	BKSGE_CORE_MATH_NAMED_ACCESS(height, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(depth,  2);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((w)(h)(d));
};

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_EXTENT3_HPP
