/**
 *	@file	unit_test_core_render_shader_parameter.cpp
 *
 *	@brief	ShaderParameterのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/color4.hpp>
#include <bksge/core/math/color3.hpp>
//#include <bksge/fnd/serialization/shared_ptr.hpp>
#include <bksge/fnd/memory.hpp>
#include <sstream>
#include <gtest/gtest.h>
//#include "serialize_test.hpp"

namespace bksge_core_render_test
{

namespace shader_parameter_test
{

GTEST_TEST(Render_ShaderParameter, BasicTest)
{
	using namespace bksge;
	using namespace bksge::render;

	{
		const ShaderParameter<float> p;
		EXPECT_EQ(0.0f, p.value());
		EXPECT_NE(nullptr, p.data());
		EXPECT_EQ(0.0f, *static_cast<const float*>(p.data()));
	}
	{
		const ShaderParameter<float> p(2.0f);
		EXPECT_EQ(2.0f, p.value());
		EXPECT_NE(nullptr, p.data());
		EXPECT_EQ(2.0f, *static_cast<const float*>(p.data()));
	}
	{
		const ShaderParameter<bksge::Vector3<float>> p(bksge::Vector3<float>{1,2,3});
		EXPECT_EQ(bksge::Vector3<float>(1,2,3), p.value());
		EXPECT_NE(nullptr, p.data());
		EXPECT_EQ(bksge::Vector3<float>(1,2,3), *static_cast<const bksge::Vector3<float>*>(p.data()));
	}
	{
		const ShaderParameter<bksge::Color4<float>> p(bksge::Color4<float>{4,5,6,7});
		EXPECT_EQ(bksge::Color4<float>(4,5,6,7), p.value());
		EXPECT_NE(nullptr, p.data());
		EXPECT_EQ(bksge::Color4<float>(4,5,6,7), *static_cast<const bksge::Color4<float>*>(p.data()));
	}
}

#if 0
GTEST_TEST(Render_ShaderParameter, CompareTest)
{
	using namespace bksge;
	using namespace bksge::render;

	const ShaderParameter<float>    p1(1);
	const ShaderParameter<float>    p2(1);
	const ShaderParameter<float>    p3(2);
	const ShaderParameter<bksge::Vector3<float>> p4(bksge::Vector3<float>{3, 4, 5});
	const ShaderParameter<bksge::Vector3<float>> p5(bksge::Vector3<float>{3, 4, 5});
	const ShaderParameter<bksge::Vector3<float>> p6(bksge::Vector3<float>{2, 4, 5});
	const ShaderParameter<bksge::Color3<float>>  p7(bksge::Color3<float>{3, 4, 5});

	EXPECT_TRUE (p1 == p1);
	EXPECT_TRUE (p1 == p2);
	EXPECT_FALSE(p1 == p3);
	EXPECT_FALSE(p1 == p4);
	EXPECT_FALSE(p1 == p5);
	EXPECT_FALSE(p1 == p6);
	EXPECT_FALSE(p1 == p7);
	EXPECT_TRUE (p4 == p4);
	EXPECT_TRUE (p4 == p5);
	EXPECT_FALSE(p4 == p6);
	EXPECT_FALSE(p4 == p7);

	EXPECT_FALSE(p1 != p1);
	EXPECT_FALSE(p1 != p2);
	EXPECT_TRUE (p1 != p3);
	EXPECT_TRUE (p1 != p4);
	EXPECT_TRUE (p1 != p5);
	EXPECT_TRUE (p1 != p6);
	EXPECT_TRUE (p1 != p7);
	EXPECT_FALSE(p4 != p4);
	EXPECT_FALSE(p4 != p5);
	EXPECT_TRUE (p4 != p6);
	EXPECT_TRUE (p4 != p7);
}
#endif

#if 0
GTEST_TEST(Render_ShaderParameter, SerializeTest)
{
	using namespace bksge;
	using namespace bksge::render;
	using namespace bksge::archive;

	const ShaderParameter<float>    p1(42);
	const ShaderParameter<bksge::Vector3<float>> p2({3, 4, 5});

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream> (p1);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream> (p2);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream> (p1);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_woarchive,  text_wiarchive,  std::wstringstream>(p2);
	SerializeTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>(p1);
#endif
}
#endif

#if 0

template <typename OArchive, typename IArchive, typename Stream>
void SerializeBasePtrTest(void)
{
	using namespace bksge;
	using namespace bksge::render;

	Stream s;
	{
		bksge::shared_ptr<ShaderParameterBase> p1 = bksge::make_shared<ShaderParameter<float>>(12.0f);
		bksge::shared_ptr<ShaderParameterBase> p2 = bksge::make_shared<ShaderParameter<bksge::Vector3<float>>>(bksge::Vector3<float>{1,2,3});
		bksge::shared_ptr<ShaderParameterBase> p3 = bksge::make_shared<ShaderParameter<bksge::Color4<float>>>(bksge::Color4<float>{4,5,6,7});

		OArchive oa(s);
		oa << BKSGE_SERIALIZATION_NVP(p1);
		oa << BKSGE_SERIALIZATION_NVP(p2);
		oa << BKSGE_SERIALIZATION_NVP(p3);
	}
	{
		bksge::shared_ptr<ShaderParameterBase> p1;
		bksge::shared_ptr<ShaderParameterBase> p2;
		bksge::shared_ptr<ShaderParameterBase> p3;

		IArchive ia(s);
		ia >> BKSGE_SERIALIZATION_NVP(p1);
		ia >> BKSGE_SERIALIZATION_NVP(p2);
		ia >> BKSGE_SERIALIZATION_NVP(p3);

		EXPECT_EQ(ShaderParameter<float>   ::StaticClassId(), p1->class_id());
		EXPECT_EQ(ShaderParameter<bksge::Vector3<float>>::StaticClassId(), p2->class_id());
		EXPECT_EQ(ShaderParameter<bksge::Color4<float>> ::StaticClassId(), p3->class_id());

		{
			auto const* p = static_cast<const float*>(p1->data());
			EXPECT_EQ(12, p[0]);
		}
		{
			auto const* p = static_cast<const float*>(p2->data());
			EXPECT_EQ(1, p[0]);
			EXPECT_EQ(2, p[1]);
			EXPECT_EQ(3, p[2]);
		}
		{
			auto const* p = static_cast<const float*>(p3->data());
			EXPECT_EQ(4, p[0]);
			EXPECT_EQ(5, p[1]);
			EXPECT_EQ(6, p[2]);
			EXPECT_EQ(7, p[3]);
		}
	}
}
#endif

#if 0
GTEST_TEST(Render_ShaderParameter, SerializeBasePtrTest)
{
	using namespace bksge::archive;

	SerializeBasePtrTest<text_oarchive,   text_iarchive,   std::stringstream> ();
	SerializeBasePtrTest<xml_oarchive,    xml_iarchive,    std::stringstream> ();
	SerializeBasePtrTest<binary_oarchive, binary_iarchive, std::stringstream> ();

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeBasePtrTest<text_woarchive,  text_wiarchive,  std::wstringstream>();
	SerializeBasePtrTest<xml_woarchive,   xml_wiarchive,   std::wstringstream>();
#endif
}
#endif

}	// namespace shader_parameter_test

}	// namespace bksge_core_render_test
