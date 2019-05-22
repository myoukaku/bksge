/**
 *	@file	unit_test_render_gl_gl_shader_stage.cpp
 *
 *	@brief	ToGlShaderStage のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_shader_stage.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlShaderStageTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_VERTEX_SHADER,          ToGlShaderStage(bksge::ShaderStage::kVertex));
	EXPECT_EQ((GLenum)GL_GEOMETRY_SHADER,        ToGlShaderStage(bksge::ShaderStage::kGeometry));
	EXPECT_EQ((GLenum)GL_FRAGMENT_SHADER,        ToGlShaderStage(bksge::ShaderStage::kFragment));
	EXPECT_EQ((GLenum)GL_TESS_CONTROL_SHADER,    ToGlShaderStage(bksge::ShaderStage::kTessellationControl));
	EXPECT_EQ((GLenum)GL_TESS_EVALUATION_SHADER, ToGlShaderStage(bksge::ShaderStage::kTessellationEvaluation));
#endif
}
