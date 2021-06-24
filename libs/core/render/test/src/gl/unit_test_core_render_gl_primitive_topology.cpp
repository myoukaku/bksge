/**
 *	@file	unit_test_core_render_gl_primitive_topology.cpp
 *
 *	@brief	PrimitiveTopology のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/gl/detail/primitive_topology.hpp>
#include <bksge/core/render/primitive_topology.hpp>
#include <bksge/core/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlPrimitiveTopologyTest)
{
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ((GLenum)GL_POINTS,    bksge::render::gl::PrimitiveTopology(bksge::PrimitiveTopology::kPoints));
	EXPECT_EQ((GLenum)GL_LINES,     bksge::render::gl::PrimitiveTopology(bksge::PrimitiveTopology::kLines));
	EXPECT_EQ((GLenum)GL_TRIANGLES, bksge::render::gl::PrimitiveTopology(bksge::PrimitiveTopology::kTriangles));
#endif
}
