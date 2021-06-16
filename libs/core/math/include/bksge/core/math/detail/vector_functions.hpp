/**
 *	@file	vector_functions.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP

#include <bksge/fnd/cmath/lerp.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/functional/negate.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/functional/minus.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/functional/divides.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

// apply_per_elem_impl
template <typename Vec, typename F, bksge::size_t... Is>
inline BKSGE_CONSTEXPR Vec
apply_per_elem_impl(Vec const& v, F f, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT
{
	using T = typename Vec::value_type;
	return {static_cast<T>(f(v[Is]))...};
}

template <typename Vec1, typename Vec2, typename F, bksge::size_t... Is>
inline BKSGE_CONSTEXPR Vec1
apply_per_elem_impl(Vec1 const& lhs, Vec2 const& rhs, F f, bksge::index_sequence<Is...>) BKSGE_NOEXCEPT
{
	using T = typename Vec1::value_type;
	return {static_cast<T>(f(lhs[Is], rhs[Is]))...};
}

// apply_per_elem
template <typename Vec, typename F>
inline BKSGE_CONSTEXPR Vec
apply_per_elem(Vec const& v, F f) BKSGE_NOEXCEPT
{
	return apply_per_elem_impl(v, f,
		bksge::make_index_sequence<bksge::tuple_size<Vec>::value>());
}

template <typename Vec1, typename Vec2, typename F>
inline BKSGE_CONSTEXPR Vec1
apply_per_elem(Vec1 const& lhs, Vec2 const& rhs, F f) BKSGE_NOEXCEPT
{
	static_assert(bksge::tuple_size<Vec1>::value == bksge::tuple_size<Vec2>::value, "");
	return apply_per_elem_impl(lhs, rhs, f,
		bksge::make_index_sequence<bksge::tuple_size<Vec1>::value>());
}

template <typename Vec>
inline BKSGE_CONSTEXPR Vec
negate_per_elem(Vec const& v) BKSGE_NOEXCEPT
{
	return apply_per_elem(v, bksge::negate<>{});
}

template <typename Vec1, typename Vec2>
inline BKSGE_CONSTEXPR Vec1
plus_per_elem(Vec1 const& lhs, Vec2 const& rhs) BKSGE_NOEXCEPT
{
	return apply_per_elem(lhs, rhs, bksge::plus<>{});
}

template <typename Vec1, typename Vec2>
inline BKSGE_CONSTEXPR Vec1
minus_per_elem(Vec1 const& lhs, Vec2 const& rhs) BKSGE_NOEXCEPT
{
	return apply_per_elem(lhs, rhs, bksge::minus<>{});
}

template <typename Vec1, typename Vec2>
inline BKSGE_CONSTEXPR Vec1
multiplies_per_elem(Vec1 const& lhs, Vec2 const& rhs) BKSGE_NOEXCEPT
{
	return apply_per_elem(lhs, rhs, bksge::multiplies<>{});
}

template <typename Vec1, typename Vec2>
inline BKSGE_CONSTEXPR Vec1
divides_per_elem(Vec1 const& lhs, Vec2 const& rhs) BKSGE_NOEXCEPT
{
	return apply_per_elem(lhs, rhs, bksge::divides<>{});
}

template <typename T>
struct lerp_t
{
	T const& m_t;

	template <typename U>
	BKSGE_CONSTEXPR U operator()(U const& lhs, U const& rhs) const
	{
		return static_cast<U>(bksge::lerp(lhs, rhs, m_t));
	}
};

template <typename Vec1, typename Vec2, typename T>
inline BKSGE_CONSTEXPR Vec1
lerp_per_elem(Vec1 const& lhs, Vec2 const& rhs, T t) BKSGE_NOEXCEPT
{
	return apply_per_elem(lhs, rhs, lerp_t<T>{t});
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_FUNCTIONS_HPP
