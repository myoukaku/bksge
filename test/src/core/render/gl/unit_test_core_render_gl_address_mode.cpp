/**
 *	@file	unit_test_core_render_gl_address_mode.cpp
 *
 *	@brief	AddressMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/gl/detail/address_mode.hpp>
#include <bksge/core/render/address_mode.hpp>
#include <bksge/core/render/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Render_GlTest, GlAddressModeTest)
{
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER
	EXPECT_EQ(GL_REPEAT,          bksge::render::gl::AddressMode(bksge::AddressMode::kRepeat));
	EXPECT_EQ(GL_CLAMP_TO_EDGE,   bksge::render::gl::AddressMode(bksge::AddressMode::kClamp));
	EXPECT_EQ(GL_CLAMP_TO_BORDER, bksge::render::gl::AddressMode(bksge::AddressMode::kBorder));
#endif
}
