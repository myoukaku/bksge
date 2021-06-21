/**
 *	@file	unit_test_core_render_type_enum.cpp
 *
 *	@brief	TypeEnumのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/detail/type_enum.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/sstream/basic_stringstream.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>

namespace bksge_core_render_test
{

namespace type_enum_test
{

GTEST_TEST(Render_TypeEnum, TypeToEnumTest)
{
	using namespace bksge::render;

	static_assert(TypeEnum::kSInt8	== TypeToEnum<bksge::int8_t>::value, "");
	static_assert(TypeEnum::kUInt8	== TypeToEnum<bksge::uint8_t>::value, "");
	static_assert(TypeEnum::kSInt16	== TypeToEnum<bksge::int16_t>::value, "");
	static_assert(TypeEnum::kUInt16	== TypeToEnum<bksge::uint16_t>::value, "");
	static_assert(TypeEnum::kSInt32	== TypeToEnum<bksge::int32_t>::value, "");
	static_assert(TypeEnum::kUInt32	== TypeToEnum<bksge::uint32_t>::value, "");
	static_assert(TypeEnum::kFloat	== TypeToEnum<float>::value, "");
}

GTEST_TEST(Render_TypeEnum, EnumToTypeTest)
{
	using namespace bksge;
	using namespace bksge::render;

	static_assert(bksge::is_same<EnumToType<TypeEnum::kSInt8>::type,  bksge::int8_t>::value, "");
	static_assert(bksge::is_same<EnumToType<TypeEnum::kUInt8>::type,  bksge::uint8_t>::value, "");
	static_assert(bksge::is_same<EnumToType<TypeEnum::kSInt16>::type, bksge::int16_t>::value, "");
	static_assert(bksge::is_same<EnumToType<TypeEnum::kUInt16>::type, bksge::uint16_t>::value, "");
	static_assert(bksge::is_same<EnumToType<TypeEnum::kSInt32>::type, bksge::int32_t>::value, "");
	static_assert(bksge::is_same<EnumToType<TypeEnum::kUInt32>::type, bksge::uint32_t>::value, "");
	static_assert(bksge::is_same<EnumToType<TypeEnum::kFloat>::type,  float>::value, "");
}

GTEST_TEST(Render_TypeEnum, GetSizeOfTest)
{
	using namespace bksge;

	EXPECT_EQ(1u, GetSizeOf(TypeEnum::kSInt8));
	EXPECT_EQ(1u, GetSizeOf(TypeEnum::kUInt8));
	EXPECT_EQ(2u, GetSizeOf(TypeEnum::kSInt16));
	EXPECT_EQ(2u, GetSizeOf(TypeEnum::kUInt16));
	EXPECT_EQ(4u, GetSizeOf(TypeEnum::kSInt32));
	EXPECT_EQ(4u, GetSizeOf(TypeEnum::kUInt32));
	EXPECT_EQ(4u, GetSizeOf(TypeEnum::kFloat));
}

GTEST_TEST(Render_TypeEnum, ToStringTest)
{
	using namespace bksge;

	EXPECT_EQ("TypeEnum::kSInt8",  to_string(TypeEnum::kSInt8));
	EXPECT_EQ("TypeEnum::kUInt8",  to_string(TypeEnum::kUInt8));
	EXPECT_EQ("TypeEnum::kSInt16", to_string(TypeEnum::kSInt16));
	EXPECT_EQ("TypeEnum::kUInt16", to_string(TypeEnum::kUInt16));
	EXPECT_EQ("TypeEnum::kSInt32", to_string(TypeEnum::kSInt32));
	EXPECT_EQ("TypeEnum::kUInt32", to_string(TypeEnum::kUInt32));
	EXPECT_EQ("TypeEnum::kFloat",  to_string(TypeEnum::kFloat));
}

template <typename TChar>
static void OutputStreamTestSub(bksge::TypeEnum t, const TChar* str)
{
	std::basic_stringstream<TChar> ss;
	ss << t;
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(Render_TypeEnum, OutputStreamTest)
{
	using namespace bksge;

	OutputStreamTestSub(TypeEnum::kSInt8,	"TypeEnum::kSInt8");
	OutputStreamTestSub(TypeEnum::kUInt8,	"TypeEnum::kUInt8");
	OutputStreamTestSub(TypeEnum::kSInt16,	"TypeEnum::kSInt16");
	OutputStreamTestSub(TypeEnum::kUInt16,	"TypeEnum::kUInt16");
	OutputStreamTestSub(TypeEnum::kSInt32,	"TypeEnum::kSInt32");
	OutputStreamTestSub(TypeEnum::kUInt32,	"TypeEnum::kUInt32");
	OutputStreamTestSub(TypeEnum::kFloat,	"TypeEnum::kFloat");

	OutputStreamTestSub(TypeEnum::kSInt8,	L"TypeEnum::kSInt8");
	OutputStreamTestSub(TypeEnum::kUInt8,	L"TypeEnum::kUInt8");
	OutputStreamTestSub(TypeEnum::kSInt16,	L"TypeEnum::kSInt16");
	OutputStreamTestSub(TypeEnum::kUInt16,	L"TypeEnum::kUInt16");
	OutputStreamTestSub(TypeEnum::kSInt32,	L"TypeEnum::kSInt32");
	OutputStreamTestSub(TypeEnum::kUInt32,	L"TypeEnum::kUInt32");
	OutputStreamTestSub(TypeEnum::kFloat,	L"TypeEnum::kFloat");
}

}	// namespace type_enum_test

}	// namespace bksge_core_render_test
