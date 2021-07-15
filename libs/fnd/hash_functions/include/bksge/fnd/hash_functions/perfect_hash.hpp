/**
 *	@file	perfect_hash.hpp
 *
 *	@brief	perfect_hashクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_PERFECT_HASH_HPP
#define BKSGE_FND_HASH_FUNCTIONS_PERFECT_HASH_HPP

#include <bksge/fnd/hash_functions/hash_facade.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

/**
 *	@brief	完全ハッシュ関数を作るクラスです
 *
 *	ハッシュ関数が完全であるとは、単射であること、つまりハッシュ値の衝突がないことです。
 *	入力される範囲があらかじめわかっている場合のみ、完全ハッシュ関数を作ることができます。
 *
 *	※最小完全ハッシュ関数がほしい場合は、minimal_perfect_hashクラスを使ってください。
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
 *	// 完全ハッシュ関数を作成します
 *	perfect_hash<> ph;
 *	bool result = ph.build(keys);	// 作成に成功したらtrueを返します
 *
 *	// ハッシュ値を取得します
 *	auto h = ph("hoge");
 *
 *	@endcode
 */
template <typename Hasher>
class perfect_hash : public hash_facade<perfect_hash<Hasher>, std::uint32_t>
{
public:
	using result_type = std::uint32_t;
	using seed_type   = std::uint32_t;

	perfect_hash(void);

	bool build(bksge::vector<bksge::string> const& keys);

	result_type range(void) const;

	int g(int i) const;

	template <typename Iterator>
	BKSGE_CONSTEXPR result_type
	invoke(Iterator first, Iterator last) const;

private:
	result_type invoke_impl(result_type v0, result_type v1, result_type v2) const;

private:
	result_type				        m_vertices_num;	// Number of the vertices of each block in the hyper graph
	seed_type				        m_seeds[3];	// Generated set of the seeds
	bksge::vector<std::uint8_t>		m_g;	// G value of each vertices
};

}	// namespace bksge

#include <bksge/fnd/hash_functions/inl/perfect_hash_inl.hpp>

#endif // BKSGE_FND_HASH_FUNCTIONS_PERFECT_HASH_HPP
