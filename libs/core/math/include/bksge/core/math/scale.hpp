/**
 *	@file	scale.hpp
 *
 *	@brief	Scale の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_SCALE_HPP
#define BKSGE_CORE_MATH_SCALE_HPP

#include <bksge/core/math/fwd/scale_fwd.hpp>
#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/core/math/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Scale : public detail::VectorBase<T, N>
{
};

/**
 *	@brief	Scale *= Scale
 */
template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator*=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Scale * Scale -> Scale
 */
template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N> const
operator*(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::multiplies_per_elem(lhs, rhs);
}

/**
 *	@brief	Scale /= Scale
 */
template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Scale<T, N>&
operator/=(Scale<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs / rhs;
}

/**
 *	@brief	Scale / Scale -> Scale
 */
template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Scale<T, N> const
operator/(Scale<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::divides_per_elem(lhs, rhs);
}

/**
 *	@brief	Vector *= Scale
 */
template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR Vector<T, N>&
operator*=(Vector<T, N>& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Vector * Scale -> Vector
 */
template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR Vector<T, N> const
operator*(Vector<T, N> const& lhs, Scale<T, N> const& rhs) BKSGE_NOEXCEPT
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
struct tuple_size<bksge::math::Scale<T, N>>
	: public tuple_size<bksge::math::detail::VectorBase<T, N>>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::math::Scale<T, N>>
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
struct hash<bksge::math::Scale<T, N>>
	: public hash<bksge::math::detail::VectorBase<T, N>>
{};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CORE_MATH_SCALE_HPP
