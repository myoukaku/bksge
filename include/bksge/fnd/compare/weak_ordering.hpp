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

class weak_ordering
{
private:
	cmp_cat::type m_value;

	constexpr explicit
	weak_ordering(cmp_cat::Ord v) noexcept
		: m_value(cmp_cat::type(v))
	{}

public:
	static const weak_ordering less;
	static const weak_ordering equivalent;
	static const weak_ordering greater;

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	// * extension *
	// std::weak_ordering からの変換
	constexpr
	weak_ordering(std::weak_ordering ord) noexcept
		: m_value(cmp_cat::type(
			ord == std::weak_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::weak_ordering::greater ? cmp_cat::Ord::greater :
			                                     cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::strong_ordering からの変換
	constexpr
	weak_ordering(std::strong_ordering ord) noexcept
		: m_value(cmp_cat::type(
			ord == std::strong_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::strong_ordering::greater ? cmp_cat::Ord::greater :
			                                       cmp_cat::Ord::equivalent))
	{}
#endif

	constexpr operator partial_ordering() const noexcept
	{
		return
			m_value == cmp_cat::type(cmp_cat::Ord::less) ?
				partial_ordering::less :
			m_value == cmp_cat::type(cmp_cat::Ord::greater) ?
				partial_ordering::greater :
			    partial_ordering::equivalent;
	}

	// comparisons
	friend constexpr bool
	operator==(weak_ordering lhs, weak_ordering rhs) noexcept
	{
		return lhs.m_value == rhs.m_value;
	}

	friend constexpr bool
	operator==(weak_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value == 0;
	}

	friend constexpr bool
	operator< (weak_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value < 0;
	}

	friend constexpr bool
	operator> (weak_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value > 0;
	}

	friend constexpr bool
	operator<=(weak_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value <= 0;
	}

	friend constexpr bool
	operator>=(weak_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value >= 0;
	}

	friend constexpr bool
	operator< (cmp_cat::unspec, weak_ordering v) noexcept
	{
		return 0 < v.m_value;
	}

	friend constexpr bool
	operator> (cmp_cat::unspec, weak_ordering v) noexcept
	{
		return 0 > v.m_value;
	}

	friend constexpr bool
	operator<=(cmp_cat::unspec, weak_ordering v) noexcept
	{
		return 0 <= v.m_value;
	}

	friend constexpr bool
	operator>=(cmp_cat::unspec, weak_ordering v) noexcept
	{
		return 0 >= v.m_value;
	}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	friend constexpr weak_ordering
	operator<=>(weak_ordering v, cmp_cat::unspec) noexcept
	{
		return v;
	}

	friend constexpr weak_ordering
	operator<=>(cmp_cat::unspec, weak_ordering v) noexcept
	{
		return weak_ordering(cmp_cat::Ord(-v.m_value));
	}
#else
	friend constexpr bool
	operator!=(weak_ordering lhs, weak_ordering rhs) noexcept
	{
		return !(lhs == rhs);
	}

	friend constexpr bool
	operator!=(weak_ordering lhs, cmp_cat::unspec rhs) noexcept
	{
		return !(lhs == rhs);
	}

	friend constexpr bool
	operator==(cmp_cat::unspec lhs, weak_ordering rhs) noexcept
	{
		return rhs == lhs;
	}

	friend constexpr bool
	operator!=(cmp_cat::unspec lhs, weak_ordering rhs) noexcept
	{
		return !(lhs == rhs);
	}
#endif
};

BKSGE_INLINE_VAR BKSGE_CONSTEXPR weak_ordering weak_ordering::less(cmp_cat::Ord::less);
BKSGE_INLINE_VAR BKSGE_CONSTEXPR weak_ordering weak_ordering::equivalent(cmp_cat::Ord::equivalent);
BKSGE_INLINE_VAR BKSGE_CONSTEXPR weak_ordering weak_ordering::greater(cmp_cat::Ord::greater);

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_WEAK_ORDERING_HPP
