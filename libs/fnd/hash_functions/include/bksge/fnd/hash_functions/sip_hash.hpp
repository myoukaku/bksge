/**
 *	@file	sip_hash.hpp
 *
 *	@brief	sip_hashクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_SIP_HASH_HPP
#define BKSGE_FND_HASH_FUNCTIONS_SIP_HASH_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/array/array.hpp>
#include <cstdint>

namespace bksge
{

/**
 *	@brief	sip_hash
 *
 *	SipHash は Jean-Philippe Aumasson と Daniel J. Bernstein によって作られた。
 *	一方向性を持つ暗号学的なハッシュ関数でありながら、
 *	短い入力に対してのオーバーヘッドが小さく、modを取った値が衝突しにくい
 *	という特性を持つ。
 *	Perl,Python,Rubyなど多くのソフトウェアのハッシュテーブルの実装に使われている。
 *	http://en.wikipedia.org/wiki/SipHash
 */
template <int CompressionRounds, int FinalizationRounds>
class sip_hash : public hash_facade<sip_hash<CompressionRounds, FinalizationRounds>, std::uint64_t>
{
public:
	using result_type = std::uint64_t;
	using seed_type   = bksge::array<std::uint8_t, 16>;

	BKSGE_CONSTEXPR
	sip_hash(void);

	BKSGE_CONSTEXPR explicit
	sip_hash(seed_type seed);

	BKSGE_CXX14_CONSTEXPR void
	set_seed(seed_type seed);

	template <typename Iterator>
	BKSGE_CXX14_CONSTEXPR result_type
	invoke(Iterator first, Iterator last) const;

private:
	seed_type		m_seed;
};

using sip_hash_2_4 = sip_hash<2, 4>;
using sip_hash_4_8 = sip_hash<4, 8>;

}	// namespace bksge

#include <bksge/fnd/hash_functions/inl/sip_hash_inl.hpp>

#endif // BKSGE_FND_HASH_FUNCTIONS_SIP_HASH_HPP
