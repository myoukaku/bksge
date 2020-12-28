/**
 *	@file	minimal_perfect_hash.hpp
 *
 *	@brief	minimal_perfect_hashクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_MINIMAL_PERFECT_HASH_HPP
#define BKSGE_FND_HASH_FUNCTIONS_MINIMAL_PERFECT_HASH_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/hash_functions/perfect_hash.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string.hpp>

namespace bksge
{

/**
 *	@brief	最小完全ハッシュ関数を作るクラスです
 *
 *	ハッシュ関数が完全であるとは、単射であること、つまりハッシュ値の衝突がないことです。
 *	ハッシュ関数が最小であるとは、n個のキーに対してその値域が[0, n)であることです。
 *	入力される範囲があらかじめわかっている場合のみ、最小完全ハッシュ関数を作ることができます。
 *
 *	使い方
 *	@code
 *
 *	// キーの集合を用意します
 *	vector<string> keys;
 *	keys.push_back("hoge");
 *	keys.push_back("huga");
 *	keys.push_back("piyo");
 *
 *	// 最小完全ハッシュ関数を作成します
 *	minimal_perfect_hash<> mph;
 *	bool result = mph.build(keys);	// 作成に成功したらtrueを返します
 *
 *	// ハッシュ値を取得します
 *	auto h = mph("hoge");
 *
 *	@endcode
 */
template <typename Hasher>
class minimal_perfect_hash : public hash_facade<minimal_perfect_hash<Hasher>, bksge::uint32_t>
{
public:
	using result_type = bksge::uint32_t;
	using seed_type   = typename Hasher::seed_type;

	minimal_perfect_hash(void);

	bool build(bksge::vector<bksge::string> const& keys);

	result_type range(void) const;

	template <typename Iterator>
	BKSGE_CONSTEXPR result_type
	invoke(Iterator first, Iterator last) const;

private:
	template <typename T>
	result_type
	invoke_impl(T i) const;

private:
	perfect_hash<Hasher>	        m_perfect_hash;
	result_type				        m_range;
	bksge::vector<result_type>		m_exists;
	bksge::vector<result_type>		m_exists_acm256;
	bksge::vector<result_type>		m_exists_acm32;
};

}	// namespace bksge

#include <bksge/fnd/hash_functions/inl/minimal_perfect_hash_inl.hpp>

#endif // BKSGE_FND_HASH_FUNCTIONS_MINIMAL_PERFECT_HASH_HPP
