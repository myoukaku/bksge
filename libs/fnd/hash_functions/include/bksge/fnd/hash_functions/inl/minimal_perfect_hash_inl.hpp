/**
 *	@file	minimal_perfect_hash_inl.hpp
 *
 *	@brief	minimal_perfect_hashクラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_INL_MINIMAL_PERFECT_HASH_INL_HPP
#define BKSGE_FND_HASH_FUNCTIONS_INL_MINIMAL_PERFECT_HASH_INL_HPP

#include <bksge/fnd/hash_functions/minimal_perfect_hash.hpp>
#include <bksge/fnd/bit/popcount.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
//#include <bksge/fnd/bit/make_bitmask_lower.hpp>
#include <bksge/fnd/algorithm/ranges/fill.hpp>
#include <cstdint>

namespace bksge
{

template <typename T>
inline BKSGE_CONSTEXPR T
make_bitmask_lower(int x) BKSGE_NOEXCEPT
{
	return
		x <= 0 ?
			0 :
		x >= static_cast<int>(bksge::bitsof<T>()) ?
			static_cast<T>(~0) :
		static_cast<T>(((T(1) << x) - 1));
}

template <typename Hasher> inline
minimal_perfect_hash<Hasher>::minimal_perfect_hash(void)
	: m_perfect_hash()
	, m_range()
	, m_exists()
	, m_exists_acm256()
	, m_exists_acm32()
{
}

template <typename Hasher> inline
bool minimal_perfect_hash<Hasher>::build(bksge::vector<bksge::string> const& keys)
{
	if (!m_perfect_hash.build(keys))
	{
		m_range = 0;
		return false;
	}

	auto const num_3v = m_perfect_hash.range();
	m_exists.resize((num_3v + 32 - 1) / 32);
	m_exists_acm256.resize((num_3v + 256 - 1) / 256);
	m_exists_acm32.resize((num_3v + 32 - 1) / 32);
	bksge::ranges::fill(m_exists,        0);
	bksge::ranges::fill(m_exists_acm256, 0);
	bksge::ranges::fill(m_exists_acm32,  0);

	result_type rnk = 0;

	for (result_type i = 0; i < num_3v; ++i)
	{
		if (i % 256 == 0)
		{
			m_exists_acm256[i / 256] = rnk;
		}

		if (i % 32 == 0)
		{
			m_exists_acm32[i / 32] = static_cast<std::uint8_t>(rnk - m_exists_acm256[i / 256]);
		}

		auto const g = m_perfect_hash.g(i);

		if (g != 3)
		{
			m_exists[i / 32] |= result_type(1) << (i % 32);
			++rnk;
		}
	}

	m_range = rnk;
	return true;
}

template <typename Hasher>
template <typename Iterator>
inline BKSGE_CONSTEXPR auto
minimal_perfect_hash<Hasher>::invoke(Iterator first, Iterator last) const
-> result_type
{
	return invoke_impl(m_perfect_hash(first, last));
}

template <typename Hasher>
template <typename T>
inline auto
minimal_perfect_hash<Hasher>::invoke_impl(T i) const
-> result_type
{
	return
		m_exists_acm256[i / 256] +
		m_exists_acm32[i / 32] +
		bksge::popcount(m_exists[i / 32] & bksge::make_bitmask_lower<result_type>(i % 32));
}

template <typename Hasher> inline
auto minimal_perfect_hash<Hasher>::range(void) const -> result_type
{
	return m_range;
}

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_INL_MINIMAL_PERFECT_HASH_INL_HPP
