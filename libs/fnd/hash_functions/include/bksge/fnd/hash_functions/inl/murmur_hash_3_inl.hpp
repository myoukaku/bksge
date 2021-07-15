/**
 *	@file	murmur_hash_3_inl.hpp
 *
 *	@brief	murmur_hash_3クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_INL_MURMUR_HASH_3_INL_HPP
#define BKSGE_FND_HASH_FUNCTIONS_INL_MURMUR_HASH_3_INL_HPP

#include <bksge/fnd/hash_functions/murmur_hash_3.hpp>
#include <bksge/fnd/bit/rotl.hpp>
#include <bksge/fnd/cmath/round_down.hpp>
#include <cstddef>
#include <cstdint>

namespace bksge
{

inline BKSGE_CONSTEXPR
murmur_hash_3::murmur_hash_3(void)
	: murmur_hash_3(0)
{
}

inline BKSGE_CONSTEXPR
murmur_hash_3::murmur_hash_3(seed_type seed)
	: m_seed(seed)
{
}

inline BKSGE_CXX14_CONSTEXPR
void murmur_hash_3::set_seed(seed_type seed)
{
	m_seed = seed;
}

namespace murmur_hash_3_detail
{

template <typename Iterator>
inline BKSGE_CONSTEXPR std::uint32_t
read_32(Iterator p)
{
#if defined(BKSGE_BIG_ENDIAN)
	// TODO
#else
	return
		(static_cast<std::uint32_t>(p[0]) << (0 * 8)) |
		(static_cast<std::uint32_t>(p[1]) << (1 * 8)) |
		(static_cast<std::uint32_t>(p[2]) << (2 * 8)) |
		(static_cast<std::uint32_t>(p[3]) << (3 * 8));
#endif
}

}	// namespace murmur_hash_3_detail

template <typename Iterator>
inline BKSGE_CXX14_CONSTEXPR auto
murmur_hash_3::invoke(Iterator first, Iterator last) const -> result_type
{
	std::size_t const bytes   = last - first;
	std::size_t const nblocks = bytes / 4;
	auto h1 = m_seed;

	std::uint32_t const c1 = 0xcc9e2d51;
	std::uint32_t const c2 = 0x1b873593;

	//----------
	// body

	for (std::size_t i = 0; i < nblocks; ++i)
	{
		auto k1 = murmur_hash_3_detail::read_32(first + i * 4);

		k1 *= c1;
		k1 = bksge::rotl(k1, 15);
		k1 *= c2;

		h1 ^= k1;
		h1 = bksge::rotl(h1, 13);
		h1 = h1 * 5 + 0xe6546b64;
	}

	//----------
	// tail

	{
		auto tail = (first + nblocks * 4);

		std::uint32_t k1 = 0;

		for (auto i = (bytes & 3); i >= 1; --i)
		{
			k1 ^= tail[i-1] << ((i-1) * 8);
		}

		k1 *= c1;
		k1 = bksge::rotl(k1, 15);
		k1 *= c2;
		h1 ^= k1;
	}

	//----------
	// finalization

	h1 ^= bytes;

	h1 ^= h1 >> 16;
	h1 *= 0x85ebca6b;
	h1 ^= h1 >> 13;
	h1 *= 0xc2b2ae35;
	h1 ^= h1 >> 16;

	return h1;
}

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_INL_MURMUR_HASH_3_INL_HPP
