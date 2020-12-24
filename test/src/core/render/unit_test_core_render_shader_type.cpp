/**
 *	@file	unit_test_core_render_shader_type.cpp
 *
 *	@brief	ShaderType のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/shader_type.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <functional>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

namespace bksge_core_render_test
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
	bksge::basic_stringstream<TChar> ss;
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

GTEST_TEST(Render_ShaderType, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::ShaderType::kGLSL;

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_ShaderType, HashTest)
{
	std::hash<bksge::ShaderType> h;

	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::ShaderType::kHLSL));
	v.push_back(h(bksge::ShaderType::kGLSL));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ShaderType::kGLSL));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace shader_type_test

}	// namespace bksge_core_render_test
