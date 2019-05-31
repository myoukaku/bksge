/**
 *	@file	any_of_inl.hpp
 *
 *	@brief	any_of の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TPP_INL_ANY_OF_INL_HPP
#define BKSGE_TPP_INL_ANY_OF_INL_HPP

#include <bksge/tpp/any_of.hpp>
#include <bksge/tpp/detail/type_tuple.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace tpp
{

namespace detail
{

template <std::size_t First, std::size_t Last, bool = (Last - First == 1)>
struct any_of_impl
{
	template <typename Tuple>
	static BKSGE_CONSTEXPR bool invoke(Tuple const& t)
	{
		return select<First>(t).m_value;
	}
};

template <std::size_t First, std::size_t Last>
struct any_of_impl<First, Last, false>
{
	template <typename Tuple>
	static BKSGE_CONSTEXPR bool invoke(Tuple const& t)
	{
		using Lhs = any_of_impl<First, (First + Last) / 2>;
		using Rhs = any_of_impl<(First + Last) / 2, Last>;
		return Lhs::invoke(t) || Rhs::invoke(t);
	}
};

}	// namespace detail

inline BKSGE_CONSTEXPR bool any_of()
{
	return false;
}

template <typename... Args>
inline BKSGE_CONSTEXPR bool any_of(Args&&... args)
{
	using Tuple = detail::type_tuple<Args...>;
	using Helper = detail::any_of_impl<0, sizeof...(Args)>;
	return Helper::invoke(Tuple(std::forward<Args>(args)...));
}

}	// namespace tpp

}	// namespace bksge

#endif // BKSGE_TPP_INL_ANY_OF_INL_HPP
