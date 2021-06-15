/**
 *	@file	fixed_bigint.hpp
 *
 *	@brief	fixed_bigint クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_FIXED_BIGINT_HPP
#define BKSGE_FND_BIGINT_DETAIL_FIXED_BIGINT_HPP

#include <bksge/fnd/bigint/detail/bigint_algo.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

class arbitrary_bigint;

template <bksge::size_t Bits, bool Signed>
class fixed_bigint
{
private:
	template <bksge::size_t, bool>
	friend class fixed_bigint;

	friend class arbitrary_bigint;

	using element_type = bksge::uint32_t;
	static const bksge::size_t N = (Bits / 8) / sizeof(element_type);
	using vector_type = bksge::array<element_type, N>;

private:
	template <bksge::size_t M>
	static constexpr bksge::array<element_type, M>
	abs(bksge::array<element_type, M> const& data) noexcept
	{
		if (bigint_algo::get_sign(data) < 0)
		{
			return bigint_algo::negate(data);
		}
		else
		{
			return data;
		}
	}

	constexpr fixed_bigint(vector_type const& data)
		: m_data(data)
	{}

public:
	constexpr fixed_bigint() noexcept
		: fixed_bigint(element_type{0})
	{}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	constexpr fixed_bigint(Arithmetic x) noexcept
		: m_data{}
	{
		auto sign = bigint_algo::init_from_arithmetic(m_data, x);
		if (sign < 0)
		{
			m_data = bigint_algo::negate(m_data);
		}
	}

	template <bksge::size_t B2, bool S2>
	constexpr fixed_bigint(fixed_bigint<B2, S2> const& other) noexcept
		: m_data{}
	{
		auto sign = bigint_algo::get_sign(other.m_data);
		if (sign < 0)
		{
			m_data = bigint_algo::construct_from_vector<vector_type>(bigint_algo::negate(other.m_data));
			m_data = bigint_algo::negate(m_data);
		}
		else
		{
			m_data = bigint_algo::construct_from_vector<vector_type>(other.m_data);
		}
	}

	template <typename CharT>
	constexpr fixed_bigint(bksge::basic_string_view<CharT> str)
		: m_data{}
	{
		auto sign = bigint_algo::init_from_string(m_data, str);
		if (sign < 0)
		{
			m_data = bigint_algo::negate(m_data);
		}
	}

	constexpr fixed_bigint
	operator-() const noexcept
	{
		return {bigint_algo::negate(m_data)};
	}

	constexpr void
	operator+=(fixed_bigint const& rhs) noexcept
	{
		bigint_algo::add(m_data, rhs.m_data);
	}

	constexpr void
	operator-=(fixed_bigint const& rhs) noexcept
	{
		bigint_algo::sub(m_data, rhs.m_data);
	}

	constexpr void
	operator*=(fixed_bigint const& rhs) noexcept
	{
		m_data = bigint_algo::multiply(m_data, rhs.m_data);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
	constexpr void
	operator*=(Float const& rhs) noexcept
	{
		m_data = bigint_algo::multiply_float(m_data, bksge::abs(rhs));
		if (rhs < 0)
		{
			m_data = bigint_algo::negate(m_data);
		}
	}

	constexpr void
	operator/=(fixed_bigint const& rhs) noexcept
	{
		if (Signed)
		{
			auto lsign = bigint_algo::get_sign(m_data);
			auto rsign = bigint_algo::get_sign(rhs.m_data);

			m_data = bigint_algo::divide(abs(m_data), abs(rhs.m_data));

			if (lsign != rsign)
			{
				m_data = bigint_algo::negate(m_data);
			}
		}
		else
		{
			m_data = bigint_algo::divide(m_data, rhs.m_data);
		}
	}

	template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
	/*constexpr*/ void
	operator/=(Float rhs) noexcept
	{
		*this *= (Float(1) / rhs);
	}

	constexpr void
	operator%=(fixed_bigint const& rhs) noexcept
	{
		if (Signed)
		{
			auto lsign = bigint_algo::get_sign(m_data);

			m_data = bigint_algo::modulus(abs(m_data), abs(rhs.m_data));

			if (lsign < 0)
			{
				m_data = bigint_algo::negate(m_data);
			}
		}
		else
		{
			m_data = bigint_algo::modulus(m_data, rhs.m_data);
		}
	}

	constexpr void
	operator&=(fixed_bigint const& rhs) noexcept
	{
		bigint_algo::bit_and(m_data, rhs.m_data);
	}

	constexpr void
	operator|=(fixed_bigint const& rhs) noexcept
	{
		bigint_algo::bit_or(m_data, rhs.m_data);
	}

	constexpr void
	operator^=(fixed_bigint const& rhs) noexcept
	{
		bigint_algo::bit_xor(m_data, rhs.m_data);
	}

	constexpr fixed_bigint
	operator~() const noexcept
	{
		return bigint_algo::bit_not(m_data);
	}

	constexpr void
	operator<<=(fixed_bigint const& rhs) noexcept
	{
		bigint_algo::bit_shift_left(m_data, rhs.m_data);
	}

	constexpr void
	operator>>=(fixed_bigint const& rhs) noexcept
	{
		bigint_algo::bit_shift_right(m_data, rhs.m_data);
	}

private:
	template <BKSGE_REQUIRES_PARAM(bksge::integral, Integral)>
	constexpr Integral to_arithmetic(bksge::detail::overload_priority<1>) const noexcept
	{
		return bigint_algo::to_arithmetic<Integral>(m_data);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
	constexpr Float to_arithmetic(bksge::detail::overload_priority<0>) const noexcept
	{
		if (Signed)
		{
			return bigint_algo::to_arithmetic<Float>(abs(m_data)) * bigint_algo::get_sign(m_data);
		}
		else
		{
			return bigint_algo::to_arithmetic<Float>(m_data);
		}
	}

public:
	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	explicit constexpr operator Arithmetic() const noexcept
	{
		return to_arithmetic<Arithmetic>(bksge::detail::overload_priority<1>{});
	}

	constexpr int
	compare(fixed_bigint const& rhs) const noexcept
	{
		if (Signed)
		{
			auto lsign = bigint_algo::get_sign(m_data);
			auto rsign = bigint_algo::get_sign(rhs.m_data);
			if (lsign != rsign)
			{
				return lsign;
			}
		}

		return bigint_algo::compare(m_data, rhs.m_data);
	}

	template <typename CharT>
	bksge::basic_string<CharT>
	to_basic_string() const
	{
		if (Signed)
		{
			bksge::basic_string<CharT> r;
			if (bigint_algo::get_sign(m_data) < 0)
			{
				r += '-';
			}
			return r + bigint_algo::to_basic_string<CharT>(abs(m_data));
		}
		else
		{
			return bigint_algo::to_basic_string<CharT>(m_data);
		}
	}

private:
	template <bksge::size_t... Indices>
	constexpr bksge::size_t
	hash_impl(bksge::index_sequence<Indices...>) const BKSGE_NOEXCEPT
	{
		return bksge::hash_combine(m_data[Indices]...);
	}

public:
	constexpr bksge::size_t
	hash() const BKSGE_NOEXCEPT
	{
		return hash_impl(bksge::make_index_sequence<N>{});
	}

private:
	vector_type	m_data;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_FIXED_BIGINT_HPP
