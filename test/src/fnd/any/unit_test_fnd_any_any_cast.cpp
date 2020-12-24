/**
 *	@file	unit_test_fnd_any_any_cast.cpp
 *
 *	@brief	any_cast のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/any/any.hpp>
#include <bksge/fnd/any/any_cast.hpp>
#include <bksge/fnd/any/bad_any_cast.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_any_test
{

namespace any_cast_test
{

static int move_count = 0;

struct MoveEnabled
{
	MoveEnabled(MoveEnabled&&)
	{
		++move_count;
	}
	MoveEnabled() = default;
	MoveEnabled(const MoveEnabled&) = default;
};

struct MoveDeleted
{
	MoveDeleted(MoveDeleted&&) = delete;
	MoveDeleted() = default;
	MoveDeleted(const MoveDeleted&) = default;
};

GTEST_TEST(AnyTest, AnyCastTest)
{
	using bksge::any;
	using bksge::any_cast;
	{
		using bksge::string;

		// taken from example in N3804 proposal

		any x(5);                                   // x holds int
		EXPECT_EQ(5, any_cast<int>(x));             // cast to value
		any_cast<int&>(x) = 10;                     // cast to reference
		EXPECT_EQ(10, any_cast<int>(x));

		x = "Meow";                                 // x holds const char*
		EXPECT_STREQ(any_cast<const char*>(x), "Meow");
		any_cast<const char*&>(x) = "Harry";
		EXPECT_STREQ(any_cast<const char*>(x), "Harry");

		x = string("Meow");                         // x holds string
		string s, s2("Jane");
		s = bksge::move(any_cast<string&>(x));             // move from any 
		EXPECT_TRUE(s == "Meow");
		any_cast<string&>(x) = bksge::move(s2);            // move to any
		EXPECT_TRUE(any_cast<const string&>(x) == "Jane");

		string cat("Meow");
		const any y(cat);                           // const y holds string
		EXPECT_TRUE(any_cast<const string&>(y) == cat);
	}
	{
		using bksge::bad_any_cast;

		any x(1);
		auto p = any_cast<double>(&x);
		EXPECT_TRUE(p == nullptr);

		x = 1.0;
		p = any_cast<double>(&x);
		EXPECT_TRUE(p != nullptr);

		x = any();
		p = any_cast<double>(&x);
		EXPECT_TRUE(p == nullptr);

		try
		{
			(void)any_cast<double>(x);
			EXPECT_TRUE(false);
		}
		catch (const bad_any_cast&)
		{
		}

		any* ap = nullptr;
		p = any_cast<double>(ap);
		EXPECT_TRUE(p == nullptr);

		const any* cap = nullptr;
		auto cp = any_cast<double>(cap);
		EXPECT_TRUE(cp == nullptr);
	}
	{
		MoveEnabled m;
		MoveEnabled m2 = any_cast<MoveEnabled>(any(m));
		(void)m2;
		EXPECT_EQ(1, move_count);

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 10) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wdangling-gsl")
#endif

		MoveEnabled&& m3 = any_cast<MoveEnabled&&>(any(m));
		(void)m3;
		EXPECT_EQ(1, move_count);

BKSGE_WARNING_POP()

#if 0
		MoveDeleted md;
		(void)md;
		//MoveDeleted&& md2 = any_cast<MoveDeleted>(any(bksge::move(md)));
		//(void)md2;
		MoveDeleted&& md3 = any_cast<MoveDeleted&&>(any(bksge::move(md)));
		(void)md3;
#endif
	}
#if 0
	{
		struct ExplicitCopy
		{
			ExplicitCopy() = default;
			explicit ExplicitCopy(const ExplicitCopy&) = default;
		};
		any x = ExplicitCopy();
		ExplicitCopy ec{ any_cast<ExplicitCopy>(x) };
		(void)ec;
		ExplicitCopy ec2{ any_cast<ExplicitCopy>(bksge::move(x)) };
		(void)ec2;
	}
	{
		// PR libstdc++/69321
		struct noncopyable
		{
			noncopyable(noncopyable const&) = delete;
		};

		any a;
		auto p = any_cast<noncopyable>(&a);
		EXPECT_TRUE(p == nullptr);
	}
#endif

	{
		using bksge::bad_any_cast;

		any x(1);
		auto p = any_cast<double>(&x);
		EXPECT_TRUE(p == nullptr);

		x = 1.0;
		p = any_cast<double>(&x);
		EXPECT_TRUE(p != nullptr);

		x = any();
		p = any_cast<double>(&x);
		EXPECT_TRUE(p == nullptr);

		try
		{
			(void)any_cast<double>(x);
			EXPECT_TRUE(false);
		}
		catch (const bad_any_cast&)
		{
		}

		try
		{
			(void)any_cast<double>(bksge::move(x));
			EXPECT_TRUE(false);
		}
		catch (const bad_any_cast&)
		{
		}

		const any y;

		try
		{
			(void)any_cast<double>(y);
			EXPECT_TRUE(false);
		}
		catch (const bad_any_cast&)
		{
		}
	}
}

}	// namespace any_cast_test

}	// namespace bksge_any_test
