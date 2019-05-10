﻿/**
 *	@file	unit_test_render_blend_factor.cpp
 *
 *	@brief	BlendFactor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/blend_factor.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace blend_factor_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::BlendFactor blend_factor, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << blend_factor;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_BlendFactor, OutputStreamTest)
{
	using bksge::BlendFactor;

	OutputStreamTestSub(BlendFactor::kZero,				"BlendFactor::kZero");
	OutputStreamTestSub(BlendFactor::kOne,				"BlendFactor::kOne");
	OutputStreamTestSub(BlendFactor::kSrcColor,			"BlendFactor::kSrcColor");
	OutputStreamTestSub(BlendFactor::kInvSrcColor,		"BlendFactor::kInvSrcColor");
	OutputStreamTestSub(BlendFactor::kSrcAlpha,			"BlendFactor::kSrcAlpha");
	OutputStreamTestSub(BlendFactor::kInvSrcAlpha,		"BlendFactor::kInvSrcAlpha");
	OutputStreamTestSub(BlendFactor::kDestAlpha,		"BlendFactor::kDestAlpha");
	OutputStreamTestSub(BlendFactor::kInvDestAlpha,		"BlendFactor::kInvDestAlpha");
	OutputStreamTestSub(BlendFactor::kDestColor,		"BlendFactor::kDestColor");
	OutputStreamTestSub(BlendFactor::kInvDestColor,		"BlendFactor::kInvDestColor");
	OutputStreamTestSub(BlendFactor::kSrcAlphaSaturate,	"BlendFactor::kSrcAlphaSaturate");
	OutputStreamTestSub(BlendFactor::kBlendFactor,		"BlendFactor::kBlendFactor");
	OutputStreamTestSub(BlendFactor::kInvBlendFactor,	"BlendFactor::kInvBlendFactor");
	OutputStreamTestSub(BlendFactor::kSrc1Color,		"BlendFactor::kSrc1Color");
	OutputStreamTestSub(BlendFactor::kInvSrc1Color,		"BlendFactor::kInvSrc1Color");
	OutputStreamTestSub(BlendFactor::kSrc1Alpha,		"BlendFactor::kSrc1Alpha");
	OutputStreamTestSub(BlendFactor::kInvSrc1Alpha,		"BlendFactor::kInvSrc1Alpha");

	OutputStreamTestSub(BlendFactor::kZero,				L"BlendFactor::kZero");
	OutputStreamTestSub(BlendFactor::kOne,				L"BlendFactor::kOne");
	OutputStreamTestSub(BlendFactor::kSrcColor,			L"BlendFactor::kSrcColor");
	OutputStreamTestSub(BlendFactor::kInvSrcColor,		L"BlendFactor::kInvSrcColor");
	OutputStreamTestSub(BlendFactor::kSrcAlpha,			L"BlendFactor::kSrcAlpha");
	OutputStreamTestSub(BlendFactor::kInvSrcAlpha,		L"BlendFactor::kInvSrcAlpha");
	OutputStreamTestSub(BlendFactor::kDestAlpha,		L"BlendFactor::kDestAlpha");
	OutputStreamTestSub(BlendFactor::kInvDestAlpha,		L"BlendFactor::kInvDestAlpha");
	OutputStreamTestSub(BlendFactor::kDestColor,		L"BlendFactor::kDestColor");
	OutputStreamTestSub(BlendFactor::kInvDestColor,		L"BlendFactor::kInvDestColor");
	OutputStreamTestSub(BlendFactor::kSrcAlphaSaturate,	L"BlendFactor::kSrcAlphaSaturate");
	OutputStreamTestSub(BlendFactor::kBlendFactor,		L"BlendFactor::kBlendFactor");
	OutputStreamTestSub(BlendFactor::kInvBlendFactor,	L"BlendFactor::kInvBlendFactor");
	OutputStreamTestSub(BlendFactor::kSrc1Color,		L"BlendFactor::kSrc1Color");
	OutputStreamTestSub(BlendFactor::kInvSrc1Color,		L"BlendFactor::kInvSrc1Color");
	OutputStreamTestSub(BlendFactor::kSrc1Alpha,		L"BlendFactor::kSrc1Alpha");
	OutputStreamTestSub(BlendFactor::kInvSrc1Alpha,		L"BlendFactor::kInvSrc1Alpha");
}

}	// namespace blend_factor_test

}	// namespace bksge_render_test