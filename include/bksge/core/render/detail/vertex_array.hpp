/**
 *	@file	vertex_array.hpp
 *
 *	@brief	VertexArray の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_VERTEX_ARRAY_HPP
#define BKSGE_CORE_RENDER_DETAIL_VERTEX_ARRAY_HPP

#include <bksge/core/render/detail/fwd/vertex_array_fwd.hpp>
#include <bksge/core/render/detail/vertex_array_base.hpp>
#include <bksge/core/render/vertex_layout.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/vector.hpp>
//#include <bksge/fnd/serialization/polymorphic_serializable.hpp>
//#include <bksge/fnd/serialization/version.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief	頂点配列
 */
template <typename T>
class VertexArray
	: public VertexArrayBase
	/*, private bksge::serialization::polymorphic_serializable<VertexArray<T>>*/
{
public:
	VertexArray(void);

	template <typename Iterator>
	VertexArray(Iterator first, Iterator last);

	// コピー禁止
	VertexArray(VertexArray const&) = delete;
	VertexArray& operator=(VertexArray const&) = delete;

	VertexLayout const& vertex_layout(void) const override;

	const_pointer data(void) const override;

	size_type bytes(void) const override;

	size_type count(void) const override;

private:
	VertexLayout	m_layout = T::make_vertex_layout();
	std::vector<T>	m_value;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(VertexArrayBase);
		ar & BKSGE_SERIALIZATION_NVP(m_layout);
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif
};

}	// namespace render

}	// namespace bksge

#include <bksge/core/render/detail/inl/vertex_array_inl.hpp>

#endif // BKSGE_CORE_RENDER_DETAIL_VERTEX_ARRAY_HPP
