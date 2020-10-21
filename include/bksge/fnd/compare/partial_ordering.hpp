/**
 *	@file	partial_ordering.hpp
 *
 *	@brief	partial_ordering の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_PARTIAL_ORDERING_HPP
#define BKSGE_FND_COMPARE_PARTIAL_ORDERING_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::partial_ordering;

}	// namespace bksge

#else

#include <bksge/fnd/compare/detail/cmp_cat.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

class partial_ordering
{
private:
	cmp_cat::type m_value;

	constexpr explicit
	partial_ordering(cmp_cat::Ord v) noexcept
		: m_value(cmp_cat::type(v))
	{}

	constexpr explicit
	partial_ordering(cmp_cat::Ncmp v) noexcept
		: m_value(cmp_cat::type(v))
	{}

public:
	static const partial_ordering less;
	static const partial_ordering equivalent;
	static const partial_ordering greater;
	static const partial_ordering unordered;

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	// * extension *
	// std::partial_ordering からの変換
	constexpr
	partial_ordering(std::partial_ordering ord) noexcept
		: m_value(cmp_cat::type(
			ord == std::partial_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::partial_ordering::greater ? cmp_cat::Ord::greater :
			                                        cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::weak_ordering からの変換
	constexpr
	partial_ordering(std::weak_ordering ord) noexcept
		: m_value(cmp_cat::type(
			ord == std::weak_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::weak_ordering::greater ? cmp_cat::Ord::greater :
			                                     cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::strong_ordering からの変換
	constexpr
	partial_ordering(std::strong_ordering ord) noexcept
		: m_value(cmp_cat::type(
			ord == std::strong_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::strong_ordering::greater ? cmp_cat::Ord::greater :
			                                       cmp_cat::Ord::equivalent))
	{}
#endif

	// comparisons
	friend constexpr bool
	operator==(partial_ordering lhs, partial_ordering rhs) noexcept
	{
		return lhs.m_value == rhs.m_value;
	}

	friend constexpr bool
	operator==(partial_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value == 0;
	}

	friend constexpr bool
	operator< (partial_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value == -1;
	}

	friend constexpr bool
	operator> (partial_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value == 1;
	}

	friend constexpr bool
	operator<=(partial_ordering v, cmp_cat::unspec) noexcept
	{
		return v.m_value <= 0;
	}

	friend constexpr bool
	operator>=(partial_ordering v, cmp_cat::unspec) noexcept
	{
		return cmp_cat::type(v.m_value & 1) == v.m_value;
	}

	friend constexpr bool
	operator< (cmp_cat::unspec, partial_ordering v) noexcept
	{
		return v.m_value == 1;
	}

	friend constexpr bool
	operator> (cmp_cat::unspec, partial_ordering v) noexcept
	{
		return v.m_value == -1;
	}

	friend constexpr bool
	operator<=(cmp_cat::unspec, partial_ordering v) noexcept
	{
		return cmp_cat::type(v.m_value & 1) == v.m_value;
	}

	friend constexpr bool
	operator>=(cmp_cat::unspec, partial_ordering v) noexcept
	{
		return 0 >= v.m_value;
	}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	friend constexpr partial_ordering
	operator<=>(partial_ordering v, cmp_cat::unspec) noexcept
	{
		return v;
	}

	friend constexpr partial_ordering
	operator<=>(cmp_cat::unspec, partial_ordering v) noexcept
	{
		if (v.m_value & 1)
		{
			return partial_ordering(cmp_cat::Ord(-v.m_value));
		}
		else
		{
			return v;
		}
	}
#else
	friend constexpr bool
	operator!=(partial_ordering lhs, partial_ordering rhs) noexcept
	{
		return !(lhs == rhs);
	}

	friend constexpr bool
	operator!=(partial_ordering lhs, cmp_cat::unspec rhs) noexcept
	{
		return !(lhs == rhs);
	}

	friend constexpr bool
	operator==(cmp_cat::unspec lhs, partial_ordering rhs) noexcept
	{
		return rhs == lhs;
	}

	friend constexpr bool
	operator!=(cmp_cat::unspec lhs, partial_ordering rhs) noexcept
	{
		return !(lhs == rhs);
	}
#endif
};

BKSGE_INLINE_VAR BKSGE_CONSTEXPR partial_ordering partial_ordering::less(cmp_cat::Ord::less);
BKSGE_INLINE_VAR BKSGE_CONSTEXPR partial_ordering partial_ordering::equivalent(cmp_cat::Ord::equivalent);
BKSGE_INLINE_VAR BKSGE_CONSTEXPR partial_ordering partial_ordering::greater(cmp_cat::Ord::greater);
BKSGE_INLINE_VAR BKSGE_CONSTEXPR partial_ordering partial_ordering::unordered(cmp_cat::Ncmp::unordered);

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_PARTIAL_ORDERING_HPP
