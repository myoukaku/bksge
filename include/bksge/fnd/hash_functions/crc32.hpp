/**
 *	@file	crc32.hpp
 *
 *	@brief	crc32クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_CRC32_HPP
#define BKSGE_FND_HASH_FUNCTIONS_CRC32_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	CRC-32 (巡回冗長検査)
 *
 *	CRCは誤り検出符号の一種である。
 *
 *	・パリティやチェックサムに比べて検出精度が高い
 *	・高速である
 *
 *	などの特徴を持つことから、伝送路ノイズなどによる誤りの検出によく使われる。
 *
 *	ただし、CRC値が変化しないように元のデータを改ざんすることは容易であり、
 *	CRC単独では意図的なデータ改ざんを検出する目的には向いていない。
 */
class crc32 : public hash_facade<crc32, bksge::uint32_t>
{
public:
	using result_type = bksge::uint32_t;
	using seed_type   = bksge::uint32_t;

	BKSGE_CONSTEXPR
	crc32(void)
		: crc32(0xffffffff)
	{}

	BKSGE_CONSTEXPR explicit
	crc32(seed_type seed)
		: m_seed(seed)
	{}

	BKSGE_CXX14_CONSTEXPR void
	set_seed(seed_type seed)
	{
		m_seed = seed;
	}

	template <typename Iterator>
	BKSGE_CXX14_CONSTEXPR result_type
	invoke(Iterator first, Iterator last) const;

private:
	seed_type		m_seed;
};

}	// namespace bksge

#include <bksge/fnd/hash_functions/inl/crc32_inl.hpp>

#endif // BKSGE_FND_HASH_FUNCTIONS_CRC32_HPP
