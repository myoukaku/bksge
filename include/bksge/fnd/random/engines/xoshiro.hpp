/**
 *	@file	xoshiro.hpp
 *
 *	@brief	xoshiro の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANDOM_ENGINES_XOSHIRO_HPP
#define BKSGE_FND_RANDOM_ENGINES_XOSHIRO_HPP

#include <bksge/fnd/random/engines/detail/xorshift_base.hpp>
#include <bksge/fnd/bit/rotl.hpp>
#include <cstdint>	// uint64_t, uint32_t

namespace bksge
{

/**
 *	@brief	xoshiro256** (XOR/shift/rotate)
 */
class xoshiro256starstar : public xorshift_base<std::uint64_t, 4, xoshiro256starstar>
{
	using base_type = xorshift_base<std::uint64_t, 4, xoshiro256starstar>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 17;
		result_type const B = 45;
		result_type const S = 5;
		result_type const R = 7;
		result_type const T = 9;

		result_type const result = bksge::rotl(m_state[1] * S, R) * T;
		result_type const t = m_state[1] << A;
		m_state[2] ^= m_state[0];
		m_state[3] ^= m_state[1];
		m_state[1] ^= m_state[2];
		m_state[0] ^= m_state[3];
		m_state[2] ^= t;
		m_state[3] = bksge::rotl(m_state[3], B);
		return result;
	}
};

/**
 *	@brief	xoshiro256+
 */
class xoshiro256plus : public xorshift_base<std::uint64_t, 4, xoshiro256plus>
{
	using base_type = xorshift_base<std::uint64_t, 4, xoshiro256plus>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 17;
		result_type const B = 45;

		result_type const result = m_state[0] + m_state[3];
		result_type const t = m_state[1] << A;
		m_state[2] ^= m_state[0];
		m_state[3] ^= m_state[1];
		m_state[1] ^= m_state[2];
		m_state[0] ^= m_state[3];
		m_state[2] ^= t;
		m_state[3] = bksge::rotl(m_state[3], B);
		return result;
	}
};

/**
 *	@brief	xoshiro128**
 */
class xoshiro128starstar : public xorshift_base<std::uint32_t, 4, xoshiro128starstar>
{
	using base_type = xorshift_base<std::uint32_t, 4, xoshiro128starstar>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 9;
		result_type const B = 11;
		result_type const S = 5;
		result_type const R = 7;
		result_type const T = 9;

		result_type const result = bksge::rotl(m_state[1] * S, R) * T;
		result_type const t = m_state[1] << A;
		m_state[2] ^= m_state[0];
		m_state[3] ^= m_state[1];
		m_state[1] ^= m_state[2];
		m_state[0] ^= m_state[3];
		m_state[2] ^= t;
		m_state[3] = bksge::rotl(m_state[3], B);
		return result;
	}
};

/**
 *	@brief	xoshiro128+
 */
class xoshiro128plus : public xorshift_base<std::uint32_t, 4, xoshiro128plus>
{
	using base_type = xorshift_base<std::uint32_t, 4, xoshiro128plus>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 9;
		result_type const B = 11;

		result_type const result = m_state[0] + m_state[3];
		result_type const t = m_state[1] << A;
		m_state[2] ^= m_state[0];
		m_state[3] ^= m_state[1];
		m_state[1] ^= m_state[2];
		m_state[0] ^= m_state[3];
		m_state[2] ^= t;
		m_state[3] = bksge::rotl(m_state[3], B);
		return result;
	}
};

/**
 *	@brief	xoshiro512**
 */
class xoshiro512starstar : public xorshift_base<std::uint64_t, 8, xoshiro512starstar>
{
	using base_type = xorshift_base<std::uint64_t, 8, xoshiro512starstar>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 11;
		result_type const B = 21;
		result_type const S = 5;
		result_type const R = 7;
		result_type const T = 9;

		result_type const result = bksge::rotl(m_state[1] * S, R) * T;
		result_type const t = m_state[1] << A;
		m_state[2] ^= m_state[0];
		m_state[5] ^= m_state[1];
		m_state[1] ^= m_state[2];
		m_state[7] ^= m_state[3];
		m_state[3] ^= m_state[4];
		m_state[4] ^= m_state[5];
		m_state[0] ^= m_state[6];
		m_state[6] ^= m_state[7];
		m_state[6] ^= t;
		m_state[7] = bksge::rotl(m_state[7], B);
		return result;
	}
};

/**
 *	@brief	xoshiro512+
 */
class xoshiro512plus : public xorshift_base<std::uint64_t, 8, xoshiro512plus>
{
	using base_type = xorshift_base<std::uint64_t, 8, xoshiro512plus>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 11;
		result_type const B = 21;

		result_type const result = m_state[0] + m_state[2];
		result_type const t = m_state[1] << A;
		m_state[2] ^= m_state[0];
		m_state[5] ^= m_state[1];
		m_state[1] ^= m_state[2];
		m_state[7] ^= m_state[3];
		m_state[3] ^= m_state[4];
		m_state[4] ^= m_state[5];
		m_state[0] ^= m_state[6];
		m_state[6] ^= m_state[7];
		m_state[6] ^= t;
		m_state[7] = bksge::rotl(m_state[7], B);
		return result;
	}
};

}	// namespace bksge

#endif // BKSGE_FND_RANDOM_ENGINES_XOSHIRO_HPP
