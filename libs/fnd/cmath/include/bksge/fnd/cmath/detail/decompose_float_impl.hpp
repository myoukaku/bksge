/**
 *	@file	decompose_float_impl.hpp
 *
 *	@brief	decompose_float 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_DECOMPOSE_FLOAT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_DECOMPOSE_FLOAT_IMPL_HPP

#include <bksge/fnd/bit/bit_cast.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/bit/countr_zero.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/cstddef.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4309);	// truncation of constant value

namespace bksge
{

namespace detail
{

template <typename T>
struct decompose_float_common
{
private:
	static bksge::uint64_t constexpr sign_bits = 1;
	static bksge::uint64_t constexpr fraction_bits = std::numeric_limits<T>::digits - 1;
	static bksge::uint64_t constexpr exponent_bits = bksge::bitsof<T>() - 1 - fraction_bits;

	static bksge::uint64_t constexpr sign_bit_shift = bksge::bitsof<T>() - 1;
	static bksge::uint64_t constexpr exponent_bit_shift = fraction_bits;
	static bksge::uint64_t constexpr fraction_bit_shift = 0;

	static bksge::uint64_t constexpr sign_bit_mask      = ((1ULL << sign_bits)     - 1) << sign_bit_shift;
	static bksge::uint64_t constexpr exponent_bit_mask  = ((1ULL << exponent_bits) - 1) << exponent_bit_shift;
	static bksge::uint64_t constexpr fraction_bit_mask  = ((1ULL << fraction_bits) - 1) << fraction_bit_shift;

	static bksge::int64_t constexpr exponent_bias = std::numeric_limits<T>::max_exponent - 1;
	static bksge::int64_t constexpr exponent_max  = (1ULL << exponent_bits) - 1;
	static bksge::int64_t constexpr fraction_bias = (1ULL << fraction_bits);

protected:
	struct result
	{
		bksge::uint32_t	sign;
		bksge::int32_t	exponent;
		bksge::uint64_t	fraction;
	};

	template <typename UnsignedType>
	static BKSGE_CXX14_CONSTEXPR result
	invoke_impl(T x) noexcept
	{
		auto rep = bksge::bit_cast<UnsignedType>(x);
		UnsignedType const sign     = (rep & sign_bit_mask)     >> sign_bit_shift;
		UnsignedType const exponent = (rep & exponent_bit_mask) >> exponent_bit_shift;
		UnsignedType const fraction = (rep & fraction_bit_mask) >> fraction_bit_shift;

		result ret;
		ret.sign     = static_cast<bksge::uint32_t>(sign);
        if (exponent == 0)
        {
			if (fraction == 0)
			{
				// +0, -0
    			ret.exponent = 0;
				ret.fraction = 0;
			}
			else
			{
				// denormal
    			ret.exponent = static_cast<bksge::int32_t>(1ULL - exponent_bias - fraction_bits);
				ret.fraction = static_cast<bksge::uint64_t>(fraction);
			}
        }
		else if (exponent == exponent_max)
		{
			// infinity, NaN
    		ret.exponent = 0;
			ret.fraction = 0;
		}
        else
        {
			// normal
    		ret.exponent = static_cast<bksge::int32_t>(exponent - exponent_bias - fraction_bits);
            ret.fraction = static_cast<bksge::uint64_t>(fraction | fraction_bias);
        }

		if (ret.fraction != 0)
		{
			auto s = bksge::countr_zero(ret.fraction);
			if (s != 0)
			{
				ret.fraction >>= s;
				ret.exponent += static_cast<bksge::int32_t>(s);
			}
		}

		return ret;
	}
};

// float型はbinary32、double型はbinary64型と決まっているが、
// long double型は特定の形式が定められておらず、処理系によって実態が違う。
// 主な処理系では、binary64、binary80、binary128の場合がある。
// なので、単純に型で処理を分岐することはできない。
// また、binary80の場合はパディングがあるため、sizeof(T)で分岐することもできない。
// numeric_limits<T>::digits で処理を分岐する。
template <typename T, bksge::size_t = std::numeric_limits<T>::digits>
struct decompose_float_impl_t;

// 単精度浮動小数点数 (32bit)
template <typename T>
struct decompose_float_impl_t<T, 24> : private decompose_float_common<T>
{
private:
	using base = decompose_float_common<T>;

public:
	using result = typename base::result;

	static BKSGE_CXX14_CONSTEXPR result
	invoke(T x) noexcept
	{
		return base::template invoke_impl<bksge::uint32_t>(x);
	}
};

// 倍精度浮動小数点数 (64bit)
template <typename T>
struct decompose_float_impl_t<T, 53> : private decompose_float_common<T>
{
private:
	using base = decompose_float_common<T>;

public:
	using result = typename base::result;

	static BKSGE_CXX14_CONSTEXPR result
	invoke(T x) noexcept
	{
		return base::template invoke_impl<bksge::uint64_t>(x);
	}
};

// 拡張倍精度浮動小数点数 (80bit)
template <typename T>
struct decompose_float_impl_t<T, 64>
{
private:
	static bksge::uint64_t constexpr fraction_bits = std::numeric_limits<T>::digits - 1;

    static bksge::uint64_t constexpr sign_bits = 1;
	static bksge::uint64_t constexpr sign_bit_shift = bksge::bitsof<bksge::uint16_t>() - 1;
	static bksge::uint64_t constexpr sign_bit_mask = ((1ULL << sign_bits) - 1) << sign_bit_shift;

	static bksge::uint64_t constexpr exponent_bits = bksge::bitsof<bksge::uint16_t>() - 1;
	static bksge::uint64_t constexpr exponent_bit_shift = 0;
	static bksge::uint64_t constexpr exponent_bit_mask  = ((1ULL << exponent_bits) - 1) << exponent_bit_shift;
	static bksge::uint64_t constexpr exponent_bias = std::numeric_limits<T>::max_exponent - 1;
	static bksge::uint64_t constexpr exponent_max  = (1ULL << exponent_bits) - 1;

public:
	struct result
	{
		bksge::uint32_t	sign;
		bksge::int32_t	exponent;
		bksge::uint64_t	fraction;
	};

	static BKSGE_CXX14_CONSTEXPR result
	invoke(T x) noexcept
	{
		auto a = bksge::bit_cast<bksge::array<bksge::uint64_t, 2>>(x);
		bksge::uint16_t const hi = static_cast<bksge::uint16_t>(a[1]);
		bksge::uint64_t const lo = a[0];

		bksge::uint16_t const sign     = (hi & sign_bit_mask)     >> sign_bit_shift;
		bksge::uint16_t const exponent = (hi & exponent_bit_mask) >> exponent_bit_shift;
		bksge::uint64_t const fraction = lo;

		result ret;
		ret.sign     = sign;
        if (exponent == 0)
        {
			if (fraction == 0)
			{
				// +0, -0
    			ret.exponent = 0;
				ret.fraction = 0;
			}
			else
			{
				// denormal
    			ret.exponent = static_cast<bksge::int32_t>(1ULL - exponent_bias - fraction_bits);
				ret.fraction = fraction;
			}
        }
		else if (exponent == exponent_max)
		{
			// infinity, NaN
    		ret.exponent = 0;
			ret.fraction = 0;
		}
        else
        {
			// normal
			ret.exponent = static_cast<bksge::int32_t>(exponent - exponent_bias - fraction_bits);
			ret.fraction = fraction;	// 拡張倍精度のときはケチ表現でない
		}

		if (ret.fraction != 0)
		{
			auto s = bksge::countr_zero(ret.fraction);
			if (s != 0)
			{
				ret.fraction >>= s;
				ret.exponent += static_cast<bksge::int32_t>(s);
			}
		}

		return ret;
	}
};

// 四倍精度浮動小数点数 (128bit)
template <typename T>
struct decompose_float_impl_t<T, 113>
{
	struct result
	{
		bksge::uint32_t	sign;
		bksge::int32_t	exponent;
		bksge::uint64_t	fraction_hi;
		bksge::uint64_t	fraction_lo;
	};

	// not implemented yet
	// TODO
};

template <typename T>
inline BKSGE_CXX14_CONSTEXPR
typename decompose_float_impl_t<T>::result
decompose_float_impl(T x) noexcept
{
	using impl = decompose_float_impl_t<T>;
	return impl::invoke(x);
}

}	// namespace detail

template <typename T>
using decompose_float_result_t =
	typename detail::decompose_float_impl_t<T>::result;

}	// namespace bksge

BKSGE_WARNING_POP();

#endif // BKSGE_FND_CMATH_DETAIL_DECOMPOSE_FLOAT_IMPL_HPP
