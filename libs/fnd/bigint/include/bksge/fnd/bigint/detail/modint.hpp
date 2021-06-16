/**
 *	@file	modint.hpp
 *
 *	@brief	modint の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MODINT_HPP
#define BKSGE_FND_BIGINT_DETAIL_MODINT_HPP

#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <bksge::uint32_t Mod>
class modint
{
private:
	bksge::uint32_t m_value;

public:
	BKSGE_CONSTEXPR modint() BKSGE_NOEXCEPT
		: m_value(0)
	{};

	BKSGE_CONSTEXPR modint(bksge::int64_t n) BKSGE_NOEXCEPT
		: m_value((n >= 0 ? n : Mod - (-n) % Mod) % Mod)
	{};

	static BKSGE_CONSTEXPR bksge::uint32_t get_mod() BKSGE_NOEXCEPT
	{
		return Mod;
	}

	BKSGE_CONSTEXPR bksge::uint32_t get() const BKSGE_NOEXCEPT
	{
		return m_value;
	}

	BKSGE_CONSTEXPR bool operator==(modint const& m) const BKSGE_NOEXCEPT
	{
		return m_value == m.m_value;
	}

	BKSGE_CONSTEXPR bool operator!=(modint const& m) const BKSGE_NOEXCEPT
	{
		return m_value != m.m_value;
	}

	BKSGE_CXX14_CONSTEXPR modint& operator+=(modint const& m) BKSGE_NOEXCEPT
	{
		m_value += m.m_value;
		m_value = (m_value < Mod ? m_value : m_value - Mod);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR modint& operator-=(modint const& m) BKSGE_NOEXCEPT
	{
		m_value += Mod - m.m_value;
		m_value = (m_value < Mod ? m_value : m_value - Mod);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR modint& operator*=(modint const& m) BKSGE_NOEXCEPT
	{
		m_value = bksge::uint64_t(m_value) * m.m_value % Mod;
		return *this;
	}

	BKSGE_CONSTEXPR modint operator+(modint const& m) const BKSGE_NOEXCEPT
	{
		return modint(*this) += m;
	}

	BKSGE_CONSTEXPR modint operator-(modint const& m) const BKSGE_NOEXCEPT
	{
		return modint(*this) -= m;
	}

	BKSGE_CONSTEXPR modint operator*(modint const& m) const BKSGE_NOEXCEPT
	{
		return modint(*this) *= m;
	}

	BKSGE_CONSTEXPR modint inv() const
	{
		BKSGE_ASSERT(m_value != 0u);
		return pow(Mod - 2);
	}

	BKSGE_CONSTEXPR modint pow(bksge::uint64_t b) const BKSGE_NOEXCEPT
	{
		modint ans = 1, m = modint(*this);
		while (b)
		{
			if (b & 1)
			{
				ans *= m;
			}

			m *= m;
			b >>= 1;
		}

		return ans;
	}
};

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MODINT_HPP
