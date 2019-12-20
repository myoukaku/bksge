/**
 *	@file	unit_test_core_render_blend_operation.cpp
 *
 *	@brief	BlendOperation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/blend_operation.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
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

GTEST_TEST(Render_BlendOperation, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v = bksge::BlendOperation::kReverseSubtract;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace blend_operation_test

}	// namespace bksge_core_render_test
