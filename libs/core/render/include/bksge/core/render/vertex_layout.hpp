﻿/**
 *	@file	vertex_layout.hpp
 *
 *	@brief	VertexLayout の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VERTEX_LAYOUT_HPP
#define BKSGE_CORE_RENDER_VERTEX_LAYOUT_HPP

#include <bksge/core/render/fwd/vertex_layout_fwd.hpp>
#include <bksge/core/render/detail/vertex_attribute.hpp>
#include <bksge/core/render/semantic.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	頂点レイアウト
 */
class VertexLayout
{
private:
	using VertexAttributeArray = bksge::vector<VertexAttribute>;

public:
	VertexLayout(void);

	// コピー禁止
	VertexLayout(VertexLayout const&) = delete;
	VertexLayout& operator=(VertexLayout const&) = delete;

	// ムーブ可能
	VertexLayout(VertexLayout&& rhs);
	VertexLayout& operator=(VertexLayout&& rhs);

	VertexAttribute const* FindVertexAttributeBySemantic(Semantic semantic) const;

	VertexAttributeArray const& vertex_attribute_array(void) const;
	bksge::size_t total_bytes(void) const;

	void AddAttribute(VertexAttribute const& attribute);

private:
	VertexAttributeArray m_vertex_attribute_array;
	bksge::size_t        m_total_bytes;

private:
	friend bool operator==(VertexLayout const& lhs, VertexLayout const& rhs);
};

bool operator!=(VertexLayout const& lhs, VertexLayout const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/vertex_layout_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VERTEX_LAYOUT_HPP
