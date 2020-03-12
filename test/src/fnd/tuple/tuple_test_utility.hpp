/**
 *	@file	tuple_test_utility.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_TUPLE_TUPLE_TEST_UTILITY_HPP
#define UNIT_TEST_FND_TUPLE_TUPLE_TEST_UTILITY_HPP

#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/memory/allocator_arg.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <cassert>


#define ASSERT_NOEXCEPT(...) \
    static_assert(noexcept(__VA_ARGS__), "Operation must be noexcept")

#define ASSERT_NOT_NOEXCEPT(...) \
    static_assert(!noexcept(__VA_ARGS__), "Operation must NOT be noexcept")


namespace bksge_tuple_test
{

// TypeID - Represent a unique identifier for a type. TypeID allows equality
// comparisons between different types.
struct TypeID
{
	friend bool operator==(TypeID const& LHS, TypeID const& RHS)
	{
		return LHS.m_id == RHS.m_id;
	}
	friend bool operator!=(TypeID const& LHS, TypeID const& RHS)
	{
		return LHS.m_id != RHS.m_id;
	}
private:
	explicit constexpr TypeID(const int* xid) : m_id(xid) {}
	const int* const m_id;
	template <typename T> friend class TypeInfo;
};

// TypeInfo - Represent information for the specified type 'T', including a
// unique TypeID.
template <typename T>
class TypeInfo
{
public:
	typedef T value_type;
	typedef TypeID ID;
	static  ID const& GetID()
	{
		static ID id(&dummy_addr);
		return id;
	}

private:
	static const int dummy_addr;
};

template <typename L, typename R>
inline bool operator==(TypeInfo<L> const&, TypeInfo<R> const&)
{
	return bksge::is_same<L, R>::value;
}

template <typename L, typename R>
inline bool operator!=(TypeInfo<L> const& lhs, TypeInfo<R> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
const int TypeInfo<T>::dummy_addr = 42;

// makeTypeID - Return the TypeID for the specified type 'T'.
template <typename T>
inline constexpr TypeID const& makeTypeID()
{
	return TypeInfo<T>::GetID();
}

template <typename... Args>
struct ArgumentListID {};

// makeArgumentID - Create and return a unique identifier for a given set
// of arguments.
template <typename... Args>
inline constexpr TypeID const& makeArgumentID()
{
	return makeTypeID<ArgumentListID<Args...>>();
}


template <typename T>
class A1
{
	int id_;
public:
	explicit A1(int id = 0) BKSGE_NOEXCEPT : id_(id) {}

	typedef T value_type;

	int id() const { return id_; }

	static bool copy_called;
	static bool move_called;
	static bool allocate_called;
	static bksge::pair<T*, bksge::size_t> deallocate_called;

	A1(A1 const& a) BKSGE_NOEXCEPT : id_(a.id()) { copy_called = true; }
	A1(A1&& a)      BKSGE_NOEXCEPT : id_(a.id()) { move_called = true; }
	A1& operator=(A1 const& a) BKSGE_NOEXCEPT { id_ = a.id(); copy_called = true; return *this; }
	A1& operator=(A1&& a)      BKSGE_NOEXCEPT { id_ = a.id(); move_called = true; return *this; }

	template <typename U>
	A1(A1<U> const& a) BKSGE_NOEXCEPT : id_(a.id()) { copy_called = true; }
	template <typename U>
	A1(A1<U>&& a) BKSGE_NOEXCEPT : id_(a.id()) { move_called = true; }

	T* allocate(bksge::size_t n)
	{
		allocate_called = true;
		return (T*)n;
	}

	void deallocate(T* p, bksge::size_t n)
	{
		deallocate_called = bksge::pair<T*, bksge::size_t>(p, n);
	}

	bksge::size_t max_size() const { return id_; }
};

template <typename T> bool A1<T>::copy_called = false;
template <typename T> bool A1<T>::move_called = false;
template <typename T> bool A1<T>::allocate_called = false;
template <typename T> bksge::pair<T*, bksge::size_t> A1<T>::deallocate_called;

template <typename T, typename U>
inline bool operator==(A1<T> const& x, A1<U> const& y)
{
	return x.id() == y.id();
}

template <typename T, typename U>
inline bool operator!=(A1<T> const& x, A1<U> const& y)
{
	return !(x == y);
}

template <typename T>
class A2
{
	int id_;
public:
	explicit A2(int id = 0) BKSGE_NOEXCEPT : id_(id) {}

	typedef T value_type;

	typedef unsigned size_type;
	typedef int difference_type;

	typedef bksge::true_type propagate_on_container_move_assignment;

	int id() const { return id_; }

	static bool copy_called;
	static bool move_called;
	static bool allocate_called;

	A2(A2 const& a) BKSGE_NOEXCEPT : id_(a.id()) { copy_called = true; }
	A2(A2&& a)      BKSGE_NOEXCEPT : id_(a.id()) { move_called = true; }
	A2& operator=(A2 const& a) BKSGE_NOEXCEPT { id_ = a.id(); copy_called = true; return *this; }
	A2& operator=(A2&& a)      BKSGE_NOEXCEPT { id_ = a.id(); move_called = true; return *this; }

	T* allocate(bksge::size_t, const void* hint)
	{
		allocate_called = true;
		return (T*) const_cast<void *>(hint);
	}
};

template <typename T> bool A2<T>::copy_called = false;
template <typename T> bool A2<T>::move_called = false;
template <typename T> bool A2<T>::allocate_called = false;

template <typename T, typename U>
inline bool operator==(A2<T> const& x, A2<U> const& y)
{
	return x.id() == y.id();
}

template <typename T, typename U>
inline bool operator!=(A2<T> const& x, A2<U> const& y)
{
	return !(x == y);
}

template <typename T>
class A3
{
	int id_;
public:
	explicit A3(int id = 0) BKSGE_NOEXCEPT : id_(id) {}

	typedef T value_type;

	typedef bksge::true_type propagate_on_container_copy_assignment;
	typedef bksge::true_type propagate_on_container_swap;

	int id() const { return id_; }

	static bool copy_called;
	static bool move_called;
	static bool constructed;
	static bool destroy_called;

	A3(A3 const& a) BKSGE_NOEXCEPT : id_(a.id()) { copy_called = true; }
	A3(A3&& a)      BKSGE_NOEXCEPT : id_(a.id())  { move_called = true; }
	A3& operator=(A3 const& a) BKSGE_NOEXCEPT { id_ = a.id(); copy_called = true; return *this; }
	A3& operator=(A3&& a)      BKSGE_NOEXCEPT { id_ = a.id(); move_called = true; return *this; }

	template <typename U, typename... Args>
	void construct(U* p, Args&& ...args)
	{
		::new (p) U(bksge::forward<Args>(args)...);
		constructed = true;
	}

	template <typename U>
	void destroy(U* p)
	{
		p->~U();
		destroy_called = true;
	}

	A3 select_on_container_copy_construction() const { return A3(-1); }
};

template <typename T> bool A3<T>::copy_called = false;
template <typename T> bool A3<T>::move_called = false;
template <typename T> bool A3<T>::constructed = false;
template <typename T> bool A3<T>::destroy_called = false;

template <typename T, typename U>
inline bool operator==(A3<T> const& x, A3<U> const& y)
{
	return x.id() == y.id();
}

template <typename T, typename U>
inline bool operator!=(A3<T> const& x, A3<U> const& y)
{
	return !(x == y);
}

template <typename T>
class TDefaultOnly
{
	int data_;

	TDefaultOnly(TDefaultOnly const&);
	TDefaultOnly& operator=(TDefaultOnly const&);
public:
	static int count;

	TDefaultOnly() : data_(-1) { ++count; }
	~TDefaultOnly() { data_ = 0; --count; }

	friend bool operator==(TDefaultOnly const& x, TDefaultOnly const& y)
	{
		return x.data_ == y.data_;
	}
	friend bool operator< (TDefaultOnly const& x, TDefaultOnly const& y)
	{
		return x.data_ < y.data_;
	}
};

template <typename T>
int TDefaultOnly<T>::count = 0;

using DefaultOnly = TDefaultOnly<void>;

class MoveOnly
{
	MoveOnly(MoveOnly const&);
	MoveOnly& operator=(MoveOnly const&);

	int data_;
public:
	MoveOnly(int data = 1) : data_(data) {}
	MoveOnly(MoveOnly&& x)
		: data_(x.data_)
	{
		x.data_ = 0;
	}

	MoveOnly& operator=(MoveOnly&& x)
	{
		data_ = x.data_; x.data_ = 0; return *this;
	}

	int get() const { return data_; }

	bool operator==(MoveOnly const& x) const { return data_ == x.data_; }
	bool operator< (MoveOnly const& x) const { return data_ <  x.data_; }
	MoveOnly operator+(MoveOnly const& x) const { return MoveOnly{data_ + x.data_}; }
	MoveOnly operator*(MoveOnly const& x) const { return MoveOnly{data_ * x.data_}; }
};

template <typename T>
struct t_alloc_first
{
	static bool allocator_constructed;

	typedef A1<int> allocator_type;

	int data_;

	t_alloc_first() : data_(0) {}
	t_alloc_first(int d) : data_(d) {}
	t_alloc_first(bksge::allocator_arg_t, A1<int> const& a)
		: data_(0)
	{
		assert(a.id() == 5);
		(void)a;
		allocator_constructed = true;
	}

	t_alloc_first(bksge::allocator_arg_t, A1<int> const& a, int d)
		: data_(d)
	{
		assert(a.id() == 5);
		(void)a;
		allocator_constructed = true;
	}

	t_alloc_first(bksge::allocator_arg_t, A1<int> const& a, t_alloc_first const& d)
		: data_(d.data_)
	{
		assert(a.id() == 5);
		(void)a;
		allocator_constructed = true;
	}

	~t_alloc_first() { data_ = -1; }

	friend bool operator==(t_alloc_first const& x, t_alloc_first const& y)
	{
		return x.data_ == y.data_;
	}
	friend bool operator< (t_alloc_first const& x, t_alloc_first const& y)
	{
		return x.data_ < y.data_;
	}
};

template <typename T>
bool t_alloc_first<T>::allocator_constructed = false;

using alloc_first = t_alloc_first<void>;

template <typename T>
struct t_alloc_last
{
	static bool allocator_constructed;

	typedef A1<int> allocator_type;

	int data_;

	t_alloc_last() : data_(0) {}
	t_alloc_last(int d) : data_(d) {}
	t_alloc_last(A1<int> const& a)
		: data_(0)
	{
		assert(a.id() == 5);
		(void)a;
		allocator_constructed = true;
	}

	t_alloc_last(int d, A1<int> const& a)
		: data_(d)
	{
		assert(a.id() == 5);
		(void)a;
		allocator_constructed = true;
	}

	t_alloc_last(t_alloc_last const& d, A1<int> const& a)
		: data_(d.data_)
	{
		assert(a.id() == 5);
		(void)a;
		allocator_constructed = true;
	}

	~t_alloc_last() { data_ = -1; }

	friend bool operator==(t_alloc_last const& x, t_alloc_last const& y)
	{
		return x.data_ == y.data_;
	}
	friend bool operator< (t_alloc_last const& x, t_alloc_last const& y)
	{
		return x.data_ < y.data_;
	}
};

template <typename T>
bool t_alloc_last<T>::allocator_constructed = false;

using alloc_last = t_alloc_last<void>;

// test_convertible
namespace detail
{

template <typename Tp> void eat_type(Tp);

template <typename Tp, typename... Args>
constexpr auto test_convertible_imp(int)
-> decltype(eat_type<Tp>({bksge::declval<Args>()...}), true)
{
	return true;
}

template <typename Tp, typename... Args>
constexpr auto test_convertible_imp(long) -> bool { return false; }

}	// namespace detail

template <typename Tp, typename... Args>
constexpr bool test_convertible()
{
	return detail::test_convertible_imp<Tp, Args...>(0);
}

}	// namespace bksge_tuple_test

#endif // UNIT_TEST_FND_TUPLE_TUPLE_TEST_UTILITY_HPP
