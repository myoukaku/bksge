/**
 *	@file	scale3.hpp
 *
 *	@brief	Scale3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_SCALE3_HPP
#define BKSGE_CORE_MATH_SCALE3_HPP

#include <bksge/core/math/fwd/scale3_fwd.hpp>
#include <bksge/core/math/scale.hpp>
#include <bksge/core/math/scale2.hpp>
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
class Scale<T, 3> : public detail::VectorBase<T, 3>
{
private:
	using BaseType = detail::VectorBase<T, 3>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Scale() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	Scale(T const& x) BKSGE_NOEXCEPT
		: BaseType{x, x, x}
	{}

	/**
	 *	@brief	値3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Scale(T const& v1, T const& v2, T const& v3) BKSGE_NOEXCEPT
		: BaseType{v1, v2, v3}
	{}

	/**
	 *	@brief	Scale2と値1つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Scale(Scale<T, 2> const& v1, T const& v2) BKSGE_NOEXCEPT
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
	Scale(Scale<U, 3> const& rhs) BKSGE_NOEXCEPT
		: BaseType{
			static_cast<T>(rhs[0]),
			static_cast<T>(rhs[1]),
			static_cast<T>(rhs[2]),
		}
	{}

	/**
	 *	@brief	ゼロスケールを作成します
	 */
	static BKSGE_CONSTEXPR Scale
	Zero() BKSGE_NOEXCEPT
	{
		return {};
	}

	/**
	 *	@brief	単位スケールを作成します
	 */
	static BKSGE_CONSTEXPR Scale
	Identity() BKSGE_NOEXCEPT
	{
		return Scale{1};
	}

	BKSGE_CORE_MATH_NAMED_ACCESS(x, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(y, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(z, 2);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y)(z));
};

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_SCALE3_HPP
