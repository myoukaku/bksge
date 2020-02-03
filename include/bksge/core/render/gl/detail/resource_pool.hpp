/**
 *	@file	resource_pool.hpp
 *
 *	@brief	ResourcePool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_RESOURCE_POOL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_RESOURCE_POOL_HPP

#include <bksge/core/render/gl/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/glsl_program_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class ResourcePool
{
public:
	GeometryShared    GetGlGeometry(bksge::Geometry const& geometry);
	GlslProgramShared GetGlslProgram(bksge::Shader const& shader);
	TextureShared     GetGlTexture(bksge::Texture const& texture);

private:
	GeometryMap               m_geometry_map;
	GlslProgramMap            m_shader_map;
	TextureMap                m_texture_map;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/resource_pool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_RESOURCE_POOL_HPP
