/**
 *	@file	unit_test_core_render_semantic.cpp
 *
 *	@brief	Semantic のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/semantic.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace semantic_test
{

static_assert(sizeof(bksge::Semantic) == 4, "");

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

GTEST_TEST(Render_Semantic, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::Semantic::kPointSize;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_Semantic, HashTest)
{
	bksge::hash<bksge::Semantic> h;

	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::Semantic::kPosition));
	v.push_back(h(bksge::Semantic::kNormal));
	v.push_back(h(bksge::Semantic::kColor));
	v.push_back(h(bksge::Semantic::kTexCoord));
	v.push_back(h(bksge::Semantic::kFogCoord));
	v.push_back(h(bksge::Semantic::kPointSize));
	v.push_back(h(bksge::Semantic::kBlendWeight));
	v.push_back(h(bksge::Semantic::kBlendIndices));
	v.push_back(h(bksge::Semantic::kTangent));
	v.push_back(h(bksge::Semantic::kBinormal));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::Semantic::kPosition));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace semantic_test

}	// namespace bksge_core_render_test
