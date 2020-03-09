/**
 *	@file	unit_test_core_math_transform3.cpp
 *
 *	@brief	Transform3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/transform3.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/units/degree.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <functional>
#include <vector>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace transform3_test
{

using Transform3f = bksge::Transform3<float>;
using Transform3i = bksge::Transform3<int>;
using Vector3f    = bksge::Vector3<float>;
using Vector3i    = bksge::Vector3<int>;
using Quaternionf = bksge::Quaternion<float>;
using Quaternioni = bksge::Quaternion<int>;
using Scale3f     = bksge::Scale3<float>;
using Scale3i     = bksge::Scale3<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathTransform3Test : public ::testing::Test {};
template <typename T>
class MathTransform3FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathTransform3Test, MathTestTypes);
TYPED_TEST_SUITE(MathTransform3FloatTest, MathFloatTestTypes);

TYPED_TEST(MathTransform3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	static_assert(sizeof(Transform3) == sizeof(T) * 10, "");
	static_assert(bksge::is_default_constructible<Transform3>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Transform3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Transform3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(0, 0, 0),    v.position());
		BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(0, 0, 0, 1), v.rotation());
		BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(1, 1, 1),       v.scale());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(0, 0, 0),    v.position());
		BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(0, 0, 0, 1), v.rotation());
		BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(1, 1, 1),       v.scale());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v={};
		BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(0, 0, 0),    v.position());
		BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(0, 0, 0, 1), v.rotation());
		BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(1, 1, 1),       v.scale());
	}
}

TYPED_TEST(MathTransform3Test, ValueConstructTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	static_assert(bksge::is_constructible<Transform3, PositionType, RotationType, ScaleType>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3, PositionType, RotationType, ScaleType>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3, PositionType, RotationType, ScaleType>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v({2,3,4},{0,1,0,1},{3,4,5});
		BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(2, 3, 4),    v.position());
		BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(0, 1, 0, 1), v.rotation());
		BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(3, 4, 5),       v.scale());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v{{2,3,4},{0,1,0,1},{3,4,5}};
		BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(2, 3, 4),    v.position());
		BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(0, 1, 0, 1), v.rotation());
		BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(3, 4, 5),       v.scale());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v = {{2,3,4},{0,1,0,1},{3,4,5}};
		BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(2, 3, 4),    v.position());
		BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(0, 1, 0, 1), v.rotation());
		BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(3, 4, 5),       v.scale());
	}
}

TYPED_TEST(MathTransform3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	static_assert(bksge::is_constructible<Transform3,  Transform3  const&>::value, "");
	static_assert(bksge::is_constructible<Transform3,  Transform3i const&>::value, "");
	static_assert(bksge::is_constructible<Transform3,  Transform3f const&>::value, "");
	static_assert(bksge::is_constructible<Transform3i, Transform3  const&>::value, "");
	static_assert(bksge::is_constructible<Transform3i, Transform3i const&>::value, "");
	static_assert(bksge::is_constructible<Transform3i, Transform3f const&>::value, "");
	static_assert(bksge::is_constructible<Transform3f, Transform3  const&>::value, "");
	static_assert(bksge::is_constructible<Transform3f, Transform3i const&>::value, "");
	static_assert(bksge::is_constructible<Transform3f, Transform3f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Transform3,  Transform3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3,  Transform3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3,  Transform3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3i, Transform3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3i, Transform3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3i, Transform3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3f, Transform3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3f, Transform3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Transform3f, Transform3f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Transform3,  Transform3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3,  Transform3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3,  Transform3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3i, Transform3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3i, Transform3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3i, Transform3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3f, Transform3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3f, Transform3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Transform3f, Transform3f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Transform3  v1{{1,2,3},{1,0,0,1},{4,5,6}};
	BKSGE_CONSTEXPR_OR_CONST Transform3  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Transform3i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Transform3f v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(1, 2, 3),    v1.position());
	BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(1, 0, 0, 1), v1.rotation());
	BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(4, 5, 6),       v1.scale());
	BKSGE_CONSTEXPR_EXPECT_EQ(PositionType(1, 2, 3),    v2.position());
	BKSGE_CONSTEXPR_EXPECT_EQ(RotationType(1, 0, 0, 1), v2.rotation());
	BKSGE_CONSTEXPR_EXPECT_EQ(ScaleType(4, 5, 6),       v2.scale());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3i(1, 2, 3),        v3.position());
	BKSGE_CONSTEXPR_EXPECT_EQ(Quaternioni(1, 0, 0, 1),  v3.rotation());
	BKSGE_CONSTEXPR_EXPECT_EQ(Scale3i(4, 5, 6),         v3.scale());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3f(1, 2, 3),        v4.position());
	BKSGE_CONSTEXPR_EXPECT_EQ(Quaternionf(1, 0, 0, 1),  v4.rotation());
	BKSGE_CONSTEXPR_EXPECT_EQ(Scale3f(4, 5, 6),         v4.scale());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathTransform3Test, CopyAssignTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	Transform3 v1({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 v2({3,4,5},{0,1,0,1},{9,8,7});
	EXPECT_EQ(PositionType(1,2,3),   v1.position());
	EXPECT_EQ(RotationType(1,0,0,1), v1.rotation());
	EXPECT_EQ(ScaleType(4,5,6),      v1.scale());
	EXPECT_EQ(PositionType(3,4,5),   v2.position());
	EXPECT_EQ(RotationType(0,1,0,1), v2.rotation());
	EXPECT_EQ(ScaleType(9,8,7),      v2.scale());

	v1 = Transform3({0,1,2},{0,0,0,1},{-4,1,2});
	v2 = Transform3i({-3,-2,-1},{0,0,1,1},{1,1,3});
	EXPECT_EQ(PositionType(0,1,2),    v1.position());
	EXPECT_EQ(RotationType(0,0,0,1),  v1.rotation());
	EXPECT_EQ(ScaleType(-4,1,2),      v1.scale());
	EXPECT_EQ(PositionType(-3,-2,-1), v2.position());
	EXPECT_EQ(RotationType(0,0,1,1),  v2.rotation());
	EXPECT_EQ(ScaleType(1,1,3),       v2.scale());

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ(PositionType(0,1,2),    v1.position());
	EXPECT_EQ(RotationType(0,0,0,1),  v1.rotation());
	EXPECT_EQ(ScaleType(-4,1,2),      v1.scale());
	EXPECT_EQ(PositionType(-3,-2,-1), v2.position());
	EXPECT_EQ(RotationType(0,0,1,1),  v2.rotation());
	EXPECT_EQ(ScaleType(1,1,3),       v2.scale());

	// 多重代入
	v1 = v2 = Transform3f({10,20,30},{1,0,0,1},{-1,-2,-3});
	EXPECT_EQ(PositionType(10,20,30), v1.position());
	EXPECT_EQ(RotationType(1,0,0,1),  v1.rotation());
	EXPECT_EQ(ScaleType(-1,-2,-3),    v1.scale());
	EXPECT_EQ(PositionType(10,20,30), v2.position());
	EXPECT_EQ(RotationType(1,0,0,1),  v2.rotation());
	EXPECT_EQ(ScaleType(-1,-2,-3),    v2.scale());
}

BKSGE_WARNING_POP()

TYPED_TEST(MathTransform3Test, SetValueTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	Transform3 v;
	EXPECT_EQ(PositionType(0,0,0),   v.position());
	EXPECT_EQ(RotationType(0,0,0,1), v.rotation());
	EXPECT_EQ(ScaleType(1,1,1),      v.scale());

	v.position() += PositionType(1, 2, 3);
	EXPECT_EQ(PositionType(1,2,3),   v.position());
	EXPECT_EQ(RotationType(0,0,0,1), v.rotation());
	EXPECT_EQ(ScaleType(1,1,1),      v.scale());

	v.rotation() = RotationType(1,1,1,1);
	EXPECT_EQ(PositionType(1,2,3),   v.position());
	EXPECT_EQ(RotationType(1,1,1,1), v.rotation());
	EXPECT_EQ(ScaleType(1,1,1),      v.scale());

	v.scale() *= 2;
	EXPECT_EQ(PositionType(1,2,3),   v.position());
	EXPECT_EQ(RotationType(1,1,1,1), v.rotation());
	EXPECT_EQ(ScaleType(2,2,2),      v.scale());
}

TYPED_TEST(MathTransform3FloatTest, GetMatrix4x4Test)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;
	//using PositionType  = typename Transform3::PositionType;
	using RotationType  = typename Transform3::RotationType;
	//using ScaleType     = typename Transform3::ScaleType;
	using Matrix4x4Type = typename Transform3::Matrix4x4Type;
	using Degree = bksge::units::degrees<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v;
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4Type::Identity();
		BKSGE_CONSTEXPR_EXPECT_EQ(m, v.GetMatrix4x4());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Transform3 v{{1,2,3},{0,0,0,1},{4,5,6}};
		BKSGE_CONSTEXPR_OR_CONST auto m =
			Matrix4x4Type::MakeScale(4,5,6) *
			Matrix4x4Type::MakeTranslation(1,2,3);
		BKSGE_CONSTEXPR_EXPECT_EQ(m, v.GetMatrix4x4());
	}
	{
		auto const q =
			RotationType::MakeRotationX(Degree(180));
		Transform3 const v{{1,2,3},q,{4,5,6}};
		auto const m =
			Matrix4x4Type::MakeScale(4,5,6) *
			Matrix4x4Type::MakeRotationX(Degree(180)) *
			Matrix4x4Type::MakeTranslation(1,2,3);
		EXPECT_EQ(m, v.GetMatrix4x4());
	}
}

TYPED_TEST(MathTransform3Test, SwapTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	Transform3 v1({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 v2({3,4,5},{0,1,0,1},{9,8,7});

	EXPECT_EQ(PositionType(1,2,3),   v1.position());
	EXPECT_EQ(RotationType(1,0,0,1), v1.rotation());
	EXPECT_EQ(ScaleType(4,5,6),      v1.scale());
	EXPECT_EQ(PositionType(3,4,5),   v2.position());
	EXPECT_EQ(RotationType(0,1,0,1), v2.rotation());
	EXPECT_EQ(ScaleType(9,8,7),      v2.scale());

	v1.swap(v2);

	EXPECT_EQ(PositionType(3,4,5),   v1.position());
	EXPECT_EQ(RotationType(0,1,0,1), v1.rotation());
	EXPECT_EQ(ScaleType(9,8,7),      v1.scale());
	EXPECT_EQ(PositionType(1,2,3),   v2.position());
	EXPECT_EQ(RotationType(1,0,0,1), v2.rotation());
	EXPECT_EQ(ScaleType(4,5,6),      v2.scale());

	swap(v1, v2);

	EXPECT_EQ(PositionType(1,2,3),   v1.position());
	EXPECT_EQ(RotationType(1,0,0,1), v1.rotation());
	EXPECT_EQ(ScaleType(4,5,6),      v1.scale());
	EXPECT_EQ(PositionType(3,4,5),   v2.position());
	EXPECT_EQ(RotationType(0,1,0,1), v2.rotation());
	EXPECT_EQ(ScaleType(9,8,7),      v2.scale());
}

TYPED_TEST(MathTransform3Test, CompareTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;

	BKSGE_CONSTEXPR_OR_CONST Transform3 v1({1,2,3},{1,0,0,1},{4,5,6});
	BKSGE_CONSTEXPR_OR_CONST Transform3 v2({1,2,3},{1,0,0,1},{4,5,6});
	BKSGE_CONSTEXPR_OR_CONST Transform3 v3({0,2,3},{1,0,0,1},{4,5,6});
	BKSGE_CONSTEXPR_OR_CONST Transform3 v4({1,2,3},{1,1,0,1},{4,5,6});
	BKSGE_CONSTEXPR_OR_CONST Transform3 v5({1,2,3},{1,0,0,1},{4,3,6});

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v5);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v5);
}

TYPED_TEST(MathTransform3Test, OutputStreamTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;

	{
		Transform3 const v;
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ { 0, 0, 0 }, { 0, 0, 0, 1 }, { 1, 1, 1 } }", ss.str());
	}
	{
		Transform3 const v{{1,2,3},{1,0,0,1},{4,5,6}};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ { 1, 2, 3 }, { 1, 0, 0, 1 }, { 4, 5, 6 } }", ss.str());
	}
}

TYPED_TEST(MathTransform3Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;

	Transform3 const v{{1,2,3},{1,0,0,1},{4,5,6}};

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathTransform3Test, HashTest)
{
	using T = TypeParam;
	using Transform3 = bksge::Transform3<T>;

	std::hash<Transform3> h;

	Transform3 const t1({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 const t2({0,2,3},{1,0,0,1},{4,5,6});
	Transform3 const t3({1,2,3},{1,1,0,1},{4,5,6});
	Transform3 const t4({1,2,3},{1,0,0,1},{4,3,6});

	bksge::vector<bksge::size_t> v;
	v.push_back(h(t1));
	v.push_back(h(t2));
	v.push_back(h(t3));
	v.push_back(h(t4));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(t1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace transform3_test

}	// namespace bksge_math_test
