﻿/**
 *	@file	unit_test_render_index_array.cpp
 *
 *	@brief	IndexArrayのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/render/detail/index_array.hpp>
//#include <bksge/serialization/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <iterator>
#include <memory>
#include <sstream>
//#include "serialize_test.hpp"

GTEST_TEST(Render_IndexArray, DefaultConstructTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		IndexArray<std::uint8_t> a;
		EXPECT_EQ(TypeEnum::kUnsignedByte, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<std::uint16_t> a;
		EXPECT_EQ(TypeEnum::kUnsignedShort, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<std::uint32_t> a;
		EXPECT_EQ(TypeEnum::kUnsignedInt, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<std::int8_t> a;
		EXPECT_EQ(TypeEnum::kByte, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<std::int16_t> a;
		EXPECT_EQ(TypeEnum::kShort, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<std::int32_t> a;
		EXPECT_EQ(TypeEnum::kInt, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<float> a;
		EXPECT_EQ(TypeEnum::kFloat, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
}

GTEST_TEST(Render_IndexArray, ConstructTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		const std::uint8_t t[] = { 0, 1, 2 };
		IndexArray<std::uint8_t> a(std::begin(t), std::end(t));
		EXPECT_EQ(TypeEnum::kUnsignedByte, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3u, a.bytes());
		EXPECT_EQ(3u, a.count());
	}
	{
		const std::uint16_t t[] = { 3 };
		IndexArray<std::uint16_t> a(std::begin(t), std::end(t));
		EXPECT_EQ(TypeEnum::kUnsignedShort, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(2u, a.bytes());
		EXPECT_EQ(1u, a.count());
	}
	{
		const std::uint32_t t[] = { 4, 5 };
		IndexArray<std::uint32_t> a(std::begin(t), std::end(t));
		EXPECT_EQ(TypeEnum::kUnsignedInt, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(std::uint32_t(4), a[0]);
		EXPECT_EQ(std::uint32_t(5), a[1]);
		EXPECT_EQ(8u, a.bytes());
		EXPECT_EQ(2u, a.count());
	}
	{
		const std::int8_t t[] = { 6, 7, 8, 9 };
		IndexArray<std::int8_t> a(std::begin(t), std::end(t));
		EXPECT_EQ(TypeEnum::kByte, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(6, a[0]);
		EXPECT_EQ(7, a[1]);
		EXPECT_EQ(8, a[2]);
		EXPECT_EQ(9, a[3]);
		EXPECT_EQ(4u, a.bytes());
		EXPECT_EQ(4u, a.count());
	}
	{
		const std::int16_t t[] = { 10, 11, 12, 13, 14 };
		IndexArray<std::int16_t> a(std::begin(t), std::end(t));
		EXPECT_EQ(TypeEnum::kShort, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(10, a[0]);
		EXPECT_EQ(14, a[4]);
		EXPECT_EQ(10u, a.bytes());
		EXPECT_EQ(5u, a.count());
	}
	{
		const std::int32_t t[] = { 15, 16, 17, 18, 19, 20 };
		IndexArray<std::int32_t> a(std::begin(t), std::end(t));
		EXPECT_EQ(TypeEnum::kInt, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(15, a[0]);
		EXPECT_EQ(20, a[5]);
		EXPECT_EQ(24u, a.bytes());
		EXPECT_EQ(6u, a.count());
	}
	{
		const float t[] = { 21, 22 };
		IndexArray<float> a(std::begin(t), std::end(t));
		EXPECT_EQ(TypeEnum::kFloat, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(21, a[0]);
		EXPECT_EQ(22, a[1]);
		EXPECT_EQ(8u, a.bytes());
		EXPECT_EQ(2u, a.count());
	}
}

GTEST_TEST(Render_IndexArray, CompareTest)
{
	using namespace bksge;
	using namespace bksge::render;

	const std::uint16_t t1[] = { 10, 11, 12, };
	const std::uint16_t t2[] = {  0, 11, 12, };
	const std::uint16_t t3[] = { 10, 10, 12, };
	const std::uint16_t t4[] = { 10, 11, 13, };
	const std::int16_t  t5[] = { 10, 11, 12, };
	const std::uint32_t t6[] = { 10, 11, 12, };

	IndexArray<std::uint16_t> a1(std::begin(t1), std::end(t1));
	IndexArray<std::uint16_t> a2(std::begin(t1), std::end(t1));
	IndexArray<std::uint16_t> a3(std::begin(t2), std::end(t2));
	IndexArray<std::uint16_t> a4(std::begin(t3), std::end(t3));
	IndexArray<std::uint16_t> a5(std::begin(t4), std::end(t4));
	IndexArray<std::int16_t>  a6(std::begin(t5), std::end(t5));
	IndexArray<std::uint32_t> a7(std::begin(t6), std::end(t6));

	EXPECT_TRUE(a1 == a1);
	EXPECT_TRUE(a1 == a2);
	EXPECT_FALSE(a1 == a3);
	EXPECT_FALSE(a1 == a4);
	EXPECT_FALSE(a1 == a5);
	EXPECT_FALSE(a1 == a6);
	EXPECT_FALSE(a1 == a7);

	EXPECT_FALSE(a1 != a1);
	EXPECT_FALSE(a1 != a2);
	EXPECT_TRUE(a1 != a3);
	EXPECT_TRUE(a1 != a4);
	EXPECT_TRUE(a1 != a5);
	EXPECT_TRUE(a1 != a6);
	EXPECT_TRUE(a1 != a7);
}

GTEST_TEST(Render_IndexArray, SerializeTest)
{
#if 0
	using namespace bksge;
	using namespace bksge::render;
	using namespace bksge::archive;

	const std::uint16_t t[] = { 10, 11, 12, };
	IndexArray<std::uint16_t> a(std::begin(t), std::end(t));

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (a);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (a);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (a);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(a);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(a);
#endif
#endif
}

#if 0
template <typename OArchive, typename IArchive, typename Stream>
void SerializeBasePtrTest(void)
{
	using namespace bksge;
	using namespace bksge::render;

	Stream s;
	{
		const std::uint8_t  t1[] = { 10, };
		const std::uint16_t t2[] = { 11, 12, };
		const std::uint32_t t3[] = { 13, 14, 15, };

		std::shared_ptr<IndexArrayBase> a1 = std::make_shared<IndexArray<std::uint8_t>>(std::begin(t1), std::end(t1));
		std::shared_ptr<IndexArrayBase> a2 = std::make_shared<IndexArray<std::uint16_t>>(std::begin(t2), std::end(t2));
		std::shared_ptr<IndexArrayBase> a3 = std::make_shared<IndexArray<std::uint32_t>>(std::begin(t3), std::end(t3));

		OArchive oa(s);
		oa << BKSGE_SERIALIZATION_NVP(a1);
		oa << BKSGE_SERIALIZATION_NVP(a2);
		oa << BKSGE_SERIALIZATION_NVP(a3);
	}
	{
		std::shared_ptr<IndexArrayBase> a1;
		std::shared_ptr<IndexArrayBase> a2;
		std::shared_ptr<IndexArrayBase> a3;

		IArchive ia(s);
		ia >> BKSGE_SERIALIZATION_NVP(a1);
		ia >> BKSGE_SERIALIZATION_NVP(a2);
		ia >> BKSGE_SERIALIZATION_NVP(a3);

		EXPECT_EQ(TypeEnum::kUnsignedByte,  a1->type());
		EXPECT_EQ(TypeEnum::kUnsignedShort, a2->type());
		EXPECT_EQ(TypeEnum::kUnsignedInt,   a3->type());

		EXPECT_EQ(10, static_cast<std::uint8_t const*> (a1->data())[0]);
		EXPECT_EQ(11, static_cast<std::uint16_t const*>(a2->data())[0]);
		EXPECT_EQ(12, static_cast<std::uint16_t const*>(a2->data())[1]);
		EXPECT_EQ(13, static_cast<std::uint32_t const*>(a3->data())[0]);
		EXPECT_EQ(14, static_cast<std::uint32_t const*>(a3->data())[1]);
		EXPECT_EQ(15, static_cast<std::uint32_t const*>(a3->data())[2]);

		EXPECT_EQ( 1u, a1->bytes());
		EXPECT_EQ( 4u, a2->bytes());
		EXPECT_EQ(12u, a3->bytes());

		EXPECT_EQ(1u, a1->count());
		EXPECT_EQ(2u, a2->count());
		EXPECT_EQ(3u, a3->count());
	}
}
#endif

GTEST_TEST(Render_IndexArray, SerializeBasePtrTest)
{
#if 0
	using namespace bksge::archive;

	SerializeBasePtrTest<text_oarchive,   text_iarchive,   std::stringstream> ();
	SerializeBasePtrTest<xml_oarchive,    xml_iarchive,    std::stringstream> ();
	SerializeBasePtrTest<binary_oarchive, binary_iarchive, std::stringstream> ();

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeBasePtrTest<text_woarchive,  text_wiarchive,  std::wstringstream>();
	SerializeBasePtrTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>();
#endif
#endif
}