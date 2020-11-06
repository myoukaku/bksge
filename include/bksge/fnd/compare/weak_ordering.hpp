/**
 *	@file	weak_ordering.hpp
 *
 *	@brief	weak_ordering の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_WEAK_ORDERING_HPP
#define BKSGE_FND_COMPARE_WEAK_ORDERING_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::weak_ordering;

}	// namespace bksge

#else

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/detail/cmp_cat.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if !defined(BKSGE_HAS_CXX17_INLINE_VARIABLES)
template <typename>
#endif
class weak_ordering_t
{
private:
	cmp_cat::type m_value;

	BKSGE_CONSTEXPR explicit
	weak_ordering_t(cmp_cat::Ord v) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(v))
	{}

public:
	static const weak_ordering_t less;
	static const weak_ordering_t equivalent;
	static const weak_ordering_t greater;

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	// * extension *
	// std::weak_ordering からの変換
	BKSGE_CONSTEXPR
	weak_ordering_t(std::weak_ordering ord) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::weak_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::weak_ordering::greater ? cmp_cat::Ord::greater :
			                                     cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::strong_ordering からの変換
	BKSGE_CONSTEXPR
	weak_ordering_t(std::strong_ordering ord) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::strong_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::strong_ordering::greater ? cmp_cat::Ord::greater :
			                                       cmp_cat::Ord::equivalent))
	{}
#endif

	BKSGE_CONSTEXPR operator partial_ordering() const BKSGE_NOEXCEPT
	{
		return
			m_value == cmp_cat::type(cmp_cat::Ord::less) ?
				partial_ordering::less :
			m_value == cmp_cat::type(cmp_cat::Ord::greater) ?
				partial_ordering::greater :
			    partial_ordering::equivalent;
	}

	// comparisons
	friend BKSGE_CONSTEXPR bool
	operator==(weak_ordering_t lhs, weak_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return lhs.m_value == rhs.m_value;
	}

	friend BKSGE_CONSTEXPR bool
	operator==(weak_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value == 0;
	}

	friend BKSGE_CONSTEXPR bool
	operator< (weak_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value < 0;
	}

	friend BKSGE_CONSTEXPR bool
	operator> (weak_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value > 0;
	}

	friend BKSGE_CONSTEXPR bool
	operator<=(weak_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value <= 0;
	}

	friend BKSGE_CONSTEXPR bool
	operator>=(weak_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value >= 0;
	}

	friend BKSGE_CONSTEXPR bool
	operator< (cmp_cat::unspec, weak_ordering_t v) BKSGE_NOEXCEPT
	{
		return 0 < v.m_value;
	}

	friend BKSGE_CONSTEXPR bool
	operator> (cmp_cat::unspec, weak_ordering_t v) BKSGE_NOEXCEPT
	{
		return 0 > v.m_value;
	}

	friend BKSGE_CONSTEXPR bool
	operator<=(cmp_cat::unspec, weak_ordering_t v) BKSGE_NOEXCEPT
	{
		return 0 <= v.m_value;
	}

	friend BKSGE_CONSTEXPR bool
	operator>=(cmp_cat::unspec, weak_ordering_t v) BKSGE_NOEXCEPT
	{
		return 0 >= v.m_value;
	}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	friend BKSGE_CONSTEXPR weak_ordering_t
	operator<=>(weak_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v;
	}

	friend BKSGE_CONSTEXPR weak_ordering_t
	operator<=>(cmp_cat::unspec, weak_ordering_t v) BKSGE_NOEXCEPT
	{
		return weak_ordering_t(cmp_cat::Ord(-v.m_value));
	}
#else
	friend BKSGE_CONSTEXPR bool
	operator!=(weak_ordering_t lhs, weak_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend BKSGE_CONSTEXPR bool
	operator!=(weak_ordering_t lhs, cmp_cat::unspec rhs) BKSGE_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend BKSGE_CONSTEXPR bool
	operator==(cmp_cat::unspec lhs, weak_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return rhs == lhs;
	}

	friend BKSGE_CONSTEXPR bool
	operator!=(cmp_cat::unspec lhs, weak_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif
};

#if defined(BKSGE_HAS_CXX17_INLINE_VARIABLES)

using weak_ordering = weak_ordering_t;

inline BKSGE_CONSTEXPR weak_ordering weak_ordering::less(cmp_cat::Ord::less);
inline BKSGE_CONSTEXPR weak_ordering weak_ordering::equivalent(cmp_cat::Ord::equivalent);
inline BKSGE_CONSTEXPR weak_ordering weak_ordering::greater(cmp_cat::Ord::greater);

#else

using weak_ordering = weak_ordering_t<void>;

template <typename T> BKSGE_CONSTEXPR weak_ordering_t<T> weak_ordering_t<T>::less(cmp_cat::Ord::less);
template <typename T> BKSGE_CONSTEXPR weak_ordering_t<T> weak_ordering_t<T>::equivalent(cmp_cat::Ord::equivalent);
template <typename T> BKSGE_CONSTEXPR weak_ordering_t<T> weak_ordering_t<T>::greater(cmp_cat::Ord::greater);

#endif

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_WEAK_ORDERING_HPP
