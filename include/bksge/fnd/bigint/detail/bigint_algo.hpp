/**
 *	@file	bigint_algo.hpp
 *
 *	@brief	bigint_algo クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_BIGINT_ALGO_HPP
#define BKSGE_FND_BIGINT_DETAIL_BIGINT_ALGO_HPP

#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/ranges/copy.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/bit/bit_cast.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/modf.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/unsigned_integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/rbegin.hpp>
#include <bksge/fnd/ranges/rend.hpp>
#include <bksge/fnd/cstddef.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/stdexcept/overflow_error.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>

namespace bksge
{

namespace detail
{

class bigint_algo
{
private:
	template <bksge::size_t N>
	struct make_sized_signed{};

	template <bksge::size_t N>
	using make_sized_signed_t = typename make_sized_signed<N>::type;

	template <> struct make_sized_signed<1> {using type = bksge::int8_t; };
	template <> struct make_sized_signed<2> {using type = bksge::int16_t; };
	template <> struct make_sized_signed<4> {using type = bksge::int32_t; };
	template <> struct make_sized_signed<8> {using type = bksge::int64_t; };

	template <bksge::size_t N>
	struct make_sized_unsigned{};

	template <bksge::size_t N>
	using make_sized_unsigned_t = typename make_sized_unsigned<N>::type;

	template <> struct make_sized_unsigned<1> {using type = bksge::uint8_t; };
	template <> struct make_sized_unsigned<2> {using type = bksge::uint16_t; };
	template <> struct make_sized_unsigned<4> {using type = bksge::uint32_t; };
	template <> struct make_sized_unsigned<8> {using type = bksge::uint64_t; };

public:
	template <typename T, bksge::size_t N>
	static BKSGE_CXX14_CONSTEXPR bool
	is_zero(bksge::array<T, N> const& value)
	{
		for (bksge::size_t i = 0; i < N; ++i)
		{
			if (value[i] != 0)
			{
				return false;
			}
		}
		return true;
	}

	template <typename T>
	static BKSGE_CXX14_CONSTEXPR bool
	is_zero(bksge::vector<T> const& value)
	{
		return
			value.size() == 0 ||
			(value.size() == 1 && value[0] == 0);
	}

private:
	template <typename T, bksge::size_t N>
	static BKSGE_CXX14_CONSTEXPR void
	resize(bksge::array<T, N>&, bksge::size_t)
	{}

	template <typename T>
	static BKSGE_CXX14_CONSTEXPR void
	resize(bksge::vector<T>& vec, bksge::size_t n)
	{
		vec.resize(n);
	}

	template <typename T, bksge::size_t N>
	static BKSGE_CXX14_CONSTEXPR void
	remove_leading_zeros(bksge::array<T, N>&)
	{}

	template <typename T>
	static BKSGE_CXX14_CONSTEXPR void
	remove_leading_zeros(bksge::vector<T>& vec)
	{
		while (vec.size() >= 2 && vec.back() == 0)
		{
			vec.pop_back();
		}
	}

	template <typename T, bksge::size_t N>
	static BKSGE_CXX14_CONSTEXPR bksge::size_t
	get_digits(bksge::array<T, N> const& vec)
	{
		for (bksge::size_t i = N; i > 0; --i)
		{
			if (vec[i-1] != 0)
			{
				return i;
			}
		}
		return 1;
	}

	template <typename T>
	static BKSGE_CXX14_CONSTEXPR bksge::size_t
	get_digits(bksge::vector<T> const& vec)
	{
		return vec.size();
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	static BKSGE_CXX14_CONSTEXPR Integral
	rshift(Integral value, bksge::size_t n)
	{
		return (n >= bksge::bitsof<Integral>()) ? 0 : (value >> n);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	static BKSGE_CXX14_CONSTEXPR Integral
	lshift(Integral value, bksge::size_t n)
	{
		return (n >= bksge::bitsof<Integral>()) ? 0 : (value << n);
	}

	template <
		typename ElementType,
		BKSGE_REQUIRES_PARAM(bksge::integral, Arithmetic)
	>
	static BKSGE_CXX14_CONSTEXPR ElementType
	lo(Arithmetic value)
	{
		return static_cast<ElementType>(value);
	}

	template <
		typename ElementType,
		BKSGE_REQUIRES_PARAM(bksge::integral, Arithmetic)
	>
	static BKSGE_CXX14_CONSTEXPR Arithmetic
	hi(Arithmetic value)
	{
		return rshift(value, bksge::bitsof<ElementType>());
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	shift_left(VectorType const& vec, bksge::size_t offset)
	{
		namespace ranges = bksge::ranges;
		VectorType result{};
		resize(result, ranges::size(vec) + offset);
		for (bksge::size_t i = offset; i < ranges::size(result); ++i)
		{
			result[i] = vec[i - offset];
		}
		return result;
	}

	template <typename T>
	static BKSGE_CXX14_CONSTEXPR bksge::vector<T>
	shift_right(bksge::vector<T> const& vec, bksge::size_t offset)
	{
		return bksge::vector<T>(vec.begin() + offset, vec.end());
	}

	template <typename T, bksge::size_t N>
	static BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
	shift_right(bksge::array<T, N> const& vec, bksge::size_t offset)
	{
		bksge::array<T, N> result{};
		for (bksge::size_t i = offset; i < N; ++i)
		{
			result[i - offset] = vec[i];
		}
		return result;
	}

	template <typename VectorType>
	struct sized_construct_impl;

	template <typename T>
	struct sized_construct_impl<bksge::vector<T>>
	{
		static BKSGE_CXX14_CONSTEXPR bksge::vector<T>
		invoke(bksge::size_t size)
		{
			return bksge::vector<T>(size);
		}
	};

	template <typename T, bksge::size_t N>
	struct sized_construct_impl<bksge::array<T, N>>
	{
		static BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
		invoke(bksge::size_t)
		{
			return bksge::array<T, N>{};
		}
	};

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	sized_construct(bksge::size_t size)
	{
		return sized_construct_impl<VectorType>::invoke(size);
	}

	template <
		typename VectorType,
		typename ElementType = bksge::ranges::range_value_t<VectorType>,
		BKSGE_REQUIRES_PARAM(bksge::integral, Integral),
		bksge::size_t N = sizeof(Integral) / sizeof(ElementType),
		typename = bksge::enable_if_t<N != 0>
	>
	static BKSGE_CXX14_CONSTEXPR VectorType
	construct_impl(Integral value, bksge::detail::overload_priority<1>)
	{
		namespace ranges = bksge::ranges;

		auto ret = sized_construct<VectorType>(N);
		auto const size = ranges::size(ret);
		for (bksge::size_t i = 0; i < size && value != 0; ++i)
		{
			ret[i] = lo<ElementType>(value);
			value  = hi<ElementType>(value);
		}
		remove_leading_zeros(ret);
		return ret;
	}

	template <
		typename VectorType,
		typename ElementType = bksge::ranges::range_value_t<VectorType>,
		BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
	>
	static BKSGE_CXX14_CONSTEXPR VectorType
	construct_impl(Integral value, bksge::detail::overload_priority<0>)
	{
		return {static_cast<ElementType>(value)};
	}

public:
	template <
		typename VectorType,
		BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)
	>
	static BKSGE_CXX14_CONSTEXPR VectorType
	construct(Arithmetic value)
	{
		return construct_impl<VectorType>(value, bksge::detail::overload_priority<1>{});
	}

private:
	template <BKSGE_REQUIRES_PARAM(bksge::unsigned_integral, T)>
	static BKSGE_CONSTEXPR T
	abs_to_unsigned_impl(T x, bksge::detail::overload_priority<1>) BKSGE_NOEXCEPT
	{
		return x;
	}

	template <typename T>
	static BKSGE_CONSTEXPR bksge::make_unsigned_t<T>
	abs_to_unsigned_impl(T x, bksge::detail::overload_priority<0>) BKSGE_NOEXCEPT
	{
		using type = bksge::make_unsigned_t<T>;
		return x < 0 ? (~type(x)+1) : type(x);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, T)>
	static BKSGE_CONSTEXPR T
	abs_to_unsigned(T x) BKSGE_NOEXCEPT
	{
		return abs_to_unsigned_impl(x, bksge::detail::overload_priority<1>{});
	}

	template <typename VectorType, typename Float>
	static BKSGE_CXX14_CONSTEXPR int
	init_from_float(VectorType& vec, Float value)
	{
		bksge::uint64_t const sign_bits = 1;
		bksge::uint64_t const fraction_bits = bksge::numeric_limits<Float>::digits - 1;
		bksge::uint64_t const exponent_bits = bksge::bitsof<Float>() - 1 - fraction_bits;

		bksge::uint64_t const sign_bit_shift = bksge::bitsof<Float>() - 1;
		bksge::uint64_t const exponent_bit_shift = fraction_bits;
		bksge::uint64_t const fraction_bit_shift = 0;

		bksge::uint64_t const sign_bit_mask      = ((1ULL << sign_bits)     - 1) << sign_bit_shift;
		bksge::uint64_t const exponent_bit_mask  = ((1ULL << exponent_bits) - 1) << exponent_bit_shift;
		bksge::uint64_t const fraction_bit_mask  = ((1ULL << fraction_bits) - 1) << fraction_bit_shift;

		bksge::uint64_t const exponent_bias = bksge::numeric_limits<Float>::max_exponent - 1;
		bksge::uint64_t const fraction_bias = (1ULL << fraction_bits);

		using utype = make_sized_unsigned_t<sizeof(Float)>;
		using stype = make_sized_signed_t<sizeof(Float)>;
		auto v = bksge::bit_cast<utype>(value);
		utype const sign     = (v & sign_bit_mask)     >> sign_bit_shift;
		utype const exponent = (v & exponent_bit_mask) >> exponent_bit_shift;
		utype const fraction = (v & fraction_bit_mask) >> fraction_bit_shift;
		vec = construct<VectorType>(fraction + fraction_bias);
		stype const shift = exponent - exponent_bias - fraction_bits;
		if (shift < 0)
		{
			bit_shift_right(vec, construct<VectorType>(-shift));
		}
		else
		{
			bit_shift_left(vec, construct<VectorType>(shift));
		}
		return sign == 1 && !is_zero(vec) ? -1 : 1;
	}

	template <
		typename VectorType,
		BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
	>
	static BKSGE_CXX14_CONSTEXPR int
	init_from_value_impl(VectorType& vec, Integral value, bksge::detail::overload_priority<1>)
	{
		int sign = value < 0 ? -1 : 1;
		vec = construct<VectorType>(abs_to_unsigned(value));
		return sign;
	}

	template <
		typename VectorType,
		BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)
	>
	static BKSGE_CXX14_CONSTEXPR int
	init_from_value_impl(VectorType& vec, Float value, bksge::detail::overload_priority<0>)
	{
		if (bksge::isnan(value) ||
			bksge::iszero(value))
		{
			vec = {0};
			return 1;
		}

		return init_from_float(vec, value);
	}

public:
	template <
		typename VectorType,
		BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)
	>
	static BKSGE_CXX14_CONSTEXPR int
	init_from_value(VectorType& vec, Arithmetic value)
	{
		return init_from_value_impl(vec, value, bksge::detail::overload_priority<1>{});
	}

	template <typename T, bksge::size_t N>
	static BKSGE_CXX14_CONSTEXPR int
	get_sign(bksge::array<T, N> const& vec) noexcept
	{
		namespace ranges = bksge::ranges;
		using element_type = T;
		element_type const sign_bit = (1 << (bksge::bitsof<element_type>() - 1));
		return ((vec[N - 1] & sign_bit) == 0) ? 1 : -1;
	}

	template <typename T>
	static BKSGE_CXX14_CONSTEXPR int
	get_sign(bksge::vector<T> const&) noexcept
	{
		return 1;
	}

	template <typename T, bksge::size_t N>
	static BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
	abs(bksge::array<T, N> const& vec) noexcept
	{
		if (get_sign(vec) < 0)
		{
			return negate(vec);
		}
		else
		{
			return vec;
		}
	}

public:
	template <
		typename ResultType,
		typename VectorType
	>
	static BKSGE_CXX14_CONSTEXPR ResultType
	construct_from_vector(VectorType const& vec)
	{
		auto const NA = get_digits(vec);
		auto result = sized_construct<ResultType>(NA);
		auto const NB = bksge::ranges::size(result);
		bksge::ranges::copy(
			bksge::ranges::begin(vec), bksge::ranges::begin(vec) + bksge::min(NA, NB),
			bksge::ranges::begin(result));
		return result;
	}

private:
	template <
		typename VectorType,
		typename Iterator
	>
	static BKSGE_CXX14_CONSTEXPR VectorType
	construct(Iterator first, Iterator last)
	{
		auto result = sized_construct<VectorType>(bksge::distance(first, last));
		bksge::ranges::copy(first, last, bksge::ranges::begin(result));
		return result;
	}

private:
	template <typename CharT>
	static BKSGE_CXX14_CONSTEXPR int
	sign_from_string(bksge::basic_string_view<CharT>* str)
	{
		if (str->size() >= 1)
		{
			if ((*str)[0] == '-')
			{
				*str = str->substr(1);
				return -1;
			}
			else if ((*str)[0] == '+')
			{
				*str = str->substr(1);
			}
		}
		return 1;
	}

	template <typename ResultType, typename CharT>
	static BKSGE_CXX14_CONSTEXPR ResultType
	base_from_string(bksge::basic_string_view<CharT>* str)
	{
		if (str->size() >= 2)
		{
			if ((*str)[0] == '0')
			{
				switch ((*str)[1])
				{
				case 'b':	// 0b
				case 'B':	// 0B
					*str = str->substr(2);
					return 2;
				case 'x':	// 0x
				case 'X':	// 0X
					*str = str->substr(2);
					return 16;
				default:	// 0
					*str = str->substr(1);
					return 8;
				}
			}
		}
		return 10;
	}

	template <typename ResultType>
	static BKSGE_CXX14_CONSTEXPR ResultType
	char_to_int(char c)
	{
		if ('0' <= c && c <= '9')
		{
			return c - '0';
		}
		else if ('a' <= c && c <= 'f')
		{
			return c - 'a' + 10;
		}
		else if ('A' <= c && c <= 'F')
		{
			return c - 'A' + 10;
		}
		else
		{
			bksge::throw_runtime_error("");
		}
	}

	template <typename ElementType, typename CharT>
	static BKSGE_CXX14_CONSTEXPR ElementType
	init_from_string_sub(bksge::basic_string_view<CharT>* str, bksge::size_t count, ElementType base, ElementType* out_multiplier)
	{
		ElementType base_multiplier = 1;
		ElementType val = 0;
		bksge::size_t i = 0;
		for (auto c : *str)
		{
			auto const n = char_to_int<ElementType>(c);
			if (n >= base)
			{
				bksge::throw_runtime_error("");
			}

			val = val * base + n;
			base_multiplier *= base;
			++i;
			if (i >= count)
			{
				break;
			}
		}
		*out_multiplier = base_multiplier;
		*str = str->substr(i);
		return val;
	}

public:
	template <typename VectorType, typename CharT>
	static BKSGE_CXX14_CONSTEXPR int
	init_from_string(VectorType& value, bksge::basic_string_view<CharT> str)
	{
		using element_type = bksge::ranges::range_value_t<VectorType>;

		auto const sign = sign_from_string(&str);
		auto const base = base_from_string<element_type>(&str);

		bksge::size_t const count =
			base == 16 ?    bksge::numeric_limits<element_type>::digits / 4 - 1 :
			base == 10 ?    bksge::numeric_limits<element_type>::digits10 :
			base == 8 ?     bksge::numeric_limits<element_type>::digits / 2 - 1 :
			/*base == 2 ?*/ bksge::numeric_limits<element_type>::digits;

		while (!str.empty())
		{
			element_type base_multiplier = 1;
			element_type val = init_from_string_sub(&str, count, base, &base_multiplier);

			value = multiply(value, base_multiplier);
			add(value, val);
		}

		remove_leading_zeros(value);
		return sign;
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	add(VectorType& lhs, VectorType const& rhs)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_signed_t<sizeof(element_type)*2>;

		auto const NA = get_digits(lhs);
		auto const NB = get_digits(rhs);

		resize(lhs, bksge::max(NA, NB) + 1);
		auto const N = ranges::size(lhs);

		double_element_type carry = 0;
		bksge::size_t i = 0;
		for (; i < NB; ++i)
		{
			auto t = double_element_type(lhs[i]) + rhs[i] + carry;
			lhs[i] = lo<element_type>(t);
			carry  = hi<element_type>(t);
		}
		for (; i < N && carry != 0; ++i)
		{
			auto t = double_element_type(lhs[i]) + carry;
			lhs[i] = lo<element_type>(t);
			carry  = hi<element_type>(t);
		}

		remove_leading_zeros(lhs);
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	add(VectorType& lhs, bksge::ranges::range_value_t<VectorType> const& rhs)
	{
		if (rhs == 0)
		{
			return;
		}

		add(lhs, VectorType{rhs});
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	sub(VectorType& lhs, VectorType const& rhs)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_signed_t<sizeof(element_type)*2>;

		auto const NA = get_digits(lhs);
		auto const NB = get_digits(rhs);

		resize(lhs, bksge::max(NA, NB) + 0);
		auto const N = ranges::size(lhs);

		double_element_type carry = 0;
		bksge::size_t i = 0;
		for (; i < NB; ++i)
		{
			auto t = double_element_type(lhs[i]) - rhs[i] + carry;
			lhs[i] = lo<element_type>(t);
			carry  = hi<element_type>(t);
		}
		for (; i < N && carry != 0; ++i)
		{
			auto t = double_element_type(lhs[i]) + carry;
			lhs[i] = lo<element_type>(t);
			carry  = hi<element_type>(t);
		}

		remove_leading_zeros(lhs);
	}

#if 0
	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	multiply(VectorType const& lhs, bksge::ranges::range_value_t<VectorType> rhs)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

		if (rhs == 0)
		{
			return {0};
		}

		if (rhs == 1)
		{
			return lhs;
		}

		auto const NA = get_digits(lhs);

		if (NA == 0)
		{
			return {0};
		}

		auto result = sized_construct<VectorType>(NA);

		for (bksge::size_t i = 0; i < NA; ++i)
		{
			double_element_type t = (double_element_type(lhs[i]) * rhs);
			auto tmp = construct<VectorType>(t);
			add(result, shift_left(tmp, i));
		}

		remove_leading_zeros(result);
		return result;
	}
#endif

private:
	template <typename VectorType, BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	static BKSGE_CXX14_CONSTEXPR VectorType
	multiply_arithmetic(VectorType const& lhs, Integral rhs, bksge::detail::overload_priority<1>)
	{
		return multiply(lhs, construct<VectorType>(rhs));
	}

	template <typename VectorType, BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
	static BKSGE_CXX14_CONSTEXPR VectorType
	multiply_arithmetic(VectorType const& lhs, Float rhs, bksge::detail::overload_priority<0>)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

		// (1) rhs を整数部と小数部にわける
		// (2) 整数部は多倍長整数にして乗算する
		// (3) 小数部はそのまま乗算する
		// (4) (2)と(3)を加算する

		Float integ;
		Float frac = bksge::modf(rhs, &integ);
		VectorType t;
		init_from_value(t, integ);
		auto tmp = multiply(lhs, t);

		auto const NA = get_digits(lhs);
		auto result = sized_construct<VectorType>(NA);

		for (bksge::size_t i = 0; i < NA; ++i)
		{
			double_element_type t2 = lhs[i] * frac;
			add(result, shift_left(construct<VectorType>(t2), i));
		}

		add(result, tmp);
		remove_leading_zeros(result);
		return result;
	}

public:
	template <typename VectorType, BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	static BKSGE_CXX14_CONSTEXPR VectorType
	multiply(VectorType const& lhs, Arithmetic rhs)
	{
		return multiply_arithmetic(lhs, rhs, bksge::detail::overload_priority<1>{});
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	multiply(VectorType const& lhs, VectorType const& rhs)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

		auto const NA = get_digits(lhs);

		if (NA == 0)
		{
			return {0};
		}

		//if (NA == 1)
		//{
		//	return multiply(rhs, lhs[0]);
		//}

		auto const NB = get_digits(rhs);

		if (NB == 0)
		{
			return {0};
		}

		//if (NB == 1)
		//{
		//	return multiply(lhs, rhs[0]);
		//}

		auto result = sized_construct<VectorType>(NA + NB);

		for (bksge::size_t i = 0; i < NA; ++i)
		{
			for (bksge::size_t j = 0; j < NB; ++j)
			{
				auto t = (double_element_type(lhs[i]) * rhs[j]);
				auto tmp = construct<VectorType>(t);
				add(result, shift_left(tmp, i+j));
			}
		}

		remove_leading_zeros(result);
		return result;
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	div_mod(VectorType const& lhs, VectorType const& rhs, VectorType* out_remainder)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

		auto const c = compare(lhs, rhs);

		// lhs < rhs
		if (c < 0)
		{
			if (out_remainder != nullptr)
			{
				*out_remainder = lhs;
			}
			return {0};
		}

		// lhs == rhs
		if (c == 0)
		{
			if (out_remainder != nullptr)
			{
				*out_remainder = VectorType{0};
			}
			return {1};
		}

		auto const NA = get_digits(lhs);
		auto const NB = get_digits(rhs);

		// ----- ステップ 1. A ÷ B の桁数を求める ----- //
		bksge::size_t D = NA - NB;
		// digit_a_partial : A の上 NB 桁を取り出したもの
		auto digit_a_partial = construct<VectorType>(lhs.begin() + D, lhs.end());
		if (compare(digit_a_partial, rhs) >= 0)
		{
			// (A の上 NB 桁) が B 以上だったら...？
			D += 1;
		}

		if (D == 0)
		{
			if (out_remainder != nullptr)
			{
				*out_remainder = lhs;
			}
			return {0};
		}

		// lhs と rhs が整数で表現可能な場合は整数で計算する
		if (D <= 2 && NA <= 2 && NB <= 2)
		{
			auto x = to_arithmetic<double_element_type>(lhs);
			auto y = to_arithmetic<double_element_type>(rhs);
			if (out_remainder != nullptr)
			{
				*out_remainder = construct<VectorType>(x % y);
			}
			return construct<VectorType>(x / y);
		}

		// ----- ステップ 2. A ÷ B を筆算で求める ----- //
		auto remainder = construct<VectorType>(lhs.begin() + (D - 1), lhs.end());

		auto quotient = sized_construct<VectorType>(D);

		for (auto i = D; i > 0; --i)
		{
			bksge::size_t index = i - 1;

			if (NB <= 2 && get_digits(remainder) <= 2)
			{
				// remainder と rhs が整数で表現可能な場合は整数で計算する
				auto x = to_arithmetic<double_element_type>(remainder);
				auto y = to_arithmetic<double_element_type>(rhs);
				quotient[index] = static_cast<element_type>(x / y);
			}
			else
			{
				// remainder / rhs をバイナリサーチで探す
				double_element_type left = 1;
				double_element_type right = bksge::numeric_limits<element_type>::max();
				right++;

				while (right - left > 1)
				{
					double_element_type mid = (left + right) / 2;
					auto x = multiply(rhs, construct<VectorType>(mid));
					if (compare(x, remainder) > 0)
					{
						right = mid;
					}
					else
					{
						left = mid;
					}
				}
				quotient[index] = static_cast<element_type>(left);
			}

			auto x_result = multiply(rhs, quotient[index]);
			sub(remainder, x_result);
			if (index >= 1)
			{
				// 新しく (index-1) の位が降りてくる
				remainder = shift_left(remainder, 1);
				add(remainder, lhs[index - 1]);
				remove_leading_zeros(remainder);
			}
		}

		if (out_remainder != nullptr)
		{
			*out_remainder = remainder;
		}

		return quotient;
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	divide(VectorType const& lhs, VectorType const& rhs)
	{
		return div_mod(lhs, rhs, static_cast<VectorType*>(nullptr));
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	modulus(VectorType const& lhs, VectorType const& rhs)
	{
		VectorType rem{};
		div_mod(lhs, rhs, &rem);
		return rem;
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	bit_and(VectorType& lhs, VectorType const& rhs)
	{
		auto const NA = get_digits(lhs);
		auto const NB = get_digits(rhs);

		resize(lhs, bksge::max(NA, NB));
		auto const N = ranges::size(lhs);

		bksge::size_t i = 0;
		for (; i < NB; ++i)
		{
			lhs[i] &= rhs[i];
		}
		for (; i < N; ++i)
		{
			lhs[i] &= 0;
		}

		remove_leading_zeros(lhs);
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	bit_or(VectorType& lhs, VectorType const& rhs)
	{
		auto const NA = get_digits(lhs);
		auto const NB = get_digits(rhs);

		resize(lhs, bksge::max(NA, NB));
		auto const N = ranges::size(lhs);

		bksge::size_t i = 0;
		for (; i < NB; ++i)
		{
			lhs[i] |= rhs[i];
		}
		for (; i < N; ++i)
		{
			lhs[i] |= 0;
		}

		remove_leading_zeros(lhs);
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	bit_xor(VectorType& lhs, VectorType const& rhs)
	{
		auto const NA = get_digits(lhs);
		auto const NB = get_digits(rhs);

		resize(lhs, bksge::max(NA, NB));
		auto const N = ranges::size(lhs);

		bksge::size_t i = 0;
		for (; i < NB; ++i)
		{
			lhs[i] ^= rhs[i];
		}
		for (; i < N; ++i)
		{
			lhs[i] ^= 0;
		}

		remove_leading_zeros(lhs);
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	bit_not(VectorType const& value) noexcept
	{
		auto const N = bksge::ranges::size(value);
		auto result = sized_construct<VectorType>(N);
		for (bksge::size_t i = 0; i < N; ++i)
		{
			result[i] = ~value[i];
		}
		return result;
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	bit_shift_left(VectorType& lhs, VectorType const& rhs)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

		auto const element_bits = bksge::bitsof<element_type>();
		VectorType rem {};
		VectorType quo = div_mod(rhs, construct<VectorType>(element_bits), &rem);

		if (!is_zero(rem))
		{
			auto shift = to_arithmetic<double_element_type>(rem);
			double_element_type carry = 0;
			auto const N = ranges::size(lhs);
			bksge::size_t i = 0;
			for (; i < N; ++i)
			{
				double_element_type t = carry + (double_element_type(lhs[i]) << shift);
				lhs[i] = lo<element_type>(t);
				carry  = hi<element_type>(t);
			}

			if (carry != 0)
			{
				resize(lhs, N + 1);
				lhs[i] = lo<element_type>(carry);
			}
		}

		if (!is_zero(quo))
		{
			auto offset = to_arithmetic<bksge::size_t>(quo);
			lhs = shift_left(lhs, offset);
		}
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR void
	bit_shift_right(VectorType& lhs, VectorType const& rhs)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;
		using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

		auto const element_bits = bksge::bitsof<element_type>();
		VectorType rem {};
		VectorType quo = div_mod(rhs, construct<VectorType>(element_bits), &rem);

		if (!is_zero(rem))
		{
			auto shift = to_arithmetic<double_element_type>(rem);
			double_element_type carry = 0;
			auto const N = ranges::size(lhs);
			for (bksge::size_t i = N; i > 0; --i)
			{
				double_element_type t = (double_element_type(lhs[i-1]) << element_bits >> shift);
				lhs[i-1] = static_cast<element_type>(carry + (t >> element_bits));
				carry    = static_cast<element_type>(t);
			}
		}

		if (!is_zero(quo))
		{
			if (compare(quo, construct<VectorType>(bksge::numeric_limits<bksge::size_t>::max())) > 0)
			{
				lhs = {0};
				return;
			}
			auto offset = to_arithmetic<bksge::size_t>(quo);
			auto N = bksge::min(offset, ranges::size(lhs));
			lhs = shift_right(lhs, N);
		}

		remove_leading_zeros(lhs);
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR VectorType
	negate(VectorType const& value) noexcept
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;

		auto result = bit_not(value);
		add(result, element_type(1));
		return result;
	}

private:
	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral), typename VectorType>
	static BKSGE_CXX14_CONSTEXPR Integral
	to_arithmetic_impl(VectorType const& value, bksge::detail::overload_priority<1>)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;

		bksge::uintmax_t r = 0;
		for (auto it = ranges::rbegin(value); it != ranges::rend(value); ++it)
		{
			r = lshift(r, bksge::bitsof<element_type>()) + *it;
		}

		return static_cast<Integral>(r);
	}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4056);	// overflow in floating-point constant arithmetic

	template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float), typename VectorType>
	static BKSGE_CXX14_CONSTEXPR Float
	to_arithmetic_impl(VectorType const& value, bksge::detail::overload_priority<0>)
	{
		namespace ranges = bksge::ranges;
		using element_type = ranges::range_value_t<VectorType>;

		auto const multiplier = static_cast<Float>(1ULL << bksge::bitsof<element_type>());
		Float r = 0;
		for (auto it = ranges::rbegin(value); it != ranges::rend(value); ++it)
		{
			r = (r * multiplier) + *it;
		}

		return r;
	}

BKSGE_WARNING_POP();

public:
	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic), typename VectorType>
	static BKSGE_CXX14_CONSTEXPR Arithmetic
	to_arithmetic(VectorType const& value)
	{
		return to_arithmetic_impl<Arithmetic>(value, bksge::detail::overload_priority<1>{});
	}

	template <
		std::size_t DstRadix,
		typename VectorType,
		typename ElementType = bksge::ranges::range_value_t<VectorType>
	>
	static BKSGE_CXX14_CONSTEXPR bksge::vector<ElementType>
	convert_radix(VectorType value)
	{
		using ResultType = bksge::vector<ElementType>;

		auto const base = construct<VectorType>(DstRadix);
		ResultType result;
		do
		{
			VectorType rem;
			VectorType quo = div_mod(value, base, &rem);
			result.push_back(rem[0]);
			value = quo;
		}
		while (!is_zero(value));

		return result;
	}

	template <typename CharT, typename VectorType>
	static bksge::basic_string<CharT>
	to_basic_string(VectorType const& value)
	{
		// 10進に変換して
		auto baseN_value = convert_radix<10>(value);

		// 文字列化する
		bksge::basic_string<CharT> r;
		for (auto it = baseN_value.rbegin(); it != baseN_value.rend(); ++it)
		{
			r += static_cast<CharT>((*it) + '0');
		}

		return r;
	}

	template <typename VectorType>
	static BKSGE_CXX14_CONSTEXPR int
	compare(VectorType const& lhs, VectorType const& rhs)  noexcept
	{
		auto const NA = get_digits(lhs);
		auto const NB = get_digits(rhs);

		if (NA > NB) { return  1; }
		if (NA < NB) { return -1; }

		for (bksge::size_t i = 0; i < NA; ++i)
		{
			auto const j = NA - i - 1;
			if (lhs[j] > rhs[j]) { return  1; }
			if (lhs[j] < rhs[j]) { return -1; }
		}

		return 0;
	}
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_BIGINT_ALGO_HPP
