/**
 *	@file	vertex.hpp
 *
 *	@brief	Vertex の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VERTEX_HPP
#define BKSGE_CORE_RENDER_VERTEX_HPP

#include <bksge/core/render/vertex_layout.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>

namespace bksge
{

namespace render
{

namespace detail
{

template <typename T>
struct VertexBase
{
	static VertexLayout const& vertex_layout(void)
	{
		static VertexLayout const s_layout = MakeVertexLayout();
		return s_layout;
	}

	static VertexLayout MakeVertexLayout(void)
	{
		VertexLayout layout;
		T::AddVertexAttribute(&layout);
		return layout;
	}
};

}	// namespace detail

/**
 *	@brief	頂点データ
 *
 *	テンプレートパラメータにVertexElementを与えて、
 *	任意のフォーマットの頂点データを定義することができます。
 *
 *	Vertex<T1, T2, T3> とした場合、
 *
 *	@code
 *	struct Vertex
 *	{
 *		T1	value1;
 *		T2	value2;
 *		T3	value3;
 *	};
 *	@endcode
 *
 *	と同じような意味になります。
 *
 *	使い方：
 *	@code
 *	// 位置、色、UVを持つ頂点データの場合
 *	Vertex<VPosition, VColor, VTexCoord> const vertex_array[] =
 *	{
 *		{{{ x, y, z }}, {{ r, g, b, a }}, {{ u, v }}},
 *		...
 *	};
 *
 *	// 位置、法線、UV、ブレンド係数、ブレンドインデックスを持つ頂点データの場合
 *	Vertex<VPosition, VNormal, VTexCoord, VBlendWeight, VBlendIndices> const vertex_array[] =
 *	{
 *		{{{ x, y, z }}, {{ nx, ny, nz }}, {{ u, v }}, {{ 1, 0, 0, 0 }}, {{ 0, 1, 2, 3 }}},
 *		...
 *	};
 *	@endcode
 */
template <typename... Types>
struct Vertex;

// std::tupleを使うと楽に実装できそうだが、
// メンバの並びが与えた引数と逆順になってしまうので、
// 仕方なく自前で実装している。
// 逆になるのがstd::tupleの仕様として決められているのであれば、
// パラメータを逆順にしてstd::tupleに与えるという方法もあったが、
// 仕様なのか実装依存なのかわからなかった。


template <typename T>
struct Vertex<T> : public detail::VertexBase<Vertex<T>>
{
	T	m_value;

	Vertex(void)
		: m_value()
	{}

	// cppcheck-suppress noExplicitConstructor
	Vertex(T const& value)
		: m_value(value)
	{}

	static void AddVertexAttribute(VertexLayout* layout)
	{
		auto offset = layout->total_bytes();
		layout->AddAttribute(MakeVertexAttribute<T>(offset));
	}

	bool operator==(Vertex const& rhs) const
	{
		return m_value == rhs.m_value;
	}

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif
};

template <typename T, typename... Rest>
struct Vertex<T, Rest...> : public detail::VertexBase<Vertex<T, Rest...>>
{
	using RestTypes = Vertex<Rest...>;

	T			m_value;
	RestTypes	m_rest;

	Vertex(void)
		: m_value()
		, m_rest()
	{}

	Vertex(T const& value, Rest const&... rest)
		: m_value(value)
		, m_rest(rest...)
	{}

	static void AddVertexAttribute(VertexLayout* layout)
	{
		Vertex<T>::AddVertexAttribute(layout);
		RestTypes::AddVertexAttribute(layout);
	}

	bool operator==(Vertex const& rhs) const
	{
		return
			m_value == rhs.m_value &&
			m_rest  == rhs.m_rest;
	}

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_value);
		ar & BKSGE_SERIALIZATION_NVP(m_rest);
	}
#endif
};

template <typename... Types>
bool operator!=(Vertex<Types...> const& lhs, Vertex<Types...> const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

using render::Vertex;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VERTEX_HPP
