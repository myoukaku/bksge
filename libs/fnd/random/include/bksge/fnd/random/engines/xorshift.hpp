/**
 *	@file	xorshift.hpp
 *
 *	@brief	xorshift の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANDOM_ENGINES_XORSHIFT_HPP
#define BKSGE_FND_RANDOM_ENGINES_XORSHIFT_HPP

#include <bksge/fnd/random/engines/detail/xorshift_base.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/cstdint/uint64_t.hpp>

namespace bksge
{

/**
 *	@brief	xorshift32
 */
class xorshift32 : public xorshift_base<bksge::uint32_t, 1, xorshift32>
{
	using base_type = xorshift_base<bksge::uint32_t, 1, xorshift32>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 13;
		result_type const B = 17;
		result_type const C =  5;

		auto x = m_state[0];
		x ^= x << A;
		x ^= x >> B;
		x ^= x << C;
		m_state[0] = x;
		return x;
	}
};

/**
 *	@brief	xorshift64
 */
class xorshift64 : public xorshift_base<bksge::uint64_t, 1, xorshift64>
{
	using base_type = xorshift_base<bksge::uint64_t, 1, xorshift64>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 13;
		result_type const B =  7;
		result_type const C = 17;

		auto x = m_state[0];
		x^= x << A;
		x^= x >> B;
		x^= x << C;
		m_state[0] = x;
		return x;
	}
};

/**
 *	@brief	xorshift128
 */
class xorshift128 : public xorshift_base<bksge::uint32_t, 4, xorshift128>
{
	using base_type = xorshift_base<bksge::uint32_t, 4, xorshift128>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 11;
		result_type const B =  8;
		result_type const C = 19;

		auto const s = m_state[0];
		auto t = m_state[3];
		t ^= t << A;
		t ^= t >> B;
		t ^= s;
		t ^= s >> C;
		m_state[3] = m_state[2];
		m_state[2] = m_state[1];
		m_state[1] = s;
		m_state[0] = t;
		return t;
	}
};

/**
 *	@brief	xorwow
 */
class xorwow : public xorshift_base<bksge::uint32_t, 5, xorwow>
{
	using base_type = xorshift_base<bksge::uint32_t, 5, xorwow>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 2;
		result_type const B = 1;
		result_type const C = 4;
		result_type const S = 362437;

		auto const s = m_state[0];
		auto t = m_state[3];
		t ^= t >> A;
		t ^= t << B;
		t ^= s;
		t ^= s << C;
		m_state[3] = m_state[2];
		m_state[2] = m_state[1];
		m_state[1] = s;
		m_state[0] = t;
		return t + (m_state[4] += S);
	}
};

/**
 *	@brief	xorshift64star
 */
class xorshift64star : public xorshift_base<bksge::uint64_t, 1, xorshift64star>
{
	using base_type = xorshift_base<bksge::uint64_t, 1, xorshift64star>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 12;
		result_type const B = 25;
		result_type const C = 27;
		result_type const S = 0x2545F4914F6CDD1D;

		auto x = m_state[0];
		x ^= x >> A;
		x ^= x << B;
		x ^= x >> C;
		m_state[0] = x;
		return x * S;
	}
};

/**
 *	@brief	xorshift1024star
 */
class xorshift1024star : public xorshift_base<bksge::uint64_t, 16, xorshift1024star>
{
	using base_type = xorshift_base<bksge::uint64_t, 16, xorshift1024star>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 31;
		result_type const B = 11;
		result_type const C = 30;
		result_type const S = 1181783497276652981;

		auto const s0 = m_state[m_p];
		m_p = ((m_p + 1) & 15);
		auto       s1 = m_state[m_p];
		s1 ^= s1 << A;
		s1 ^= s1 >> B;
		s1 ^= s0 ^ (s0 >> C);
		m_state[m_p] = s1;
		return s1 * S;
	}

private:
	int	m_p = 0;
};

/**
 *	@brief	xorshift128plus
 */
class xorshift128plus : public xorshift_base<bksge::uint64_t, 2, xorshift128plus>
{
	using base_type = xorshift_base<bksge::uint64_t, 2, xorshift128plus>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 23;
		result_type const B = 17;
		result_type const C = 26;

		auto       x = m_state[0];
		auto const y = m_state[1];
		m_state[0] = y;
		x ^= x << A;
		m_state[1] = x ^ y ^ (x >> B) ^ (y >> C);
		return m_state[1] + y;
	}
};

}	// namespace bksge

#endif // BKSGE_FND_RANDOM_ENGINES_XORSHIFT_HPP
