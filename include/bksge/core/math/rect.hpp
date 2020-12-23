/**
 *	@file	rect.hpp
 *
 *	@brief	Rect の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_RECT_HPP
#define BKSGE_CORE_MATH_RECT_HPP

#include <bksge/core/math/fwd/rect_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/extent2.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

template <typename T>
class Rect : public detail::VectorBase<T, 4>
{
private:
	using BaseType = detail::VectorBase<T, 4>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 *
	 *	全て0に初期化します。
	 */
	BKSGE_CONSTEXPR Rect(void) BKSGE_NOEXCEPT
		: BaseType()
	{}

	/**
	 *	@brief	指定した2つの点をちょうど格納できる矩形を求めます
	 */
	BKSGE_CXX14_CONSTEXPR Rect(Vector2<T> const& p1, Vector2<T> const& p2) BKSGE_NOEXCEPT
		: Rect(
			inter_ctor_tag(),
			p1.x(),
			p1.y(),
			p2.x(),
			p2.y())
	{}

	/**
	 *	@brief	左上の座標と幅と高さを指定するコンストラクタです
	 */
	BKSGE_CXX14_CONSTEXPR Rect(Vector2<T> const& pos, Extent2<T> const& extent) BKSGE_NOEXCEPT
		: Rect(
			inter_ctor_tag(),
			pos.x(),
			pos.y(),
			pos.x() + extent.width(),
			pos.y() + extent.height())
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
	BKSGE_CONSTEXPR Rect(Rect<U> const& rhs) BKSGE_NOEXCEPT
		: BaseType(
			static_cast<T>(rhs.left()),
			static_cast<T>(rhs.top()),
			static_cast<T>(rhs.right()),
			static_cast<T>(rhs.bottom()))
	{}

	BKSGE_CONSTEXPR T left(void) const
	{
		return (*this)[0];
	}

	BKSGE_CONSTEXPR T top(void) const
	{
		return (*this)[1];
	}

	BKSGE_CONSTEXPR T right(void) const
	{
		return (*this)[2];
	}

	BKSGE_CONSTEXPR T bottom(void) const
	{
		return (*this)[3];
	}

	BKSGE_CONSTEXPR T width(void) const
	{
		return right() - left();
	}

	BKSGE_CONSTEXPR T height(void) const
	{
		return bottom() - top();
	}

private:
	struct inter_ctor_tag {};

	BKSGE_CXX14_CONSTEXPR
	Rect(inter_ctor_tag, T l, T t, T r, T b) BKSGE_NOEXCEPT
		: BaseType(
			bksge::min(l, r),
			bksge::min(t, b),
			bksge::max(l, r),
			bksge::max(t, b))
	{}
};

}	// namespace math

}	// namespace bksge

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace BKSGE_TUPLE_NAMESPACE
{

/**
 *	@brief	tuple_size
 */
template <typename T>
struct tuple_size<bksge::math::Rect<T>>
	: public tuple_size<bksge::math::detail::VectorBase<T, 4>>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T>
struct tuple_element<I, bksge::math::Rect<T>>
	: public tuple_element<I, bksge::math::detail::VectorBase<T, 4>>
{};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <functional>

namespace std
{

template <typename T>
struct hash<bksge::math::Rect<T>>
	: public hash<bksge::math::detail::VectorBase<T, 4>>
{};

}	// namespace std

#endif // BKSGE_CORE_MATH_RECT_HPP
