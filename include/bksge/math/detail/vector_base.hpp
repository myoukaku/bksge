/**
 *	@file	vector_base.hpp
 *
 *	@brief	VectorBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_DETAIL_VECTOR_BASE_HPP
#define BKSGE_MATH_DETAIL_VECTOR_BASE_HPP

#include <bksge/math/detail/vector_value.hpp>
#include <bksge/type_traits/conjunction.hpp>
#include <bksge/utility/make_index_sequence.hpp>
#include <bksge/utility/index_sequence.hpp>
#include <bksge/config.hpp>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
class VectorBase : public vector_value<T, N>
{
private:
	using base_type = vector_value<T, N>;

#if defined(_MSC_VER)
public:
#else
private:
#endif
	template <bool, typename... UTypes>
	struct CheckArgsCtorImpl
	{
		static constexpr bool enable_implicit = false;
		static constexpr bool enable_explicit = false;
	};

	template <typename... UTypes>
	struct CheckArgsCtorImpl<true, UTypes...>
	{
		static constexpr bool enable_implicit =
			bksge::conjunction<std::is_convertible<UTypes, T>...>::value;

		static constexpr bool enable_explicit =
			bksge::conjunction<std::is_constructible<T, UTypes>...>::value &&
			!enable_implicit;
	};

	template <typename... UTypes>
	struct CheckArgsCtor
		: public CheckArgsCtorImpl<
			sizeof...(UTypes) == N,
			UTypes...
		>
	{};

	template <typename... UTypes>
	struct IsNothrowArgsConstructible
		: public bksge::conjunction<
			std::is_nothrow_constructible<T, UTypes>...
		>
	{};

public:
	// Default ctor
	BKSGE_CONSTEXPR
	VectorBase() BKSGE_NOEXCEPT_OR_NOTHROW
		: base_type()
	{}

	// Converting ctor
	template <
		typename... UTypes,
		typename std::enable_if<CheckArgsCtor<UTypes&&...>::enable_implicit>::type* = nullptr
	>
	BKSGE_CONSTEXPR
	VectorBase(UTypes&&... args)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<UTypes...>::value)
		: base_type({static_cast<T>(args)...})
	{}

	template <
		typename... UTypes,
		typename std::enable_if<CheckArgsCtor<UTypes&&...>::enable_explicit>::type* = nullptr
	>
	explicit BKSGE_CONSTEXPR
	VectorBase(UTypes&&... args)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<UTypes...>::value)
		: base_type(static_cast<T>(args)...)
	{}

	// Converting copy-ctor
	template <
		typename U,
		typename std::enable_if<CheckArgsCtorImpl<true, U const&>::enable_implicit>::type* = nullptr
	>
	BKSGE_CONSTEXPR
	VectorBase(vector_value<U, N> const& other)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<U>::value)
		: VectorBase(other, bksge::make_index_sequence<N>())
	{}

	template <
		typename U,
		typename std::enable_if<CheckArgsCtorImpl<true, U const&>::enable_explicit>::type* = nullptr
	>
	explicit BKSGE_CONSTEXPR
	VectorBase(vector_value<U, N> const& other)
		BKSGE_NOEXCEPT_IF(IsNothrowArgsConstructible<U>::value)
		: VectorBase(other, bksge::make_index_sequence<N>())
	{}

private:
	template <typename Vector, std::size_t... Is>
	BKSGE_CONSTEXPR
	VectorBase(Vector const& other, bksge::index_sequence<Is...>)
		BKSGE_NOEXCEPT_OR_NOTHROW
		: base_type(static_cast<T>(other[Is])...)
	{}
};

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_MATH_DETAIL_VECTOR_BASE_HPP
