/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GEOMETRY_HPP
#define BKSGE_CORE_RENDER_GEOMETRY_HPP

#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/primitive_topology.hpp>
#include <bksge/core/render/detail/fwd/vertex_array_fwd.hpp>
#include <bksge/core/render/detail/fwd/index_array_fwd.hpp>
#include <bksge/core/render/fwd/vertex_layout_fwd.hpp>
#include <bksge/core/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/core/render/detail/identifiable.hpp>
#include <bksge/core/render/detail/vertex_array.hpp>
#include <bksge/core/render/detail/index_array.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/shared_ptr.hpp>
//#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_value_type.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <memory>

namespace bksge
{

namespace render
{

/**
 *	@brief	幾何情報
 *
 *	頂点データ
 *	インデックスデータ
 *	プリミティブの種類
 *	頂点レイアウト
 */
class Geometry : public Identifiable
{
public:
	Geometry(void);

	template <typename VertexRange, typename IndexRange>
	Geometry(
		PrimitiveTopology primitive_topology,
		VertexRange const& vertex_range,
		IndexRange const& index_range)
		: Geometry(
			primitive_topology,
			bksge::begin(vertex_range),
			bksge::end(vertex_range),
			bksge::begin(index_range),
			bksge::end(index_range))
	{}

	template <typename VertexRange>
	Geometry(
		PrimitiveTopology primitive_topology,
		VertexRange const& vertex_range)
		: Geometry(
			primitive_topology,
			bksge::begin(vertex_range),
			bksge::end(vertex_range))
	{}

	template <
		typename VertexIterator,
		typename IndexIterator,
		typename VertexType = bksge::iterator_value_type<VertexIterator>,
		typename IndexType = bksge::iterator_value_type<IndexIterator>
	>
	Geometry(
		PrimitiveTopology primitive_topology,
		VertexIterator vertex_first,
		VertexIterator vertex_last,
		IndexIterator index_first,
		IndexIterator index_last)
		: m_primitive_topology(primitive_topology)
		, m_vertex_array(new VertexArray<VertexType>(vertex_first, vertex_last))
		, m_index_array(new IndexArray<IndexType>(index_first, index_last))
	{}

	template <
		typename VertexIterator,
		typename VertexType = bksge::iterator_value_type<VertexIterator>
	>
	Geometry(
		PrimitiveTopology primitive_topology,
		VertexIterator vertex_first,
		VertexIterator vertex_last)
		: m_primitive_topology(primitive_topology)
		, m_vertex_array(new VertexArray<VertexType>(vertex_first, vertex_last))
		, m_index_array()
	{}

	PrimitiveTopology const& primitive_topology(void) const;
	VertexLayout const& vertex_layout(void) const;

	void const*   vertex_array_data(void) const;
	bksge::size_t vertex_array_bytes(void) const;
	bksge::size_t vertex_array_count(void) const;

	void const*   index_array_data(void) const;
	bksge::size_t index_array_bytes(void) const;
	bksge::size_t index_array_count(void) const;
	TypeEnum index_array_type(void) const;

private:
	PrimitiveTopology					m_primitive_topology;
	std::shared_ptr<VertexArrayBase>	m_vertex_array;
	std::shared_ptr<IndexArrayBase>	m_index_array;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_id);
		ar & BKSGE_SERIALIZATION_NVP(m_primitive_topology);
		ar & BKSGE_SERIALIZATION_NVP(m_vertex_array);
		ar & BKSGE_SERIALIZATION_NVP(m_index_array);
	}
#endif

private:
	friend bool operator==(Geometry const& lhs, Geometry const& rhs);
};

bool operator!=(Geometry const& lhs, Geometry const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GEOMETRY_HPP
