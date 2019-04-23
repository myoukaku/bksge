/**
 *	@file	unit_test_render_stencil_operation.cpp
 *
 *	@brief	StencilOperation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/stencil_operation.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_render_test
{

namespace stencil_operation_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::StencilOperation stencil_operation, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << stencil_operation;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_StencilOperation, OutputStreamTest)
{
	using bksge::StencilOperation;

	OutputStreamTestSub(StencilOperation::kKeep,			"StencilOperation::kKeep");
	OutputStreamTestSub(StencilOperation::kZero,			"StencilOperation::kZero");
	OutputStreamTestSub(StencilOperation::kReplace,			"StencilOperation::kReplace");
	OutputStreamTestSub(StencilOperation::kIncrSaturate,	"StencilOperation::kIncrSaturate");
	OutputStreamTestSub(StencilOperation::kDecrSaturate,	"StencilOperation::kDecrSaturate");
	OutputStreamTestSub(StencilOperation::kInvert,			"StencilOperation::kInvert");
	OutputStreamTestSub(StencilOperation::kIncr,			"StencilOperation::kIncr");
	OutputStreamTestSub(StencilOperation::kDecr,			"StencilOperation::kDecr");

	OutputStreamTestSub(StencilOperation::kKeep,			L"StencilOperation::kKeep");
	OutputStreamTestSub(StencilOperation::kZero,			L"StencilOperation::kZero");
	OutputStreamTestSub(StencilOperation::kReplace,			L"StencilOperation::kReplace");
	OutputStreamTestSub(StencilOperation::kIncrSaturate,	L"StencilOperation::kIncrSaturate");
	OutputStreamTestSub(StencilOperation::kDecrSaturate,	L"StencilOperation::kDecrSaturate");
	OutputStreamTestSub(StencilOperation::kInvert,			L"StencilOperation::kInvert");
	OutputStreamTestSub(StencilOperation::kIncr,			L"StencilOperation::kIncr");
	OutputStreamTestSub(StencilOperation::kDecr,			L"StencilOperation::kDecr");
}

}	// namespace stencil_operation_test

}	// namespace bksge_render_test
