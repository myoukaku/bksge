/**
 *	@file	unit_test_core_math_transform3.cpp
 *
 *	@brief	Transform3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/transform3.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/quaternion.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/units/degree.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace transform3_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Transform3f = bksge::Transform3<float>;
using Transform3i = bksge::Transform3<int>;
using Vector3f    = bksge::Vector3<float>;
using Vector3i    = bksge::Vector3<int>;
using Quaternionf = bksge::Quaternion<float>;
using Quaternioni = bksge::Quaternion<int>;
using Scale3f     = bksge::Scale3<float>;
using Scale3i     = bksge::Scale3<int>;

using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathTransform3Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathTransform3Test, MathTestTypes);

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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	Transform3 v1({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 v2({3,4,5},{0,1,0,1},{9,8,7});
	VERIFY(PositionType(1,2,3)   == v1.position());
	VERIFY(RotationType(1,0,0,1) == v1.rotation());
	VERIFY(ScaleType(4,5,6)      == v1.scale());
	VERIFY(PositionType(3,4,5)   == v2.position());
	VERIFY(RotationType(0,1,0,1) == v2.rotation());
	VERIFY(ScaleType(9,8,7)      == v2.scale());

	v1 = Transform3({0,1,2},{0,0,0,1},{-4,1,2});
	v2 = Transform3i({-3,-2,-1},{0,0,1,1},{1,1,3});
	VERIFY(PositionType(0,1,2)    == v1.position());
	VERIFY(RotationType(0,0,0,1)  == v1.rotation());
	VERIFY(ScaleType(-4,1,2)      == v1.scale());
	VERIFY(PositionType(-3,-2,-1) == v2.position());
	VERIFY(RotationType(0,0,1,1)  == v2.rotation());
	VERIFY(ScaleType(1,1,3)       == v2.scale());

	// 自己代入
	v1 = v1;
	v2 = v2;
	VERIFY(PositionType(0,1,2)    == v1.position());
	VERIFY(RotationType(0,0,0,1)  == v1.rotation());
	VERIFY(ScaleType(-4,1,2)      == v1.scale());
	VERIFY(PositionType(-3,-2,-1) == v2.position());
	VERIFY(RotationType(0,0,1,1)  == v2.rotation());
	VERIFY(ScaleType(1,1,3)       == v2.scale());

	// 多重代入
	v1 = v2 = Transform3f({10,20,30},{1,0,0,1},{-1,-2,-3});
	VERIFY(PositionType(10,20,30) == v1.position());
	VERIFY(RotationType(1,0,0,1)  == v1.rotation());
	VERIFY(ScaleType(-1,-2,-3)    == v1.scale());
	VERIFY(PositionType(10,20,30) == v2.position());
	VERIFY(RotationType(1,0,0,1)  == v2.rotation());
	VERIFY(ScaleType(-1,-2,-3)    == v2.scale());

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathTransform3Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SetValueTest()
{
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	Transform3 v;
	VERIFY(PositionType(0,0,0)   == v.position());
	VERIFY(RotationType(0,0,0,1) == v.rotation());
	VERIFY(ScaleType(1,1,1)      == v.scale());

	v.position() += PositionType(1, 2, 3);
	VERIFY(PositionType(1,2,3)   == v.position());
	VERIFY(RotationType(0,0,0,1) == v.rotation());
	VERIFY(ScaleType(1,1,1)      == v.scale());

	v.rotation() = RotationType(1,1,1,1);
	VERIFY(PositionType(1,2,3)   == v.position());
	VERIFY(RotationType(1,1,1,1) == v.rotation());
	VERIFY(ScaleType(1,1,1)      == v.scale());

	v.scale() *= 2;
	VERIFY(PositionType(1,2,3)   == v.position());
	VERIFY(RotationType(1,1,1,1) == v.rotation());
	VERIFY(ScaleType(2,2,2)      == v.scale());

	return true;
}

TYPED_TEST(MathTransform3Test, SetValueTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SetValueTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool GetMatrix4x4Test()
{
	using Transform3 = bksge::Transform3<T>;
	//using PositionType  = typename Transform3::PositionType;
	using RotationType  = typename Transform3::RotationType;
	//using ScaleType     = typename Transform3::ScaleType;
	using Matrix4x4Type = typename Transform3::Matrix4x4Type;
	using Degree = bksge::units::degrees<T>;

	{
		Transform3 v;
		VERIFY(Matrix4x4Type::Identity() == v.GetMatrix4x4());
	}
	{
		Transform3 v{{1,2,3},{0,0,0,1},{4,5,6}};
		auto m =
			Matrix4x4Type::MakeScale(4,5,6) *
			Matrix4x4Type::MakeTranslation(1,2,3);
		VERIFY(m == v.GetMatrix4x4());
	}
	{
		auto const q =
			RotationType::MakeRotationX(Degree(180));
		Transform3 const v{{1,2,3},q,{4,5,6}};
		auto const m =
			Matrix4x4Type::MakeScale(4,5,6) *
			Matrix4x4Type::MakeRotationX(Degree(180)) *
			Matrix4x4Type::MakeTranslation(1,2,3);
		VERIFY(m == v.GetMatrix4x4());
	}
	return true;
}

TYPED_TEST(MathTransform3Test, GetMatrix4x4Test)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(GetMatrix4x4Test<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Transform3 = bksge::Transform3<T>;
	using PositionType = typename Transform3::PositionType;
	using RotationType = typename Transform3::RotationType;
	using ScaleType    = typename Transform3::ScaleType;

	Transform3 v1({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 v2({3,4,5},{0,1,0,1},{9,8,7});

	v1.swap(v2);

	VERIFY(PositionType(3,4,5)   == v1.position());
	VERIFY(RotationType(0,1,0,1) == v1.rotation());
	VERIFY(ScaleType(9,8,7)      == v1.scale());
	VERIFY(PositionType(1,2,3)   == v2.position());
	VERIFY(RotationType(1,0,0,1) == v2.rotation());
	VERIFY(ScaleType(4,5,6)      == v2.scale());

	bksge::ranges::swap(v1, v2);

	VERIFY(PositionType(1,2,3)   == v1.position());
	VERIFY(RotationType(1,0,0,1) == v1.rotation());
	VERIFY(ScaleType(4,5,6)      == v1.scale());
	VERIFY(PositionType(3,4,5)   == v2.position());
	VERIFY(RotationType(0,1,0,1) == v2.rotation());
	VERIFY(ScaleType(9,8,7)      == v2.scale());

	return true;
}

TYPED_TEST(MathTransform3Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Transform3 = bksge::Transform3<T>;

	Transform3 const v1({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 const v2({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 const v3({0,2,3},{1,0,0,1},{4,5,6});
	Transform3 const v4({1,2,3},{1,1,0,1},{4,5,6});
	Transform3 const v5({1,2,3},{1,0,0,1},{4,3,6});

	VERIFY( (v1 == v1));
	VERIFY( (v1 == v2));
	VERIFY(!(v1 == v3));
	VERIFY(!(v1 == v4));
	VERIFY(!(v1 == v5));

	VERIFY(!(v1 != v1));
	VERIFY(!(v1 != v2));
	VERIFY( (v1 != v3));
	VERIFY( (v1 != v4));
	VERIFY( (v1 != v5));

	return true;
}

TYPED_TEST(MathTransform3Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool HashTest()
{
	using Transform3 = bksge::Transform3<T>;

	Transform3 const v1({1,2,3},{1,0,0,1},{4,5,6});
	Transform3 const v2({0,2,3},{1,0,0,1},{4,5,6});
	Transform3 const v3({1,2,3},{1,1,0,1},{4,5,6});
	Transform3 const v4({1,2,3},{1,0,0,1},{4,3,6});

	bksge::hash<Transform3> h;

	VERIFY(h(v1) == h(v1));
	VERIFY(h(v1) != h(v2));
	VERIFY(h(v1) != h(v3));
	VERIFY(h(v1) != h(v4));

	VERIFY(h(v2) != h(v1));
	VERIFY(h(v2) == h(v2));
	VERIFY(h(v2) != h(v3));
	VERIFY(h(v2) != h(v4));

	VERIFY(h(v3) != h(v1));
	VERIFY(h(v3) != h(v2));
	VERIFY(h(v3) == h(v3));
	VERIFY(h(v3) != h(v4));

	VERIFY(h(v4) != h(v1));
	VERIFY(h(v4) != h(v2));
	VERIFY(h(v4) != h(v3));
	VERIFY(h(v4) == h(v4));

	return true;
}

TYPED_TEST(MathTransform3Test, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

#undef VERIFY

}	// namespace transform3_test

}	// namespace bksge_math_test
