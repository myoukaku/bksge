/**
 *	@file	color.hpp
 *
 *	@brief	Color の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_COLOR_HPP
#define BKSGE_CORE_MATH_COLOR_HPP

#include <bksge/core/math/fwd/color_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename>
struct color_scale
{
	static BKSGE_CONSTEXPR double get() { return 255.0; }
};
template <>
struct color_scale<float>
{
	static BKSGE_CONSTEXPR double get() { return 1.0; }
};
template <>
struct color_scale<double>
{
	static BKSGE_CONSTEXPR double get() { return 1.0; }
};
template <>
struct color_scale<long double>
{
	static BKSGE_CONSTEXPR double get() { return 1.0; }
};

}	// namespace detail

template <typename T, bksge::size_t N>
class Color : public detail::VectorBase<T, N>
{
};

/**
 *	@brief	Color *= Color
 */
template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator*=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Color * Color -> Color
 */
template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Color<T, N> const
operator*(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::multiplies_per_elem(lhs, rhs);
}

/**
 *	@brief	Color /= Color
 */
template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR Color<T, N>&
operator/=(Color<T, N>& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs / rhs;
}

/**
 *	@brief	Color / Color -> Color
 */
template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR Color<T, N> const
operator/(Color<T, N> const& lhs, Color<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::divides_per_elem(lhs, rhs);
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
struct tuple_size<bksge::math::Color<T, N>>
	: public tuple_size<bksge::math::detail::VectorBase<T, N>>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T, bksge::size_t N>
struct tuple_element<I, bksge::math::Color<T, N>>
	: public tuple_element<I, bksge::math::detail::VectorBase<T, N>>
{};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <functional>

namespace std
{

/**
 *	@brief	hash
 */
template <typename T, bksge::size_t N>
struct hash<bksge::math::Color<T, N>>
	: public hash<bksge::math::detail::VectorBase<T, N>>
{};

}	// namespace std

#endif // BKSGE_CORE_MATH_COLOR_HPP
