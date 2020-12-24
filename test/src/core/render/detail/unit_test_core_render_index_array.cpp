/**
 *	@file	unit_test_core_render_index_array.cpp
 *
 *	@brief	IndexArrayのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/detail/index_array.hpp>
//#include <bksge/fnd/serialization/shared_ptr.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/memory.hpp>
#include <gtest/gtest.h>
//#include "serialize_test.hpp"

GTEST_TEST(Render_IndexArray, DefaultConstructTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		IndexArray<bksge::uint8_t> a;
		EXPECT_EQ(TypeEnum::kUInt8, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<bksge::uint16_t> a;
		EXPECT_EQ(TypeEnum::kUInt16, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<bksge::uint32_t> a;
		EXPECT_EQ(TypeEnum::kUInt32, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<bksge::int8_t> a;
		EXPECT_EQ(TypeEnum::kSInt8, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<bksge::int16_t> a;
		EXPECT_EQ(TypeEnum::kSInt16, a.type());
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(0u, a.bytes());
		EXPECT_EQ(0u, a.count());
	}
	{
		IndexArray<bksge::int32_t> a;
		EXPECT_EQ(TypeEnum::kSInt32, a.type());
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
		const bksge::uint8_t t[] = { 0, 1, 2 };
		IndexArray<bksge::uint8_t> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(TypeEnum::kUInt8, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3u, a.bytes());
		EXPECT_EQ(3u, a.count());
	}
	{
		const bksge::uint16_t t[] = { 3 };
		IndexArray<bksge::uint16_t> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(TypeEnum::kUInt16, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(2u, a.bytes());
		EXPECT_EQ(1u, a.count());
	}
	{
		const bksge::uint32_t t[] = { 4, 5 };
		IndexArray<bksge::uint32_t> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(TypeEnum::kUInt32, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(bksge::uint32_t(4), a[0]);
		EXPECT_EQ(bksge::uint32_t(5), a[1]);
		EXPECT_EQ(8u, a.bytes());
		EXPECT_EQ(2u, a.count());
	}
	{
		const bksge::int8_t t[] = { 6, 7, 8, 9 };
		IndexArray<bksge::int8_t> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(TypeEnum::kSInt8, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(6, a[0]);
		EXPECT_EQ(7, a[1]);
		EXPECT_EQ(8, a[2]);
		EXPECT_EQ(9, a[3]);
		EXPECT_EQ(4u, a.bytes());
		EXPECT_EQ(4u, a.count());
	}
	{
		const bksge::int16_t t[] = { 10, 11, 12, 13, 14 };
		IndexArray<bksge::int16_t> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(TypeEnum::kSInt16, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(10, a[0]);
		EXPECT_EQ(14, a[4]);
		EXPECT_EQ(10u, a.bytes());
		EXPECT_EQ(5u, a.count());
	}
	{
		const bksge::int32_t t[] = { 15, 16, 17, 18, 19, 20 };
		IndexArray<bksge::int32_t> a(bksge::begin(t), bksge::end(t));
		EXPECT_EQ(TypeEnum::kSInt32, a.type());
		EXPECT_NE(nullptr, a.data());
		EXPECT_EQ(15, a[0]);
		EXPECT_EQ(20, a[5]);
		EXPECT_EQ(24u, a.bytes());
		EXPECT_EQ(6u, a.count());
	}
	{
		const float t[] = { 21, 22 };
		IndexArray<float> a(bksge::begin(t), bksge::end(t));
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

	const bksge::uint16_t t1[] = { 10, 11, 12, };
	const bksge::uint16_t t2[] = {  0, 11, 12, };
	const bksge::uint16_t t3[] = { 10, 10, 12, };
	const bksge::uint16_t t4[] = { 10, 11, 13, };
	const bksge::int16_t  t5[] = { 10, 11, 12, };
	const bksge::uint32_t t6[] = { 10, 11, 12, };

	IndexArray<bksge::uint16_t> a1(bksge::begin(t1), bksge::end(t1));
	IndexArray<bksge::uint16_t> a2(bksge::begin(t1), bksge::end(t1));
	IndexArray<bksge::uint16_t> a3(bksge::begin(t2), bksge::end(t2));
	IndexArray<bksge::uint16_t> a4(bksge::begin(t3), bksge::end(t3));
	IndexArray<bksge::uint16_t> a5(bksge::begin(t4), bksge::end(t4));
	IndexArray<bksge::int16_t>  a6(bksge::begin(t5), bksge::end(t5));
	IndexArray<bksge::uint32_t> a7(bksge::begin(t6), bksge::end(t6));

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

	const bksge::uint16_t t[] = { 10, 11, 12, };
	IndexArray<bksge::uint16_t> a(bksge::begin(t), bksge::end(t));

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream> (a);
	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream> (a);
	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream> (a);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  bksge::wstringstream>(a);
	SerializeTest<xml_woarchive,   xml_wiarchive,   bksge::wstringstream>(a);
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
		const bksge::uint8_t  t1[] = { 10, };
		const bksge::uint16_t t2[] = { 11, 12, };
		const bksge::uint32_t t3[] = { 13, 14, 15, };

		bksge::shared_ptr<IndexArrayBase> a1 = bksge::make_shared<IndexArray<bksge::uint8_t>>(bksge::begin(t1), bksge::end(t1));
		bksge::shared_ptr<IndexArrayBase> a2 = bksge::make_shared<IndexArray<bksge::uint16_t>>(bksge::begin(t2), bksge::end(t2));
		bksge::shared_ptr<IndexArrayBase> a3 = bksge::make_shared<IndexArray<bksge::uint32_t>>(bksge::begin(t3), bksge::end(t3));

		OArchive oa(s);
		oa << BKSGE_SERIALIZATION_NVP(a1);
		oa << BKSGE_SERIALIZATION_NVP(a2);
		oa << BKSGE_SERIALIZATION_NVP(a3);
	}
	{
		bksge::shared_ptr<IndexArrayBase> a1;
		bksge::shared_ptr<IndexArrayBase> a2;
		bksge::shared_ptr<IndexArrayBase> a3;

		IArchive ia(s);
		ia >> BKSGE_SERIALIZATION_NVP(a1);
		ia >> BKSGE_SERIALIZATION_NVP(a2);
		ia >> BKSGE_SERIALIZATION_NVP(a3);

		EXPECT_EQ(TypeEnum::kUInt8,  a1->type());
		EXPECT_EQ(TypeEnum::kUInt16, a2->type());
		EXPECT_EQ(TypeEnum::kUInt32,   a3->type());

		EXPECT_EQ(10, static_cast<bksge::uint8_t const*> (a1->data())[0]);
		EXPECT_EQ(11, static_cast<bksge::uint16_t const*>(a2->data())[0]);
		EXPECT_EQ(12, static_cast<bksge::uint16_t const*>(a2->data())[1]);
		EXPECT_EQ(13, static_cast<bksge::uint32_t const*>(a3->data())[0]);
		EXPECT_EQ(14, static_cast<bksge::uint32_t const*>(a3->data())[1]);
		EXPECT_EQ(15, static_cast<bksge::uint32_t const*>(a3->data())[2]);

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

	SerializeBasePtrTest<text_oarchive,   text_iarchive,   bksge::stringstream> ();
	SerializeBasePtrTest<xml_oarchive,    xml_iarchive,    bksge::stringstream> ();
	SerializeBasePtrTest<binary_oarchive, binary_iarchive, bksge::stringstream> ();

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeBasePtrTest<text_woarchive,  text_wiarchive,  bksge::wstringstream>();
	SerializeBasePtrTest<xml_woarchive,   xml_wiarchive,   bksge::wstringstream>();
#endif
#endif
}
