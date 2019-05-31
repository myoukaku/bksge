/**
 *	@file	all_of_inl.hpp
 *
 *	@brief	all_of の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TPP_INL_ALL_OF_INL_HPP
#define BKSGE_TPP_INL_ALL_OF_INL_HPP

#include <bksge/tpp/all_of.hpp>
#include <bksge/tpp/detail/type_tuple.hpp>
#include <bksge/utility/forward.hpp>
#include <bksge/config.hpp>
#include <cstddef>

namespace bksge
{

namespace tpp
{

namespace detail
{

template <std::size_t First, std::size_t Last, bool = (Last - First == 1)>
struct all_of_impl
{
	template <typename Tuple>
	static BKSGE_CONSTEXPR bool invoke(Tuple const& t)
	{
		return select<First>(t).m_value;
	}
};

template <std::size_t First, std::size_t Last>
struct all_of_impl<First, Last, false>
{
	template <typename Tuple>
	static BKSGE_CONSTEXPR bool invoke(Tuple const& t)
	{
		using Lhs = all_of_impl<First, (First + Last) / 2>;
		using Rhs = all_of_impl<(First + Last) / 2, Last>;
		return Lhs::invoke(t) && Rhs::invoke(t);
	}
};

}	// namespace detail

inline BKSGE_CONSTEXPR bool all_of()
{
	return true;
}

template <typename... Args>
inline BKSGE_CONSTEXPR bool all_of(Args&&... args)
{
	using Tuple = detail::type_tuple<Args...>;
	using Helper = detail::all_of_impl<0, sizeof...(Args)>;
	return Helper::invoke(Tuple(bksge::forward<Args>(args)...));
}

}	// namespace tpp

}	// namespace bksge

#endif // BKSGE_TPP_INL_ALL_OF_INL_HPP
