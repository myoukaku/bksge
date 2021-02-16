/**
 *	@file	arbitrary_bigint.hpp
 *
 *	@brief	arbitrary_bigint クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_ARBITRARY_BIGINT_HPP
#define BKSGE_FND_BIGINT_DETAIL_ARBITRARY_BIGINT_HPP

#include <bksge/fnd/bigint/detail/bigint_algo.hpp>
#include <bksge/fnd/bigint/detail/fixed_bigint.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/unsigned_integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace detail
{

class arbitrary_bigint
{
private:
	using element_type = bksge::uint32_t;
	using vector_type = bksge::vector<element_type>;

public:
	/*constexpr*/ arbitrary_bigint() noexcept
		: m_sign(1)
		, m_magnitude{0}
	{}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	/*constexpr*/ arbitrary_bigint(Arithmetic x)
	{
		m_sign = bigint_algo::init_from_value(m_magnitude, x);
	}

	template <bksge::size_t B2, bool S2>
	/*constexpr*/ arbitrary_bigint(fixed_bigint<B2, S2> const& other) noexcept
	{
		if (S2)
		{
			m_sign = bigint_algo::get_sign(other.m_data);
			m_magnitude = bigint_algo::construct_from_vector<vector_type>(bigint_algo::abs(other.m_data));
		}
		else
		{
			m_sign = 1;
			m_magnitude = bigint_algo::construct_from_vector<vector_type>(other.m_data);
		}
	}

	template <bksge::size_t B2, bool S2>
	/*constexpr*/ operator fixed_bigint<B2, S2>() const
	{
		using vec_type = typename fixed_bigint<B2, S2>::vector_type;
		auto mag = bigint_algo::construct_from_vector<vec_type>(m_magnitude);
		if (m_sign < 0)
		{
			mag = bigint_algo::negate(mag);
		}
		return {mag};
	}

	template <typename CharT>
	/*constexpr*/ arbitrary_bigint(bksge::basic_string_view<CharT> str)
		: m_sign(1)
		, m_magnitude{0}
	{
		m_sign = bigint_algo::init_from_string(m_magnitude, str);
	}

private:
	/*constexpr*/ arbitrary_bigint(int sign, vector_type const& mag)
		: m_sign(sign)
		, m_magnitude(mag)
	{}

private:
	/*constexpr*/ void add_impl(arbitrary_bigint const& rhs)
	{
		bigint_algo::add(m_magnitude, rhs.m_magnitude);
	}

	/*constexpr*/ void sub_impl(arbitrary_bigint const& rhs)
	{
		auto t = bigint_algo::compare(m_magnitude, rhs.m_magnitude);

		if (t == 0)
		{
			m_magnitude = {0};
			m_sign = 1;
		}
		else if (t > 0)
		{
			// lhs = lhs - rhs
			bigint_algo::sub(m_magnitude, rhs.m_magnitude);
		}
		else if (t < 0)
		{
			// lhs = rhs - lhs
			vector_type tmp(rhs.m_magnitude);
			bigint_algo::sub(tmp, m_magnitude);
			m_magnitude = tmp;
			m_sign = -m_sign;
		}
	}

public:
	/*constexpr*/ arbitrary_bigint
	operator-() const noexcept
	{
		if (bigint_algo::is_zero(m_magnitude))
		{
			return *this;
		}
		return {-m_sign, m_magnitude};
	}

	/*constexpr*/ void
	operator+=(arbitrary_bigint const& rhs) noexcept
	{
		if (m_sign != rhs.m_sign)
		{
			sub_impl(rhs);
		}
		else
		{
			add_impl(rhs);
		}
	}

	/*constexpr*/ void
	operator-=(arbitrary_bigint const& rhs) noexcept
	{
		if (m_sign != rhs.m_sign)
		{
			add_impl(rhs);
		}
		else
		{
			sub_impl(rhs);
		}
	}

	/*constexpr*/ void
	operator*=(arbitrary_bigint const& rhs) noexcept
	{
		m_magnitude = bigint_algo::multiply(m_magnitude, rhs.m_magnitude);
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
		else
		{
			m_sign *= rhs.m_sign;
		}
	}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	/*constexpr*/ void
	operator*=(Arithmetic rhs) noexcept
	{
		m_magnitude = bigint_algo::multiply(m_magnitude, bksge::abs(rhs));
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
		else
		{
			m_sign *= (rhs < 0 ? -1 : 1);
		}
	}

	/*constexpr*/ void
	operator/=(arbitrary_bigint const& rhs) noexcept
	{
		m_magnitude = bigint_algo::divide(m_magnitude, rhs.m_magnitude);
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
		else
		{
			m_sign /= rhs.m_sign;
		}
	}

	template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
	/*constexpr*/ void
	operator/=(Float rhs) noexcept
	{
		*this *= (Float(1) / rhs);
	}

	/*constexpr*/ void
	operator%=(arbitrary_bigint const& rhs) noexcept
	{
		m_magnitude = bigint_algo::modulus(m_magnitude, rhs.m_magnitude);
		if (bigint_algo::is_zero(m_magnitude))
		{
			m_sign = 1;
		}
	}

	/*constexpr*/ void
	operator&=(arbitrary_bigint const& rhs) noexcept
	{
		bigint_algo::bit_and(m_magnitude, rhs.m_magnitude);
	}

	/*constexpr*/ void
	operator|=(arbitrary_bigint const& rhs) noexcept
	{
		bigint_algo::bit_or(m_magnitude, rhs.m_magnitude);
	}

	/*constexpr*/ void
	operator^=(arbitrary_bigint const& rhs) noexcept
	{
		bigint_algo::bit_xor(m_magnitude, rhs.m_magnitude);
	}

	/*constexpr*/ void
	operator<<=(arbitrary_bigint const& rhs) noexcept
	{
		bigint_algo::bit_shift_left(m_magnitude, rhs.m_magnitude);
	}

	/*constexpr*/ void
	operator>>=(arbitrary_bigint const& rhs) noexcept
	{
		bigint_algo::bit_shift_right(m_magnitude, rhs.m_magnitude);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
	explicit /*constexpr*/ operator Arithmetic() const noexcept
	{
		return static_cast<Arithmetic>(bigint_algo::to_arithmetic<Arithmetic>(m_magnitude) * m_sign);
	}

	/*constexpr*/ int
	compare(arbitrary_bigint const& rhs) const noexcept
	{
		if (m_sign != rhs.m_sign)
		{
			return m_sign;
		}

		return bigint_algo::compare(m_magnitude, rhs.m_magnitude) * m_sign;
	}

	template <typename CharT>
	/*constexpr*/ bksge::basic_string<CharT>
	to_basic_string() const
	{
		bksge::basic_string<CharT> r;
		if (m_sign < 0)
		{
			r += '-';
		}
		return r + bigint_algo::to_basic_string<CharT>(m_magnitude);
	}

	/*constexpr*/ bksge::size_t
	hash() const BKSGE_NOEXCEPT
	{
		bksge::size_t result = bksge::hash_combine(m_sign);
		for (auto mag : m_magnitude)
		{
			result = bksge::hash_combine(result, mag);
		}
		return result;
	}

private:
	int			m_sign = 1;	// m_magnitude >= 0 なら 1、m_magnitude < 0 なら -1
	vector_type	m_magnitude;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_ARBITRARY_BIGINT_HPP
