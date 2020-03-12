/**
 *	@file	unit_test_fnd_list_list.cpp
 *
 *	@brief	list のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <string>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/memory/allocator.hpp>
#include <iosfwd>
#include <utility>
#include <gtest/gtest.h>

namespace bksge_container_list_test
{

#if 0
template <typename T>
struct NonPropagateAllocator
	: public bksge::allocator<T>
{
	using propagate_on_container_move_assignment = bksge::false_type;
};
#endif

GTEST_TEST(ListTest, ConstructTest)
{
	// デフォルト構築
	{
		bksge::list<int> l;
		EXPECT_TRUE(l.empty());
		EXPECT_LE(0u, l.max_size());
	}
	{
		bksge::list<int> l = {};
		EXPECT_TRUE(l.empty());
		EXPECT_LE(0u, l.max_size());
	}
	{
		bksge::list<int> l {};
		EXPECT_TRUE(l.empty());
		EXPECT_LE(0u, l.max_size());
	}
	// アロケータ指定
	{
		bksge::allocator<int> alloc;
		bksge::list<int> l(alloc);
		EXPECT_TRUE(l.empty());
	}
	{
		bksge::allocator<int> alloc;
		bksge::list<int> l{alloc};
		EXPECT_TRUE(l.empty());
	}
	// n個の指定された値を要素に持つリストを作成
	{
		bksge::list<int> l(3, 42);
		EXPECT_FALSE(l.empty());
		EXPECT_LE(0u, l.max_size());
		auto it = l.begin();
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(42, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(42, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(42, *it++);
		EXPECT_TRUE(it == l.end());
	}
	// n個の指定された値を要素に持つリストを作成(アロケータ指定)
	{
		bksge::allocator<int> alloc;
		bksge::list<int> l(3, 42, alloc);
		EXPECT_FALSE(l.empty());
		EXPECT_LE(0u, l.max_size());
		auto it = l.begin();
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(42, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(42, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(42, *it++);
		EXPECT_TRUE(it == l.end());
	}
	// n個の要素を持つリストを作成
	{
		bksge::list<int> l(4);
		EXPECT_FALSE(l.empty());
		EXPECT_LE(0u, l.max_size());
		auto it = l.begin();
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == l.end());
	}
	// n個の要素を持つリストを作成(アロケータ指定)
#if (BKSGE_CXX_STANDARD >= 14)
	{
		bksge::allocator<int> alloc;
		bksge::list<int> l(4, alloc);
		EXPECT_FALSE(l.empty());
		EXPECT_LE(0u, l.max_size());
		auto it = l.begin();
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == l.end());
	}
#endif
	{
		// 範囲から構築
		bksge::vector<int> v { 1, 2, 3, 4, 5 };
		bksge::list<int> l(v.begin(), v.end());
		EXPECT_FALSE(l.empty());
		EXPECT_LE(0u, l.max_size());
		{
			auto it = l.begin();
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(1, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(2, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(3, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(4, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(5, *it++);
			EXPECT_TRUE(it == l.end());
		}

		// コピー構築
		bksge::list<int> l2 = l;
		{
			auto it = l2.begin();
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(1, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(2, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(3, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(4, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(5, *it++);
			EXPECT_TRUE(it == l2.end());
		}

		// ムーブ構築
		bksge::list<int> l3 = bksge::move(l2);
		{
			auto it = l3.begin();
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(1, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(2, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(3, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(4, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(5, *it++);
			EXPECT_TRUE(it == l3.end());
		}
	}
	{
		bksge::allocator<int> alloc;

		// 範囲から構築(アロケータ指定)
		bksge::vector<int> v { 1, 2, 3, 4, 5 };
		bksge::list<int> l(v.begin(), v.end(), alloc);
		EXPECT_FALSE(l.empty());
		EXPECT_LE(0u, l.max_size());
		{
			auto it = l.begin();
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(1, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(2, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(3, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(4, *it++);
			EXPECT_FALSE(it == l.end());
			EXPECT_EQ(5, *it++);
			EXPECT_TRUE(it == l.end());
		}

		// コピー構築(アロケータ指定)
		bksge::list<int> l2(l, alloc);
		{
			auto it = l2.begin();
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(1, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(2, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(3, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(4, *it++);
			EXPECT_FALSE(it == l2.end());
			EXPECT_EQ(5, *it++);
			EXPECT_TRUE(it == l2.end());
		}

		// ムーブ構築(アロケータ指定)
		bksge::list<int> l3(bksge::move(l2), alloc);
		{
			auto it = l3.begin();
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(1, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(2, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(3, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(4, *it++);
			EXPECT_FALSE(it == l3.end());
			EXPECT_EQ(5, *it++);
			EXPECT_TRUE(it == l3.end());
		}
	}
	// 初期化子リストで構築
	{
		bksge::list<int> l = { 7, 8, 9 };
		auto it = l.begin();
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(7, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(8, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == l.end());
	}
	// 初期化子リストで構築(アロケータ指定)
	{
		bksge::allocator<int> alloc;
		bksge::list<int> l({ 7, 8, 9 }, alloc);
		auto it = l.begin();
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(7, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(8, *it++);
		EXPECT_FALSE(it == l.end());
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == l.end());
	}
}

GTEST_TEST(ListTest, OperatorAssignTest)
{
	{
		bksge::list<int> l1 = { 1, 2, 3 };

		// コピー代入
		bksge::list<int> l2;
		l2 = l1;
		EXPECT_EQ(l1, l2);

		// ムーブ代入
		bksge::list<int> l3;
		l3 = bksge::move(l1);
		EXPECT_EQ(l2, l3);

		// 初期化子リストからの代入
		bksge::list<int> l4;
		l4 = { 1, 2, 3 };
		EXPECT_EQ(l3, l4);
	}
#if 0
	{
		bksge::list<int, NonPropagateAllocator<int>> l1 = { 1, 2, 3 };

		// コピー代入
		bksge::list<int, NonPropagateAllocator<int>> l2;
		l2 = l1;
		EXPECT_EQ(l1, l2);

		// ムーブ代入
		bksge::list<int, NonPropagateAllocator<int>> l3;
		l3 = bksge::move(l1);
		EXPECT_EQ(l2, l3);

		// 初期化子リストからの代入
		bksge::list<int, NonPropagateAllocator<int>> l4;
		l4 = { 1, 2, 3 };
		EXPECT_EQ(l3, l4);
	}
#endif
}

GTEST_TEST(ListTest, AssignTest)
{
	// 範囲を代入
	{
		bksge::vector<int> v = { 1, 2, 3 };
		bksge::list<int> l;
		l.assign(v.begin(), v.end());
		bksge::list<int> expected = {1, 2, 3};
		EXPECT_EQ(expected, l);
	}
	// n個の指定された値で埋める
	{
		bksge::list<int> l;
		l.assign(4, 13);
		bksge::list<int> expected = {13, 13, 13, 13};
		EXPECT_EQ(expected, l);
	}
	// 初期化子リストを代入
	{
		bksge::list<int> l;
		l.assign({3, 4, 5, 6, 7});
		bksge::list<int> expected = {3, 4, 5, 6, 7};
		EXPECT_EQ(expected, l);
	}
}

GTEST_TEST(ListTest, GetAllocatorTest)
{
	bksge::allocator<int> alloc;
	bksge::list<int> l(alloc);

	auto result = l.get_allocator();
	EXPECT_EQ(alloc, result);
}

GTEST_TEST(ListTest, FrontTest)
{
	{
		bksge::list<int> l = {1, 2, 3, 4, 5};
		EXPECT_EQ(1, l.front());
	}
	{
		bksge::list<int> const l = {3, 1, 4};
		EXPECT_EQ(3, l.front());
	}
}

GTEST_TEST(ListTest, BackTest)
{
	{
		bksge::list<int> l = {1, 2, 3, 4, 5};
		EXPECT_EQ(5, l.back());
	}
	{
		bksge::list<int> const l = {3, 1, 4};
		EXPECT_EQ(4, l.back());
	}
}

GTEST_TEST(ListTest, BeginEndTest)
{
	{
		bksge::list<std::string> l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.begin();
		EXPECT_EQ("A", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("DEF", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("A", *it);
		EXPECT_EQ(1u, it->size());
		*it = "GHIJ";
		EXPECT_FALSE(it == l.end());
		EXPECT_TRUE (it != l.end());
		++it;
		EXPECT_FALSE(it == l.end());
		EXPECT_TRUE (it != l.end());
		++it;
		EXPECT_FALSE(it == l.end());
		EXPECT_TRUE (it != l.end());
		++it;
		EXPECT_TRUE (it == l.end());
		EXPECT_FALSE(it != l.end());

		bksge::list<std::string> expected
		{
			"GHIJ",
			"BC",
			"DEF",
		};
		EXPECT_EQ(expected, l);
	}
	{
		bksge::list<std::string> const l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.begin();
		EXPECT_EQ("A", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("DEF", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("A", *it);
		EXPECT_EQ(1u, it->size());
		EXPECT_FALSE(it == l.end());
		EXPECT_TRUE (it != l.end());
		++it;
		EXPECT_FALSE(it == l.end());
		EXPECT_TRUE (it != l.end());
		++it;
		EXPECT_FALSE(it == l.end());
		EXPECT_TRUE (it != l.end());
		++it;
		EXPECT_TRUE (it == l.end());
		EXPECT_FALSE(it != l.end());
	}
}

GTEST_TEST(ListTest, CBeginCEndTest)
{
	{
		bksge::list<std::string> l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.cbegin();
		EXPECT_EQ("A", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("DEF", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("A", *it);
		EXPECT_EQ(1u, it->size());
		EXPECT_FALSE(it == l.cend());
		EXPECT_TRUE (it != l.cend());
		++it;
		EXPECT_FALSE(it == l.cend());
		EXPECT_TRUE (it != l.cend());
		++it;
		EXPECT_FALSE(it == l.cend());
		EXPECT_TRUE (it != l.cend());
		++it;
		EXPECT_TRUE (it == l.cend());
		EXPECT_FALSE(it != l.cend());
	}
	{
		bksge::list<std::string> const l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.cbegin();
		EXPECT_EQ("A", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("DEF", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("A", *it);
		EXPECT_EQ(1u, it->size());
		EXPECT_FALSE(it == l.cend());
		EXPECT_TRUE (it != l.cend());
		++it;
		EXPECT_FALSE(it == l.cend());
		EXPECT_TRUE (it != l.cend());
		++it;
		EXPECT_FALSE(it == l.cend());
		EXPECT_TRUE (it != l.cend());
		++it;
		EXPECT_TRUE (it == l.cend());
		EXPECT_FALSE(it != l.cend());
	}
}

GTEST_TEST(ListTest, RBeginREndTest)
{
	{
		bksge::list<std::string> l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.rbegin();
		EXPECT_EQ("DEF", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("A", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("DEF", *it);
		EXPECT_EQ(3u, it->size());
		*it = "GHIJ";
		EXPECT_FALSE(it == l.rend());
		EXPECT_TRUE (it != l.rend());
		++it;
		EXPECT_FALSE(it == l.rend());
		EXPECT_TRUE (it != l.rend());
		++it;
		EXPECT_FALSE(it == l.rend());
		EXPECT_TRUE (it != l.rend());
		++it;
		EXPECT_TRUE (it == l.rend());
		EXPECT_FALSE(it != l.rend());

		bksge::list<std::string> expected
		{
			"A",
			"BC",
			"GHIJ",
		};
		EXPECT_EQ(expected, l);
	}
	{
		bksge::list<std::string> const l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.rbegin();
		EXPECT_EQ("DEF", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("A", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("DEF", *it);
		EXPECT_EQ(3u, it->size());
		EXPECT_FALSE(it == l.rend());
		EXPECT_TRUE (it != l.rend());
		++it;
		EXPECT_FALSE(it == l.rend());
		EXPECT_TRUE (it != l.rend());
		++it;
		EXPECT_FALSE(it == l.rend());
		EXPECT_TRUE (it != l.rend());
		++it;
		EXPECT_TRUE (it == l.rend());
		EXPECT_FALSE(it != l.rend());
	}
}

GTEST_TEST(ListTest, CRBeginCREndTest)
{
	{
		bksge::list<std::string> l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.crbegin();
		EXPECT_EQ("DEF", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("A", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("DEF", *it);
		EXPECT_EQ(3u, it->size());
		EXPECT_FALSE(it == l.crend());
		EXPECT_TRUE (it != l.crend());
		++it;
		EXPECT_FALSE(it == l.crend());
		EXPECT_TRUE (it != l.crend());
		++it;
		EXPECT_FALSE(it == l.crend());
		EXPECT_TRUE (it != l.crend());
		++it;
		EXPECT_TRUE (it == l.crend());
		EXPECT_FALSE(it != l.crend());
	}
	{
		bksge::list<std::string> const l
		{
			"A",
			"BC",
			"DEF",
		};

		auto it = l.crbegin();
		EXPECT_EQ("DEF", *it++);
		EXPECT_EQ("BC", *it);
		EXPECT_EQ(2u, it->size());
		EXPECT_EQ("A", *(++it));
		EXPECT_EQ("BC", *(--it));
		EXPECT_EQ("BC", *it--);
		EXPECT_EQ("DEF", *it);
		EXPECT_EQ(3u, it->size());
		EXPECT_FALSE(it == l.crend());
		EXPECT_TRUE (it != l.crend());
		++it;
		EXPECT_FALSE(it == l.crend());
		EXPECT_TRUE (it != l.crend());
		++it;
		EXPECT_FALSE(it == l.crend());
		EXPECT_TRUE (it != l.crend());
		++it;
		EXPECT_TRUE (it == l.crend());
		EXPECT_FALSE(it != l.crend());
	}
}

GTEST_TEST(ListTest, EmptyTest)
{
	{
		bksge::list<int> l;
		EXPECT_TRUE(l.empty());
	}
	{
		bksge::list<int> l = {1, 2, 3};
		EXPECT_FALSE(l.empty());
	}
}

GTEST_TEST(ListTest, SizeTest)
{
	{
		bksge::list<int> l;
		EXPECT_EQ(0u, l.size());
	}
	{
		bksge::list<int> l = {1, 2, 3};
		EXPECT_EQ(3u, l.size());
	}
	{
		bksge::list<int> l = {3, 1, 4, 1, 5, 9, 2};
		EXPECT_EQ(7u, l.size());
	}
}

GTEST_TEST(ListTest, MaxSizeTest)
{
	{
		bksge::list<int> l;
		EXPECT_LE(0u, l.max_size());
	}
	{
		bksge::list<int> l = {1, 2, 3};
		EXPECT_LE(0u, l.max_size());
	}
}

GTEST_TEST(ListTest, ClearTest)
{
	bksge::list<int> l = { 1, 2, 3 };
	EXPECT_FALSE(l.empty());
	l.clear();
	EXPECT_TRUE(l.empty());
}

GTEST_TEST(ListTest, InsertTest)
{
	// ひとつの要素を挿入する
	{
		bksge::list<int> ls ={1, 2, 4};

		// 先頭に0を挿入
		{
			auto it = ls.insert(ls.begin(), 0);
			EXPECT_TRUE(it == ls.begin());
		}

		// 4の前に3を挿入
		{
			auto it = ls.insert(bksge::next(ls.cbegin(), 3), 3);
			EXPECT_TRUE(it == bksge::next(ls.begin(), 3));
		}

		bksge::list<int> expected ={0, 1, 2, 3, 4};
		EXPECT_EQ(expected, ls);
	}
	// n個の要素を挿入する
	{
		bksge::list<int> ls ={1, 2, 5};

		// 5の前に3を2個挿入する
		auto it = ls.insert(bksge::next(ls.begin(), 2), 2, 3);
		EXPECT_TRUE(it == bksge::next(ls.begin(), 2));

		bksge::list<int> expected ={1, 2, 3, 3, 5};
		EXPECT_EQ(expected, ls);
	}
	// 指定範囲の要素を挿入する
	{
		bksge::list<int> ls ={1, 2, 6};

		// vの全ての要素をlsに挿入する
		const bksge::vector<int> v ={3, 4, 5};
		auto it = ls.insert(bksge::next(ls.begin(), 2), v.begin(), v.end());
		EXPECT_TRUE(it == bksge::next(ls.begin(), 2));

		bksge::list<int> expected ={1, 2, 3, 4, 5, 6};
		EXPECT_EQ(expected, ls);
	}
	// 初期化子リストで要素を挿入する
	{
		bksge::list<int> ls ={1, 2, 6};

		auto it = ls.insert(bksge::next(ls.begin(), 2), {3, 4, 5});
		EXPECT_TRUE(it == bksge::next(ls.begin(), 2));

		bksge::list<int> expected ={1, 2, 3, 4, 5, 6};
		EXPECT_EQ(expected, ls);
	}
}

GTEST_TEST(ListTest, EmplaceTest)
{
	bksge::list<std::pair<int, std::string>> l;
	{
		auto it = l.emplace(l.begin(), 1, std::string("world"));
		EXPECT_EQ(1, it->first);
		EXPECT_EQ("world", it->second);
	}
	{
		auto it = l.emplace(l.begin(), 3, std::string("hello"));
		EXPECT_EQ(3, it->first);
		EXPECT_EQ("hello", it->second);
	}

	{
		auto it = l.begin();
		EXPECT_EQ(3, it->first);
		EXPECT_EQ("hello", it->second);
		++it;
		EXPECT_EQ(1, it->first);
		EXPECT_EQ("world", it->second);
		++it;
		EXPECT_TRUE(it == l.end());
	}
}

GTEST_TEST(ListTest, EraseTest)
{
	// 1引数版
	{
		bksge::list<int> ls ={1, 2, 3, 4, 5};

		// 4を削除
		ls.erase(bksge::next(ls.begin(), 3));

		bksge::list<int> expected ={1, 2, 3, 5};
		EXPECT_EQ(expected, ls);
	}

	// 2引数版
	{
		bksge::list<int> ls ={1, 2, 3, 4, 5};

		// 3以降を削除
		ls.erase(bksge::next(ls.begin(), 2), ls.end());

		bksge::list<int> expected ={1, 2};
		EXPECT_EQ(expected, ls);
	}
}

GTEST_TEST(ListTest, PushBackTest)
{
	bksge::list<std::string> l;

	// const&バージョン
	std::string s = "world";
	l.push_back(s);

	// &&バージョン
	l.push_back(std::string("hello"));

	auto it = l.begin();
	EXPECT_EQ("world", *it++);
	EXPECT_EQ("hello", *it++);
	EXPECT_TRUE(it == l.end());
}

GTEST_TEST(ListTest, EmplaceBackTest)
{
	bksge::list<std::pair<int, std::string>> l;
	l.emplace_back(1, std::string("world"));
	l.emplace_back(3, std::string("hello"));

	auto it = l.begin();
	EXPECT_EQ(1, it->first);
	EXPECT_EQ("world", it->second);
	++it;
	EXPECT_EQ(3, it->first);
	EXPECT_EQ("hello", it->second);
	++it;
	EXPECT_TRUE(it == l.end());
}

GTEST_TEST(ListTest, PopBackTest)
{
	bksge::list<int> l = { 1, 2, 3 };

	l.pop_back();

	bksge::list<int> expected = { 1, 2 };
	EXPECT_EQ(expected, l);
}

GTEST_TEST(ListTest, PushFrontTest)
{
	bksge::list<std::string> l;

	// const&バージョン
	std::string s = "world";
	l.push_front(s);

	// &&バージョン
	l.push_front(std::string("hello"));

	auto it = l.begin();
	EXPECT_EQ("hello", *it++);
	EXPECT_EQ("world", *it++);
	EXPECT_TRUE(it == l.end());
}

GTEST_TEST(ListTest, EmplaceFrontTest)
{
	bksge::list<std::pair<int, std::string>> l;
	l.emplace_front(1, std::string("world"));
	l.emplace_front(3, std::string("hello"));

	auto it = l.begin();
	EXPECT_EQ(3, it->first);
	EXPECT_EQ("hello", it->second);
	++it;
	EXPECT_EQ(1, it->first);
	EXPECT_EQ("world", it->second);
	++it;
	EXPECT_TRUE(it == l.end());
}

GTEST_TEST(ListTest, PopFrontTest)
{
	bksge::list<int> l = { 1, 2, 3 };

	l.pop_front();

	bksge::list<int> expected = { 2, 3 };
	EXPECT_EQ(expected, l);
}

GTEST_TEST(ListTest, ResizeTest)
{
	{
		bksge::list<int> l = { 1, 2, 3 };
		l.resize(5);
		bksge::list<int> expected = { 1, 2, 3, 0, 0 };
		EXPECT_EQ(expected, l);
	}
	{
		bksge::list<int> l = { 1, 2, 3 };
		l.resize(5, 8);
		bksge::list<int> expected = { 1, 2, 3, 8, 8 };
		EXPECT_EQ(expected, l);
	}
	{
		bksge::list<int> l = { 1, 2, 3 };
		l.resize(1);
		bksge::list<int> expected = { 1 };
		EXPECT_EQ(expected, l);
	}
	{
		bksge::list<int> l = { 1, 2, 3 };
		l.resize(1, 8);
		bksge::list<int> expected = { 1 };
		EXPECT_EQ(expected, l);
	}
}

GTEST_TEST(ListTest, SwapTest)
{
	bksge::list<int> l1 = { 1, 2, 3 };
	bksge::list<int> l2 = { 4, 5, 6 };

	bksge::list<int> expected1 = { 1, 2, 3 };
	bksge::list<int> expected2 = { 4, 5, 6 };
	EXPECT_EQ(expected1, l1);
	EXPECT_EQ(expected2, l2);

	l1.swap(l2);
	EXPECT_EQ(expected2, l1);
	EXPECT_EQ(expected1, l2);

	l1.swap(l2);
	EXPECT_EQ(expected1, l1);
	EXPECT_EQ(expected2, l2);

	swap(l1, l2);
	EXPECT_EQ(expected2, l1);
	EXPECT_EQ(expected1, l2);
}

GTEST_TEST(ListTest, MergeTest)
{
	{
		bksge::list<int> l1 = { 1, 3, 4, 5 };
		bksge::list<int> l2 = { 2, 6 };
		l1.merge(l2);
		bksge::list<int> expected = { 1, 2, 3, 4, 5, 6 };
		EXPECT_EQ(expected, l1);
	}
	{
		bksge::list<int> l1 = { 1, 3, 4, 5 };
		bksge::list<int> l2 = { 2, 6 };
		l1.merge(bksge::move(l2));
		bksge::list<int> expected = { 1, 2, 3, 4, 5, 6 };
		EXPECT_EQ(expected, l1);
	}
	{
		bksge::list<int> l1 = { 1, 3, 4, 5 };
		bksge::list<int> l2 = { 2, 6 };
		l1.merge(l2, [](int x, int y) { return x < y; });
		bksge::list<int> expected = { 1, 2, 3, 4, 5, 6 };
		EXPECT_EQ(expected, l1);
	}
	{
		bksge::list<int> l1 = { 1, 3, 4, 5 };
		bksge::list<int> l2 = { 2, 6 };
		l1.merge(bksge::move(l2), [](int x, int y) { return x < y; });
		bksge::list<int> expected = { 1, 2, 3, 4, 5, 6 };
		EXPECT_EQ(expected, l1);
	}
}

GTEST_TEST(ListTest, SpliceTest)
{
	// ysの全ての要素をxsに移動する
	{
		bksge::list<int> xs ={4, 5, 6};
		bksge::list<int> ys ={1, 2, 3};

		xs.splice(xs.begin(), bksge::move(ys));

		bksge::list<int> expected = { 1, 2, 3, 4, 5, 6 };
		EXPECT_EQ(expected, xs);
	}
	// ysのうち、1だけを移動する
	{
		bksge::list<int> xs ={4, 5, 6};
		bksge::list<int> ys ={1, 2, 3};

		xs.splice(xs.begin(), bksge::move(ys), ys.begin());

		bksge::list<int> expected = { 1, 4, 5, 6 };
		EXPECT_EQ(expected, xs);
	}
	// ysのうち、1と2だけを移動する
	{
		bksge::list<int> xs ={4, 5, 6};
		bksge::list<int> ys ={1, 2, 3};

		xs.splice(xs.begin(), bksge::move(ys), ys.begin(), bksge::next(ys.begin(), 2));

		bksge::list<int> expected = { 1, 2, 4, 5, 6 };
		EXPECT_EQ(expected, xs);
	}
}

GTEST_TEST(ListTest, RemoveTest)
{
	bksge::list<int> l = { 3, 1, 4, 1, 5};
	l.remove(1);
	bksge::list<int> expected = { 3, 4, 5 };
	EXPECT_EQ(expected, l);
}

GTEST_TEST(ListTest, RemoveIfTest)
{
	bksge::list<int> l = { 3, 1, 4, 1, 5};
	l.remove_if([](int x) { return x % 2 == 0; });
	bksge::list<int> expected = { 3, 1, 1, 5 };
	EXPECT_EQ(expected, l);
}

GTEST_TEST(ListTest, ReverseTest)
{
	{
		bksge::list<int> l = { 1, 2, 3 };
		l.reverse();
		bksge::list<int> expected = { 3, 2, 1 };
		EXPECT_EQ(expected, l);
	}
}

GTEST_TEST(ListTest, UniqueTest)
{
	{
		bksge::list<int> l = { 1, 1, 2, 3, 3, 3, 4, 5, 5, 5 };
		l.unique();
		bksge::list<int> expected = { 1, 2, 3, 4, 5 };
		EXPECT_EQ(expected, l);
	}
	{
		bksge::list<int> l = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		l.sort();
		l.unique([](int x, int y) { return x == y; });
		bksge::list<int> expected = { 1, 2, 3, 4, 5, 6, 9 };
		EXPECT_EQ(expected, l);
	}
}

GTEST_TEST(ListTest, SortTest)
{
	{
		bksge::list<int> l = { 3, 1, 4, 1, 5 };
		l.sort();
		bksge::list<int> expected = { 1, 1, 3, 4, 5 };
		EXPECT_EQ(expected, l);
	}
	{
		bksge::list<int> l = { 3, 1, 4, 1, 5 };
		l.sort([](int x, int y) { return x > y; });
		bksge::list<int> expected = { 5, 4, 3, 1, 1 };
		EXPECT_EQ(expected, l);
	}
}

GTEST_TEST(ListTest, CompareTest)
{
	bksge::list<int> l1 = { 1, 2, 3 };
	bksge::list<int> l2 = { 1, 2, 3 };
	bksge::list<int> l3 = { 2, 2, 3 };
	bksge::list<int> l4 = { 1, 1, 3 };
	bksge::list<int> l5 = { 1, 2, 3, 4 };
	bksge::list<int> l6 = { 1, 2 };

	EXPECT_TRUE (l1 == l1);
	EXPECT_TRUE (l1 == l2);
	EXPECT_FALSE(l1 == l3);
	EXPECT_FALSE(l1 == l4);
	EXPECT_FALSE(l1 == l5);
	EXPECT_FALSE(l1 == l6);

	EXPECT_FALSE(l1 != l1);
	EXPECT_FALSE(l1 != l2);
	EXPECT_TRUE (l1 != l3);
	EXPECT_TRUE (l1 != l4);
	EXPECT_TRUE (l1 != l5);
	EXPECT_TRUE (l1 != l6);

	EXPECT_FALSE(l1 <  l1);
	EXPECT_FALSE(l1 <  l2);
	EXPECT_TRUE (l1 <  l3);
	EXPECT_FALSE(l1 <  l4);
	EXPECT_TRUE (l1 <  l5);
	EXPECT_FALSE(l1 <  l6);

	EXPECT_FALSE(l1 >  l1);
	EXPECT_FALSE(l1 >  l2);
	EXPECT_FALSE(l1 >  l3);
	EXPECT_TRUE (l1 >  l4);
	EXPECT_FALSE(l1 >  l5);
	EXPECT_TRUE (l1 >  l6);

	EXPECT_TRUE (l1 <= l1);
	EXPECT_TRUE (l1 <= l2);
	EXPECT_TRUE (l1 <= l3);
	EXPECT_FALSE(l1 <= l4);
	EXPECT_TRUE (l1 <= l5);
	EXPECT_FALSE(l1 <= l6);

	EXPECT_TRUE (l1 >= l1);
	EXPECT_TRUE (l1 >= l2);
	EXPECT_FALSE(l1 >= l3);
	EXPECT_TRUE (l1 >= l4);
	EXPECT_FALSE(l1 >= l5);
	EXPECT_TRUE (l1 >= l6);
}

}	// namespace bksge_container_list_test
