/**
 *	@file	reverse_iterator.hpp
 *
 *	@brief	reverse_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_REVERSE_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_REVERSE_ITERATOR_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17) && defined(__cpp_lib_concepts)
#    define BKSGE_USE_STD_REVERSE_ITERATOR
#endif

#if defined(BKSGE_USE_STD_REVERSE_ITERATOR)

#include <iterator>

namespace bksge
{

using std::reverse_iterator;

}	// namespace bksge

#else

#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <iterator>

namespace bksge
{

template <typename Iter>
class reverse_iterator
{
public:
	using iterator_type     = Iter;
	using iterator_category = typename bksge::iterator_traits<Iter>::iterator_category;
	using value_type        = bksge::iter_value_t<Iter>;
	using difference_type   = bksge::iter_difference_t<Iter>;
	using pointer           = typename bksge::iterator_traits<Iter>::pointer;
	using reference         = bksge::iter_reference_t<Iter>;

	BKSGE_CXX14_CONSTEXPR reverse_iterator(): current() {}
	BKSGE_CXX14_CONSTEXPR explicit reverse_iterator(iterator_type x): current(x) {}
	template <typename U>
	BKSGE_CXX14_CONSTEXPR reverse_iterator(reverse_iterator<U> const& u) : current(u.base()) {}
	template <typename U>
	BKSGE_CXX14_CONSTEXPR reverse_iterator& operator=(reverse_iterator<U> const& u)
	{
		current = u.base(); return *this;
	}
	BKSGE_CXX14_CONSTEXPR iterator_type base() const { return current; }
	BKSGE_CXX14_CONSTEXPR reference operator*() const { iterator_type tmp = current; return *--tmp; }
	BKSGE_CXX14_CONSTEXPR pointer  operator->() const { return bksge::addressof(operator*()); }
	BKSGE_CXX14_CONSTEXPR reverse_iterator& operator++() { --current; return *this; }
	BKSGE_CXX14_CONSTEXPR reverse_iterator  operator++(int) { reverse_iterator tmp(*this); --current; return tmp; }
	BKSGE_CXX14_CONSTEXPR reverse_iterator& operator--() { ++current; return *this; }
	BKSGE_CXX14_CONSTEXPR reverse_iterator  operator--(int) { reverse_iterator tmp(*this); ++current; return tmp; }
	BKSGE_CXX14_CONSTEXPR reverse_iterator  operator+ (difference_type n) const { return reverse_iterator(current - n); }
	BKSGE_CXX14_CONSTEXPR reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
	BKSGE_CXX14_CONSTEXPR reverse_iterator  operator- (difference_type n) const { return reverse_iterator(current + n); }
	BKSGE_CXX14_CONSTEXPR reverse_iterator& operator-=(difference_type n) { current += n; return *this; }
	BKSGE_CXX14_CONSTEXPR reference         operator[](difference_type n) const { return *(*this + n); }

protected:
	Iter current;
};

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator==(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator<(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator!=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator>(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator>=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return lhs.base() <= rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR bool
operator<=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return lhs.base() >= rhs.base();
}

template <typename Iter1, typename Iter2>
inline BKSGE_CXX14_CONSTEXPR auto
operator-(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
->decltype(rhs.base() - lhs.base())
{
	return rhs.base() - lhs.base();
}

template <class Iter>
inline BKSGE_CXX14_CONSTEXPR reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, reverse_iterator<Iter> const& it)
{
	return reverse_iterator<Iter>(it.base() - n);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_REVERSE_ITERATOR_HPP
