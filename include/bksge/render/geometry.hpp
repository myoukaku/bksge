/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GEOMETRY_HPP
#define BKSGE_RENDER_GEOMETRY_HPP

#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/primitive.hpp>
#include <bksge/render/detail/fwd/vertex_array_fwd.hpp>
#include <bksge/render/detail/fwd/index_array_fwd.hpp>
#include <bksge/render/detail/fwd/vertex_layout_fwd.hpp>
#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/detail/identifiable.hpp>
#include <bksge/render/detail/vertex_array.hpp>
#include <bksge/render/detail/index_array.hpp>
//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
//#include <bksge/serialization/shared_ptr.hpp>
#include <cstddef>
#include <iterator>
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
		Primitive primitive,
		VertexRange const& vertex_range,
		IndexRange const& index_range)
		: Geometry(
			primitive,
			std::begin(vertex_range),
			std::end(vertex_range),
			std::begin(index_range),
			std::end(index_range))
	{}

	template <typename VertexRange>
	Geometry(
		Primitive primitive,
		VertexRange const& vertex_range)
		: Geometry(
			primitive,
			std::begin(vertex_range),
			std::end(vertex_range))
	{}

	template <
		typename VertexIterator,
		typename IndexIterator,
		typename VertexType = typename std::iterator_traits<VertexIterator>::value_type,
		typename IndexType = typename std::iterator_traits<IndexIterator>::value_type
	>
	Geometry(
		Primitive primitive,
		VertexIterator vertex_first,
		VertexIterator vertex_last,
		IndexIterator index_first,
		IndexIterator index_last)
		: m_primitive(primitive)
		, m_vertex_array(new VertexArray<VertexType>(vertex_first, vertex_last))
		, m_index_array(new IndexArray<IndexType>(index_first, index_last))
	{}

	template <
		typename VertexIterator,
		typename VertexType = typename std::iterator_traits<VertexIterator>::value_type
	>
	Geometry(
		Primitive primitive,
		VertexIterator vertex_first,
		VertexIterator vertex_last)
		: m_primitive(primitive)
		, m_vertex_array(new VertexArray<VertexType>(vertex_first, vertex_last))
		, m_index_array()
	{}

	Primitive const& primitive(void) const;
	VertexLayout const& vertex_layout(void) const;

	void const* vertex_array_data(void) const;
	std::size_t vertex_array_bytes(void) const;
	std::size_t vertex_array_count(void) const;

	void const* index_array_data(void) const;
	std::size_t index_array_bytes(void) const;
	std::size_t index_array_count(void) const;
	TypeEnum index_array_type(void) const;

private:
	Primitive					        m_primitive;
	std::shared_ptr<VertexArrayBase>	m_vertex_array;
	std::shared_ptr<IndexArrayBase>		m_index_array;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_id);
		ar & BKSGE_SERIALIZATION_NVP(m_primitive);
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

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_RENDER_GEOMETRY_HPP
