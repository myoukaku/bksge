/**
 *	@file	normal_iterator.hpp
 *
 *	@brief	normal_iterator クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_NORMAL_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_NORMAL_ITERATOR_HPP

#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_concept.hpp>
#include <bksge/fnd/compare/detail/synth3way.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Iterator, typename Container>
class normal_iterator
{
protected:
	Iterator m_current;

	using traits_type = bksge::iterator_traits<Iterator>;

public:
	using iterator_type     = Iterator;
	using iterator_category = typename traits_type::iterator_category;
	using value_type        = typename traits_type::value_type;
	using difference_type   = typename traits_type::difference_type;
	using reference         = typename traits_type::reference;
	using pointer           = typename traits_type::pointer;

	using iterator_concept  = bksge::detail::iter_concept<Iterator>;

	BKSGE_CONSTEXPR
	normal_iterator() BKSGE_NOEXCEPT
		: m_current(Iterator()) {}

	explicit BKSGE_CONSTEXPR
	normal_iterator(Iterator const& i) BKSGE_NOEXCEPT
		: m_current(i) {}

	// Allow iterator to const_iterator conversion
	template <typename Iter,
		typename = bksge::enable_if_t<
			bksge::is_same<Iter, typename Container::pointer>::value
		>
	>
	BKSGE_CONSTEXPR
	normal_iterator(normal_iterator<Iter, Container> const& i) BKSGE_NOEXCEPT
		: m_current(i.base()) {}

	// Forward iterator requirements
	BKSGE_CONSTEXPR
	reference operator*() const BKSGE_NOEXCEPT
	{
		return *m_current;
	}

	BKSGE_CONSTEXPR
	pointer operator->() const BKSGE_NOEXCEPT
	{
		return m_current;
	}

	BKSGE_CXX14_CONSTEXPR
	normal_iterator& operator++() BKSGE_NOEXCEPT
	{
		++m_current;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR
	normal_iterator operator++(int) BKSGE_NOEXCEPT
	{
		return normal_iterator(m_current++);
	}

	// Bidirectional iterator requirements
	BKSGE_CXX14_CONSTEXPR
	normal_iterator& operator--() BKSGE_NOEXCEPT
	{
		--m_current;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR
	normal_iterator operator--(int) BKSGE_NOEXCEPT
	{
		return normal_iterator(m_current--);
	}

	// Random access iterator requirements
	BKSGE_CONSTEXPR
	reference operator[](difference_type n) const BKSGE_NOEXCEPT
	{
		return m_current[n];
	}

	BKSGE_CXX14_CONSTEXPR
	normal_iterator& operator+=(difference_type n) BKSGE_NOEXCEPT
	{
		m_current += n;
		return *this;
	}

	BKSGE_CONSTEXPR
	normal_iterator operator+(difference_type n) const BKSGE_NOEXCEPT
	{
		return normal_iterator(m_current + n);
	}

	BKSGE_CXX14_CONSTEXPR
	normal_iterator& operator-=(difference_type n) BKSGE_NOEXCEPT
	{
		m_current -= n;
		return *this;
	}

	BKSGE_CONSTEXPR
	normal_iterator operator-(difference_type n) const BKSGE_NOEXCEPT
	{
		return normal_iterator(m_current - n);
	}

	BKSGE_CONSTEXPR
	Iterator const& base() const BKSGE_NOEXCEPT
	{
		return m_current;
	}
};

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename IteratorL, typename IteratorR, typename Container>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires requires(IteratorL lhs, IteratorR rhs)
{
	{ lhs == rhs } -> bksge::convertible_to<bool>;
}
#endif
inline BKSGE_CONSTEXPR bool
operator==(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs)
	noexcept(noexcept(lhs.base() == rhs.base()))
{
	return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CXX14_CONSTEXPR bksge::detail::synth3way_t<IteratorR, IteratorL>
operator<=>(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs)
	noexcept(noexcept(bksge::detail::synth3way(lhs.base(), rhs.base())))
{
	return bksge::detail::synth3way(lhs.base(), rhs.base());
}

#else

// Forward iterator requirements
template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CONSTEXPR bool operator==(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() == rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR bool operator==(
	normal_iterator<Iterator, Container> const& lhs,
	normal_iterator<Iterator, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CONSTEXPR bool operator!=(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() != rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR bool operator!=(
	normal_iterator<Iterator, Container> const& lhs,
	normal_iterator<Iterator, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() != rhs.base();
}

// Random access iterator requirements
template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CONSTEXPR bool operator<(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() < rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR bool operator<(
	normal_iterator<Iterator, Container> const& lhs,
	normal_iterator<Iterator, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() < rhs.base();
}

template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CONSTEXPR bool operator>(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() > rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR bool operator>(
	normal_iterator<Iterator, Container> const& lhs,
	normal_iterator<Iterator, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() > rhs.base();
}

template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CONSTEXPR bool operator<=(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() <= rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR bool operator<=(
	normal_iterator<Iterator, Container> const& lhs,
	normal_iterator<Iterator, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() <= rhs.base();
}

template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CONSTEXPR bool operator>=(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() >= rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR bool operator>=(
	normal_iterator<Iterator, Container> const& lhs,
	normal_iterator<Iterator, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() >= rhs.base();
}

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename IteratorL, typename IteratorR, typename Container>
inline BKSGE_CONSTEXPR auto
operator-(
	normal_iterator<IteratorL, Container> const& lhs,
	normal_iterator<IteratorR, Container> const& rhs) BKSGE_NOEXCEPT
->decltype(lhs.base() - rhs.base())
{
	return lhs.base() - rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR
typename normal_iterator<Iterator, Container>::difference_type
operator-(
	normal_iterator<Iterator, Container> const& lhs,
	normal_iterator<Iterator, Container> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.base() - rhs.base();
}

template <typename Iterator, typename Container>
inline BKSGE_CONSTEXPR
normal_iterator<Iterator, Container>
operator+(
	typename normal_iterator<Iterator, Container>::difference_type n,
	normal_iterator<Iterator, Container> const& i) BKSGE_NOEXCEPT
{
	return normal_iterator<Iterator, Container>(i.base() + n);
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_NORMAL_ITERATOR_HPP
