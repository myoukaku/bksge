/**
 *	@file	unit_test_render_shader_stage.cpp
 *
 *	@brief	ShaderStageのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/shader_stage.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace shader_stage_test
{

GTEST_TEST(Render_TextureFilter, ToStringTest)
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

GTEST_TEST(Render_TextureFilter, OutputStreamTest)
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

}	// namespace shader_stage_test

}	// namespace bksge_render_test
