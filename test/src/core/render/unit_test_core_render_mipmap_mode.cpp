/**
 *	@file	unit_test_core_render_mipmap_mode.cpp
 *
 *	@brief	MipmapMode のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/mipmap_mode.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace mipmap_mode_test
{

static_assert(sizeof(bksge::MipmapMode) == 4, "");

template <typename TChar>
static void OutputStreamTestSub(bksge::MipmapMode mipmap_mode, const TChar* str)
{
	bksge::basic_stringstream<TChar> ss;
	ss << mipmap_mode;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_MipmapMode, OutputStreamTest)
{
	using bksge::MipmapMode;

	OutputStreamTestSub(MipmapMode::kDisable,	"MipmapMode::kDisable");
	OutputStreamTestSub(MipmapMode::kNearest,	"MipmapMode::kNearest");
	OutputStreamTestSub(MipmapMode::kLinear,	"MipmapMode::kLinear");

	OutputStreamTestSub(MipmapMode::kDisable,	L"MipmapMode::kDisable");
	OutputStreamTestSub(MipmapMode::kNearest,	L"MipmapMode::kNearest");
	OutputStreamTestSub(MipmapMode::kLinear,	L"MipmapMode::kLinear");
}

GTEST_TEST(Render_MipmapMode, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::MipmapMode::kLinear;

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_MipmapMode, HashTest)
{
	bksge::hash<bksge::MipmapMode> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::MipmapMode::kDisable));
	v.push_back(h(bksge::MipmapMode::kNearest));
	v.push_back(h(bksge::MipmapMode::kLinear));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::MipmapMode::kNearest));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace mipmap_mode_test

}	// namespace bksge_core_render_test
