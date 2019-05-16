/**
 *	@file	unit_test_render_shader_map.cpp
 *
 *	@brief	ShaderMap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/shader_map.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/shader_type.hpp>
#include <bksge/render/shader_stage.hpp>
#include <gtest/gtest.h>
//#include "serialize_test.hpp"

GTEST_TEST(Render_ShaderMap, CtorTest)
{
	bksge::ShaderMap const shader_map
	{
		{
			bksge::ShaderType::kGLSL,
			bksge::Shader
			{
				{ bksge::ShaderStage::kVertex,   "ab" },
				{ bksge::ShaderStage::kFragment, "cde" },
			},
		},
		{
			bksge::ShaderType::kHLSL,
			bksge::Shader
			{
				{ bksge::ShaderStage::kVertex,   "efgh" },
				{ bksge::ShaderStage::kFragment, "ijklmn" },
			},
		},
	};


	{
		auto const* shader = shader_map.GetShader(bksge::ShaderType::kGLSL);
		EXPECT_NE(nullptr, shader);
		auto const& program_map = shader->program_map();
		EXPECT_EQ("ab",  program_map.at(bksge::ShaderStage::kVertex));
		EXPECT_EQ("cde", program_map.at(bksge::ShaderStage::kFragment));
	}
	{
		auto const* shader = shader_map.GetShader(bksge::ShaderType::kHLSL);
		EXPECT_NE(nullptr, shader);
		auto const& program_map = shader->program_map();
		EXPECT_EQ("efgh",   program_map.at(bksge::ShaderStage::kVertex));
		EXPECT_EQ("ijklmn", program_map.at(bksge::ShaderStage::kFragment));
	}
}

#if 0
GTEST_TEST(Render_ShaderMap, SerializeTest)
{
	using namespace bksge;
	using namespace bksge::archive;

}
#endif
