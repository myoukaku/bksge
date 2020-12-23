/**
 *	@file	quantity.hpp
 *
 *	@brief	quantity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_QUANTITY_HPP
#define BKSGE_FND_UNITS_DETAIL_QUANTITY_HPP

#include <bksge/fnd/units/detail/quantity_fwd.hpp>
#include <bksge/fnd/units/detail/derived_dimension_fwd.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/cstdint/intmax_t.hpp>
#include <bksge/fnd/config.hpp>
#include <ratio>
#include <iosfwd>

namespace bksge
{

namespace units
{

/**
 *	@brief	quantity
 */
template <typename T, typename Dimension, typename Scale, typename Offset>
class quantity
{
public:
	using this_type       = quantity<T, Dimension, Scale, Offset>;
	using value_type      = T;
	using dimension_type  = Dimension;
	using scale_type      = Scale;
	using offset_type     = Offset;
	using reference       = value_type&;
	using const_reference = value_type const&;

	BKSGE_CONSTEXPR quantity() BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR explicit quantity(const_reference value) BKSGE_NOEXCEPT;

	template <typename T2, typename S2, typename O2>
	BKSGE_CONSTEXPR quantity(quantity<T2, Dimension, S2, O2> const& rhs) BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR const_reference value() const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR void swap(quantity& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
	{
		using bksge::swap;
		swap(m_value, other.m_value);
	}

private:
	value_type		m_value;
};

/**
 *	@brief	swap
 */
template <typename T, typename Dimension, typename Scale, typename Offset>
inline BKSGE_CXX14_CONSTEXPR void
swap(
	quantity<T, Dimension, Scale, Offset>& lhs,
	quantity<T, Dimension, Scale, Offset>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

// dimensionless
template <typename T, typename Scale = std::ratio<1>>
using dimensionless = quantity<T, derived_dimension<>, Scale>;

// quantity_common_type
template <typename Q1, typename Q2>
struct quantity_common_type;

template <typename Q1, typename Q2>
using quantity_common_type_t = typename quantity_common_type<Q1, Q2>::type;

// quantity_multiply_result
template <typename Q1, typename Q2>
struct quantity_multiply_result;

template <typename Q1, typename Q2>
using quantity_multiply_result_t = typename quantity_multiply_result<Q1, Q2>::type;

// quantity_divide_result
template <typename Q1, typename Q2>
struct quantity_divide_result;

template <typename Q1, typename Q2>
using quantity_divide_result_t = typename quantity_divide_result<Q1, Q2>::type;

/**
 *	@brief	単項+演算子
 */
template <typename... T>
BKSGE_CONSTEXPR quantity<T...>
operator+(quantity<T...> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	単項-演算子
 */
template <typename... T>
BKSGE_CONSTEXPR quantity<T...>
operator-(quantity<T...> const& q) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity + quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR auto
operator+(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_common_type_t<quantity<T...>, quantity<U...>>;

/**
 *	@brief	quantity += quantity
 */
template <typename... T, typename... U>
BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator+=(quantity<T...>& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity - quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR auto
operator-(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_common_type_t<quantity<T...>, quantity<U...>>;

/**
 *	@brief	quantity -= quantity
 */
template <typename... T, typename... U>
BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator-=(quantity<T...>& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity * Scalar
 */
template <
	typename... T,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR quantity<T...>
operator*(quantity<T...> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scalar * quantity
 */
template <
	typename... T,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR quantity<T...>
operator*(ArithmeticType lhs, quantity<T...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity * ratio
 */
template <typename... T, bksge::intmax_t N, bksge::intmax_t D>
BKSGE_CONSTEXPR auto
operator*(quantity<T...> const& lhs, std::ratio<N, D> const& rhs) BKSGE_NOEXCEPT
-> quantity_multiply_result_t<quantity<T...>, dimensionless<int, std::ratio<N, D>>>;

/**
 *	@brief	quantity *= Scalar
 */
template <
	typename... T,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator*=(quantity<T...>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity * quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR auto
operator*(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_multiply_result_t<quantity<T...>, quantity<U...>>;

/**
 *	@brief	quantity / Scalar
 */
template <
	typename... T,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR quantity<T...>
operator/(quantity<T...> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	Scalar / quantity
 */
template <
	typename... T,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR quantity_divide_result_t<dimensionless<ArithmeticType>, quantity<T...>>
operator/(ArithmeticType lhs, quantity<T...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity /= Scalar
 */
template <
	typename... T,
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator/=(quantity<T...>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity / quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR auto
operator/(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_divide_result_t<quantity<T...>, quantity<U...>>;

/**
 *	@brief	quantity == quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR bool
operator==(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity != quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR bool
operator!=(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity < quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR bool
operator<(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity > quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR bool
operator>(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity <= quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR bool
operator<=(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	quantity >= quantity
 */
template <typename... T, typename... U>
BKSGE_CONSTEXPR bool
operator>=(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	ストリームへの出力
 */
template <typename E, typename T, typename... U>
std::basic_ostream<E, T>& operator<<(std::basic_ostream<E, T>& os, quantity<U...> const& rhs);

}	// namespace units

}	// namespace bksge

#include <bksge/fnd/units/detail/quantity_inl.hpp>

#endif // BKSGE_FND_UNITS_DETAIL_QUANTITY_HPP
