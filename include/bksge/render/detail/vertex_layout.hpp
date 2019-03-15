/**
 *	@file	vertex_layout.hpp
 *
 *	@brief	VertexLayout の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_VERTEX_LAYOUT_HPP
#define BKSGE_RENDER_DETAIL_VERTEX_LAYOUT_HPP

#include <bksge/render/detail/fwd/vertex_layout_fwd.hpp>
#include <bksge/render/detail/vertex_attribute.hpp>
#include <bksge/render/semantic.hpp>
#include <cstddef>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief	頂点レイアウト
 */
class VertexLayout
{
public:
	VertexLayout(void);

	// コピー禁止
	VertexLayout(VertexLayout const&) = delete;
	VertexLayout& operator=(VertexLayout const&) = delete;

	// ムーブ可能
	VertexLayout(VertexLayout&& rhs);
	VertexLayout& operator=(VertexLayout&& rhs);

	VertexAttribute const* FindVertexAttributeBySemantic(Semantic semantic) const;

	std::size_t total_bytes(void) const;

	void AddAttribute(VertexAttribute const& attribute);

private:
	using VertexAttributeArray = std::vector<VertexAttribute>;

	VertexAttributeArray m_vertex_attribute_array;
	std::size_t        m_total_bytes;

private:
	friend bool operator==(VertexLayout const& lhs, VertexLayout const& rhs);
};

bool operator!=(VertexLayout const& lhs, VertexLayout const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/detail/inl/vertex_layout_inl.hpp>
#endif

#endif // BKSGE_RENDER_DETAIL_VERTEX_LAYOUT_HPP
