/**
 *	@file	unit_test_core_render_shader_parameter_map.cpp
 *
 *	@brief	ShaderParameterMapのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/shader_parameter_map.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/color4.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <sstream>
#include <gtest/gtest.h>
//#include "serialize_test.hpp"

GTEST_TEST(Render_ShaderParameterMap, BasicTest)
{
	using namespace bksge;
	using namespace bksge::render;

	ShaderParameterMap m;

	EXPECT_EQ(nullptr, m["foo"]);
	EXPECT_EQ(nullptr, m["COLOR"]);
	EXPECT_EQ(nullptr, m["Position"]);

	m.SetParameter("foo", 2.0f);

	EXPECT_NE(nullptr, m["foo"]);
	EXPECT_EQ(nullptr, m["COLOR"]);
	EXPECT_EQ(nullptr, m["Position"]);
	{
		auto const& param = m["foo"];
		auto const* p = static_cast<const float*>(param->data());
		EXPECT_EQ(2.0f, p[0]);
	}

	m.SetParameter("COLOR", bksge::Color4<float>(3, 4, 5, 6));
	EXPECT_NE(nullptr, m["foo"]);
	EXPECT_NE(nullptr, m["COLOR"]);
	EXPECT_EQ(nullptr, m["Position"]);
	{
		auto const& param = m["COLOR"];
		auto const* p = static_cast<const float*>(param->data());
		EXPECT_EQ(3.0f, p[0]);
		EXPECT_EQ(4.0f, p[1]);
		EXPECT_EQ(5.0f, p[2]);
		EXPECT_EQ(6.0f, p[3]);
	}

	// 値の更新
	m.SetParameter("COLOR", bksge::Color4<float>(1, 2, 3, 4));
	EXPECT_NE(nullptr, m["foo"]);
	EXPECT_NE(nullptr, m["COLOR"]);
	EXPECT_EQ(nullptr, m["Position"]);
	{
		auto const& param = m["COLOR"];
		auto const* p = static_cast<const float*>(param->data());
		EXPECT_EQ(1.0f, p[0]);
		EXPECT_EQ(2.0f, p[1]);
		EXPECT_EQ(3.0f, p[2]);
		EXPECT_EQ(4.0f, p[3]);
	}

	m.SetParameter("Position", bksge::Vector3<float>(7, 8, 9));
	EXPECT_NE(nullptr, m["foo"]);
	EXPECT_NE(nullptr, m["COLOR"]);
	EXPECT_NE(nullptr, m["Position"]);
	{
		auto const& param = m["Position"];
		auto const* p = static_cast<const float*>(param->data());
		EXPECT_EQ(7.0f, p[0]);
		EXPECT_EQ(8.0f, p[1]);
		EXPECT_EQ(9.0f, p[2]);
	}

	// 違う型で作り直し
	m.SetParameter("Position", bksge::Vector4<float>(10, 11, 12, 13));
	EXPECT_NE(nullptr, m["foo"]);
	EXPECT_NE(nullptr, m["COLOR"]);
	EXPECT_NE(nullptr, m["Position"]);
	{
		auto const& param = m["Position"];
		auto const* p = static_cast<const float*>(param->data());
		EXPECT_EQ(10.0f, p[0]);
		EXPECT_EQ(11.0f, p[1]);
		EXPECT_EQ(12.0f, p[2]);
		EXPECT_EQ(13.0f, p[3]);
	}

	// 大文字小文字は区別される
	EXPECT_EQ(nullptr, m["Foo"]);
	EXPECT_EQ(nullptr, m["Color"]);
	EXPECT_EQ(nullptr, m["position"]);
	EXPECT_EQ(nullptr, m["FOO"]);
	EXPECT_EQ(nullptr, m["color"]);
	EXPECT_EQ(nullptr, m["POSITION"]);
}

GTEST_TEST(Render_ShaderParameterMap, MoveTest)
{
	using namespace bksge;
	using namespace bksge::render;

	ShaderParameterMap m;
	m.SetParameter("COLOR", bksge::Color4<float>(1, 2, 3, 4));
	m.SetParameter("Position", bksge::Vector3<float>(5, 6, 7));
	m.SetParameter("mat", bksge::Matrix4x4<float>::Identity());

	//ShaderParameterMap const m2 = m;	// コピー禁止
	ShaderParameterMap const m2 = bksge::move(m);
	{
		auto const& param = m2["COLOR"];
		EXPECT_NE(nullptr, param);
		auto const* p = static_cast<const bksge::Color4<float>*>(param->data());
		EXPECT_EQ(bksge::Color4<float>(1, 2, 3, 4), *p);
	}
	{
		auto const& param = m2["Position"];
		EXPECT_NE(nullptr, param);
		auto const* p = static_cast<const bksge::Vector3<float>*>(param->data());
		EXPECT_EQ(bksge::Vector3<float>(5, 6, 7), *p);
	}
	{
		auto const& param = m2["mat"];
		EXPECT_NE(nullptr, param);
		auto const* p = static_cast<bksge::Matrix4x4<float> const*>(param->data());
		EXPECT_EQ(bksge::Matrix4x4<float>::Identity(), *p);
	}
}

#if 0
GTEST_TEST(Render_ShaderParameterMap, SerializeTest)
{
	using namespace bksge;
	using namespace bksge::render;
	using namespace bksge::archive;

	ShaderParameterMap m;
	m.SetParameter("COLOR", bksge::Color4<float>(1, 2, 3, 4));
	m.SetParameter("Position", bksge::Vector3<float>(5, 6, 7));
	m.SetParameter("mat", bksge::Matrix4x4<float>::Identity());

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (m);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (m);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (m);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(m);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(m);
#endif
}
#endif
