/**
 *	@file	unit_test_core_render_front_face.cpp
 *
 *	@brief	FrontFace のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/front_face.hpp>
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

namespace front_face_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::FrontFace front_face, const TChar* str)
{
	bksge::basic_stringstream<TChar> ss;
	ss << front_face;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_FrontFace, OutputStreamTest)
{
	using bksge::FrontFace;

	OutputStreamTestSub(FrontFace::kClockwise,		  "FrontFace::kClockwise");
	OutputStreamTestSub(FrontFace::kCounterClockwise, "FrontFace::kCounterClockwise");

	OutputStreamTestSub(FrontFace::kClockwise,		  L"FrontFace::kClockwise");
	OutputStreamTestSub(FrontFace::kCounterClockwise, L"FrontFace::kCounterClockwise");
}

GTEST_TEST(Render_FrontFace, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::FrontFace::kClockwise;

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_FrontFace, HashTest)
{
	std::hash<bksge::FrontFace> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::FrontFace::kClockwise));
	v.push_back(h(bksge::FrontFace::kCounterClockwise));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::FrontFace::kCounterClockwise));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace front_face_test

}	// namespace bksge_core_render_test
