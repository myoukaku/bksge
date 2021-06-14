/**
 *	@file	tuple_element.hpp
 *
 *	@brief	tuple_element の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_ELEMENT_HPP
#define BKSGE_FND_TUPLE_TUPLE_ELEMENT_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE)

namespace bksge
{

using std::tuple_element;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/config.hpp>
#include <bksge/fnd/type_traits/add_const.hpp>
#include <bksge/fnd/type_traits/add_volatile.hpp>
#include <bksge/fnd/type_traits/add_cv.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

template <bksge::size_t I, typename T>
struct tuple_element;

template <bksge::size_t I, typename T>
struct tuple_element<I, T const>
{
	using type = bksge::add_const_t<
		typename bksge::tuple_element<I, T>::type>;
};

template <bksge::size_t I, typename T>
struct tuple_element<I, T volatile>
{
	using type = bksge::add_volatile_t<
		typename bksge::tuple_element<I, T>::type>;
};

template <bksge::size_t I, typename T>
struct tuple_element<I, T const volatile>
{
	using type = bksge::add_cv_t<
		typename bksge::tuple_element<I, T>::type>;
};

template <bksge::size_t I, typename Head, typename... Tail>
struct tuple_element<I, bksge::tuple<Head, Tail...> >
	: public tuple_element<I - 1, bksge::tuple<Tail...> > {};

template <typename Head, typename... Tail>
struct tuple_element<0, bksge::tuple<Head, Tail...> >
{
	using type = Head;
};

template <bksge::size_t I>
struct tuple_element<I, bksge::tuple<>>
{
	static_assert(I < bksge::tuple_size<bksge::tuple<>>::value, "tuple index is in range");
};

}	// namespace bksge

#endif

#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

template <bksge::size_t I, typename T>
using tuple_element_t = typename bksge::tuple_element<I, T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_TUPLE_ELEMENT_HPP
