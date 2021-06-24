/**
 *	@file	unit_test_core_render_gl_filter_mode.cpp
 *
 *	@brief	FilterMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/gl/detail/filter_mode.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlFilterModeTest)
{
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ(GL_LINEAR,  bksge::render::gl::FilterMode(bksge::FilterMode::kLinear));
	EXPECT_EQ(GL_NEAREST, bksge::render::gl::FilterMode(bksge::FilterMode::kNearest));
#endif
}
