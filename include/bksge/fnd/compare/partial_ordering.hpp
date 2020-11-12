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

#if !defined(BKSGE_HAS_CXX17_INLINE_VARIABLES)
template <typename>
#endif
class partial_ordering_t
{
private:
	cmp_cat::type m_value;

	BKSGE_CONSTEXPR explicit
	partial_ordering_t(cmp_cat::Ord v) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(v))
	{}

	BKSGE_CONSTEXPR explicit
	partial_ordering_t(cmp_cat::Ncmp v) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(v))
	{}

public:
	static const partial_ordering_t less;
	static const partial_ordering_t equivalent;
	static const partial_ordering_t greater;
	static const partial_ordering_t unordered;

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	// * extension *
	// std::partial_ordering からの変換
	BKSGE_CONSTEXPR
	partial_ordering_t(std::partial_ordering ord) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::partial_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::partial_ordering::greater ? cmp_cat::Ord::greater :
			                                        cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::weak_ordering からの変換
	BKSGE_CONSTEXPR
	partial_ordering_t(std::weak_ordering ord) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::weak_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::weak_ordering::greater ? cmp_cat::Ord::greater :
			                                     cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::strong_ordering からの変換
	BKSGE_CONSTEXPR
	partial_ordering_t(std::strong_ordering ord) BKSGE_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::strong_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::strong_ordering::greater ? cmp_cat::Ord::greater :
			                                       cmp_cat::Ord::equivalent))
	{}
#endif

	// comparisons
	friend BKSGE_CONSTEXPR bool
	operator==(partial_ordering_t lhs, partial_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return lhs.m_value == rhs.m_value;
	}

	friend BKSGE_CONSTEXPR bool
	operator==(partial_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value == 0;
	}

	friend BKSGE_CONSTEXPR bool
	operator< (partial_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value == -1;
	}

	friend BKSGE_CONSTEXPR bool
	operator> (partial_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value == 1;
	}

	friend BKSGE_CONSTEXPR bool
	operator<=(partial_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v.m_value <= 0;
	}

	friend BKSGE_CONSTEXPR bool
	operator>=(partial_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return cmp_cat::type(v.m_value & 1) == v.m_value;
	}

	friend BKSGE_CONSTEXPR bool
	operator< (cmp_cat::unspec, partial_ordering_t v) BKSGE_NOEXCEPT
	{
		return v.m_value == 1;
	}

	friend BKSGE_CONSTEXPR bool
	operator> (cmp_cat::unspec, partial_ordering_t v) BKSGE_NOEXCEPT
	{
		return v.m_value == -1;
	}

	friend BKSGE_CONSTEXPR bool
	operator<=(cmp_cat::unspec, partial_ordering_t v) BKSGE_NOEXCEPT
	{
		return cmp_cat::type(v.m_value & 1) == v.m_value;
	}

	friend BKSGE_CONSTEXPR bool
	operator>=(cmp_cat::unspec, partial_ordering_t v) BKSGE_NOEXCEPT
	{
		return 0 >= v.m_value;
	}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	friend BKSGE_CONSTEXPR partial_ordering_t
	operator<=>(partial_ordering_t v, cmp_cat::unspec) BKSGE_NOEXCEPT
	{
		return v;
	}

	friend BKSGE_CONSTEXPR partial_ordering_t
	operator<=>(cmp_cat::unspec, partial_ordering_t v) BKSGE_NOEXCEPT
	{
		if (v.m_value & 1)
		{
			return partial_ordering_t(cmp_cat::Ord(-v.m_value));
		}
		else
		{
			return v;
		}
	}
#else
	friend BKSGE_CONSTEXPR bool
	operator!=(partial_ordering_t lhs, partial_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend BKSGE_CONSTEXPR bool
	operator!=(partial_ordering_t lhs, cmp_cat::unspec rhs) BKSGE_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend BKSGE_CONSTEXPR bool
	operator==(cmp_cat::unspec lhs, partial_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return rhs == lhs;
	}

	friend BKSGE_CONSTEXPR bool
	operator!=(cmp_cat::unspec lhs, partial_ordering_t rhs) BKSGE_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif
};

#if defined(BKSGE_HAS_CXX17_INLINE_VARIABLES)

using partial_ordering = partial_ordering_t;

inline BKSGE_CONSTEXPR partial_ordering partial_ordering::less(cmp_cat::Ord::less);
inline BKSGE_CONSTEXPR partial_ordering partial_ordering::equivalent(cmp_cat::Ord::equivalent);
inline BKSGE_CONSTEXPR partial_ordering partial_ordering::greater(cmp_cat::Ord::greater);
inline BKSGE_CONSTEXPR partial_ordering partial_ordering::unordered(cmp_cat::Ncmp::unordered);

#else

using partial_ordering = partial_ordering_t<void>;

template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::less(cmp_cat::Ord::less);
template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::equivalent(cmp_cat::Ord::equivalent);
template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::greater(cmp_cat::Ord::greater);
template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::unordered(cmp_cat::Ncmp::unordered);

#endif

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_PARTIAL_ORDERING_HPP
