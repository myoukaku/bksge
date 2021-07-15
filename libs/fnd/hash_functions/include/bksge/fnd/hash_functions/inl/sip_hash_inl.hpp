/**
 *	@file	sip_hash_inl.hpp
 *
 *	@brief	sip_hashクラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_INL_SIP_HASH_INL_HPP
#define BKSGE_FND_HASH_FUNCTIONS_INL_SIP_HASH_INL_HPP

#include <bksge/fnd/hash_functions/sip_hash.hpp>
#include <bksge/fnd/bit/rotl.hpp>
#include <bksge/fnd/cmath/round_down.hpp>
//#include <bksge/fnd/range/irange.hpp>
//#include <bksge/fnd/range/adaptor/as_array.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/utility/make_integer_sequence.hpp>
#include <cstddef>

namespace bksge
{

namespace sip_hash_detail
{

template <typename Iterator>
inline BKSGE_CXX14_CONSTEXPR bksge::uint64_t
read_64(Iterator p)
{
	bksge::uint64_t result = 0;

	for (int i = 0; i < 8; ++i)
	{
		result |= (static_cast<bksge::uint64_t>(p[i]) << (i * 8));
	}

	return result;
}

inline BKSGE_CXX14_CONSTEXPR void
sip_round(bksge::uint64_t& state0, bksge::uint64_t& state1, bksge::uint64_t& state2, bksge::uint64_t& state3)
{
	state0 += state1;
	state2 += state3;
	state1 = bksge::rotl(state1, 13);
	state3 = bksge::rotl(state3, 16);
	state1 ^= state0;
	state3 ^= state2;
	state0 = bksge::rotl(state0, 32);
	state2 += state1;
	state0 += state3;
	state1 = bksge::rotl(state1, 17);
	state3 = bksge::rotl(state3, 21);
	state1 ^= state2;
	state3 ^= state0;
	state2 = bksge::rotl(state2, 32);
}

template <typename Iterator>
inline BKSGE_CXX14_CONSTEXPR bksge::uint64_t
sip_hash_impl(
	Iterator first,
	Iterator last,
	bksge::uint64_t key0,
	bksge::uint64_t key1,
	int c_rounds,
	int d_rounds)
{
	auto state0 = key0 ^ UINT64_C(0x736f6d6570736575);
	auto state1 = key1 ^ UINT64_C(0x646f72616e646f6d);
	auto state2 = key0 ^ UINT64_C(0x6c7967656e657261);
	auto state3 = key1 ^ UINT64_C(0x7465646279746573);

	std::size_t const bytes = last - first;
	auto const tail_size = bytes & 7;
	auto const main_loop_end = first + bytes - tail_size;

	// The main loop
	for (; first != main_loop_end; first += 8)
	{
		auto const current_word = read_64(first);

		state3 ^= current_word;

		for (int i = 0; i < c_rounds; ++i)
		{
			sip_round(state0, state1, state2, state3);
		}

		state0 ^= current_word;
	}

	// We're left with 0..7 bytes.
	auto tail_word = static_cast<bksge::uint64_t>(bytes) << 56;

	for (std::size_t i = 0; i < tail_size; ++i)
	{
		tail_word |= static_cast<bksge::uint64_t>(first[i]) << (i * 8);
	}

	// Mix-in the tail block.
	state3 ^= tail_word;

	for (int i = 0; i < c_rounds; ++i)
	{
		sip_round(state0, state1, state2, state3);
	}

	state0 ^= tail_word;

	// The final sip_round
	state2 ^= 0xff;

	for (int i = 0; i < d_rounds; ++i)
	{
		sip_round(state0, state1, state2, state3);
	}

	return state0 ^ state1 ^ state2  ^ state3;
}

template <typename T, std::size_t N, T... Is>
inline BKSGE_CONSTEXPR bksge::array<T, N>
init_seed_impl(bksge::integer_sequence<T, Is...>)
{
	return {{Is...}};
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR bksge::array<T, N>
init_seed(bksge::array<T, N> const&)
{
	return init_seed_impl<T, N>(bksge::make_integer_sequence<T, N>{});
}

}	// namespace sip_hash_detail

template <int C, int D>
inline BKSGE_CONSTEXPR
sip_hash<C, D>::sip_hash(void)
	: m_seed(sip_hash_detail::init_seed(m_seed))
{}

template <int C, int D>
inline BKSGE_CONSTEXPR
sip_hash<C, D>::sip_hash(seed_type seed)
	: m_seed(seed)
{}

template <int C, int D>
inline BKSGE_CXX14_CONSTEXPR
void sip_hash<C, D>::set_seed(seed_type seed)
{
	m_seed = seed;
}

template <int C, int D>
template <typename Iterator>
inline BKSGE_CXX14_CONSTEXPR auto
sip_hash<C, D>::invoke(Iterator first, Iterator last) const -> result_type
{
	return sip_hash_detail::sip_hash_impl(
		first,
		last,
		sip_hash_detail::read_64(&m_seed[0]),
		sip_hash_detail::read_64(&m_seed[8]),
		C,
		D);
}

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_INL_SIP_HASH_INL_HPP
