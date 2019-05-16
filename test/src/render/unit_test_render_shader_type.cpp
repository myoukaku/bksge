/**
 *	@file	unit_test_render_shader_type.cpp
 *
 *	@brief	ShaderType のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/shader_type.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace shader_type_test
{

GTEST_TEST(Render_ShaderType, ToStringTest)
{
	using namespace bksge;
	EXPECT_EQ("ShaderType::kHLSL", to_string(ShaderType::kHLSL));
	EXPECT_EQ("ShaderType::kGLSL", to_string(ShaderType::kGLSL));
}

template <typename TChar>
static void OutputStreamTestSub(bksge::ShaderType shader_type, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << shader_type;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_ShaderType, OutputStreamTest)
{
	using namespace bksge;
	OutputStreamTestSub(ShaderType::kHLSL, "ShaderType::kHLSL");
	OutputStreamTestSub(ShaderType::kGLSL, "ShaderType::kGLSL");

	OutputStreamTestSub(ShaderType::kHLSL, L"ShaderType::kHLSL");
	OutputStreamTestSub(ShaderType::kGLSL, L"ShaderType::kGLSL");
}

}	// namespace shader_type_test

}	// namespace bksge_render_test
