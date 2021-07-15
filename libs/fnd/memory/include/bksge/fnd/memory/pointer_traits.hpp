/**
 *	@file	pointer_traits.hpp
 *
 *	@brief	pointer_traits を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_POINTER_TRAITS_HPP
#define BKSGE_FND_MEMORY_POINTER_TRAITS_HPP

#include <memory>

#if defined(__cpp_lib_constexpr_memory) && (__cpp_lib_constexpr_memory >= 201811L)

#define BKSGE_POINTER_TRAITS_NAMESPACE std

namespace bksge
{

using std::pointer_traits;

}	// namespace bksge

#else

#define BKSGE_POINTER_TRAITS_NAMESPACE bksge

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

/// Implementation of the detection idiom (negative case).
template <typename Default, typename AlwaysVoid, template <typename...> class Op, typename... Args>
struct detector
{
	using value_t = bksge::false_type;
	using type = Default;
};

/// Implementation of the detection idiom (positive case).
template <typename Default, template <typename...> class Op, typename... Args>
struct detector<Default, bksge::void_t<Op<Args...>>, Op, Args...>
{
	using value_t = bksge::true_type;
	using type = Op<Args...>;
};

// Detect whether Op<Args...> is a valid type, use Default if not.
template <typename Default, template <typename...> class Op, typename... Args>
using detected_or = detector<Default, void, Op, Args...>;

// Op<Args...> if that is a valid type, otherwise Default.
template <typename Default, template <typename...> class Op, typename... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

class undefined;

// Given Template<T, ...> return T, otherwise invalid.
template <typename T>
struct get_first_arg
{
	using type = undefined;
};

template <template <typename, typename...> class Template, typename T, typename... Types>
struct get_first_arg<Template<T, Types...>>
{
	using type = T;
};

template <typename T>
using get_first_arg_t = typename get_first_arg<T>::type;

// Given Template<T, ...> and U return Template<U, ...>, otherwise invalid.
template <typename T, typename U>
struct replace_first_arg
{};

template <template <typename, typename...> class Template, typename U, typename T, typename... Types>
struct replace_first_arg<Template<T, Types...>, U>
{
	using type = Template<U, Types...>;
};

template <typename T>
using make_not_void = typename bksge::conditional<bksge::is_void<T>::value, undefined, T>::type;

}	// namespace detail

template <typename Ptr>
struct pointer_traits
{
private:
	template <typename T>
	using element_type_0 = typename T::element_type;

	template <typename T>
	using difference_type_0 = typename T::difference_type;

	template <typename T, typename U, typename = void>
	struct rebind_0 : detail::replace_first_arg<T, U> {};

	template <typename T, typename U>
	struct rebind_0<T, U, bksge::void_t<typename T::template rebind<U>>>
	{
		using type = typename T::template rebind<U>;
	};

public:
	using pointer         = Ptr;
	using element_type    = detail::detected_or_t<detail::get_first_arg_t<Ptr>, element_type_0, Ptr>;
	using difference_type = detail::detected_or_t<std::ptrdiff_t, difference_type_0, Ptr>;

	template <typename U>
	using rebind = typename rebind_0<Ptr, U>::type;

	static Ptr pointer_to(detail::make_not_void<element_type>& e)
	{
		return Ptr::pointer_to(e);
	}

	static_assert(!bksge::is_same<element_type, detail::undefined>::value,
		"pointer type defines element_type or is like SomePointer<T, Args>");
};

template <typename T>
struct pointer_traits<T*>
{
	using pointer         = T*;
	using element_type    = T;
	using difference_type = std::ptrdiff_t;

	template <typename U>
	using rebind = U*;

	static BKSGE_CXX14_CONSTEXPR pointer
	pointer_to(detail::make_not_void<element_type>& r) noexcept
	{
		return bksge::addressof(r);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_MEMORY_POINTER_TRAITS_HPP
