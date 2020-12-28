/**
 *	@file	sax_hash.hpp
 *
 *	@brief	sax_hashクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_SAX_HASH_HPP
#define BKSGE_FND_HASH_FUNCTIONS_SAX_HASH_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	sax_hash
 *
 *	Sax(Shift-Add-Xor) ハッシュ
 */
class sax_hash : public hash_facade<sax_hash, bksge::uint32_t>
{
public:
	using result_type = bksge::uint32_t;
	using seed_type   = bksge::uint32_t;

	BKSGE_CONSTEXPR
	sax_hash(void)
		: sax_hash(0)
	{}

	BKSGE_CONSTEXPR explicit
	sax_hash(seed_type seed)
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
			h = h ^ ((h << 5) + (h >> 2) + *first);
		}

		return h;
	}

private:
	seed_type		m_seed;
};

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_SAX_HASH_HPP
