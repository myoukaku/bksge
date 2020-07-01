/**
 *	@file	move_iterator.hpp
 *
 *	@brief	move_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_MOVE_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_MOVE_ITERATOR_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17)

#include <iterator>

namespace bksge
{

using std::move_iterator;

}	// namespace bksge

#else

#include <bksge/fnd/iterator/type_traits/iterator_category.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_value_type.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_reference.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>

namespace bksge
{

template <typename Iter>
class move_iterator
{
private:
	Iter m_i;
public:
	using iterator_type     = Iter;
	using iterator_category = bksge::iterator_category<iterator_type>;
	using value_type        = bksge::iterator_value_type<iterator_type>;
	using difference_type   = bksge::iterator_difference_type<iterator_type>;
	using pointer           = iterator_type;
private:
	using raw_reference     = bksge::iterator_reference<iterator_type>;
public:
	using reference         = bksge::conditional_t<
		bksge::is_reference<raw_reference>::value,
		bksge::remove_reference_t<raw_reference>&&,
		raw_reference
	>;

	BKSGE_CXX14_CONSTEXPR move_iterator(): m_i() {}
	BKSGE_CXX14_CONSTEXPR explicit move_iterator(Iter x): m_i(x) {}
	template <typename U>
	BKSGE_CXX14_CONSTEXPR move_iterator(move_iterator<U> const& other) : m_i(other.base()) {}
	BKSGE_CXX14_CONSTEXPR Iter base() const { return m_i; }
	BKSGE_CXX14_CONSTEXPR reference operator*() const { return static_cast<reference>(*m_i); }
	BKSGE_CXX14_CONSTEXPR pointer  operator->() const { return m_i; }
	BKSGE_CXX14_CONSTEXPR move_iterator& operator++() { ++m_i; return *this; }
	BKSGE_CXX14_CONSTEXPR move_iterator  operator++(int) { move_iterator tmp(*this); ++m_i; return tmp; }
	BKSGE_CXX14_CONSTEXPR move_iterator& operator--() { --m_i; return *this; }
	BKSGE_CXX14_CONSTEXPR move_iterator  operator--(int) { move_iterator tmp(*this); --m_i; return tmp; }
	BKSGE_CXX14_CONSTEXPR move_iterator  operator+ (difference_type n) const { return move_iterator(m_i + n); }
	BKSGE_CXX14_CONSTEXPR move_iterator& operator+=(difference_type n) { m_i += n; return *this; }
	BKSGE_CXX14_CONSTEXPR move_iterator  operator- (difference_type n) const { return move_iterator(m_i - n); }
	BKSGE_CXX14_CONSTEXPR move_iterator& operator-=(difference_type n) { m_i -= n; return *this; }
	BKSGE_CXX14_CONSTEXPR reference operator[](difference_type n) const { return static_cast<reference>(m_i[n]); }
};

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator==(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator<(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator!=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator>(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator>=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() >= rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator<=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() <= rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR auto
operator-(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
-> decltype(lhs.base() - rhs.base())
{
	return lhs.base() - rhs.base();
}

template <typename Iter>
inline BKSGE_CXX14_CONSTEXPR move_iterator<Iter>
operator+(typename move_iterator<Iter>::difference_type n, move_iterator<Iter> const& rhs)
{
	return move_iterator<Iter>(rhs.base() + n);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_MOVE_ITERATOR_HPP
