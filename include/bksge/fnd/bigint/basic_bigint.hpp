/**
 *	@file	basic_bigint.hpp
 *
 *	@brief	basic_bigint クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_BASIC_BIGINT_HPP
#define BKSGE_FND_BIGINT_BASIC_BIGINT_HPP

#include <bksge/fnd/bigint/fwd/basic_bigint_fwd.hpp>
#include <bksge/fnd/bigint/infinity_bits.hpp>
#include <bksge/fnd/bigint/detail/arbitrary_bigint.hpp>
#include <bksge/fnd/bigint/detail/fixed_bigint.hpp>
#include <bksge/fnd/bigint/detail/bigint_or_arithmetic.hpp>
#include <bksge/fnd/bigint/detail/bigint_or_integral.hpp>
#include <bksge/fnd/bigint/detail/common_type.hpp>
#include <bksge/fnd/bigint/detail/bigint_access.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/limits.hpp>

namespace bksge
{

template <bksge::size_t Bits, bool Signed>
class basic_bigint
{
private:
	template <bksge::size_t, bool>
	friend class basic_bigint;

	friend class bksge::detail::bigint_access;

	using value_type = bksge::conditional_t<
		Bits == bksge::infinity_bits,
		bksge::detail::arbitrary_bigint,
		bksge::detail::fixed_bigint<Bits, Signed>
	>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 *
	 *	値を0に初期化する
	 *
	 *	@exception	例外を投げない
	 */
	constexpr basic_bigint() noexcept = default;

	/**
	 *	@brief	算術型からのコンストラクタ
	 *
	 *	@param	other
	 *
	 *	otherから integral conversion rules に従って値を初期化する
	 *
	 *	@exception	Bits != infinity_bits のとき例外を投げない
	 */
	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	constexpr basic_bigint(Arithmetic other)
		noexcept(Bits != infinity_bits)
		: m_value(other)
	{}

	/**
	 *	@brief	変換コンストラクタ
	 *
	 *	@param	other
	 *
	 *	otherから integral conversion rules に従って値を初期化する
	 *
	 *	@exception	Bits != infinity_bits のとき例外を投げない
	 *
	 *	@note	Bits < B2 のとき、explicit指定される
	 */
#if defined(BKSGE_HAS_CXX20_CONDITIONAL_EXPLICIT)
	template <bksge::size_t B2, bool S2>
	explicit(Bits < B2)
	constexpr basic_bigint(basic_bigint<B2, S2> const& other)
		noexcept(Bits != infinity_bits)
		: m_value(other.m_value)
	{}
#else
	template <bksge::size_t B2, bool S2, bksge::enable_if_t<(Bits < B2)>* = nullptr>
	explicit
	constexpr basic_bigint(basic_bigint<B2, S2> const& other)
		noexcept(Bits != infinity_bits)
		: m_value(other.m_value)
	{}

	template <bksge::size_t B2, bool S2, bksge::enable_if_t<!(Bits < B2)>* = nullptr>
	constexpr basic_bigint(basic_bigint<B2, S2> const& other)
		noexcept(Bits != infinity_bits)
		: m_value(other.m_value)
	{}
#endif

	/**
	 *	@brief	文字列からのコンストラクタ
	 *
	 *	@param	str
	 *
	 *	@exception	変換できない文字列が渡された場合は、runtime_error 例外が送出される。
	 */
	explicit constexpr basic_bigint(bksge::string_view str)
		: m_value(str)
	{}

	explicit constexpr basic_bigint(bksge::wstring_view str)
		: m_value(str)
	{}

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	explicit constexpr basic_bigint(bksge::u8string_view str)
		: m_value(str)
	{}
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	explicit constexpr basic_bigint(bksge::u16string_view str)
		: m_value(str)
	{}
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	explicit constexpr basic_bigint(bksge::u32string_view str)
		: m_value(str)
	{}
#endif

private:
	constexpr basic_bigint(value_type const& val)
		: m_value(val)
	{}

public:
	/**
	 *	TODO テンプレートパラメータ制約: B != infinity_bits
	 */
	constexpr basic_bigint operator~() const noexcept
	{
		return {~m_value};
	}

	constexpr basic_bigint operator+() const noexcept
	{
		return *this;
	}

	constexpr basic_bigint operator-() const noexcept
	{
		return {-m_value};
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator+=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value += rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	constexpr basic_bigint&
	operator+=(Arithmetic const& rhs) noexcept
	{
		return *this += basic_bigint(rhs);
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator-=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value -= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	constexpr basic_bigint&
	operator-=(Arithmetic const& rhs) noexcept
	{
		return *this -= basic_bigint(rhs);
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator*=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value *= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	constexpr basic_bigint&
	operator*=(Arithmetic const& rhs) noexcept
	{
		m_value *= rhs;
		return *this;
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator/=(basic_bigint<B2, S2> const& rhs)
	{
		if (rhs == 0)
		{
			bksge::throw_overflow_error("bigint: divide by zero");
		}

		m_value /= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	constexpr basic_bigint&
	operator/=(Arithmetic const& rhs)
	{
		if (rhs == 0)
		{
			bksge::throw_overflow_error("bigint: divide by zero");
		}

		m_value /= rhs;
		return *this;
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator%=(basic_bigint<B2, S2> const& rhs)
	{
		if (rhs == 0)
		{
			bksge::throw_overflow_error("bigint: divide by zero");
		}

		m_value %= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	constexpr basic_bigint&
	operator%=(Integral const& rhs)
	{
		if (rhs == 0)
		{
			bksge::throw_overflow_error("bigint: divide by zero");
		}

		return *this %= basic_bigint(rhs);
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator&=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value &= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	constexpr basic_bigint&
	operator&=(Integral const& rhs) noexcept
	{
		return *this &= basic_bigint(rhs);
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator|=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value |= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	constexpr basic_bigint&
	operator|=(Integral const& rhs) noexcept
	{
		return *this |= basic_bigint(rhs);
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator^=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value ^= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	constexpr basic_bigint&
	operator^=(Integral const& rhs) noexcept
	{
		return *this ^= basic_bigint(rhs);
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator<<=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value <<= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	constexpr basic_bigint&
	operator<<=(Integral const& rhs) noexcept
	{
		return *this <<= basic_bigint(rhs);
	}

	template <bksge::size_t B2, bool S2>
	constexpr basic_bigint&
	operator>>=(basic_bigint<B2, S2> const& rhs) noexcept
	{
		m_value >>= rhs.m_value;
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	constexpr basic_bigint&
	operator>>=(Integral const& rhs) noexcept
	{
		return *this >>= basic_bigint(rhs);
	}

	constexpr basic_bigint& operator++() noexcept
	{
		return *this += 1;
	}

	constexpr basic_bigint& operator--() noexcept
	{
		return *this -= 1;
	}

	constexpr basic_bigint operator++(int) noexcept
	{
		auto tmp = *this;
		++(*this);
		return tmp;
	}

	constexpr basic_bigint operator--(int) noexcept
	{
		auto tmp = *this;
		--(*this);
		return tmp;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	explicit constexpr operator Arithmetic() const noexcept
	{
		return static_cast<Arithmetic>(m_value);
	}

private:
	constexpr int
	compare(basic_bigint const& rhs) const noexcept
	{
		return m_value.compare(rhs.m_value);
	}

	template <typename CharT>
	bksge::basic_string<CharT>
	to_basic_string() const
	{
		return m_value.template to_basic_string<CharT>();
	}

	BKSGE_CXX14_CONSTEXPR bksge::size_t
	hash() const BKSGE_NOEXCEPT
	{
		return m_value.hash();
	}

private:
	value_type m_value;
};

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bool
operator==(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	return bksge::detail::bigint_access::compare(CT(lhs), CT(rhs)) == 0;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bksge::strong_ordering
operator<=>(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	return static_cast<bksge::strong_ordering>(
		bksge::detail::bigint_access::compare(CT(lhs), CT(rhs)) <=> 0);
}

#else

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bool
operator!=(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	return !(lhs == rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bool
operator<(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	return bksge::detail::bigint_access::compare(CT(lhs), CT(rhs)) < 0;
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bool
operator>(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	return rhs < lhs;
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bool
operator<=(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	return !(lhs > rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bool
operator>=(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	return !(lhs < rhs);
}

#endif

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator+(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp += CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator-(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp -= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator*(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp *= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_arithmetic, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator/(BigInt1 const& lhs, BigInt2 const& rhs)
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp /= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator%(BigInt1 const& lhs, BigInt2 const& rhs)
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp %= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator&(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp &= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator|(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp |= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator^(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp ^= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator<<(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp <<= CT(rhs);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt1),
	BKSGE_REQUIRES_PARAM(bksge::detail::bigint_or_integral, BigInt2)
>
constexpr bksge::common_type_t<BigInt1, BigInt2>
operator>>(BigInt1 const& lhs, BigInt2 const& rhs) noexcept
{
	using CT = bksge::common_type_t<BigInt1, BigInt2>;
	CT tmp(lhs);
	return tmp >>= CT(rhs);
}

template <bksge::size_t B, bool S>
bksge::string to_string(basic_bigint<B, S> const& val)
{
	return bksge::detail::bigint_access::to_basic_string<char>(val);
}

template <bksge::size_t B, bool S>
bksge::wstring to_wstring(basic_bigint<B, S> const& val)
{
	return bksge::detail::bigint_access::to_basic_string<wchar_t>(val);
}

//template <bksge::size_t B, bool S>
//bksge::to_chars_result
//to_chars(char* first, char* last, basic_bigint<B, S> const& value, int base = 10);

//template <bksge::size_t B, bool S>
//bksge::from_chars_result
//from_chars(const char* first, const char* last, basic_bigint<B, S>& value, int base = 10);

template <typename Char, typename Traits, bksge::size_t B, bool S>
bksge::basic_ostream<Char, Traits>&
operator<<(bksge::basic_ostream<Char, Traits>& os, basic_bigint<B, S> const& val)
{
	return os << bksge::detail::bigint_access::to_basic_string<Char>(val);
}

template <typename Char, typename Traits, bksge::size_t B, bool S>
bksge::basic_istream<Char, Traits>&
operator>>(bksge::basic_istream<Char, Traits>& is, basic_bigint<B, S>& val)
{
	// いったん string で受け取る
	// TODO 最適化
	bksge::basic_string<Char, Traits> tmp;
	is >> tmp;
	val = basic_bigint<B, S>(tmp.c_str());
	return is;
}

}	// namespace bksge

#include <bksge/fnd/functional/hash.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template <bksge::size_t B, bool S>
struct hash<bksge::basic_bigint<B, S>>
{
	BKSGE_CXX14_CONSTEXPR bksge::size_t
	operator()(bksge::basic_bigint<B, S> const& x) const BKSGE_NOEXCEPT
	{
		return bksge::detail::bigint_access::hash(x);
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

namespace BKSGE_NUMERIC_LIMITS_NAMESPACE
{

template <bksge::size_t Bits, bool Signed>
class numeric_limits<bksge::basic_bigint<Bits, Signed>>
{
private:
	using T = bksge::basic_bigint<Bits, Signed>;

	BKSGE_STATIC_CONSTEXPR bool is_fixed_precision = (Bits != bksge::infinity_bits);

	static BKSGE_CONSTEXPR int get_digits10(int d) { return (d > INT_MAX / 301) ? (d / 1000) * 301L : (d * 301) / 1000; }

public:
	BKSGE_STATIC_CONSTEXPR bool is_specialized = true;

	BKSGE_STATIC_CONSTEXPR int  digits            = is_fixed_precision ? static_cast<int>(Bits - (Signed ? 1 : 0)) : INT_MAX;
	BKSGE_STATIC_CONSTEXPR int  digits10          = is_fixed_precision ? get_digits10(digits) : INT_MAX;
	BKSGE_STATIC_CONSTEXPR int  max_digits10      = 0;
	BKSGE_STATIC_CONSTEXPR bool is_signed         = Signed;
	BKSGE_STATIC_CONSTEXPR bool is_integer        = true;
	BKSGE_STATIC_CONSTEXPR bool is_exact          = true;
	BKSGE_STATIC_CONSTEXPR int  radix             = 2;
	BKSGE_STATIC_CONSTEXPR int  min_exponent      = 0;
	BKSGE_STATIC_CONSTEXPR int  min_exponent10    = 0;
	BKSGE_STATIC_CONSTEXPR int  max_exponent      = 0;
	BKSGE_STATIC_CONSTEXPR int  max_exponent10    = 0;
	BKSGE_STATIC_CONSTEXPR bool has_infinity      = false;
	BKSGE_STATIC_CONSTEXPR bool has_quiet_NaN     = false;
	BKSGE_STATIC_CONSTEXPR bool has_signaling_NaN = false;
	BKSGE_STATIC_CONSTEXPR bool has_denorm_loss   = false;
	BKSGE_STATIC_CONSTEXPR bool is_iec559         = false;
	BKSGE_STATIC_CONSTEXPR bool is_bounded        = is_fixed_precision;
	BKSGE_STATIC_CONSTEXPR bool is_modulo         = !Signed;
	BKSGE_STATIC_CONSTEXPR bool traps             = false;
	BKSGE_STATIC_CONSTEXPR bool tinyness_before   = false;
	BKSGE_STATIC_CONSTEXPR std::float_denorm_style has_denorm  = std::denorm_absent;
	BKSGE_STATIC_CONSTEXPR std::float_round_style  round_style = std::round_toward_zero;
	static BKSGE_CONSTEXPR T min()           { return is_fixed_precision && is_signed ? (T(1) << T(digits)) : 0; }
	static BKSGE_CONSTEXPR T max()           { return is_fixed_precision ? ((T(1) << T(digits)) - T(1)) : 0; }
	static BKSGE_CONSTEXPR T lowest()        { return min(); }
	static BKSGE_CONSTEXPR T epsilon()       { return 0; }
	static BKSGE_CONSTEXPR T round_error()   { return 0; }
	static BKSGE_CONSTEXPR T infinity()      { return 0; }
	static BKSGE_CONSTEXPR T quiet_NaN()     { return 0; }
	static BKSGE_CONSTEXPR T signaling_NaN() { return 0; }
	static BKSGE_CONSTEXPR T denorm_min()    { return 0; }
};

}	// namespace BKSGE_NUMERIC_LIMITS_NAMESPACE

#endif // BKSGE_FND_BIGINT_BASIC_BIGINT_HPP
