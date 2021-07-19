/**
 *	@file	make_from_tuple.hpp
 *
 *	@brief	make_from_tuple 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_MAKE_FROM_TUPLE_HPP
#define BKSGE_FND_TUPLE_MAKE_FROM_TUPLE_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE) && defined(__cpp_lib_make_from_tuple) && (__cpp_lib_make_from_tuple >= 201606)

namespace bksge
{

using std::make_from_tuple;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4100)

namespace bksge
{

#define BKSGE_NOEXCEPT_RETURN(...) noexcept(noexcept(__VA_ARGS__)) { return __VA_ARGS__; }

namespace detail
{

template <typename T, typename Tuple, std::size_t... Indices>
inline BKSGE_CXX14_CONSTEXPR T
make_from_tuple_impl(Tuple&& t, bksge::index_sequence<Indices...>)
BKSGE_NOEXCEPT_RETURN(
	T(bksge::get<Indices>(std::forward<Tuple>(t))...))

}	// namespace detail

/**
 *	@brief	タプルからオブジェクトを構築する
 *
 *	@tparam		T		構築するオブジェクトの型
 *	@tparam		Tuple	タプル型
 *
 *	@param		t		Tのコンストラクタの引数として使われる値を要素とするタプル
 *
 *	@return		構築されたT型のオブジェクト
 *
 *	@note		Tuple は必ずしも bksge::tuple 型でなくても、
 *				bksge::get と bksge::tuple_size に対応している型であれば良い。
 *				例えば bksge::array や bksge::pair など。
 */
template <typename T, typename Tuple>
inline BKSGE_CXX14_CONSTEXPR T
make_from_tuple(Tuple&& t)
BKSGE_NOEXCEPT_RETURN(
	detail::make_from_tuple_impl<T>(std::forward<Tuple>(t),
		bksge::make_index_sequence<bksge::tuple_size<bksge::remove_reference_t<Tuple>>::value>{}))

#undef BKSGE_NOEXCEPT_RETURN

}	// namespace bksge

BKSGE_WARNING_POP()

#endif

#endif // BKSGE_FND_TUPLE_MAKE_FROM_TUPLE_HPP
