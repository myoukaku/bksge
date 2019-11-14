/**
 *	@file	resource_cache.hpp
 *
 *	@brief	ResourceCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_RESOURCE_CACHE_HPP
#define BKSGE_RENDER_GL_DETAIL_RESOURCE_CACHE_HPP

#include <bksge/render/gl/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/gl/detail/fwd/geometry_fwd.hpp>
#include <bksge/render/gl/detail/fwd/glsl_program_fwd.hpp>
#include <bksge/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class ResourceCache
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

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/resource_cache_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_RESOURCE_CACHE_HPP
