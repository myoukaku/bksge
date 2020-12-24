/**
 *	@file	unit_test_core_render_blend_operation.cpp
 *
 *	@brief	BlendOperation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/blend_operation.hpp>
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

namespace blend_operation_test
{

template <typename TChar>
static void OutputStreamTestSub(bksge::BlendOperation blend_operation, const TChar* str)
{
	bksge::basic_stringstream<TChar> ss;
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

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

GTEST_TEST(Render_BlendOperation, HashTest)
{
	std::hash<bksge::BlendOperation> h;
	bksge::vector<bksge::size_t> v;
	v.push_back(h(bksge::BlendOperation::kAdd));
	v.push_back(h(bksge::BlendOperation::kSubtract));
	v.push_back(h(bksge::BlendOperation::kReverseSubtract));
	v.push_back(h(bksge::BlendOperation::kMin));
	v.push_back(h(bksge::BlendOperation::kMax));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(bksge::BlendOperation::kReverseSubtract));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace blend_operation_test

}	// namespace bksge_core_render_test
