/**
 *	@file	unit_test_core_render_clear_flag.cpp
 *
 *	@brief	ClearFlag のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/clear_flag.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace clear_flag_test
{

GTEST_TEST(Render_ClearFlag, BasicTest)
{
	using bksge::ClearFlag;

	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kNone;
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kColor);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kDepth);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kStencil);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kColor;
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kColor,   f & ClearFlag::kColor);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kDepth);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kStencil);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kColor | ClearFlag::kStencil;
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kColor,   f & ClearFlag::kColor);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kDepth);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kStencil, f & ClearFlag::kStencil);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kNone;
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kColor,   f ^ ClearFlag::kColor);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kDepth,   f ^ ClearFlag::kDepth);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kStencil, f ^ ClearFlag::kStencil);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kAll;
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kDepth | ClearFlag::kStencil, f ^ ClearFlag::kColor);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kColor | ClearFlag::kStencil, f ^ ClearFlag::kDepth);
		BKSGE_CONSTEXPR_EXPECT_EQ(ClearFlag::kColor | ClearFlag::kDepth,   f ^ ClearFlag::kStencil);
	}
	{
		ClearFlag f = ClearFlag::kNone;
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kColor);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kDepth);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kStencil);

		f |= ClearFlag::kDepth;
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kColor);
		EXPECT_EQ(ClearFlag::kDepth,   f & ClearFlag::kDepth);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kStencil);

		f |= ClearFlag::kStencil;
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kColor);
		EXPECT_EQ(ClearFlag::kDepth,   f & ClearFlag::kDepth);
		EXPECT_EQ(ClearFlag::kStencil, f & ClearFlag::kStencil);

		f ^= ClearFlag::kAll;
		EXPECT_EQ(ClearFlag::kColor,   f & ClearFlag::kColor);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kDepth);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kStencil);

		f ^= ClearFlag::kDepth;
		EXPECT_EQ(ClearFlag::kColor,   f & ClearFlag::kColor);
		EXPECT_EQ(ClearFlag::kDepth,   f & ClearFlag::kDepth);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kStencil);

		f &= ClearFlag::kColor;
		EXPECT_EQ(ClearFlag::kColor,   f & ClearFlag::kColor);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kDepth);
		EXPECT_EQ(ClearFlag::kNone,    f & ClearFlag::kStencil);
	}
}

GTEST_TEST(Render_ClearFlag, TestTest)
{
	using bksge::ClearFlag;

	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kNone;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kStencil));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kColor;
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kStencil));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kDepth;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kStencil));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kStencil;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kStencil));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kColor | ClearFlag::kDepth;
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kStencil));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kDepth | ClearFlag::kStencil;
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kStencil));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kColor | ClearFlag::kStencil;
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kStencil));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ClearFlag f = ClearFlag::kAll;
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kColor));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kDepth));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::render::Test(f, ClearFlag::kStencil));
	}
}

template <typename TChar>
static void OutputStreamTestSub(bksge::ClearFlag clear_flag, const TChar* str)
{
	bksge::basic_stringstream<TChar> ss;
	ss << clear_flag;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_ClearFlag, OutputStreamTest)
{
	using bksge::ClearFlag;

	OutputStreamTestSub(ClearFlag::kNone,                        "ClearFlag::kNone");
	OutputStreamTestSub(ClearFlag::kColor,                       "ClearFlag::kColor");
	OutputStreamTestSub(ClearFlag::kDepth,                       "ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kStencil,                     "ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kAll,                         "ClearFlag::kAll");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kDepth,   "ClearFlag::kColor | ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kDepth | ClearFlag::kStencil, "ClearFlag::kDepth | ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kStencil, "ClearFlag::kColor | ClearFlag::kStencil");

	OutputStreamTestSub(ClearFlag::kNone,                        L"ClearFlag::kNone");
	OutputStreamTestSub(ClearFlag::kColor,                       L"ClearFlag::kColor");
	OutputStreamTestSub(ClearFlag::kDepth,                       L"ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kStencil,                     L"ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kAll,                         L"ClearFlag::kAll");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kDepth,   L"ClearFlag::kColor | ClearFlag::kDepth");
	OutputStreamTestSub(ClearFlag::kDepth | ClearFlag::kStencil, L"ClearFlag::kDepth | ClearFlag::kStencil");
	OutputStreamTestSub(ClearFlag::kColor | ClearFlag::kStencil, L"ClearFlag::kColor | ClearFlag::kStencil");
}

GTEST_TEST(Render_ClearFlag, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::ClearFlag::kColor | bksge::ClearFlag::kStencil;

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_ClearFlag, HashTest)
{
	bksge::hash<bksge::ClearFlag> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::ClearFlag::kNone));
	v.push_back(h(bksge::ClearFlag::kColor));
	v.push_back(h(bksge::ClearFlag::kDepth));
	v.push_back(h(bksge::ClearFlag::kStencil));
	v.push_back(h(bksge::ClearFlag::kAll));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ClearFlag::kColor | bksge::ClearFlag::kDepth));
	v.push_back(h(bksge::ClearFlag::kDepth | bksge::ClearFlag::kStencil));
	v.push_back(h(bksge::ClearFlag::kColor | bksge::ClearFlag::kStencil));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::ClearFlag::kNone));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace clear_flag_test

}	// namespace bksge_core_render_test
