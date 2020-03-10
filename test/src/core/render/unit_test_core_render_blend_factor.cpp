/**
 *	@file	unit_test_core_render_blend_factor.cpp
 *
 *	@brief	BlendFactor のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/blend_factor.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/sstream/basic_stringstream.hpp>
#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace blend_factor_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::BlendFactor blend_factor, const TChar* str)
{
	bksge::basic_stringstream<TChar> ss;
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

GTEST_TEST(Render_BlendFactor, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::BlendFactor::kInvDestColor;

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_BlendFactor, HashTest)
{
	std::hash<bksge::BlendFactor> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::BlendFactor::kZero));
	v.push_back(h(bksge::BlendFactor::kOne));
	v.push_back(h(bksge::BlendFactor::kSrcColor));
	v.push_back(h(bksge::BlendFactor::kInvSrcColor));
	v.push_back(h(bksge::BlendFactor::kSrcAlpha));
	v.push_back(h(bksge::BlendFactor::kInvSrcAlpha));
	v.push_back(h(bksge::BlendFactor::kDestAlpha));
	v.push_back(h(bksge::BlendFactor::kInvDestAlpha));
	v.push_back(h(bksge::BlendFactor::kDestColor));
	v.push_back(h(bksge::BlendFactor::kInvDestColor));
	v.push_back(h(bksge::BlendFactor::kSrcAlphaSaturate));
	v.push_back(h(bksge::BlendFactor::kBlendFactor));
	v.push_back(h(bksge::BlendFactor::kInvBlendFactor));
	v.push_back(h(bksge::BlendFactor::kSrc1Color));
	v.push_back(h(bksge::BlendFactor::kInvSrc1Color));
	v.push_back(h(bksge::BlendFactor::kSrc1Alpha));
	v.push_back(h(bksge::BlendFactor::kInvSrc1Alpha));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::BlendFactor::kZero));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace blend_factor_test

}	// namespace bksge_core_render_test
