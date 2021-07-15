/**
 *	@file	djb_hash.hpp
 *
 *	@brief	djb_hashクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_DJB_HASH_HPP
#define BKSGE_FND_HASH_FUNCTIONS_DJB_HASH_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>

namespace bksge
{

/**
 *	@brief	djb_hash
 *
 *	D. J. Bernstein によるハッシュ関数
 *	http://cr.yp.to/hash.html
 */
class djb_hash : public hash_facade<djb_hash, std::uint32_t>
{
public:
	using result_type = std::uint32_t;
	using seed_type   = std::uint32_t;

	BKSGE_CONSTEXPR
	djb_hash(void)
		: djb_hash(5381)
	{}

	BKSGE_CONSTEXPR explicit
	djb_hash(seed_type seed)
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
			h = h * 33 + *first;
		}

		return h;
	}

private:
	seed_type		m_seed;
};

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_DJB_HASH_HPP
