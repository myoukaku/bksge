/**
 *	@file	unit_test_render_blend_operation.cpp
 *
 *	@brief	BlendOperation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/blend_operation.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace blend_operation_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::BlendOperation blend_operation, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << blend_operation;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_BlendOperation, OutputStreamTest)
{
	using bksge::BlendOperation;

	OutputStreamTestSub(BlendOperation::kAdd,				"BlendOperation::kAdd");
	OutputStreamTestSub(BlendOperation::kSubtract,			"BlendOperation::kSubtract");
	OutputStreamTestSub(BlendOperation::kReverseSubtract,	"BlendOperation::kReverseSubtract");
	OutputStreamTestSub(BlendOperation::kMin,				"BlendOperation::kMin");
	OutputStreamTestSub(BlendOperation::kMax,				"BlendOperation::kMax");

	OutputStreamTestSub(BlendOperation::kAdd,				L"BlendOperation::kAdd");
	OutputStreamTestSub(BlendOperation::kSubtract,			L"BlendOperation::kSubtract");
	OutputStreamTestSub(BlendOperation::kReverseSubtract,	L"BlendOperation::kReverseSubtract");
	OutputStreamTestSub(BlendOperation::kMin,				L"BlendOperation::kMin");
	OutputStreamTestSub(BlendOperation::kMax,				L"BlendOperation::kMax");
}

}	// namespace blend_operation_test

}	// namespace bksge_render_test
