/**
 *	@file	primitive_topology_inl.hpp
 *
 *	@brief	PrimitiveTopology クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/primitive_topology.hpp>
#include <bksge/core/render/primitive_topology.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlPrimitiveTopology(bksge::PrimitiveTopology primitive_topology)
{
	switch (primitive_topology)
	{
	case bksge::PrimitiveTopology::kPoints:    return GL_POINTS;
	case bksge::PrimitiveTopology::kLines:     return GL_LINES;
	case bksge::PrimitiveTopology::kTriangles: return GL_TRIANGLES;
	}
	return GL_POINTS;
}

}	// namespace detail

BKSGE_INLINE
PrimitiveTopology::PrimitiveTopology(bksge::PrimitiveTopology primitive_topology)
	: m_primitive_topology(detail::ToGlPrimitiveTopology(primitive_topology))
{}

BKSGE_INLINE
PrimitiveTopology::operator ::GLenum() const
{
	return m_primitive_topology;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
