/**
 *	@file	unit_test_core_render_identifier.cpp
 *
 *	@brief	Identifierのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/detail/identifier.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <gtest/gtest.h>
//#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace identifier_test
{

GTEST_TEST(Render_Identifier, BasicTest)
{
	using namespace bksge::render;

	Identifier id_1;
	Identifier id_2;

	EXPECT_FALSE(id_1 == id_2);
	EXPECT_TRUE (id_1 != id_2);
}

template <typename T>
void TestAsymmetry(T const& x, T const& y)
{
	if (x < y)
	{
		EXPECT_FALSE(y < x);
	}
}

template <typename T>
void TestTransivity(T const& x, T const& y, T const& z)
{
	if (x < y && y < z)
	{
		EXPECT_TRUE(x < z);
	}
}

template <typename T>
void TestEquality(T const& x, T const& y)
{
	if (!(x < y) && !(y < x))
	{
		EXPECT_TRUE(x == y);
	}
}

GTEST_TEST(Render_Identifier, CompareTest)
{
	using namespace bksge::render;

	// Identifier が全順序の条件を満たすことをテストします

	Identifier id_1;
	Identifier id_2;
	Identifier id_3;

	// （非）反射性
	EXPECT_FALSE(id_1 < id_1);
	EXPECT_FALSE(id_2 < id_2);
	EXPECT_FALSE(id_3 < id_3);

	// （非）対称性
	TestAsymmetry(id_1, id_1);
	TestAsymmetry(id_1, id_2);
	TestAsymmetry(id_1, id_3);
	TestAsymmetry(id_2, id_1);
	TestAsymmetry(id_2, id_2);
	TestAsymmetry(id_2, id_3);
	TestAsymmetry(id_3, id_1);
	TestAsymmetry(id_3, id_2);
	TestAsymmetry(id_3, id_3);

	// 推移性
	TestTransivity(id_1, id_2, id_3);
	TestTransivity(id_1, id_3, id_2);
	TestTransivity(id_2, id_1, id_3);
	TestTransivity(id_2, id_3, id_1);
	TestTransivity(id_3, id_1, id_2);
	TestTransivity(id_3, id_2, id_1);

	// 同値条件
	TestEquality(id_1, id_1);
	TestEquality(id_1, id_2);
	TestEquality(id_1, id_3);
	TestEquality(id_2, id_1);
	TestEquality(id_2, id_2);
	TestEquality(id_2, id_3);
	TestEquality(id_3, id_1);
	TestEquality(id_3, id_2);
	TestEquality(id_3, id_3);
}

GTEST_TEST(Render_Identifier, SerializeTest)
{
#if 0
	using namespace bksge::render;
	using namespace bksge::archive;

	Identifier id;

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (id);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (id);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (id);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(id);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(id);
#endif
#endif
}

}	// namespace identifier_test

}	// namespace bksge_core_render_test
