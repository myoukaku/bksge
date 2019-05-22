/**
 *	@file	unit_test_render_gl_gl_filter_mode.cpp
 *
 *	@brief	ToGlFilterMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/gl/gl_filter_mode.hpp>
#include <bksge/render/filter_mode.hpp>
#include <bksge/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, ToGlFilterModeTest)
{
#if BKSGE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ(GL_LINEAR,  ToGlFilterMode(bksge::FilterMode::kLinear));
	EXPECT_EQ(GL_NEAREST, ToGlFilterMode(bksge::FilterMode::kNearest));
#endif
}
