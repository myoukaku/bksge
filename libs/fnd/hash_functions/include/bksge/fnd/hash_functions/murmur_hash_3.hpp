/**
 *	@file	murmur_hash_3.hpp
 *
 *	@brief	murmur_hash_3クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_MURMUR_HASH_3_HPP
#define BKSGE_FND_HASH_FUNCTIONS_MURMUR_HASH_3_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>

namespace bksge
{

/**
 *	@brief	murmur_hash_3
 *
 *	MurmurHashは Austin Appleby によって作られたハッシュ関数。
 *	https://sites.google.com/site/murmurhash/
 */
class murmur_hash_3 : public hash_facade<murmur_hash_3, std::uint32_t>
{
public:
	using result_type = std::uint32_t;
	using seed_type   = std::uint32_t;

	BKSGE_CONSTEXPR
	murmur_hash_3(void);

	BKSGE_CONSTEXPR explicit
	murmur_hash_3(seed_type seed);

	BKSGE_CXX14_CONSTEXPR void
	set_seed(seed_type seed);

	template <typename Iterator>
	BKSGE_CXX14_CONSTEXPR result_type
	invoke(Iterator first, Iterator last) const;

private:
	seed_type		m_seed;
};

}	// namespace bksge

#include <bksge/fnd/hash_functions/inl/murmur_hash_3_inl.hpp>

#endif // BKSGE_FND_HASH_FUNCTIONS_MURMUR_HASH_3_HPP
