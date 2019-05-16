/**
 *	@file	unit_test_render_semantic.cpp
 *
 *	@brief	Semantic のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/semantic.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace semantic_test
{

template <typename TChar>
static void StringToSemanticTestSub(bksge::Semantic semantic, const TChar* str)
{
	EXPECT_EQ(semantic, bksge::render::ToSemantic(str));
}

GTEST_TEST(Render_Semantic, StringToSemanticTest)
{
	using bksge::Semantic;

	StringToSemanticTestSub(Semantic::kPosition,     "POSITION");
	StringToSemanticTestSub(Semantic::kNormal,       "NORMAL");
	StringToSemanticTestSub(Semantic::kColor,        "COLOR");
	StringToSemanticTestSub(Semantic::kTexCoord,     "TEXCOORD");
	StringToSemanticTestSub(Semantic::kFogCoord,     "FOGCOORD");
	StringToSemanticTestSub(Semantic::kPointSize,    "POINTSIZE");
	StringToSemanticTestSub(Semantic::kBlendWeight,  "BLENDWEIGHT");
	StringToSemanticTestSub(Semantic::kBlendIndices, "BLENDINDICES");
	StringToSemanticTestSub(Semantic::kTangent,      "TANGENT");
	StringToSemanticTestSub(Semantic::kBinormal,     "BINORMAL");
	StringToSemanticTestSub(Semantic::kUnknown,      "");
}

template <typename TChar>
static void ToSemanticNameTestSub(bksge::Semantic semantic, const TChar* str)
{
	EXPECT_STREQ(str, bksge::render::ToSemanticName(semantic));
}

GTEST_TEST(Render_Semantic, ToSemanticNameTest)
{
	using bksge::Semantic;

	ToSemanticNameTestSub(Semantic::kPosition,     "POSITION");
	ToSemanticNameTestSub(Semantic::kNormal,       "NORMAL");
	ToSemanticNameTestSub(Semantic::kColor,        "COLOR");
	ToSemanticNameTestSub(Semantic::kTexCoord,     "TEXCOORD");
	ToSemanticNameTestSub(Semantic::kFogCoord,     "FOGCOORD");
	ToSemanticNameTestSub(Semantic::kPointSize,    "POINTSIZE");
	ToSemanticNameTestSub(Semantic::kBlendWeight,  "BLENDWEIGHT");
	ToSemanticNameTestSub(Semantic::kBlendIndices, "BLENDINDICES");
	ToSemanticNameTestSub(Semantic::kTangent,      "TANGENT");
	ToSemanticNameTestSub(Semantic::kBinormal,     "BINORMAL");
	ToSemanticNameTestSub(Semantic::kUnknown,      "UNKNOWN");
}

template <typename TChar>
static void OutputStreamTestSub(bksge::Semantic semantic, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << semantic;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_Semantic, OutputStreamTest)
{
	using bksge::Semantic;

	OutputStreamTestSub(Semantic::kPosition,		"Semantic::kPosition");
	OutputStreamTestSub(Semantic::kNormal,			"Semantic::kNormal");
	OutputStreamTestSub(Semantic::kColor,			"Semantic::kColor");
	OutputStreamTestSub(Semantic::kTexCoord,		"Semantic::kTexCoord");
	OutputStreamTestSub(Semantic::kFogCoord,		"Semantic::kFogCoord");
	OutputStreamTestSub(Semantic::kPointSize,		"Semantic::kPointSize");
	OutputStreamTestSub(Semantic::kBlendWeight,		"Semantic::kBlendWeight");
	OutputStreamTestSub(Semantic::kBlendIndices,	"Semantic::kBlendIndices");
	OutputStreamTestSub(Semantic::kTangent,			"Semantic::kTangent");
	OutputStreamTestSub(Semantic::kBinormal,		"Semantic::kBinormal");
	OutputStreamTestSub(Semantic::kUnknown,		    "Semantic::kUnknown");
	OutputStreamTestSub((Semantic)-1,               "Semantic::kUnknown");

	OutputStreamTestSub(Semantic::kPosition,		L"Semantic::kPosition");
	OutputStreamTestSub(Semantic::kNormal,			L"Semantic::kNormal");
	OutputStreamTestSub(Semantic::kColor,			L"Semantic::kColor");
	OutputStreamTestSub(Semantic::kTexCoord,		L"Semantic::kTexCoord");
	OutputStreamTestSub(Semantic::kFogCoord,		L"Semantic::kFogCoord");
	OutputStreamTestSub(Semantic::kPointSize,		L"Semantic::kPointSize");
	OutputStreamTestSub(Semantic::kBlendWeight,		L"Semantic::kBlendWeight");
	OutputStreamTestSub(Semantic::kBlendIndices,	L"Semantic::kBlendIndices");
	OutputStreamTestSub(Semantic::kTangent,			L"Semantic::kTangent");
	OutputStreamTestSub(Semantic::kBinormal,		L"Semantic::kBinormal");
	OutputStreamTestSub(Semantic::kUnknown,		    L"Semantic::kUnknown");
	OutputStreamTestSub((Semantic)-1,               L"Semantic::kUnknown");
}

}	// namespace semantic_test

}	// namespace bksge_render_test
