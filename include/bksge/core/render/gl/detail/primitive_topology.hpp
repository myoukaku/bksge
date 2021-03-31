/**
 *	@file	primitive_topology.hpp
 *
 *	@brief	PrimitiveTopology クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_PRIMITIVE_TOPOLOGY_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_PRIMITIVE_TOPOLOGY_HPP

#include <bksge/core/render/fwd/primitive_topology_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	PrimitiveTopology を OpenGL の enum に変換
 */
class PrimitiveTopology
{
public:
	explicit PrimitiveTopology(bksge::PrimitiveTopology primitive_topology);

	operator ::GLenum() const;

private:
	::GLenum const	m_primitive_topology;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/primitive_topology_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_PRIMITIVE_TOPOLOGY_HPP
