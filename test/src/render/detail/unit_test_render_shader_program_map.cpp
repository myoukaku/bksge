/**
 *	@file	unit_test_render_shader_program_map.cpp
 *
 *	@brief	ShaderProgramMapのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/detail/shader_program_map.hpp>
#include <bksge/render/shader_stage.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>
//#include "serialize_test.hpp"

GTEST_TEST(Render_ShaderProgramMap, BasicTest)
{
	using namespace bksge;
	using namespace bksge::render;

	ShaderProgramMap m;
	m[ShaderStage::kFragment] = "foo";
	m[ShaderStage::kVertex]   = "bar";

	EXPECT_EQ("foo", m[ShaderStage::kFragment]);
	EXPECT_EQ("bar", m[ShaderStage::kVertex]);
	EXPECT_EQ("",    m[ShaderStage::kGeometry]);

	m[ShaderStage::kGeometry] = "baz";

	EXPECT_EQ("foo", m[ShaderStage::kFragment]);
	EXPECT_EQ("bar", m[ShaderStage::kVertex]);
	EXPECT_EQ("baz", m[ShaderStage::kGeometry]);
}

GTEST_TEST(Render_ShaderProgramMap, MoveTest)
{
	using namespace bksge;
	using namespace bksge::render;

	ShaderProgramMap m;
	m[ShaderStage::kFragment] = "012345";
	m[ShaderStage::kVertex]   = "abcdefghikjl";
	m[ShaderStage::kGeometry] = "ABCDE";

	//ShaderProgramMap m2 = m;	// コピー禁止
	ShaderProgramMap m2 = std::move(m);
	EXPECT_EQ("012345",       m2[ShaderStage::kFragment]);
	EXPECT_EQ("abcdefghikjl", m2[ShaderStage::kVertex]);
	EXPECT_EQ("ABCDE",        m2[ShaderStage::kGeometry]);
}

GTEST_TEST(Render_ShaderProgramMap, IteratorTest)
{
	using namespace bksge;
	using namespace bksge::render;

	ShaderProgramMap m;
	m[ShaderStage::kFragment] = "foo";
	m[ShaderStage::kVertex]   = "bar";
	m[ShaderStage::kGeometry] = "baz";

	for (auto&& i : m)
	{
		switch (i.first)
		{
		case ShaderStage::kFragment:	EXPECT_EQ("foo", i.second);	break;
		case ShaderStage::kVertex:		EXPECT_EQ("bar", i.second);	break;
		case ShaderStage::kGeometry:	EXPECT_EQ("baz", i.second);	break;
		default:						GTEST_FAIL(); break;
		}
	}
}

GTEST_TEST(Render_ShaderProgramMap, CompareTest)
{
	using namespace bksge;
	using namespace bksge::render;

	ShaderProgramMap m1;
	m1[ShaderStage::kFragment] = "foo";
	m1[ShaderStage::kVertex]   = "bar";
	m1[ShaderStage::kGeometry] = "baz";

	ShaderProgramMap m2;
	m2[ShaderStage::kGeometry] = "baz";
	m2[ShaderStage::kVertex]   = "bar";
	m2[ShaderStage::kFragment] = "foo";

	ShaderProgramMap m3;
	m3[ShaderStage::kFragment] = "FOO";
	m3[ShaderStage::kVertex]   = "bar";
	m3[ShaderStage::kGeometry] = "baz";

	ShaderProgramMap m4;
	m4[ShaderStage::kVertex]   = "foo";
	m4[ShaderStage::kFragment] = "bar";
	m4[ShaderStage::kGeometry] = "baz";

	ShaderProgramMap m5;
	m5[ShaderStage::kFragment] = "foo";
	m5[ShaderStage::kVertex]   = "bar";

	ShaderProgramMap m6;
	m6[ShaderStage::kFragment] = "foo";
	m6[ShaderStage::kVertex]   = "bar";
	m6[ShaderStage::kGeometry] = "baz";
	m6[ShaderStage::kTessellationControl] = "abc";

	EXPECT_TRUE(m1 == m1);
	EXPECT_TRUE(m1 == m2);
	EXPECT_FALSE(m1 == m3);
	EXPECT_FALSE(m1 == m4);
	EXPECT_FALSE(m1 == m5);
	EXPECT_FALSE(m1 == m6);

	EXPECT_FALSE(m1 != m1);
	EXPECT_FALSE(m1 != m2);
	EXPECT_TRUE(m1 != m3);
	EXPECT_TRUE(m1 != m4);
	EXPECT_TRUE(m1 != m5);
	EXPECT_TRUE(m1 != m6);
}

GTEST_TEST(Render_ShaderProgramMap, SerializeTest)
{
#if 0
	using namespace bksge;
	using namespace bksge::render;
	using namespace bksge::archive;

	ShaderProgramMap m;
	m[ShaderStage::kFragment] = "a";
	m[ShaderStage::kVertex]   = "BCD";
	m[ShaderStage::kGeometry] = "eFgHiJk";

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (m);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (m);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (m);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(m);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(m);
#endif
#endif
}
