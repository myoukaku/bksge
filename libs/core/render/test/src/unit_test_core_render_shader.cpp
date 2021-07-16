/**
 *	@file	unit_test_core_render_shader.cpp
 *
 *	@brief	Shader のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <sstream>
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

	Shader shader_tmp
	{
		{ ShaderStage::kVertex, vs_source },
		{ ShaderStage::kFragment, fs_source },
	};

	auto const id_tmp = shader_tmp.id();

//	Shader shader(shader_tmp);			// コピーコンストラクタはエラー
	Shader shader(std::move(shader_tmp));	// moveコンストラクタはOK

	EXPECT_EQ(id_tmp, shader.id());

	for (auto&& it : shader)
	{
		if (it.first == ShaderStage::kVertex)
		{
			EXPECT_EQ(vs_source, it.second);
		}
		if (it.first == ShaderStage::kFragment)
		{
			EXPECT_EQ(fs_source, it.second);
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

	Shader shader
	{
		{ ShaderStage::kVertex, vs_source },
		{ ShaderStage::kFragment, fs_source },
	};

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (shader);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (shader);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (shader);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(shader);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(shader);
#endif
}
#endif
