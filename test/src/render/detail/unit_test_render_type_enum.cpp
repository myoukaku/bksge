/**
 *	@file	unit_test_render_type_enum.cpp
 *
 *	@brief	TypeEnumのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/detail/type_enum.hpp>
#include <sstream>
#include <type_traits>
#include <gtest/gtest.h>

namespace bksge_render_test
{

namespace type_enum_test
{

GTEST_TEST(Render_TypeEnum, TypeToEnumTest)
{
	using namespace bksge::render;

	static_assert(TypeEnum::kByte			== TypeToEnum<signed char>::value, "");
	static_assert(TypeEnum::kUnsignedByte	== TypeToEnum<unsigned char>::value, "");
	static_assert(TypeEnum::kShort			== TypeToEnum<signed short>::value, "");
	static_assert(TypeEnum::kUnsignedShort	== TypeToEnum<unsigned short>::value, "");
	static_assert(TypeEnum::kInt			== TypeToEnum<signed int>::value, "");
	static_assert(TypeEnum::kUnsignedInt	== TypeToEnum<unsigned int>::value, "");
	static_assert(TypeEnum::kFloat			== TypeToEnum<float>::value, "");
}

GTEST_TEST(Render_TypeEnum, EnumToTypeTest)
{
	using namespace bksge;
	using namespace bksge::render;

	static_assert(std::is_same<EnumToType<TypeEnum::kByte>::type			, signed char>::value, "");
	static_assert(std::is_same<EnumToType<TypeEnum::kUnsignedByte>::type	, unsigned char>::value, "");
	static_assert(std::is_same<EnumToType<TypeEnum::kShort>::type			, signed short>::value, "");
	static_assert(std::is_same<EnumToType<TypeEnum::kUnsignedShort>::type	, unsigned short>::value, "");
	static_assert(std::is_same<EnumToType<TypeEnum::kInt>::type				, signed int>::value, "");
	static_assert(std::is_same<EnumToType<TypeEnum::kUnsignedInt>::type		, unsigned int>::value, "");
	static_assert(std::is_same<EnumToType<TypeEnum::kFloat>::type			, float>::value, "");
}

GTEST_TEST(Render_TypeEnum, GetSizeOfTest)
{
	using namespace bksge;

	EXPECT_EQ(sizeof(signed char)	 , GetSizeOf(TypeEnum::kByte));
	EXPECT_EQ(sizeof(unsigned char)	 , GetSizeOf(TypeEnum::kUnsignedByte));
	EXPECT_EQ(sizeof(signed short)	 , GetSizeOf(TypeEnum::kShort));
	EXPECT_EQ(sizeof(unsigned short) , GetSizeOf(TypeEnum::kUnsignedShort));
	EXPECT_EQ(sizeof(signed int)	 , GetSizeOf(TypeEnum::kInt));
	EXPECT_EQ(sizeof(unsigned int)	 , GetSizeOf(TypeEnum::kUnsignedInt));
	EXPECT_EQ(sizeof(float)			 , GetSizeOf(TypeEnum::kFloat));
}

GTEST_TEST(Render_TypeEnum, ToStringTest)
{
	using namespace bksge;

	EXPECT_EQ("TypeEnum::kByte"			, to_string(TypeEnum::kByte));
	EXPECT_EQ("TypeEnum::kUnsignedByte"	, to_string(TypeEnum::kUnsignedByte));
	EXPECT_EQ("TypeEnum::kShort"		, to_string(TypeEnum::kShort));
	EXPECT_EQ("TypeEnum::kUnsignedShort", to_string(TypeEnum::kUnsignedShort));
	EXPECT_EQ("TypeEnum::kInt"			, to_string(TypeEnum::kInt));
	EXPECT_EQ("TypeEnum::kUnsignedInt"	, to_string(TypeEnum::kUnsignedInt));
	EXPECT_EQ("TypeEnum::kFloat"		, to_string(TypeEnum::kFloat));
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

	OutputStreamTestSub(TypeEnum::kByte,			"TypeEnum::kByte");
	OutputStreamTestSub(TypeEnum::kUnsignedByte,	"TypeEnum::kUnsignedByte");
	OutputStreamTestSub(TypeEnum::kShort,			"TypeEnum::kShort");
	OutputStreamTestSub(TypeEnum::kUnsignedShort,	"TypeEnum::kUnsignedShort");
	OutputStreamTestSub(TypeEnum::kInt,				"TypeEnum::kInt");
	OutputStreamTestSub(TypeEnum::kUnsignedInt,		"TypeEnum::kUnsignedInt");
	OutputStreamTestSub(TypeEnum::kFloat,			"TypeEnum::kFloat");

	OutputStreamTestSub(TypeEnum::kByte,			L"TypeEnum::kByte");
	OutputStreamTestSub(TypeEnum::kUnsignedByte,	L"TypeEnum::kUnsignedByte");
	OutputStreamTestSub(TypeEnum::kShort,			L"TypeEnum::kShort");
	OutputStreamTestSub(TypeEnum::kUnsignedShort,	L"TypeEnum::kUnsignedShort");
	OutputStreamTestSub(TypeEnum::kInt,				L"TypeEnum::kInt");
	OutputStreamTestSub(TypeEnum::kUnsignedInt,		L"TypeEnum::kUnsignedInt");
	OutputStreamTestSub(TypeEnum::kFloat,			L"TypeEnum::kFloat");
}

}	// namespace type_enum_test

}	// namespace bksge_render_test
