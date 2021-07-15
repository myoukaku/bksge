/**
 *	@file	fnv_hash.hpp
 *
 *	@brief	fnv_hashクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_FNV_HASH_HPP
#define BKSGE_FND_HASH_FUNCTIONS_FNV_HASH_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>

namespace bksge
{

/**
 *	@brief	FNV ハッシュ
 *
 *	FNV(Fowler–Noll–Vo) ハッシュは Glenn Fowler, Landon Curt Noll, Phong Vo の3人によって作られた、
 *	1バイトごとに乗算1回と排他的論理和1回という高速なハッシュ関数。
 *	http://www.isthe.com/chongo/tech/comp/fnv/
 */
class fnv_hash : public hash_facade<fnv_hash, std::uint32_t>
{
public:
	using result_type = std::uint32_t;
	using seed_type   = std::uint32_t;

	BKSGE_CONSTEXPR
	fnv_hash(void)
		: fnv_hash(0x811c9dc5)
	{}

	BKSGE_CONSTEXPR explicit
	fnv_hash(seed_type seed)
		: m_seed(seed)
	{}

	BKSGE_CXX14_CONSTEXPR void
	set_seed(seed_type seed)
	{
		m_seed = seed;
	}

	template <typename Iterator>
	BKSGE_CXX14_CONSTEXPR result_type
	invoke(Iterator first, Iterator last) const
	{
		auto h = m_seed;

		for (; first != last; ++first)
		{
			h = (h * 0x01000193) ^ *first;
		}

		return h;
	}

private:
	seed_type		m_seed;
};

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_FNV_HASH_HPP
