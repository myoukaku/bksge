/**
 *	@file	unit_test_core_render_logic_operation.cpp
 *
 *	@brief	LogicOperation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/logic_operation.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <sstream>
#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace logic_operation_test
{

static_assert(sizeof(bksge::LogicOperation) == 4, "");

template <typename TChar>
static void OutputStreamTestSub(bksge::LogicOperation logic_operation, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << logic_operation;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_LogicOperation, OutputStreamTest)
{
	using bksge::LogicOperation;

	OutputStreamTestSub(LogicOperation::kClear,				"LogicOperation::kClear");
	OutputStreamTestSub(LogicOperation::kSet,				"LogicOperation::kSet");
	OutputStreamTestSub(LogicOperation::kCopy,				"LogicOperation::kCopy");
	OutputStreamTestSub(LogicOperation::kCopyInverted,		"LogicOperation::kCopyInverted");
	OutputStreamTestSub(LogicOperation::kNoop,				"LogicOperation::kNoop");
	OutputStreamTestSub(LogicOperation::kInvert,			"LogicOperation::kInvert");
	OutputStreamTestSub(LogicOperation::kAnd,				"LogicOperation::kAnd");
	OutputStreamTestSub(LogicOperation::kNand,				"LogicOperation::kNand");
	OutputStreamTestSub(LogicOperation::kOr,				"LogicOperation::kOr");
	OutputStreamTestSub(LogicOperation::kNor,				"LogicOperation::kNor");
	OutputStreamTestSub(LogicOperation::kXor,				"LogicOperation::kXor");
	OutputStreamTestSub(LogicOperation::kEquiv,				"LogicOperation::kEquiv");
	OutputStreamTestSub(LogicOperation::kAndReverse,		"LogicOperation::kAndReverse");
	OutputStreamTestSub(LogicOperation::kAndInverted,		"LogicOperation::kAndInverted");
	OutputStreamTestSub(LogicOperation::kOrReverse,			"LogicOperation::kOrReverse");
	OutputStreamTestSub(LogicOperation::kOrInverted,		"LogicOperation::kOrInverted");

	OutputStreamTestSub(LogicOperation::kClear,				L"LogicOperation::kClear");
	OutputStreamTestSub(LogicOperation::kSet,				L"LogicOperation::kSet");
	OutputStreamTestSub(LogicOperation::kCopy,				L"LogicOperation::kCopy");
	OutputStreamTestSub(LogicOperation::kCopyInverted,		L"LogicOperation::kCopyInverted");
	OutputStreamTestSub(LogicOperation::kNoop,				L"LogicOperation::kNoop");
	OutputStreamTestSub(LogicOperation::kInvert,			L"LogicOperation::kInvert");
	OutputStreamTestSub(LogicOperation::kAnd,				L"LogicOperation::kAnd");
	OutputStreamTestSub(LogicOperation::kNand,				L"LogicOperation::kNand");
	OutputStreamTestSub(LogicOperation::kOr,				L"LogicOperation::kOr");
	OutputStreamTestSub(LogicOperation::kNor,				L"LogicOperation::kNor");
	OutputStreamTestSub(LogicOperation::kXor,				L"LogicOperation::kXor");
	OutputStreamTestSub(LogicOperation::kEquiv,				L"LogicOperation::kEquiv");
	OutputStreamTestSub(LogicOperation::kAndReverse,		L"LogicOperation::kAndReverse");
	OutputStreamTestSub(LogicOperation::kAndInverted,		L"LogicOperation::kAndInverted");
	OutputStreamTestSub(LogicOperation::kOrReverse,			L"LogicOperation::kOrReverse");
	OutputStreamTestSub(LogicOperation::kOrInverted,		L"LogicOperation::kOrInverted");
}

GTEST_TEST(Render_LogicOperation, SerializeTest)
{
	using namespace bksge::serialization;

	auto const v1 = bksge::LogicOperation::kSet;
	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v1);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v1);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v1);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	auto const v2 = bksge::LogicOperation::kCopy;
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v2);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v2);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v2);
#endif
}

GTEST_TEST(Render_LogicOperation, HashTest)
{
	bksge::hash<bksge::LogicOperation> h;
	bksge::vector<std::size_t> v;

	v.push_back(h(bksge::LogicOperation::kClear));
	v.push_back(h(bksge::LogicOperation::kSet));
	v.push_back(h(bksge::LogicOperation::kCopy));
	v.push_back(h(bksge::LogicOperation::kCopyInverted));
	v.push_back(h(bksge::LogicOperation::kNoop));
	v.push_back(h(bksge::LogicOperation::kInvert));
	v.push_back(h(bksge::LogicOperation::kAnd));
	v.push_back(h(bksge::LogicOperation::kNand));
	v.push_back(h(bksge::LogicOperation::kOr));
	v.push_back(h(bksge::LogicOperation::kNor));
	v.push_back(h(bksge::LogicOperation::kXor));
	v.push_back(h(bksge::LogicOperation::kEquiv));
	v.push_back(h(bksge::LogicOperation::kAndReverse));
	v.push_back(h(bksge::LogicOperation::kAndInverted));
	v.push_back(h(bksge::LogicOperation::kOrReverse));
	v.push_back(h(bksge::LogicOperation::kOrInverted));

	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::LogicOperation::kNoop));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace logic_operation_test

}	// namespace bksge_core_render_test
