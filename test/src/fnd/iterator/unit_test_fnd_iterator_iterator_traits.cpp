/**
 *	@file	unit_test_fnd_iterator_iterator_traits.cpp
 *
 *	@brief	iterator_traits のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <iterator>
#include <map>

namespace bksge_iterator_test
{

namespace iterator_traits_test
{

static_assert(bksge::is_same<bksge::iterator_traits<int               *>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int               *>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int               *>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int               *>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int               *>::pointer,           int*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int               *>::reference,         int&>::value, "");

static_assert(bksge::is_same<bksge::iterator_traits<int const         *>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const         *>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const         *>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const         *>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const         *>::pointer,           int const*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const         *>::reference,         int const&>::value, "");

static_assert(bksge::is_same<bksge::iterator_traits<int       volatile*>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int       volatile*>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int       volatile*>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int       volatile*>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int       volatile*>::pointer,           int volatile*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int       volatile*>::reference,         int volatile&>::value, "");

static_assert(bksge::is_same<bksge::iterator_traits<int const volatile*>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const volatile*>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const volatile*>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const volatile*>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const volatile*>::pointer,           int const volatile*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<int const volatile*>::reference,         int const volatile&>::value, "");

using it1 = std::vector<float>::iterator;
//static_assert(bksge::is_same<bksge::iterator_traits<it1>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it1>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it1>::value_type,        float>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it1>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it1>::pointer,           float*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it1>::reference,         float&>::value, "");

using it2 = std::vector<float>::const_iterator;
//static_assert(bksge::is_same<bksge::iterator_traits<it2>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it2>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it2>::value_type,        float>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it2>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it2>::pointer,           float const*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it2>::reference,         float const&>::value, "");

using it3 = std::string::iterator;
//static_assert(bksge::is_same<bksge::iterator_traits<it3>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it3>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it3>::value_type,        char>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it3>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it3>::pointer,           char*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it3>::reference,         char&>::value, "");

using it4 = std::list<int>::iterator;
//static_assert(bksge::is_same<bksge::iterator_traits<it4>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it4>::iterator_category, bksge::bidirectional_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it4>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it4>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it4>::pointer,           int*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it4>::reference,         int&>::value, "");

using it5 = std::forward_list<int>::iterator;
//static_assert(bksge::is_same<bksge::iterator_traits<it5>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it5>::iterator_category, bksge::forward_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it5>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it5>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it5>::pointer,           int*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it5>::reference,         int&>::value, "");

using it6 = std::reverse_iterator<int*>;
//static_assert(bksge::is_same<bksge::iterator_traits<it6>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it6>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it6>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it6>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it6>::pointer,           int*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it6>::reference,         int&>::value, "");

using it7 = std::map<int, float>::iterator;
//static_assert(bksge::is_same<bksge::iterator_traits<it7>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it7>::iterator_category, bksge::bidirectional_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it7>::value_type,        std::pair<int const, float>>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it7>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it7>::pointer,           std::pair<int const, float>*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<it7>::reference,         std::pair<int const, float>&>::value, "");

struct MyIterator1
{
	using iterator_category = bksge::forward_iterator_tag;
	using value_type        = char;
	using difference_type   = short;
	using pointer           = int;
	using reference         = long;
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator1>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator1>::iterator_category, bksge::forward_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator1>::value_type,        char>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator1>::difference_type,   short>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator1>::pointer,           int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator1>::reference,         long>::value, "");

struct MyIterator2
{
	using iterator_category = bksge::bidirectional_iterator_tag;
	using value_type        = float;
	using difference_type   = double;
	using reference         = long double;
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator2>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator2>::iterator_category, bksge::bidirectional_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator2>::value_type,        float>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator2>::difference_type,   double>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator2>::pointer,           void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator2>::reference,         long double>::value, "");

struct MyIterator3
{
	using value_type        = int;
	using difference_type   = long;

	int& operator*() const;
	MyIterator3& operator++();
	MyIterator3  operator++(int);
	bool operator==(MyIterator3 const&) const;
	bool operator!=(MyIterator3 const&) const;
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator3>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator3>::iterator_category, bksge::forward_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator3>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator3>::difference_type,   long>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator3>::pointer,           void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator3>::reference,         int&>::value, "");

struct MyIterator4
{
	using value_type        = float;
	using difference_type   = int;
	using pointer           = float*;
	using reference         = float&;

	float& operator*() const;
	MyIterator4& operator++();
	MyIterator4  operator++(int);
	MyIterator4& operator--();
	MyIterator4  operator--(int);
	bool operator==(MyIterator4 const&) const;
	bool operator!=(MyIterator4 const&) const;
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator4>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator4>::iterator_category, bksge::bidirectional_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator4>::value_type,        float>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator4>::difference_type,   int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator4>::pointer,           float*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator4>::reference,         float&>::value, "");

struct MyIterator5
{
	using value_type        = int;
	using difference_type   = long;

	int operator*() const;
	int* operator->() const;
	MyIterator5& operator++();
	MyIterator5  operator++(int);
	bool operator==(MyIterator5 const&) const;
	bool operator!=(MyIterator5 const&) const;
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator5>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator5>::iterator_category, bksge::input_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator5>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator5>::difference_type,   long>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator5>::pointer,           int*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator5>::reference,         int>::value, "");

struct MyIterator6
{
	using value_type        = int;

	value_type& operator*() const;
	value_type* operator->() const;
	MyIterator6& operator++();
	MyIterator6  operator++(int);
	MyIterator6& operator--();
	MyIterator6  operator--(int);
	MyIterator6& operator+=(bksge::ptrdiff_t);
	MyIterator6& operator-=(bksge::ptrdiff_t);
	MyIterator6 operator+(bksge::ptrdiff_t) const;
	MyIterator6 operator-(bksge::ptrdiff_t) const;
	bksge::ptrdiff_t operator-(MyIterator6 const&) const;
	friend MyIterator6 operator+(bksge::ptrdiff_t, MyIterator6 const&);
	value_type& operator[](bksge::ptrdiff_t);
	bool operator==(MyIterator6 const&) const;
	bool operator!=(MyIterator6 const&) const;
	bool operator< (MyIterator6 const&) const;
	bool operator> (MyIterator6 const&) const;
	bool operator<=(MyIterator6 const&) const;
	bool operator>=(MyIterator6 const&) const;
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator6>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator6>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator6>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator6>::difference_type,   bksge::ptrdiff_t>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator6>::pointer,           int*>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator6>::reference,         int&>::value, "");

struct MyIterator7
{
	using iterator_category = bksge::random_access_iterator_tag;
	using value_type        = int;
	using difference_type   = long;

	int& operator*() const;
	MyIterator7& operator++();
	MyIterator7  operator++(int);
	bool operator==(MyIterator7 const&) const;
	bool operator!=(MyIterator7 const&) const;
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator7>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator7>::iterator_category, bksge::random_access_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator7>::value_type,        int>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator7>::difference_type,   long>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator7>::pointer,           void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator7>::reference,         int&>::value, "");

struct MyIterator8
{
	using value_type        = int;
	using difference_type   = long;

	int& operator*() const;
	MyIterator8& operator++();
	MyIterator8  operator++(int);
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator8>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator8>::iterator_category, bksge::output_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator8>::value_type,        void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator8>::difference_type,   long>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator8>::pointer,           void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator8>::reference,         void>::value, "");

struct MyIterator9
{
	using value_type        = int;

	int& operator*() const;
	MyIterator9& operator++();
	MyIterator9  operator++(int);
};

//static_assert(bksge::is_same<bksge::iterator_traits<MyIterator9>::iterator_concept,  bksge::contiguous_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator9>::iterator_category, bksge::output_iterator_tag>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator9>::value_type,        void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator9>::difference_type,   void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator9>::pointer,           void>::value, "");
static_assert(bksge::is_same<bksge::iterator_traits<MyIterator9>::reference,         void>::value, "");

}	// namespace iterator_traits_test

}	// namespace bksge_iterator_test
