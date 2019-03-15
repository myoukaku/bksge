/**
 *	@file	unit_test_render_shader.cpp
 *
 *	@brief	Shaderのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/shader.hpp>
#include <bksge/render/detail/shader_parameter.hpp>
#include <bksge/math/vector3.hpp>
#include <bksge/math/matrix3x3.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>
//#include "serialize_test.hpp"

GTEST_TEST(Render_Shader, MoveTest)
{
	using namespace bksge;

	char const* vs_source =
		"void main(									"
		"	float4 aPosition : POSITION,			"
		"	out float4 oPosition : POSITION)		"
		"{											"
		"	oPosition = aPosition;					"
		"}											"
	;

	char const* fs_source =
		"void main(									"
		"	out float4 oColor : COLOR)				"
		"{											"
		"	oColor = float4(1, 0, 0, 1);			"
		"}											"
	;

	Shader shader_tmp("Cg");
	shader_tmp.SetProgram(ShaderStage::kVertex, vs_source);
	shader_tmp.SetProgram(ShaderStage::kFragment, fs_source);

	shader_tmp.SetParameter("Foo", 0.0f);
	shader_tmp.SetParameter("Bar", bksge::Vector3<float>(1, 2, 3));
	shader_tmp.SetParameter("Baz", bksge::Matrix3x3<float>::Identity());

	auto const id_tmp = shader_tmp.id();

//	Shader shader(shader_tmp);			// コピーコンストラクタはエラー
	Shader shader(std::move(shader_tmp));	// moveコンストラクタはOK

	EXPECT_EQ("Cg", shader.type());
	EXPECT_EQ(id_tmp, shader.id());
	{
		auto const& program_map = shader.program_map();
		auto it = program_map.begin();
		EXPECT_EQ(ShaderStage::kVertex, it->first);
		EXPECT_EQ(vs_source, it->second);
		++it;
		EXPECT_EQ(ShaderStage::kFragment, it->first);
		EXPECT_EQ(fs_source, it->second);
		++it;
		EXPECT_TRUE(it == program_map.end());
	}
	{
		auto const& parameter_map = shader.parameter_map();
		{
			auto const& param = parameter_map["Foo"];
			ASSERT_TRUE(param != nullptr);
			auto const p = param->data();
			ASSERT_TRUE(p != nullptr);
			EXPECT_EQ(0.0f, *(const float*)p);
		}
		{
			auto const& param = parameter_map["Bar"];
			ASSERT_TRUE(param != nullptr);
			auto const p = param->data();
			ASSERT_TRUE(p != nullptr);
			EXPECT_EQ(bksge::Vector3<float>(1, 2, 3), *(const bksge::Vector3<float>*)p);
		}
		{
			auto const& param = parameter_map["Baz"];
			ASSERT_TRUE(param != nullptr);
			auto const p = param->data();
			ASSERT_TRUE(p != nullptr);
			EXPECT_EQ(bksge::Matrix3x3<float>::Identity(), *(const bksge::Matrix3x3<float>*)p);
		}
	}

	Shader shader2;
//	shader2 = shader;		// コピー代入はエラー
	shader2 = std::move(shader);	// move代入はOK

	EXPECT_EQ("Cg", shader2.type());
	EXPECT_EQ(id_tmp, shader2.id());
	{
		auto const& program_map = shader2.program_map();
		auto it = program_map.begin();
		EXPECT_EQ(ShaderStage::kVertex, it->first);
		EXPECT_EQ(vs_source, it->second);
		++it;
		EXPECT_EQ(ShaderStage::kFragment, it->first);
		EXPECT_EQ(fs_source, it->second);
		++it;
		EXPECT_TRUE(it == program_map.end());
	}
	{
		auto const& parameter_map = shader2.parameter_map();
		{
			auto const& param = parameter_map["Foo"];
			ASSERT_TRUE(param != nullptr);
			auto const p = param->data();
			ASSERT_TRUE(p != nullptr);
			EXPECT_EQ(0.0f, *(const float*)p);
		}
		{
			auto const& param = parameter_map["Bar"];
			ASSERT_TRUE(param != nullptr);
			auto const p = param->data();
			ASSERT_TRUE(p != nullptr);
			EXPECT_EQ(bksge::Vector3<float>(1, 2, 3), *(const bksge::Vector3<float>*)p);
		}
		{
			auto const& param = parameter_map["Baz"];
			ASSERT_TRUE(param != nullptr);
			auto const p = param->data();
			ASSERT_TRUE(p != nullptr);
			EXPECT_EQ(bksge::Matrix3x3<float>::Identity(), *(const bksge::Matrix3x3<float>*)p);
		}
	}
}

#if 0
GTEST_TEST(Render_Shader, SerializeTest)
{
	using namespace bksge;
	using namespace bksge::archive;

	char const* vs_source =
		"void main(									"
		"	float4 aPosition : POSITION,			"
		"	out float4 oPosition : POSITION)		"
		"{											"
		"	oPosition = aPosition;					"
		"}											"
	;

	char const* fs_source =
		"void main(									"
		"	out float4 oColor : COLOR)				"
		"{											"
		"	oColor = float4(1, 0, 0, 1);			"
		"}											"
	;

	Shader shader("Cg");
	shader.SetProgram(ShaderStage::kVertex, vs_source);
	shader.SetProgram(ShaderStage::kFragment, fs_source);

	shader.SetParameter("Foo", 0.0f);
	shader.SetParameter("Bar", bksge::Vector3<float>(1, 2, 3));
	shader.SetParameter("Baz", bksge::Matrix4x4f::Identity());

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (shader);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (shader);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (shader);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(shader);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(shader);
#endif
}
#endif
