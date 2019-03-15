/**
 *	@file	unit_test_render_clear_flag.cpp
 *
 *	@brief	ClearFlagのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/clear_flag.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(Render_ClearFlag, BasicTest)
{
	using namespace bksge;

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
	using namespace bksge;

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
