/**
 *	@file	unit_test_render_gl_shader_stage.cpp
 *
 *	@brief	ShaderStage のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/detail/shader_stage.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlShaderStageTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_VERTEX_SHADER,          bksge::render::gl::ShaderStage(bksge::ShaderStage::kVertex));
	EXPECT_EQ((GLenum)GL_GEOMETRY_SHADER,        bksge::render::gl::ShaderStage(bksge::ShaderStage::kGeometry));
	EXPECT_EQ((GLenum)GL_FRAGMENT_SHADER,        bksge::render::gl::ShaderStage(bksge::ShaderStage::kFragment));
	EXPECT_EQ((GLenum)GL_TESS_CONTROL_SHADER,    bksge::render::gl::ShaderStage(bksge::ShaderStage::kTessellationControl));
	EXPECT_EQ((GLenum)GL_TESS_EVALUATION_SHADER, bksge::render::gl::ShaderStage(bksge::ShaderStage::kTessellationEvaluation));
#endif
}
