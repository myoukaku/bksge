/**
 *	@file	apply.hpp
 *
 *	@brief	apply 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_APPLY_HPP
#define BKSGE_FND_TUPLE_APPLY_HPP

#include <tuple>

#if defined(__cpp_lib_apply) && (__cpp_lib_apply >= 201603)

namespace bksge
{

using std::apply;

}	// namespace bksge

#else

#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <tuple>

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4100)

namespace bksge
{

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace detail
{

template <typename Function, typename Tuple, bksge::size_t... Indices>
inline BKSGE_CXX14_CONSTEXPR auto
apply_tuple_impl(Function&& func, Tuple&& t, bksge::index_sequence<Indices...>)
BKSGE_NOEXCEPT_DECLTYPE_RETURN(
	bksge::invoke(
		bksge::forward<Function>(func),
		std::get<Indices>(bksge::forward<Tuple>(t))...))

}	// namespace detail

template <typename Function, typename Tuple>
inline BKSGE_CXX14_CONSTEXPR auto
apply(Function&& func, Tuple&& t)
BKSGE_NOEXCEPT_DECLTYPE_RETURN(
	detail::apply_tuple_impl(
		bksge::forward<Function>(func), bksge::forward<Tuple>(t),
		bksge::make_index_sequence<std::tuple_size<bksge::remove_reference_t<Tuple>>::value>{}))

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace bksge

BKSGE_WARNING_POP()

#endif

#endif // BKSGE_FND_TUPLE_APPLY_HPP
