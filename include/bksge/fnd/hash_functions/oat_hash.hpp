/**
 *	@file	oat_hash.hpp
 *
 *	@brief	oat_hashクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_OAT_HASH_HPP
#define BKSGE_FND_HASH_FUNCTIONS_OAT_HASH_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	oat_hash
 *
 *	Oat(one-at-a-time) ハッシュは Bob Jenkins によって作られたハッシュ関数。
 *	Jenkins Hash とも呼ばれる。
 *	http://en.wikipedia.org/wiki/Jenkins_hash_function
 */
class oat_hash : public hash_facade<oat_hash, bksge::uint32_t>
{
public:
	using result_type = bksge::uint32_t;
	using seed_type   = bksge::uint32_t;

	BKSGE_CONSTEXPR
	oat_hash(void)
		: oat_hash(0)
	{}

	BKSGE_CONSTEXPR explicit
	oat_hash(seed_type seed)
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
			h += *first;
			h += (h << 10);
			h ^= (h >> 6);
		}

		h += (h << 3);
		h ^= (h >> 11);
		h += (h << 15);

		return h;
	}

private:
	seed_type		m_seed;
};

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_OAT_HASH_HPP
