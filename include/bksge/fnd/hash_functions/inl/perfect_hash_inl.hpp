/**
 *	@file	perfect_hash_inl.hpp
 *
 *	@brief	perfect_hashクラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_INL_PERFECT_HASH_INL_HPP
#define BKSGE_FND_HASH_FUNCTIONS_INL_PERFECT_HASH_INL_HPP

#include <bksge/fnd/hash_functions/perfect_hash.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cmath/ceil.hpp>
#include <bksge/fnd/algorithm/ranges/reverse.hpp>
#include <bksge/fnd/algorithm/ranges/fill.hpp>
//#include <bksge/fnd/random/mersenne_twister_engine.hpp>
#include <random>
#include <bksge/fnd/queue.hpp>

namespace bksge
{

template <typename Hasher> inline
perfect_hash<Hasher>::perfect_hash(void)
	: m_vertices_num(0)
{
}

template <typename Hasher> inline
bool perfect_hash<Hasher>::build(bksge::vector<bksge::string> const& keys)
{
	static int const kNumTrial = 100;
	static double const kScale = 1.3;
	m_vertices_num = bksge::max(5, static_cast<int>(bksge::ceil(keys.size() * kScale / 3)));
	int const num_3v = m_vertices_num * 3;
	std::mt19937 rng;

	for (int t = 0; t < kNumTrial; ++t)
	{
		// Generate a candidate set of the seeds
		for (auto& seed : m_seeds)
		{
			seed = rng();
		}

		// Generate the edges
		bksge::vector<bksge::vector<int>> edges;

		for (auto const& key : keys)
		{
			bksge::vector<int> edge;

			{
				int offset = 0;

				for (auto const& seed : m_seeds)
				{
					auto const h = Hasher(seed)(key.data(), key.size());
					edge.push_back(h % m_vertices_num + offset);
					offset += m_vertices_num;
				}
			}

			edges.push_back(edge);
		}

		// Construct the adjacency list
		bksge::vector<bksge::vector<int>> adj(num_3v);

		{
			int i = 0;

			for (auto const& edge : edges)
			{
				for (auto const& e : edge)
				{
					adj[e].push_back(i);
				}

				++i;
			}
		}

		// Prepare for BFS
		bksge::vector<int> deg(num_3v);
		bksge::queue<int> que;

		for (int i = 0; i < num_3v; ++i)
		{
			deg[i] = static_cast<int>(adj[i].size());

			if (deg[i] == 1)
			{
				que.push(i);
			}
		}

		// BFS
		bksge::vector<bool> edge_del(edges.size());
		bksge::vector<int> edge_ord;
		bksge::vector<int> edge_to_vertex(edges.size());

		while (!que.empty())
		{
			int const v = que.front();
			que.pop();

			// Find the last remaining edge connected to |v|
			int eid = -1;

			for (auto const& a : adj[v])
			{
				if (!edge_del[a])
				{
					eid = a;
				}
			}

			if (eid == -1)
			{
				continue;
			}

			edge_del[eid] = true;
			edge_ord.push_back(eid);
			edge_to_vertex[eid] = v;

			// Decrease |deg| and enque vertices
			for (auto const w : edges[eid])
			{
				if (--deg[w] == 1)
				{
					que.push(w);
				}
			}
		}

		// Failed, i.e. the graph has cycles
		if (edge_ord.size() != edges.size())
		{
			continue;
		}

		// Compute |g|
		bksge::ranges::reverse(edge_ord);
		bksge::vector<bool> vertex_vis(num_3v);
		bksge::vector<int> tg(num_3v, 3);

		for (auto const eid : edge_ord)
		{
			auto const& edge = edges[eid];
			int const v = edge_to_vertex[eid];

			tg[v] = 0;

			{
				int j = 0;

				for (auto const& e : edge)
				{
					if (e == v)
					{
						tg[v] += j;
					}
					else if (vertex_vis[e])
					{
						tg[v] += 3 - tg[e];
					}

					++j;
				}
			}

			tg[v] %= 3;
			vertex_vis[v] = true;
		}

		m_g.resize((num_3v + 3) / 4);
		bksge::ranges::fill(m_g, static_cast<bksge::uint8_t>(0));

		for (int i = 0; i < num_3v; ++i)
		{
			m_g[i / 4] |= tg[i] << ((i % 4) * 2);
		}

		return true;
	}

	// Failed
	m_vertices_num = 0;
	return false;
}

template <typename Hasher>
template <typename Iterator>
inline BKSGE_CONSTEXPR auto
perfect_hash<Hasher>::invoke(Iterator first, Iterator last) const
-> result_type
{
	return invoke_impl(
		Hasher(m_seeds[0])(first, last) % m_vertices_num,
		Hasher(m_seeds[1])(first, last) % m_vertices_num + m_vertices_num,
		Hasher(m_seeds[2])(first, last) % m_vertices_num + m_vertices_num * 2);
}

template <typename Hasher>
inline auto
perfect_hash<Hasher>::invoke_impl(result_type v0, result_type v1, result_type v2) const
-> result_type
{
	result_type const v[3] =
	{
		v0,
		v1,
		v2,
	};
	return v[(g(v[0]) + g(v[1]) + g(v[2])) % 3];
}

template <typename Hasher> inline
auto perfect_hash<Hasher>::range(void) const -> result_type
{
	return m_vertices_num * 3;
}

template <typename Hasher> inline
int perfect_hash<Hasher>::g(int i) const
{
	return 3 & (m_g[i / 4] >> ((i % 4) * 2));
}

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_INL_PERFECT_HASH_INL_HPP
