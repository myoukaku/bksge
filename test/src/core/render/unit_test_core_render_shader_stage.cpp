/**
 *	@file	unit_test_core_render_shader_stage.cpp
 *
 *	@brief	ShaderStage のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/shader_stage.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace shader_stage_test
{

GTEST_TEST(Render_ShaderStage, ToStringTest)
{
	using namespace bksge;
	EXPECT_EQ("ShaderStage::kVertex"					, to_string(ShaderStage::kVertex));
	EXPECT_EQ("ShaderStage::kGeometry"					, to_string(ShaderStage::kGeometry));
	EXPECT_EQ("ShaderStage::kFragment"					, to_string(ShaderStage::kFragment));
	EXPECT_EQ("ShaderStage::kTessellationControl"		, to_string(ShaderStage::kTessellationControl));
	EXPECT_EQ("ShaderStage::kTessellationEvaluation"	, to_string(ShaderStage::kTessellationEvaluation));
}

template <typename TChar>
static void OutputStreamTestSub(bksge::ShaderStage shader_stage, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << shader_stage;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_ShaderStage, OutputStreamTest)
{
	using namespace bksge;
	OutputStreamTestSub(ShaderStage::kVertex					, "ShaderStage::kVertex");
	OutputStreamTestSub(ShaderStage::kGeometry					, "ShaderStage::kGeometry");
	OutputStreamTestSub(ShaderStage::kFragment					, "ShaderStage::kFragment");
	OutputStreamTestSub(ShaderStage::kTessellationControl		, "ShaderStage::kTessellationControl");
	OutputStreamTestSub(ShaderStage::kTessellationEvaluation	, "ShaderStage::kTessellationEvaluation");

	OutputStreamTestSub(ShaderStage::kVertex					, L"ShaderStage::kVertex");
	OutputStreamTestSub(ShaderStage::kGeometry					, L"ShaderStage::kGeometry");
	OutputStreamTestSub(ShaderStage::kFragment					, L"ShaderStage::kFragment");
	OutputStreamTestSub(ShaderStage::kTessellationControl		, L"ShaderStage::kTessellationControl");
	OutputStreamTestSub(ShaderStage::kTessellationEvaluation	, L"ShaderStage::kTessellationEvaluation");
}

GTEST_TEST(Render_ShaderStage, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::ShaderStage::kFragment;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

GTEST_TEST(Render_ShaderStage, HashTest)
{
	std::hash<bksge::ShaderStage> h;

	std::vector<std::size_t> v;
	v.push_back(h(bksge::ShaderStage::kVertex));
	v.push_back(h(bksge::ShaderStage::kGeometry));
	v.push_back(h(bksge::ShaderStage::kFragment));
	v.push_back(h(bksge::ShaderStage::kTessellationControl));
	v.push_back(h(bksge::ShaderStage::kTessellationEvaluation));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ShaderStage::kFragment));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace shader_stage_test

}	// namespace bksge_core_render_test
