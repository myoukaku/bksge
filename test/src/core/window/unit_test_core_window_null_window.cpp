/**
 *	@file	unit_test_core_window_null_window.cpp
 *
 *	@brief	NullWindow のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/window/null/null_window.hpp>
#include <gtest/gtest.h>

namespace bksge_core_window_test
{

namespace null_window_test
{

GTEST_TEST(WindowTest, NullWindowTest)
{
	using WindowType = bksge::window::NullWindow;
	using SizeType = WindowType::SizeType;

	WindowType w{{400, 300}, "hoge"};

	EXPECT_EQ("hoge", w.title());
	EXPECT_EQ(SizeType(400, 300), w.client_size());
	w.handle();

	w.SetTitle("foo");
	w.SetClientSize({10, 20});

	EXPECT_EQ("foo", w.title());
	EXPECT_EQ(SizeType(10, 20), w.client_size());

	w.Update();

	w.Destroy();
}

}	// namespace null_window_test

}	// namespace bksge_core_window_test
