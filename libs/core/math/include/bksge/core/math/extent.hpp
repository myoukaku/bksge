/**
 *	@file	extent.hpp
 *
 *	@brief	Extent の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_EXTENT_HPP
#define BKSGE_CORE_MATH_EXTENT_HPP

#include <bksge/core/math/fwd/extent_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/core/math/scale.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Extent : public detail::VectorBase<T, N>
{
};

/**
 *	@brief	Extent *= Scale
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR Extent<T, N>&
operator*=(Extent<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Extent * Scale -> Extent
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR Extent<T, N> const
operator*(Extent<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::multiplies_per_elem(lhs, rhs);
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
template <typename T, std::size_t N>
struct tuple_size<bksge::math::Extent<T, N>>
	: public tuple_size<bksge::math::detail::VectorBase<T, N>>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::math::Extent<T, N>>
	: public tuple_element<I, bksge::math::detail::VectorBase<T, N>>
{};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <bksge/fnd/functional/hash.hpp>

namespace BKSGE_HASH_NAMESPACE
{

/**
 *	@brief	hash
 */
template <typename T, std::size_t N>
struct hash<bksge::math::Extent<T, N>>
	: public hash<bksge::math::detail::VectorBase<T, N>>
{};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CORE_MATH_EXTENT_HPP
