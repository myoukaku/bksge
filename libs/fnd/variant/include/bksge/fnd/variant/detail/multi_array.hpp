﻿/**
 *	@file	multi_array.hpp
 *
 *	@brief	MultiArray の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_MULTI_ARRAY_HPP
#define BKSGE_FND_VARIANT_DETAIL_MULTI_ARRAY_HPP

#include <bksge/fnd/variant/detail/variant_cookie.hpp>
#include <bksge/fnd/variant/detail/deduce_visit_result.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/nth.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace variant_detail
{

// Used for storing a multi-dimensional vtable.
template <typename T, bksge::size_t... Dimensions>
struct MultiArray;

// Partial specialization with rank zero, stores a single T element.
template <typename T>
struct MultiArray<T>
{
private:
	template <typename>
	struct untag_result
		: public bksge::false_type
	{
		using element_type = T;
	};

	template <typename... Args>
	struct untag_result<void(*)(Args...)>
		: public bksge::false_type
	{
		using element_type = void(*)(Args...);
	};

	template <typename... Args>
	struct untag_result<variant_detail::VariantCookie(*)(Args...)>
		: public bksge::false_type
	{
		using element_type = void(*)(Args...);
	};

	template <typename... Args>
	struct untag_result<variant_detail::VariantIdxCookie(*)(Args...)>
		: public bksge::false_type
	{
		using element_type = void(*)(Args...);
	};

	template <typename Res, typename... Args>
	struct untag_result<variant_detail::DeduceVisitResult<Res>(*)(Args...)>
		: public bksge::true_type
	{
		using element_type = Res(*)(Args...);
	};

public:
	static constexpr bool result_is_deduced = untag_result<T>::value;

	constexpr typename untag_result<T>::element_type const&
	access() const
	{
		return m_data;
	}

	typename untag_result<T>::element_type m_data;
};

// Partial specialization with rank >= 1.
template <
	typename Ret,
	typename Visitor,
	typename... Variants,
	bksge::size_t First, bksge::size_t... Rest>
struct MultiArray<Ret(*)(Visitor, Variants...), First, Rest...>
{
private:
	static constexpr bksge::size_t Index =
		sizeof...(Variants) - sizeof...(Rest) - 1;

	using Variant = bksge::nth_t<Index, Variants...>;

	static constexpr int DoCookie =
		variant_detail::extra_visit_slot_needed<Ret, Variant>::value ? 1 : 0;

	using T = Ret(*)(Visitor, Variants...);

public:
	MultiArray<T, Rest...> m_arr[First + DoCookie];

	template <typename... Args>
	constexpr auto
	access(bksge::size_t first_index, Args... rest_indices) const
	->decltype(m_arr[first_index + DoCookie].access(rest_indices...))
	{
		return m_arr[first_index + DoCookie].access(rest_indices...);
	}
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_MULTI_ARRAY_HPP
