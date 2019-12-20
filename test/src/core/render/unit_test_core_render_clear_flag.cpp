/**
 *	@file	unit_test_core_render_clear_flag.cpp
 *
 *	@brief	ClearFlag のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/clear_flag.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

GTEST_TEST(Render_ClearFlag, BasicTest)
{
	using bksge::ClearFlag;

	ClearFlag f0 = ClearFlag::kNone;
	EXPECT_FALSE(bool(f0 & ClearFlag::kColor));
	EXPECT_FALSE(bool(f0 & ClearFlag::kDepth));
	EXPECT_FALSE(bool(f0 & ClearFlag::kStencil));

	ClearFlag f1 = ClearFlag::kColor;
	EXPECT_TRUE (bool(f1 & ClearFlag::kColor));
	EXPECT_FALSE(bool(f1 & ClearFlag::kDepth));
	EXPECT_FALSE(bool(f1 & ClearFlag::kStencil));

	ClearFlag f2 = ClearFlag::kColor | ClearFlag::kStencil;
	EXPECT_TRUE (bool(f2 & ClearFlag::kColor));
	EXPECT_FALSE(bool(f2 & ClearFlag::kDepth));
	EXPECT_TRUE (bool(f2 & ClearFlag::kStencil));
}

#if 0	// TODO
GTEST_TEST(Render_ClearFlag, OutputStreamTest)
{
	using bksge::ClearFlag;

	{
		ClearFlag f = ClearFlag::kColor;

		std::stringstream ss;
		ss << f;
		EXPECT_EQ("00000000000000000000000000000001", ss.str());
	}
	{
		ClearFlag f = ClearFlag::kColor | ClearFlag::kStencil;

		std::wstringstream ss;
		ss << f;
		EXPECT_EQ(L"00000000000000000000000000000101", ss.str());
	}
}
#endif

GTEST_TEST(Render_ClearFlag, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::ClearFlag::kColor | bksge::ClearFlag::kStencil;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}
