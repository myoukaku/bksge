﻿/**
 *	@file	quantity_inl.hpp
 *
 *	@brief	quantity の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_DETAIL_QUANTITY_INL_HPP
#define BKSGE_UNITS_DETAIL_QUANTITY_INL_HPP

#include <bksge/units/detail/quantity.hpp>
#include <bksge/units/detail/dimension_multiply.hpp>
#include <bksge/units/detail/dimension_divide.hpp>
#include <bksge/ratio/ratio_gcd.hpp>
#include <bksge/config.hpp>
#include <cstdint>
#include <ostream>
#include <ratio>
#include <type_traits>

namespace bksge
{

namespace units
{

template <typename T1, typename D, typename S1, typename O1, typename T2, typename S2, typename O2>
struct quantity_common_type<quantity<T1, D, S1, O1>, quantity<T2, D, S2, O2>>
{
	using type = quantity<
		typename std::common_type<T1, T2>::type,
		D,
		bksge::ratio_gcd<S1, S2>
	>;
};

template <typename T1, typename D1, typename S1, typename T2, typename D2, typename S2>
struct quantity_multiply_result<quantity<T1, D1, S1>, quantity<T2, D2, S2>>
{
	using type = quantity<
		typename std::common_type<T1, T2>::type,
		dimension_multiply<D1, D2>,
		std::ratio_multiply<S1, S2>
	>;
};

template <typename T1, typename D1, typename S1, typename T2, typename D2, typename S2>
struct quantity_divide_result<quantity<T1, D1, S1>, quantity<T2, D2, S2>>
{
	using type = quantity<
		typename std::common_type<T1, T2>::type,
		dimension_divide<D1, D2>,
		std::ratio_divide<S1, S2>
	>;
};

template <typename Q>
struct quantity_without_scale_offset;

template <typename Q>
using quantity_without_scale_offset_t = typename quantity_without_scale_offset<Q>::type;

template <typename T, typename D, typename S, typename O>
struct quantity_without_scale_offset<quantity<T, D, S, O>>
{
	using type = quantity<T, D>;
};

template <typename Q>
struct quantity_without_offset;

template <typename Q>
using quantity_without_offset_t = typename quantity_without_offset<Q>::type;

template <typename T, typename D, typename S, typename O>
struct quantity_without_offset<quantity<T, D, S, O>>
{
	using type = quantity<T, D, S>;
};

template <typename R>
inline BKSGE_CONSTEXPR long double
ratio_to_float()
{
	return static_cast<long double>(R::num) / R::den;
}

template <typename ToQuantity, typename FromQuantity>
inline BKSGE_CONSTEXPR ToQuantity
quantity_cast(FromQuantity const& q) BKSGE_NOEXCEPT
{
	using T1 = typename ToQuantity::value_type;
	using R1 = typename ToQuantity::scale_type;
	using R2 = typename FromQuantity::scale_type;
	using R3 = std::ratio_divide<R2, R1>;
	using O1 = typename ToQuantity::offset_type;
	using O2 = typename FromQuantity::offset_type;
	return ToQuantity(static_cast<T1>((q.value() + ratio_to_float<O2>()) * R3::num / R3::den - ratio_to_float<O1>()));
}

template <typename T, typename D, typename S, typename O>
inline BKSGE_CONSTEXPR
quantity<T, D, S, O>::quantity() BKSGE_NOEXCEPT
	: m_value()
{}

template <typename T, typename D, typename S, typename O>
inline BKSGE_CONSTEXPR
quantity<T, D, S, O>::quantity(const_reference value) BKSGE_NOEXCEPT
	: m_value(value)
{}

template <typename T, typename D, typename S, typename O>
template <typename T2, typename S2, typename O2>
inline BKSGE_CONSTEXPR
quantity<T, D, S, O>::quantity(quantity<T2, D, S2, O2> const& rhs) BKSGE_NOEXCEPT
	: m_value(quantity_cast<this_type>(rhs).value())
{}

template <typename T, typename D, typename S, typename O>
inline BKSGE_CONSTEXPR auto
quantity<T, D, S, O>::value() const BKSGE_NOEXCEPT
-> const_reference
{
	return m_value;
}

///////////////////////////////////////////////////////////////////////////////
template <typename... T>
inline BKSGE_CONSTEXPR quantity<T...>
operator+(quantity<T...> const& q) BKSGE_NOEXCEPT
{
	return q;
}

template <typename... T>
inline BKSGE_CONSTEXPR quantity<T...>
operator-(quantity<T...> const& q) BKSGE_NOEXCEPT
{
	return quantity<T...> { -q.value() };
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR auto
operator+(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_common_type_t<quantity<T...>, quantity<U...>>
{
	using type = quantity_common_type_t<quantity<T...>, quantity<U...>>;
	return type{ type{ lhs }.value() + type{ rhs }.value() };
}

template <typename... T, typename... U>
inline BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator+=(quantity<T...>& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs + rhs;
	return lhs;
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR auto
operator-(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_common_type_t<quantity<T...>, quantity<U...>>
{
	using type = quantity_common_type_t<quantity<T...>, quantity<U...>>;
	return type{ type{ lhs }.value() - type{ rhs }.value() };
}

template <typename... T, typename... U>
inline BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator-=(quantity<T...>& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	lhs = lhs - rhs;
	return lhs;
}

template <typename... T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR quantity<T...>
operator*(quantity<T...> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	using Q = quantity<T...>;
	using T1 = typename Q::value_type;
	using Q2 = quantity_without_offset_t<Q>;
	return Q { Q2 { static_cast<T1>(Q2 { lhs }.value() * rhs) } };
}

template <typename... T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR quantity<T...>
operator*(ArithmeticType lhs, quantity<T...> const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

template <typename... T, std::intmax_t N, std::intmax_t D>
BKSGE_CONSTEXPR auto
operator*(quantity<T...> const& lhs, std::ratio<N, D> const&) BKSGE_NOEXCEPT
-> quantity_multiply_result_t<quantity<T...>, dimensionless<int, std::ratio<N, D>>>
{
	using type = quantity_multiply_result_t<quantity<T...>, dimensionless<int, std::ratio<N, D>>>;
	return type(lhs.value());
}

template <typename... T, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator*=(quantity<T...>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs * rhs;
	return lhs;
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR auto
operator*(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_multiply_result_t<quantity<T...>, quantity<U...>>
{
	using Q1 = quantity<T...>;
	using Q2 = quantity<U...>;
	using result_type = quantity_multiply_result_t<Q1, Q2>;
	return result_type
	{
		quantity_without_scale_offset_t<result_type>
		{
			quantity_without_scale_offset_t<Q1>{lhs}.value() *
			quantity_without_scale_offset_t<Q2>{rhs}.value()
		}
	};
}

template <typename... T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR quantity<T...>
operator/(quantity<T...> const& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	using Q = quantity<T...>;
	using T1 = typename Q::value_type;
	using Q2 = quantity_without_offset_t<Q>;
	return Q { Q2 { static_cast<T1>(Q2 { lhs }.value() / rhs) } };
}

template <typename... T, typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR auto
operator/(ArithmeticType lhs, quantity<T...> const& rhs) BKSGE_NOEXCEPT
-> quantity_divide_result_t<dimensionless<ArithmeticType>, quantity<T...>>
{
#if defined(_MSC_VER) && (_MSC_VER == 1900)
	using Q1 = dimensionless<ArithmeticType>;
	using Q2 = quantity<T...>;
	using result_type = quantity_divide_result_t<Q1, Q2>;
	return result_type
	{
		quantity_without_scale_offset_t<result_type>
		{
			quantity_without_scale_offset_t<Q1>{lhs}.value() /
			quantity_without_scale_offset_t<Q2>{rhs}.value()
		}
	};
	// MSVC14 だと何故か↓のコードがconstexprにならない
#else
	return dimensionless<ArithmeticType>(lhs) / rhs;
#endif
}

template <typename... T, typename ArithmeticType, typename>
inline BKSGE_CXX14_CONSTEXPR quantity<T...>&
operator/=(quantity<T...>& lhs, ArithmeticType rhs) BKSGE_NOEXCEPT
{
	lhs = lhs / rhs;
	return lhs;
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR auto
operator/(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
-> quantity_divide_result_t<quantity<T...>, quantity<U...>>
{
	using Q1 = quantity<T...>;
	using Q2 = quantity<U...>;
	using result_type = quantity_divide_result_t<Q1, Q2>;
	return result_type
	{
		quantity_without_scale_offset_t<result_type>
		{
			quantity_without_scale_offset_t<Q1>{lhs}.value() /
			quantity_without_scale_offset_t<Q2>{rhs}.value()
		}
	};
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR bool
operator==(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	using type = quantity_common_type_t<quantity<T...>, quantity<U...>>;
	return type{lhs}.value() == type{rhs}.value();
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR bool
operator!=(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR bool
operator<(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	using type = quantity_common_type_t<quantity<T...>, quantity<U...>>;
	return type{lhs}.value() < type{rhs}.value();
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR bool
operator>(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	return rhs < lhs;
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR bool
operator<=(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	return !(rhs < lhs);
}

template <typename... T, typename... U>
inline BKSGE_CONSTEXPR bool
operator>=(quantity<T...> const& lhs, quantity<U...> const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs < rhs);
}

template <typename E, typename T, typename... U>
inline std::basic_ostream<E, T>&
operator<<(std::basic_ostream<E, T>& os, quantity<U...> const& rhs)
{
	return os << rhs.value();
}

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_DETAIL_QUANTITY_INL_HPP