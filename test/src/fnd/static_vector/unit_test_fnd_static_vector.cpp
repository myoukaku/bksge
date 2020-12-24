/**
 *	@file	unit_test_fnd_static_vector.cpp
 *
 *	@brief	bksge::static_vector のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/static_vector.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/rbegin.hpp>
#include <bksge/fnd/iterator/rend.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4267);
BKSGE_WARNING_DISABLE_MSVC(4834);

namespace bksge_static_vector_test
{

class value_ndc
{
public:
	BKSGE_CXX14_CONSTEXPR explicit value_ndc(int a): aa(a) {}
	BKSGE_CXX14_CONSTEXPR explicit value_ndc(int a, int b): aa(a+b) {}
	~value_ndc() = default;
	BKSGE_CXX14_CONSTEXPR bool operator==(value_ndc const& v) const { return aa == v.aa; }
	BKSGE_CXX14_CONSTEXPR bool operator< (value_ndc const& v) const { return aa <  v.aa; }
	BKSGE_CXX14_CONSTEXPR value_ndc(value_ndc&& rhs) : aa(rhs.aa) { rhs.aa = 0; }
	BKSGE_CXX14_CONSTEXPR value_ndc& operator=(value_ndc&& rhs) { aa = rhs.aa; rhs.aa = 0; return *this; }
private:
	value_ndc(value_ndc const&) {}
	value_ndc& operator=(value_ndc const&) { return *this; }
	int aa;
};

class value_nd
{
public:
	BKSGE_CXX14_CONSTEXPR explicit value_nd(int a): aa(a) {}
	BKSGE_CXX14_CONSTEXPR explicit value_nd(int a, int b): aa(a+b) {}
	~value_nd() = default;
	BKSGE_CXX14_CONSTEXPR bool operator==(value_nd const& v) const { return aa == v.aa; }
	BKSGE_CXX14_CONSTEXPR bool operator< (value_nd const& v) const { return aa <  v.aa; }
private:
	int aa;
};

class value_nc
{
public:
	BKSGE_CXX14_CONSTEXPR value_nc(): aa(0) {}
	BKSGE_CXX14_CONSTEXPR explicit value_nc(int a): aa(a) {}
	BKSGE_CXX14_CONSTEXPR explicit value_nc(int a, int b): aa(a+b) {}
	~value_nc() = default;
	BKSGE_CXX14_CONSTEXPR bool operator==(value_nc const& v) const { return aa == v.aa; }
	BKSGE_CXX14_CONSTEXPR bool operator< (value_nc const& v) const { return aa <  v.aa; }
	BKSGE_CXX14_CONSTEXPR value_nc(value_nc&& rhs) : aa(rhs.aa) { rhs.aa = 0; }
	BKSGE_CXX14_CONSTEXPR value_nc& operator=(value_nc&& rhs) { aa = rhs.aa; rhs.aa = 0; return *this; }
private:
	value_nc(value_nc const&) {}
	value_nc& operator=(value_nc const&) { return *this; }
	int aa;
};

class value_dc
{
public:
	BKSGE_CXX14_CONSTEXPR value_dc(): aa(0) {}
	BKSGE_CXX14_CONSTEXPR explicit value_dc(int a): aa(a) {}
	BKSGE_CXX14_CONSTEXPR explicit value_dc(int a, int b): aa(a+b) {}
	~value_dc() = default;
	BKSGE_CXX14_CONSTEXPR bool operator==(value_dc const& v) const { return aa == v.aa; }
	BKSGE_CXX14_CONSTEXPR bool operator< (value_dc const& v) const { return aa <  v.aa; }
	BKSGE_CXX14_CONSTEXPR value_dc(value_dc const& rhs) : aa(rhs.aa) {}
	BKSGE_CXX14_CONSTEXPR value_dc& operator=(value_dc const& rhs) { aa = rhs.aa; return *this; }
private:
	int aa;
};

class shptr_value
{
public:
	explicit shptr_value(int a = 0): m_ptr(new int(a)) {}
	bool operator==(shptr_value const& v) const { return *m_ptr == *(v.m_ptr); }
	bool operator< (shptr_value const& v) const { return *m_ptr <  *(v.m_ptr); }
private:
	bksge::shared_ptr<int> m_ptr;
};

class counting_value
{
public:
	explicit counting_value(int a = 0, int b = 0): aa(a), bb(b) { ++c(); }
	counting_value(counting_value const& v): aa(v.aa), bb(v.bb) { ++c(); }
	counting_value(counting_value&& p): aa(p.aa), bb(p.bb) { p.aa = 0; p.bb = 0; ++c(); }
	counting_value& operator=(counting_value&& p) { aa = p.aa; p.aa = 0; bb = p.bb; p.bb = 0; return *this; }
	counting_value& operator=(counting_value const& p) { aa = p.aa; bb = p.bb; return *this; }
	~counting_value() { --c(); }
	bool operator==(counting_value const& v) const { return aa == v.aa && bb == v.bb; }
	bool operator< (counting_value const& v) const { return aa < v.aa || (aa == v.aa && bb < v.bb); }
	static bksge::size_t count() { return c(); }

private:
	static bksge::size_t& c() { static bksge::size_t co = 0; return co; }
	int aa, bb;
};

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_ctor_default()
{
	static_assert((bksge::static_vector<T, N>::static_capacity) == N, "");

	bksge::static_vector<T, N> s;

	//EXPECT_THROW(s.at(0u), std::out_of_range);

	return
		s.size()     == 0u &&
		s.capacity() == N  &&
		s.max_size() == N;
}

GTEST_TEST(StaticVectorTest, CtorDefaultTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_default<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_default<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_default<value_nc, 12>()));
	                      EXPECT_TRUE((test_ctor_default<value_nd, 13>()));
	                      EXPECT_TRUE((test_ctor_default<value_ndc, 13>()));
	                      EXPECT_TRUE((test_ctor_default<counting_value, 14>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_ctor_default<shptr_value, 15>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_ctor_count(bksge::size_t n)
{
	static_assert((bksge::static_vector<T, N>::static_capacity) == N, "");

	bksge::static_vector<T, N> s(n);

	for (bksge::size_t i = 0; i < n; ++i)
	{
		if (!(s[i]  == T() &&
			s.at(i) == T()))
		{
			return false;
		}
	}

	if (n >= 1)
	{
		if (!(
			!s.empty()           &&
			s.front() == T()     &&
			s.back()  == T()     &&
			s.data()  != nullptr &&
			*s.data() == T()))
		{
			return false;
		}
	}

	return 
		s.size()     == n &&
		s.capacity() == N &&
		s.max_size() == N;
}

GTEST_TEST(StaticVectorTest, CtorCountTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count<int, 10>(10)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count<int, 10>(0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count<value_dc, 11>(9)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count<value_dc, 11>(0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count<value_nc, 12>(8)));
//	                      EXPECT_TRUE((test_ctor_count<value_nd, 13>(7)));
//	                      EXPECT_TRUE((test_ctor_count<value_ndc, 13>(7)));
	                      EXPECT_TRUE((test_ctor_count<counting_value, 13>(7)));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_ctor_count<shptr_value, 14>(6)));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_ctor_count_value(bksge::size_t n, T const& v)
{
	static_assert((bksge::static_vector<T, N>::static_capacity) == N, "");

	bksge::static_vector<T, N> s(n, v);

	for (bksge::size_t i = 0; i < n; ++i)
	{
		if (!(s[i]  == v &&
			s.at(i) == v))
		{
			return false;
		}
	}

	if (n >= 1)
	{
		if (!(
			!s.empty()           &&
			s.front() == v       &&
			s.back()  == v       &&
			s.data()  != nullptr &&
			*s.data() == v))
		{
			return false;
		}
	}

	return 
		s.size()     == n &&
		s.capacity() == N &&
		s.max_size() == N;
}

GTEST_TEST(StaticVectorTest, CtorCountValueTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count_value<int, 10>(5, 10)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count_value<int, 10>(0, 10)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count_value<value_dc, 10>(6, value_dc(20))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count_value<value_dc, 10>(0, value_dc(20))));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_count_value<value_nc, 10>(0, value_nc(20))));
	                      EXPECT_TRUE((test_ctor_count_value<value_nd, 10>(7, value_nd(30))));
//	                      EXPECT_TRUE((test_ctor_count_value<value_ndc, 10>(7, value_ndc(30))));
	                      EXPECT_TRUE((test_ctor_count_value<counting_value, 10>(8, counting_value(40))));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_ctor_count_value<shptr_value, 10>(9, shptr_value(50))));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_ctor_iterator()
{
	static_assert((bksge::static_vector<T, N>::static_capacity) == N, "");

	T a[] = { T(3), T(1), T(4) };
	bksge::size_t n = bksge::size(a);

	bksge::static_vector<T, N> s(bksge::begin(a), bksge::end(a));

	for (bksge::size_t i = 0; i < n; ++i)
	{
		if (!(s[i]  == a[i] &&
			s.at(i) == a[i]))
		{
			return false;
		}
	}

	if (n >= 1)
	{
		if (!(
			!s.empty()           &&
			s.front() == a[0]    &&
			s.back()  == a[n-1]  &&
			s.data()  != nullptr &&
			*s.data() == a[0]))
		{
			return false;
		}
	}

	return 
		s.size()     == n &&
		s.capacity() == N &&
		s.max_size() == N;
}

GTEST_TEST(StaticVectorTest, CtorIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_iterator<int, 20>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_iterator<value_dc, 21>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_iterator<value_nc, 21>()));
	                      EXPECT_TRUE((test_ctor_iterator<value_nd, 22>()));
//	                      EXPECT_TRUE((test_ctor_iterator<value_ndc, 22>()));
	                      EXPECT_TRUE((test_ctor_iterator<counting_value, 23>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_ctor_iterator<shptr_value, 24>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_ctor_initializer_list(std::initializer_list<T> il)
{
	bksge::size_t n = il.size();

	bksge::static_vector<T, N> s(il);

	{
		auto it = il.begin();
		for (bksge::size_t i = 0; i < n; ++i)
		{
			if (!(s[i]  == *it &&
				s.at(i) == *it))
			{
				return false;
			}
			++it;
		}
	}

	if (n >= 1)
	{
		if (!(
			!s.empty()           &&
			s.front() == s[0]    &&
			s.back()  == s[n-1]  &&
			s.data()  != nullptr &&
			*s.data() == s[0]))
		{
			return false;
		}
	}

	return 
		s.size()     == n &&
		s.capacity() == N &&
		s.max_size() == N;
}

GTEST_TEST(StaticVectorTest, CtorInitializerListTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_initializer_list<int, 10>({ 1, 2, 3 })));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_initializer_list<int, 10>({ })));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_initializer_list<value_dc, 10>({ value_dc(0), value_dc(1) })));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_initializer_list<value_dc, 10>({ })));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_initializer_list<value_nc, 10>({ })));
	EXPECT_TRUE((test_ctor_initializer_list<value_nd, 10>({ value_nd(0), value_nd(1), value_nd(2), value_nd(3), value_nd(4) })));
	EXPECT_TRUE((test_ctor_initializer_list<value_nd, 10>({ })));
//	EXPECT_TRUE((test_ctor_initializer_list<value_ndc, 10>({ })));
	EXPECT_TRUE((test_ctor_initializer_list<counting_value, 10>({ counting_value(10), counting_value(20), counting_value(30), counting_value(40)})));
	EXPECT_EQ(0u, counting_value::count());
	EXPECT_TRUE((test_ctor_initializer_list<shptr_value, 10>({shptr_value(1), shptr_value(11), shptr_value(111)})));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_ctor_copy(bksge::size_t n, T const& v)
{
	bksge::static_vector<T, N> t(n, v);
	bksge::static_vector<T, N> s(t);

	for (bksge::size_t i = 0; i < n; ++i)
	{
		if (!(s[i]  == v &&
			s.at(i) == v))
		{
			return false;
		}
	}

	if (n >= 1)
	{
		if (!(
			!s.empty()           &&
			s.front() == s[0]    &&
			s.back()  == s[n-1]  &&
			s.data()  != nullptr &&
			*s.data() == s[0]))
		{
			return false;
		}
	}

	return 
		s.size()     == n &&
		s.capacity() == N &&
		s.max_size() == N;
}

GTEST_TEST(StaticVectorTest, CtorCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_copy<int, 10>(5, 42)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_copy<int, 10>(0, 42)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_copy<value_dc, 10>(4, value_dc(8))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_copy<value_dc, 10>(0, value_dc(8))));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_copy<value_nc, 10>(4, value_nc(8))));
	                      EXPECT_TRUE((test_ctor_copy<value_nd, 10>(3, value_nd(11))));
	                      EXPECT_TRUE((test_ctor_copy<value_nd, 10>(0, value_nd(11))));
//	                      EXPECT_TRUE((test_ctor_copy<value_ndc, 10>(3, value_ndc(11))));
	                      EXPECT_TRUE((test_ctor_copy<counting_value, 10>(2, counting_value(23))));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_ctor_copy<shptr_value, 10>(1, shptr_value(7))));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_ctor_move(bksge::size_t n)
{
	bksge::static_vector<T, N> t;
	for (bksge::size_t i = 0; i < n; ++i)
	{
		t.emplace_back((int)i);
	}

	bksge::static_vector<T, N> s(bksge::move(t));

	if (!t.empty())
	{
		return false;
	}

	for (bksge::size_t i = 0; i < n; ++i)
	{
		if (!(s[i]  == T(i) &&
			s.at(i) == T(i)))
		{
			return false;
		}
	}

	if (n >= 1)
	{
		if (!(
			!s.empty()           &&
			s.front() == s[0]    &&
			s.back()  == s[n-1]  &&
			s.data()  != nullptr &&
			*s.data() == s[0]))
		{
			return false;
		}
	}

	return 
		s.size()     == n &&
		s.capacity() == N &&
		s.max_size() == N;
}

GTEST_TEST(StaticVectorTest, CtorMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_move<int, 10>(5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_move<int, 10>(0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_move<value_dc, 10>(5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_move<value_dc, 10>(0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_move<value_nc, 10>(5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_ctor_move<value_nc, 10>(0)));
	                      EXPECT_TRUE((test_ctor_move<value_nd, 10>(5)));
	                      EXPECT_TRUE((test_ctor_move<value_nd, 10>(0)));
	                      EXPECT_TRUE((test_ctor_move<value_ndc, 10>(5)));
	                      EXPECT_TRUE((test_ctor_move<value_ndc, 10>(0)));
	                      EXPECT_TRUE((test_ctor_move<counting_value, 10>(5)));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_ctor_move<shptr_value, 10>(5)));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_resize_count(bksge::size_t n)
{
	bksge::static_vector<T, N> s;

	for (;;)
	{
		s.resize(n);

		if (!(
			s.size() == n &&
			s.capacity() == N &&
			s.max_size() == N))
		{
			return false;
		}

		for (bksge::size_t i = 0; i < n; ++i)
		{
			if (!(s[i]  == T() &&
				s.at(i) == T()))
			{
				return false;
			}
		}

		if (n == 0)
		{
			break;
		}
		--n;
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_resize_count_value(bksge::size_t n, T const& v)
{
	bksge::static_vector<T, N> s;

	for (;;)
	{
		s.resize(n, v);

		if (!(
			s.size() == n &&
			s.capacity() == N &&
			s.max_size() == N))
		{
			return false;
		}

		for (bksge::size_t i = 0; i < n; ++i)
		{
			if (!(s[i]  == v &&
				s.at(i) == v))
			{
				return false;
			}
		}

		if (n == 0)
		{
			break;
		}
		--n;
	}
	return true;
}

GTEST_TEST(StaticVectorTest, ResizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_resize_count<int, 10>(5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_resize_count<value_dc, 10>(6)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_resize_count<value_nc, 10>(6)));
//	                      EXPECT_TRUE((test_resize_count<value_nd, 10>(7)));
//	                      EXPECT_TRUE((test_resize_count<value_ndc, 10>(7)));
	                      EXPECT_TRUE((test_resize_count<counting_value, 10>(7)));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_resize_count<shptr_value, 10>(8)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_resize_count_value<int, 10>(10, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_resize_count_value<value_dc, 10>(9, value_dc(11))));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_resize_count_value<value_nc, 10>(9, value_nc(11))));
	                      EXPECT_TRUE((test_resize_count_value<value_nd, 10>(9, value_nd(11))));
//	                      EXPECT_TRUE((test_resize_count_value<value_ndc, 10>(9, value_ndc(11))));
	                      EXPECT_TRUE((test_resize_count_value<counting_value, 10>(8, counting_value(111))));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_resize_count_value<shptr_value, 10>(7, shptr_value(1111))));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_push_back_copy()
{
	bksge::static_vector<T, N> s;

	if (!(
		s.empty()         &&
		s.capacity() == N &&
		s.max_size() == N))
	{
		return false;
	}

	for (bksge::size_t i = 0; i < N; ++i)
	{
		T const t(i);
		s.push_back(t);

		if (!(
			s.size()  == i + 1 &&
			s.at(i)   == T(i)  &&
			s[i]      == T(i)  &&
			s.back()  == T(i)  &&
			s.front() == T(0)))
		{
			return false;
		}
	}

	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_push_back_move()
{
	bksge::static_vector<T, N> s;

	if (!(
		s.empty()         &&
		s.capacity() == N &&
		s.max_size() == N))
	{
		return false;
	}

	for (bksge::size_t i = 0; i < N; ++i)
	{
		T t(i);
		s.push_back(bksge::move(t));

		if (!(
			s.size()  == i + 1 &&
			s.at(i)   == T(i)  &&
			s[i]      == T(i)  &&
			s.back()  == T(i)  &&
			s.front() == T(0)))
		{
			return false;
		}
	}

	return true;
}

GTEST_TEST(StaticVectorTest, PushBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_push_back_copy<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_push_back_copy<value_dc, 10>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_push_back_copy<value_nc, 10>()));
	                      EXPECT_TRUE((test_push_back_copy<value_nd, 10>()));
//	                      EXPECT_TRUE((test_push_back_copy<value_ndc, 10>()));
	                      EXPECT_TRUE((test_push_back_copy<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_push_back_copy<shptr_value, 10>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_push_back_move<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_push_back_move<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_push_back_move<value_nc, 10>()));
	                      EXPECT_TRUE((test_push_back_move<value_nd, 10>()));
	                      EXPECT_TRUE((test_push_back_move<value_ndc, 10>()));
	                      EXPECT_TRUE((test_push_back_move<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_push_back_move<shptr_value, 10>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_pop_back()
{
	bksge::static_vector<T, N> s;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.push_back(T(i));
	}

	if (!(
		!s.empty()        &&
		s.size()     == N &&
		s.capacity() == N &&
		s.max_size() == N))
	{
		return false;
	}

	for (bksge::size_t i = 0; i < N-1; ++i)
	{
		s.pop_back();

		if (!(
			s.size()  == N - i - 1   &&
			s.back()  == T((int)s.size() - 1)  &&
			s.front() == T(0)))
		{
			return false;
		}

		for (bksge::size_t j = 0; j < s.size(); ++j)
		{
			if (!(
				s.at(j) == T(j)  &&
				s[j]    == T(j)))
			{
				return false;
			}
		}
	}

	s.pop_back();

	if (!(
		s.empty()         &&
		s.size()     == 0 &&
		s.capacity() == N &&
		s.max_size() == N))
	{
		return false;
	}
	return true;
}

GTEST_TEST(StaticVectorTest, PopBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_pop_back<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_pop_back<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_pop_back<value_nc, 10>()));
	                      EXPECT_TRUE((test_pop_back<value_nd, 10>()));
	                      EXPECT_TRUE((test_pop_back<value_ndc, 10>()));
	                      EXPECT_TRUE((test_pop_back<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_pop_back<shptr_value, 10>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_op_assign_copy()
{
	bksge::static_vector<T, N> s1;
	bksge::static_vector<T, N> s2;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s1.push_back(T(i));
	}

	if ( s1.empty() ||
	    !s2.empty())
	{
		return false;
	}

	s2 = s1;

	if (s1.empty() ||
		s2.empty())
	{
		return false;
	}

	return bksge::equal(s1.begin(), s1.end(), s2.begin(), s2.end());
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_op_assign_move()
{
	bksge::static_vector<T, N> s1;
	bksge::static_vector<T, N> s2;
	bksge::static_vector<T, N> s3;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s1.push_back(T(i));
		s2.push_back(T(i));
	}

	if ( s1.empty() ||
	     s2.empty() ||
	    !s3.empty())
	{
		return false;
	}

	s3 = bksge::move(s2);

	if ( s1.empty() ||
	    !s2.empty() ||
	     s3.empty())
	{
		return false;
	}

	return bksge::equal(s3.begin(), s3.end(), s1.begin(), s1.end());
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_op_assign_initializer_list(std::initializer_list<T> il)
{
	bksge::static_vector<T, N> s;

	if (!s.empty())
	{
		return false;
	}

	s = il;

	if (s.empty())
	{
		return false;
	}

	return bksge::equal(s.begin(), s.end(), il.begin(), il.end());
}

GTEST_TEST(StaticVectorTest, OpAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_copy<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_copy<value_dc, 10>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_copy<value_nc, 10>()));
	                      EXPECT_TRUE((test_op_assign_copy<value_nd, 10>()));
//	                      EXPECT_TRUE((test_op_assign_copy<value_ndc, 10>()));
	                      EXPECT_TRUE((test_op_assign_copy<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_op_assign_copy<shptr_value, 10>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_move<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_move<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_move<value_nc, 10>()));
	                      EXPECT_TRUE((test_op_assign_move<value_nd, 10>()));
	                      EXPECT_TRUE((test_op_assign_move<value_ndc, 10>()));
	                      EXPECT_TRUE((test_op_assign_move<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_op_assign_move<shptr_value, 10>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_initializer_list<int, 10>({1, 2, 3})));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_initializer_list<value_dc, 10>({value_dc(1), value_dc(2), value_dc(3), value_dc(4)})));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_op_assign_initializer_list<value_nc, 10>({value_nc(1), value_nc(2), value_nc(3), value_nc(4)})));
	                      EXPECT_TRUE((test_op_assign_initializer_list<value_nd, 10>({value_nd(1), value_nd(2), value_nd(3), value_nd(4), value_nd(5)})));
//	                      EXPECT_TRUE((test_op_assign_initializer_list<value_ndc, 10>({value_ndc(1), value_ndc(2), value_ndc(3), value_ndc(4), value_ndc(5)})));
	                      EXPECT_TRUE((test_op_assign_initializer_list<counting_value, 10>({counting_value(1), counting_value(2), counting_value(3), counting_value(4), counting_value(5), counting_value(6)})));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_op_assign_initializer_list<shptr_value, 10>({shptr_value(1), shptr_value(2), shptr_value(3), shptr_value(4), shptr_value(5), shptr_value(6)})));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_assign_count_value(bksge::size_t n, T const& v)
{
	bksge::static_vector<T, N> s;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.push_back(T(i));
	}

	if (s.size() != N)
	{
		return false;
	}

	s.assign(n, v);

	if (s.size() != n)
	{
		return false;
	}
	for (bksge::size_t i = 0; i < n; ++i)
	{
		if (!(s[i] == v))
		{
			return false;
		}
	}

	return true;
}

template <typename T, bksge::size_t N, typename Iterator>
BKSGE_CXX14_CONSTEXPR bool test_assign_iterator(Iterator first, Iterator last)
{
	bksge::static_vector<T, N> s;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.push_back(T(i));
	}

	if (s.size() != N)
	{
		return false;
	}

	s.assign(first, last);

	return bksge::equal(s.begin(), s.end(), first, last);
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_assign_initializer_list(std::initializer_list<T> il)
{
	bksge::static_vector<T, N> s;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.push_back(T(i));
	}

	if (s.size() != N)
	{
		return false;
	}

	s.assign(il);

	return bksge::equal(s.begin(), s.end(), il.begin(), il.end());
}

GTEST_TEST(StaticVectorTest, AssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_count_value<int, 10>(5, 10)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_count_value<int, 10>(0, 10)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_count_value<value_dc, 10>(6, value_dc(20))));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_count_value<value_dc, 10>(0, value_dc(20))));
	                      EXPECT_TRUE((test_assign_count_value<value_nd, 10>(7, value_nd(30))));
	                      EXPECT_TRUE((test_assign_count_value<value_nd, 10>(0, value_nd(30))));
	                      EXPECT_TRUE((test_assign_count_value<shptr_value, 10>(9, shptr_value(50))));
	                      EXPECT_TRUE((test_assign_count_value<counting_value, 10>(8, counting_value(40))));
	EXPECT_EQ(0u, counting_value::count());

	{
		BKSGE_CXX14_CONSTEXPR int a[] = {1, 2, 3, 4, 5};
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_iterator<int, 10>(bksge::begin(a), bksge::end(a))));
	}
	{
		BKSGE_CXX14_CONSTEXPR value_dc a[] = {value_dc(10), value_dc(20)};
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_iterator<value_dc, 10>(bksge::begin(a), bksge::end(a))));
	}
	{
		bksge::vector<value_nd> a = {value_nd(10), value_nd(20), value_nd(30), value_nd(40)};
		EXPECT_TRUE((test_assign_iterator<value_nd, 10>(bksge::begin(a), bksge::end(a))));
	}
	{
		bksge::vector<counting_value> a = {counting_value(10), counting_value(20), counting_value(30)};
		EXPECT_TRUE((test_assign_iterator<counting_value, 10>(bksge::begin(a), bksge::end(a))));
	}
	EXPECT_EQ(0u, counting_value::count());
	{
		bksge::vector<shptr_value> a = {shptr_value(10), shptr_value(20), shptr_value(30), shptr_value(40), shptr_value(50)};
		EXPECT_TRUE((test_assign_iterator<shptr_value, 10>(bksge::begin(a), bksge::end(a))));
	}

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_initializer_list<int, 10>({1, 2, 3, 4, 5, 6, 7})));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_assign_initializer_list<value_dc, 10>({value_dc(10), value_dc(20), value_dc(30)})));
	EXPECT_TRUE((test_assign_initializer_list<value_nd, 10>({value_nd(10), value_nd(20), value_nd(30), value_nd(40)})));
	EXPECT_TRUE((test_assign_initializer_list<counting_value, 10>({counting_value(10), counting_value(20), counting_value(30)})));
	EXPECT_EQ(0u, counting_value::count());
	EXPECT_TRUE((test_assign_initializer_list<shptr_value, 10>({shptr_value(10), shptr_value(20), shptr_value(30), shptr_value(40), shptr_value(50)})));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_iterators()
{
	T a[] = { T(1), T(2), T(3), T(4), T(5) };

	bksge::static_vector<T, N> s(bksge::begin(a), bksge::end(a));

	return
		bksge::equal(s.begin(),   s.end(),   bksge::begin(a),  bksge::end(a)) &&
		bksge::equal(s.cbegin(),  s.cend(),  bksge::begin(a),  bksge::end(a)) &&
		bksge::equal(s.rbegin(),  s.rend(),  bksge::rbegin(a), bksge::rend(a)) &&
		bksge::equal(s.crbegin(), s.crend(), bksge::rbegin(a), bksge::rend(a));
}

GTEST_TEST(StaticVectorTest, IteratorsTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_iterators<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_iterators<value_dc, 10>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_iterators<value_nc, 10>()));
	                      EXPECT_TRUE((test_iterators<value_nd, 10>()));
//	                      EXPECT_TRUE((test_iterators<value_ndc, 10>()));
	                      EXPECT_TRUE((test_iterators<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_iterators<shptr_value, 10>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_erase_pos()
{
	typedef typename bksge::static_vector<T, N>::iterator It;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		bksge::static_vector<T, N> s1;
		for (bksge::size_t j = 0; j < N; ++j)
		{
			s1.push_back(T(j));
		}

		It it = s1.erase(s1.begin() + i);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == N - 1)) { return false; }
		for (bksge::size_t j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		for (bksge::size_t j = i+1; j < N; ++j)
		{
			if (!(s1[j-1] == T(j))) { return false; }
		}
	}

	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_erase_iter()
{
	typedef typename bksge::static_vector<T, N>::iterator It;

	bksge::size_t n = N/3;
	for (bksge::size_t i = 0; i <= N; ++i)
	{
		bksge::static_vector<T, N> s1;
		for (bksge::size_t j = 0; j < N; ++j)
		{
			s1.push_back(T(j));
		}

		bksge::size_t removed = i + n < N ? n : N - i;
		It it = s1.erase(s1.begin() + i, s1.begin() + i + removed);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == N - removed)) { return false; }
		for (bksge::size_t j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		for (bksge::size_t j = i+n; j < N; ++j)
		{
			if (!(s1[j-n] == T(j))) { return false; }
		}
	}

	return true;
}

GTEST_TEST(StaticVectorTest, EraseTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_erase_pos<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_erase_pos<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_erase_pos<value_nc, 10>()));
	                      EXPECT_TRUE((test_erase_pos<value_nd, 10>()));
	                      EXPECT_TRUE((test_erase_pos<value_ndc, 10>()));
	                      EXPECT_TRUE((test_erase_pos<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_erase_pos<shptr_value, 10>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_erase_iter<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_erase_iter<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_erase_iter<value_nc, 10>()));
	                      EXPECT_TRUE((test_erase_iter<value_nd, 10>()));
	                      EXPECT_TRUE((test_erase_iter<value_ndc, 10>()));
	                      EXPECT_TRUE((test_erase_iter<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_erase_iter<shptr_value, 10>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_reserve()
{
	{
		bksge::static_vector<T, N> s;
		s.reserve(1);
		if (!(0 == s.size())) { return false; }
		if (!(N == s.capacity())) { return false; }
		s.reserve(N);
		if (!(0 == s.size())) { return false; }
		if (!(N == s.capacity())) { return false; }
	}
	return true;
}

template <typename T, bksge::size_t N>
void test_reserve_throw()
{
	bksge::static_vector<T, N> s;
	EXPECT_THROW(s.reserve(N+1), std::bad_alloc);
}

GTEST_TEST(StaticVectorTest, ReserveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_reserve<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_reserve<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_reserve<value_nc, 12>()));
	                      EXPECT_TRUE((test_reserve<value_nd, 13>()));
	                      EXPECT_TRUE((test_reserve<value_ndc, 14>()));
	                      EXPECT_TRUE((test_reserve<counting_value, 15>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_reserve<shptr_value, 16>()));

	test_reserve_throw<int, 17>();
	test_reserve_throw<value_dc, 18>();
	test_reserve_throw<value_nc, 19>();
	test_reserve_throw<value_nd, 20>();
	test_reserve_throw<value_ndc, 21>();
	test_reserve_throw<counting_value, 22>();
	EXPECT_EQ(0u, counting_value::count());
	test_reserve_throw<shptr_value, 23>();
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_shrink_to_fit()
{
	bksge::static_vector<T, N> s;
	if (!(0 == s.size())) { return false; }
	if (!(N == s.capacity())) { return false; }

	s.shrink_to_fit();
	if (!(0 == s.size())) { return false; }
	if (!(N == s.capacity())) { return false; }

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.push_back(T(i));
	}

	s.shrink_to_fit();
	if (!(N == s.size())) { return false; }
	if (!(N == s.capacity())) { return false; }

	return true;
}

GTEST_TEST(StaticVectorTest, ShrinkToFitTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_shrink_to_fit<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_shrink_to_fit<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_shrink_to_fit<value_nc, 12>()));
	                      EXPECT_TRUE((test_shrink_to_fit<value_nd, 13>()));
	                      EXPECT_TRUE((test_shrink_to_fit<value_ndc, 14>()));
	                      EXPECT_TRUE((test_shrink_to_fit<counting_value, 15>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_shrink_to_fit<shptr_value, 16>()));
}	                      

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_clear()
{
	bksge::static_vector<T, N> s;
	if (!(s.empty())) { return false; }
	if (!(0 == s.size())) { return false; }
	if (!(N == s.capacity())) { return false; }

	s.clear();

	if (!(s.empty())) { return false; }
	if (!(0 == s.size())) { return false; }
	if (!(N == s.capacity())) { return false; }

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.push_back(T(i));
	}

	if ( (s.empty())) { return false; }
	if (!(N == s.size())) { return false; }
	if (!(N == s.capacity())) { return false; }

	s.clear();

	if (!(s.empty())) { return false; }
	if (!(0 == s.size())) { return false; }
	if (!(N == s.capacity())) { return false; }

	return true;
}

GTEST_TEST(StaticVectorTest, ClearTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_clear<int, 20>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_clear<value_dc, 21>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_clear<value_nc, 22>()));
	                      EXPECT_TRUE((test_clear<value_nd, 23>()));
	                      EXPECT_TRUE((test_clear<value_ndc, 24>()));
	                      EXPECT_TRUE((test_clear<counting_value, 25>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_clear<shptr_value, 26>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_insert_pos_value_copy(T const& val)
{
	bksge::size_t h = N/2;

	bksge::static_vector<T, N> s;

	typedef typename bksge::static_vector<T, N>::iterator It;

	for (bksge::size_t i = 0; i < h; ++i)
	{
		s.push_back(T(i));
	}

	for (bksge::size_t i = 0; i <= h; ++i)
	{
		bksge::static_vector<T, N> s1(s);
		It it = s1.insert(s1.begin() + i, val);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == h+1)) { return false; }
		for (bksge::size_t j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		if (!(s1[i] == val)) { return false; }
		for (bksge::size_t j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+1] == T(j+i))) { return false; }
		}
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_insert_pos_value_move()
{
	bksge::size_t h = N/2;

	typedef typename bksge::static_vector<T, N>::iterator It;

	for (bksge::size_t i = 0; i <= h; ++i)
	{
		bksge::static_vector<T, N> s1;
		for (bksge::size_t j = 0; j < h; ++j)
		{
			s1.emplace_back(T(j));
		}

		It it = s1.insert(s1.begin() + i, T(42));
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == h+1)) { return false; }
		for (bksge::size_t j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		if (!(s1[i] == T(42))) { return false; }
		for (bksge::size_t j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+1] == T(j+i))) { return false; }
		}
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_insert_pos_count_value_copy(T const& val)
{
	bksge::size_t h = N/2;

	bksge::static_vector<T, N> s;

	typedef typename bksge::static_vector<T, N>::iterator It;

	for (bksge::size_t i = 0; i < h; ++i)
	{
		s.push_back(T(i));
	}

	bksge::size_t n = bksge::size_t(h/1.5f);
	for (bksge::size_t i = 0; i <= h; ++i)
	{
		bksge::static_vector<T, N> s1(s);
		It it = s1.insert(s1.begin() + i, n, val);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == h+n)) { return false; }
		for (bksge::size_t j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		for (bksge::size_t j = 0; j < n; ++j)
		{
			if (!(s1[j+i] == val)) { return false; }
		}
		for (bksge::size_t j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+n] == T(j+i))) { return false; }
		}
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_insert_iter()
{
	bksge::size_t h = N/2;
	bksge::size_t n = bksge::size_t(h/1.5f);

	bksge::static_vector<T, N> s, ss;

	typedef typename bksge::static_vector<T, N>::iterator It;

	for (bksge::size_t i = 0; i < h; ++i)
	{
		s.push_back(T(i));
		ss.push_back(T(100 + i));
	}

	for (bksge::size_t i = 0; i <= h; ++i)
	{
		bksge::static_vector<T, N> s1(s);

		It it1 = s1.insert(s1.begin() + i, ss.begin(), ss.begin() + n);

		if (!(s1.begin() + i == it1)) { return false; }
		if (!(s1.size() == h+n)) { return false; }
		for (bksge::size_t j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		for (bksge::size_t j = 0; j < n; ++j)
		{
			if (!(s1[j+i] == T(100 + j))) { return false; }
		}
		for (bksge::size_t j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+n] == T(j+i))) { return false; }
		}
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_insert_initializer_list()
{
	bksge::size_t h = N/2;

	bksge::static_vector<T, N> s;

	typedef typename bksge::static_vector<T, N>::iterator It;

	for (bksge::size_t i = 0; i < h; ++i)
	{
		s.push_back(T(i));
	}

	for (bksge::size_t i = 0; i <= h; ++i)
	{
		std::initializer_list<T> il = {T(3),T(1),T(4)};
		bksge::size_t n = il.size();
		bksge::static_vector<T, N> s1(s);
		It it = s1.insert(s1.begin() + i, il);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == h+n)) { return false; }
		for (bksge::size_t j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		for (bksge::size_t j = 0; j < n; ++j)
		{
			if (!(s1[j+i] == *(il.begin() + j))) { return false; }
		}
		for (bksge::size_t j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+n] == T(j+i))) { return false; }
		}
	}
	return true;
}

GTEST_TEST(StaticVectorTest, InsertTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_pos_value_copy<int, 10>(50)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_pos_value_copy<value_dc, 11>(value_dc(51))));
	                      EXPECT_TRUE((test_insert_pos_value_copy<value_nd, 12>(value_nd(52))));
	                      EXPECT_TRUE((test_insert_pos_value_copy<counting_value, 13>(counting_value(53))));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_insert_pos_value_copy<shptr_value, 14>(shptr_value(54))));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_pos_value_move<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_pos_value_move<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_pos_value_move<value_nc, 12>()));
	                      EXPECT_TRUE((test_insert_pos_value_move<value_nd, 13>()));
	                      EXPECT_TRUE((test_insert_pos_value_move<value_ndc, 14>()));
	                      EXPECT_TRUE((test_insert_pos_value_move<counting_value, 15>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_insert_pos_value_move<shptr_value, 16>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_pos_count_value_copy<int, 10>(50)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_pos_count_value_copy<value_dc, 11>(value_dc(51))));
	                      EXPECT_TRUE((test_insert_pos_count_value_copy<value_nd, 12>(value_nd(52))));
	                      EXPECT_TRUE((test_insert_pos_count_value_copy<counting_value, 13>(counting_value(53))));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_insert_pos_count_value_copy<shptr_value, 14>(shptr_value(54))));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_iter<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_iter<value_dc, 11>()));
	                      EXPECT_TRUE((test_insert_iter<value_nd, 12>()));
	                      EXPECT_TRUE((test_insert_iter<counting_value, 13>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_insert_iter<shptr_value, 14>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_initializer_list<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_insert_initializer_list<value_dc, 11>()));
	                      EXPECT_TRUE((test_insert_initializer_list<value_nd, 12>()));
	                      EXPECT_TRUE((test_insert_initializer_list<counting_value, 13>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_insert_initializer_list<shptr_value, 14>()));
}

template <typename T>
void test_capacity_0_nd()
{
	bksge::static_vector<T, 10> v(5u, T(0));

	bksge::static_vector<T, 0 > s;
	EXPECT_EQ(s.size(), 0u);
	EXPECT_EQ(s.capacity(), 0u);
	EXPECT_THROW(s.at(0), std::out_of_range);
	EXPECT_THROW(s.resize(5u, T(0)), std::bad_alloc);
	EXPECT_THROW(s.push_back(T(0)), std::bad_alloc);
	EXPECT_THROW(s.emplace_back(T(0)), std::bad_alloc);
	EXPECT_THROW(s.insert(s.end(), T(0)), std::bad_alloc);
	EXPECT_THROW(s.insert(s.end(), 5u, T(0)), std::bad_alloc);
	EXPECT_THROW(s.insert(s.end(), v.begin(), v.end()), std::bad_alloc);
	EXPECT_THROW(s.emplace(s.end(), T(0)), std::bad_alloc);
	EXPECT_THROW(s.assign(v.begin(), v.end()), std::bad_alloc);
	EXPECT_THROW(s.assign(5u, T(0)), std::bad_alloc);
	typedef bksge::static_vector<T, 0> static_vector_0_t;
	EXPECT_THROW(static_vector_0_t s2(v.begin(), v.end()), std::bad_alloc);
	EXPECT_THROW(static_vector_0_t s1(5u, T(0)), std::bad_alloc);
}

GTEST_TEST(StaticVectorTest, Capacity0Test)
{
	test_capacity_0_nd<int>();
	test_capacity_0_nd<value_dc>();
//	test_capacity_0_nd<value_nc>();
	test_capacity_0_nd<value_nd>();
//	test_capacity_0_nd<value_ndc>();
	test_capacity_0_nd<counting_value>();
	EXPECT_EQ(0u, counting_value::count());
	test_capacity_0_nd<shptr_value>();
}

template <typename T, bksge::size_t N>
void test_exceptions_nd()
{
	bksge::static_vector<T, N> v(N, T(0));
	bksge::static_vector<T, N/2> s(N/2, T(0));

	EXPECT_THROW(s.resize(N, T(0)), std::bad_alloc);
	EXPECT_THROW(s.push_back(T(0)), std::bad_alloc);
	EXPECT_THROW(s.emplace_back(T(0)), std::bad_alloc);
	EXPECT_THROW(s.insert(s.end(), T(0)), std::bad_alloc);
	EXPECT_THROW(s.insert(s.end(), 1, T(0)), std::bad_alloc);
	EXPECT_THROW(s.insert(s.end(), v.begin(), v.end()), std::bad_alloc);
	EXPECT_THROW(s.emplace(s.end(), T(0)), std::bad_alloc);
	EXPECT_THROW(s.assign(v.begin(), v.end()), std::bad_alloc);
	EXPECT_THROW(s.assign(N, T(0)), std::bad_alloc);
	typedef bksge::static_vector<T, N/2> static_vector_n_half_t;
	EXPECT_THROW(static_vector_n_half_t s2(v.begin(), v.end()), std::bad_alloc);
	EXPECT_THROW(static_vector_n_half_t s1(N/2+1, T(0)), std::bad_alloc);
}

GTEST_TEST(StaticVectorTest, ExceptionsTest)
{
	test_exceptions_nd<int, 10>();
	test_exceptions_nd<value_dc, 10>();
//	test_exceptions_nd<value_nc, 10>();
	test_exceptions_nd<value_nd, 10>();
//	test_exceptions_nd<value_ndc, 10>();
	test_exceptions_nd<counting_value, 10>();
	EXPECT_EQ(0u, counting_value::count());
	test_exceptions_nd<shptr_value, 10>();
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_swap()
{
	{
		bksge::static_vector<T, N> s1, s2;

		for (bksge::size_t i = 0; i < N; ++i)
		{
			s1.emplace_back(T(i));
		}
		for (bksge::size_t i = 0; i < N/2; ++i)
		{
			s2.emplace_back(T(100 + i));
		}

		s1.swap(s2);

		if (!(s1.size() == N/2)) { return false; }
		if (!(s2.size() == N)) { return false; }

		for (bksge::size_t i = 0; i < N/2; ++i)
		{
			if (!(s1[i] == T(100 + i))) { return false; }
		}
		for (bksge::size_t i = 0; i < N; ++i)
		{
			if (!(s2[i] == T(i))) { return false; }
		}

		swap(s1, s2);

		if (!(s1.size() == N)) { return false; }
		if (!(s2.size() == N/2)) { return false; }

		for (bksge::size_t i = 0; i < N; ++i)
		{
			if (!(s1[i] == T(i))) { return false; }
		}
		for (bksge::size_t i = 0; i < N/2; ++i)
		{
			if (!(s2[i] == T(100 + i))) { return false; }
		}
	}
	return true;
}

GTEST_TEST(StaticVectorTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_swap<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_swap<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_swap<value_nc, 10>()));
	                      EXPECT_TRUE((test_swap<value_nd, 10>()));
	                      EXPECT_TRUE((test_swap<value_ndc, 10>()));
	                      EXPECT_TRUE((test_swap<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_swap<shptr_value, 10>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_emplace_back_0()
{
	bksge::static_vector<T, N> s;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.emplace_back();
	}
	if (!(s.size() == N)) { return false; }
	for (bksge::size_t i = 0; i < N; ++i)
	{
		if (!(s[i] == T())) { return false; }
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_emplace_back_1()
{
	bksge::static_vector<T, N> s;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.emplace_back((int)i);
	}
	if (!(s.size() == N)) { return false; }
	for (bksge::size_t i = 0; i < N; ++i)
	{
		if (!(s[i] == T(i))) { return false; }
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_emplace_back_2()
{
	bksge::static_vector<T, N> s;

	for (bksge::size_t i = 0; i < N; ++i)
	{
		s.emplace_back((int)i, (int)i+100);
	}
	if (!(s.size() == N)) { return false; }
	for (bksge::size_t i = 0; i < N; ++i)
	{
		if (!(s[i] == T((int)i, (int)i+100))) { return false; }
	}
	return true;
}

GTEST_TEST(StaticVectorTest, EmplaceBackTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_0<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_0<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_0<value_nc, 10>()));
//	                      EXPECT_TRUE((test_emplace_back_0<value_nd, 10>()));
//	                      EXPECT_TRUE((test_emplace_back_0<value_ndc, 10>()));
	                      EXPECT_TRUE((test_emplace_back_0<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_emplace_back_0<shptr_value, 10>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_1<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_1<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_1<value_nc, 10>()));
	                      EXPECT_TRUE((test_emplace_back_1<value_nd, 10>()));
	                      EXPECT_TRUE((test_emplace_back_1<value_ndc, 10>()));
	                      EXPECT_TRUE((test_emplace_back_1<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_emplace_back_1<shptr_value, 10>()));

//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_2<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_2<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_back_2<value_nc, 10>()));
	                      EXPECT_TRUE((test_emplace_back_2<value_nd, 10>()));
	                      EXPECT_TRUE((test_emplace_back_2<value_ndc, 10>()));
	                      EXPECT_TRUE((test_emplace_back_2<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
//	                      EXPECT_TRUE((test_emplace_back_2<shptr_value, 10>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_emplace_0()
{
	typedef typename bksge::static_vector<T, N>::iterator It;

	int h = N / 2;

	for (int i = 0; i <= h; ++i)
	{
		bksge::static_vector<T, N> s1;
		for (int j = 0; j < h; ++j)
		{
			s1.emplace_back(j);
		}

		It it = s1.emplace(s1.begin() + i);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == bksge::size_t(h+1))) { return false; }
		for (int j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		if (!(s1[i] == T())) { return false; }
		for (int j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+1] == T(j+i))) { return false; }
		}
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_emplace_1()
{
	typedef typename bksge::static_vector<T, N>::iterator It;

	int h = N / 2;

	for (int i = 0; i <= h; ++i)
	{
		bksge::static_vector<T, N> s1;
		for (int j = 0; j < h; ++j)
		{
			s1.emplace_back(j);
		}

		It it = s1.emplace(s1.begin() + i, i+100);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == bksge::size_t(h+1))) { return false; }
		for (int j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j))) { return false; }
		}
		if (!(s1[i] == T(i+100))) { return false; }
		for (int j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+1] == T(j+i))) { return false; }
		}
	}
	return true;
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_emplace_2()
{
	typedef typename bksge::static_vector<T, N>::iterator It;

	int h = N / 2;

	for (int i = 0; i <= h; ++i)
	{
		bksge::static_vector<T, N> s1;
		for (int j = 0; j < h; ++j)
		{
			s1.emplace_back(j, 100 + j);
		}

		It it = s1.emplace(s1.begin() + i, i+100, i+200);
		if (!(s1.begin() + i == it)) { return false; }
		if (!(s1.size() == bksge::size_t(h+1))) { return false; }
		for (int j = 0; j < i; ++j)
		{
			if (!(s1[j] == T(j, j+100))) { return false; }
		}
		if (!(s1[i] == T(i+100, i+200))) { return false; }
		for (int j = 0; j < h-i; ++j)
		{
			if (!(s1[j+i+1] == T(j+i, j+i+100))) { return false; }
		}
	}
	return true;
}

GTEST_TEST(StaticVectorTest, EmplaceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_0<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_0<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_0<value_nc, 12>()));
//	                      EXPECT_TRUE((test_emplace_0<value_nd, 13>()));
//	                      EXPECT_TRUE((test_emplace_0<value_ndc, 14>()));
	                      EXPECT_TRUE((test_emplace_0<counting_value, 15>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_emplace_0<shptr_value, 16>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_1<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_1<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_1<value_nc, 12>()));
	                      EXPECT_TRUE((test_emplace_1<value_nd, 13>()));
	                      EXPECT_TRUE((test_emplace_1<value_ndc, 14>()));
	                      EXPECT_TRUE((test_emplace_1<counting_value, 15>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_emplace_1<shptr_value, 16>()));

//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_2<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_2<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_emplace_2<value_nc, 12>()));
	                      EXPECT_TRUE((test_emplace_2<value_nd, 13>()));
	                      EXPECT_TRUE((test_emplace_2<value_ndc, 14>()));
	                      EXPECT_TRUE((test_emplace_2<counting_value, 15>()));
	                      EXPECT_EQ(0u, counting_value::count());
//	                      EXPECT_TRUE((test_emplace_2<shptr_value, 16>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_compare()
{
	int h = N / 2;

	bksge::static_vector<T, N> s1;
	bksge::static_vector<T, N> s2;
	bksge::static_vector<T, N> s3;
	bksge::static_vector<T, N> s4;
	bksge::static_vector<T, N> s5;
	bksge::static_vector<T, N> s6;
	for (int i = 0; i < h; ++i)
	{
		s1.emplace_back(i+1);
		s4.emplace_back(i+1);
		s5.emplace_back(i+1);
		s6.emplace_back(i+1);
	}
	for (int i = 0; i < h+1; ++i)
	{
		s2.emplace_back(i+1);
	}
	for (int i = 0; i < h-1; ++i)
	{
		s3.emplace_back(i+1);
	}
	s4[0] = T(0);
	s5[h-1] = T(100);

	if (!(s1 == s1)) { return false; }
	if ( (s1 == s2)) { return false; }
	if ( (s1 == s3)) { return false; }
	if ( (s1 == s4)) { return false; }
	if ( (s1 == s5)) { return false; }
	if (!(s1 == s6)) { return false; }

	if ( (s1 != s1)) { return false; }
	if (!(s1 != s2)) { return false; }
	if (!(s1 != s3)) { return false; }
	if (!(s1 != s4)) { return false; }
	if (!(s1 != s5)) { return false; }
	if ( (s1 != s6)) { return false; }

	if ( (s1 < s1)) { return false; }
	if (!(s1 < s2)) { return false; }
	if ( (s1 < s3)) { return false; }
	if ( (s1 < s4)) { return false; }
	if (!(s1 < s5)) { return false; }
	if ( (s1 < s6)) { return false; }

	if (!(s1 <= s1)) { return false; }
	if (!(s1 <= s2)) { return false; }
	if ( (s1 <= s3)) { return false; }
	if ( (s1 <= s4)) { return false; }
	if (!(s1 <= s5)) { return false; }
	if (!(s1 <= s6)) { return false; }

	if ( (s1 > s1)) { return false; }
	if ( (s1 > s2)) { return false; }
	if (!(s1 > s3)) { return false; }
	if (!(s1 > s4)) { return false; }
	if ( (s1 > s5)) { return false; }
	if ( (s1 > s6)) { return false; }

	if (!(s1 >= s1)) { return false; }
	if ( (s1 >= s2)) { return false; }
	if (!(s1 >= s3)) { return false; }
	if (!(s1 >= s4)) { return false; }
	if ( (s1 >= s5)) { return false; }
	if (!(s1 >= s6)) { return false; }

	return true;
}

GTEST_TEST(StaticVectorTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_compare<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_compare<value_dc, 11>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_compare<value_nc, 12>()));
	                      EXPECT_TRUE((test_compare<value_nd, 13>()));
	                      EXPECT_TRUE((test_compare<value_ndc, 14>()));
	                      EXPECT_TRUE((test_compare<counting_value, 15>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_compare<shptr_value, 16>()));
}

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_nonmember_erase()
{
	bksge::static_vector<T, N> s;
	s.emplace_back(3);
	s.emplace_back(1);
	s.emplace_back(4);
	s.emplace_back(1);
	s.emplace_back(5);

	{
		auto r = bksge::erase(s, T(1));
		if (!(3u == s.size())) { return false; }
		if (!(2u == r)) { return false; }
		if (!(T(3) == s[0])) { return false; }
		if (!(T(4) == s[1])) { return false; }
		if (!(T(5) == s[2])) { return false; }
	}
	{
		auto r = bksge::erase(s, T(2));
		if (!(3u == s.size())) { return false; }
		if (!(0u == r)) { return false; }
		if (!(T(3) == s[0])) { return false; }
		if (!(T(4) == s[1])) { return false; }
		if (!(T(5) == s[2])) { return false; }
	}
	{
		auto r = bksge::erase(s, T(3));
		if (!(2u == s.size())) { return false; }
		if (!(1u == r)) { return false; }
		if (!(T(4) == s[0])) { return false; }
		if (!(T(5) == s[1])) { return false; }
	}
	return true;
}

GTEST_TEST(StaticVectorTest, NonMemberEraseTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_nonmember_erase<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_nonmember_erase<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_nonmember_erase<value_nc, 10>()));
	                      EXPECT_TRUE((test_nonmember_erase<value_nd, 10>()));
	                      EXPECT_TRUE((test_nonmember_erase<value_ndc, 10>()));
	                      EXPECT_TRUE((test_nonmember_erase<counting_value, 10>()));
	                      EXPECT_EQ(0u, counting_value::count());
	                      EXPECT_TRUE((test_nonmember_erase<shptr_value, 10>()));
}

struct Pred1
{
	template <typename T>
	BKSGE_CXX14_CONSTEXPR bool operator()(T const& x) const { return x == T(3); }
};

struct Pred2
{
	template <typename T>
	BKSGE_CXX14_CONSTEXPR bool operator()(T const& x) const { return x < T(3); }
};

struct Pred3
{
	template <typename T>
	BKSGE_CXX14_CONSTEXPR bool operator()(T const& x) const { return x < T(5); }
};

template <typename T, bksge::size_t N>
BKSGE_CXX14_CONSTEXPR bool test_nonmember_erase_if()
{
	bksge::static_vector<T, N> s;
	s.emplace_back(3);
	s.emplace_back(1);
	s.emplace_back(4);
	s.emplace_back(1);
	s.emplace_back(5);
	{
		auto r = bksge::erase_if(s, Pred1());
		if (!(4u == s.size())) { return false; }
		if (!(1u == r)) { return false; }
		if (!(T(1) == s[0])) { return false; }
		if (!(T(4) == s[1])) { return false; }
		if (!(T(1) == s[2])) { return false; }
		if (!(T(5) == s[3])) { return false; }
	}
	{
		auto r = bksge::erase_if(s, Pred2());
		if (!(2u == s.size())) { return false; }
		if (!(2u == r)) { return false; }
		if (!(T(4) == s[0])) { return false; }
		if (!(T(5) == s[1])) { return false; }
	}
	{
		auto r = bksge::erase_if(s, Pred3());
		if (!(1u == s.size())) { return false; }
		if (!(1u == r)) { return false; }
		if (!(T(5) == s[0])) { return false; }
	}
	return true;
}

GTEST_TEST(StaticVectorTest, NonMemberEraseIfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_nonmember_erase_if<int, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_nonmember_erase_if<value_dc, 10>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_nonmember_erase_if<value_nc, 10>()));
	EXPECT_TRUE((test_nonmember_erase_if<value_nd, 10>()));
	EXPECT_TRUE((test_nonmember_erase_if<value_ndc, 10>()));
	EXPECT_TRUE((test_nonmember_erase_if<counting_value, 10>()));
	EXPECT_EQ(0u, counting_value::count());
	EXPECT_TRUE((test_nonmember_erase_if<shptr_value, 10>()));
}

}	// namespace bksge_static_vector_test

BKSGE_WARNING_POP();
