/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStage クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_SHADER_STAGE_HPP
#define BKSGE_RENDER_GL_DETAIL_SHADER_STAGE_HPP

#include <bksge/render/shader_stage.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	ShaderStage を OpenGL の enum に変換
 */
class ShaderStage
{
public:
	explicit ShaderStage(bksge::ShaderStage stage);

	operator ::GLenum() const;

private:
	::GLenum	m_stage;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/shader_stage_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_SHADER_STAGE_HPP
