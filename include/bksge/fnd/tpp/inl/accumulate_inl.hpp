/**
 *	@file	accumulate_inl.hpp
 *
 *	@brief	accumulate の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TPP_INL_ACCUMULATE_INL_HPP
#define BKSGE_FND_TPP_INL_ACCUMULATE_INL_HPP

#include <bksge/fnd/tpp/accumulate.hpp>
#include <bksge/fnd/tpp/detail/type_tuple.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace tpp
{

namespace detail
{

template <typename Result, bksge::size_t First, bksge::size_t Last, bool = (Last - First == 1)>
struct accumulate_impl
{
	template <typename Tuple>
	static BKSGE_CONSTEXPR Result invoke(Tuple const& t)
	{
		return select<First>(t).m_value;
	}
};

template <typename Result, bksge::size_t First, bksge::size_t Last>
struct accumulate_impl<Result, First, Last, false>
{
	template <typename Tuple>
	static BKSGE_CONSTEXPR Result invoke(Tuple const& t)
	{
		using Lhs = accumulate_impl<Result, First, (First + Last) / 2>;
		using Rhs = accumulate_impl<Result, (First + Last) / 2, Last>;
		return Lhs::invoke(t) + Rhs::invoke(t);
	}
};

}	// namespace detail

template <typename Result>
inline BKSGE_CONSTEXPR Result accumulate()
{
	return Result{};
}

template <typename Result, typename... Args>
inline BKSGE_CONSTEXPR Result accumulate(Args&&... args)
{
	using Tuple = detail::type_tuple<Args...>;
	using Helper = detail::accumulate_impl<Result, 0, sizeof...(Args)>;
	return Helper::invoke(Tuple(bksge::forward<Args>(args)...));
}

}	// namespace tpp

}	// namespace bksge

#endif // BKSGE_FND_TPP_INL_ACCUMULATE_INL_HPP
