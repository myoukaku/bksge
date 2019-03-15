/**
 *	@file	unit_test_render_semantic.cpp
 *
 *	@brief	Semanticのテスト
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
}

}	// namespace semantic_test

}	// namespace bksge_render_test
