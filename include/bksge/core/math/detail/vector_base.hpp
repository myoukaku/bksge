/**
 *	@file	vector_base.hpp
 *
 *	@brief	VectorBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_HPP

#include <bksge/core/math/detail/vector_value.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <cstddef>
#include <iosfwd>		// basic_ostream
#include <tuple>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
class VectorBase
{
#if defined(_MSC_VER)
public:
#else
private:
#endif
	template <bool, typename... UTypes>
	struct CheckArgsCtorImpl
	{
		static constexpr bool value = false;
	};

	template <typename... UTypes>
	struct CheckArgsCtorImpl<true, UTypes...>
	{
		static constexpr bool value =
			bksge::conjunction<bksge::is_constructible<T, UTypes>...>::value;
	};

	template <typename... UTypes>
	struct CheckArgsCtor
		: public CheckArgsCtorImpl<
			sizeof...(UTypes) == N,
			UTypes...
		>
	{};

public:
	using value_type             = T;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;
	using reference              = T&;
	using const_reference        = T const&;
	using pointer                = T*;
	using const_pointer          = T const*;
	using iterator               = T*;
	using const_iterator         = T const*;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// Default ctor
	explicit BKSGE_CONSTEXPR
	VectorBase() BKSGE_NOEXCEPT_OR_NOTHROW;

	// Converting ctor
	template <
		typename... UTypes,
		typename = bksge::enable_if_t<
			CheckArgsCtor<UTypes const&...>::value
		>
	>
	BKSGE_CONSTEXPR
	VectorBase(UTypes const&... args)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	template <
		typename U,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, U>::value
		>
	>
	BKSGE_CONSTEXPR
	VectorBase(VectorValue<U, N> const& a)
		BKSGE_NOEXCEPT_OR_NOTHROW;

private:
	template <typename U, std::size_t... Is>
	explicit BKSGE_CONSTEXPR
	VectorBase(
		VectorValue<U, N> const& a,
		bksge::index_sequence<Is...>)
		BKSGE_NOEXCEPT_OR_NOTHROW;

public:
	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reference
	operator[](size_type pos) BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reference
	operator[](size_type pos) const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reference
	at(size_type pos);

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reference
	at(size_type pos) const;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR pointer
	data() BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_pointer
	data() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR iterator
	begin() BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	begin() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR iterator
	end() BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	end() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reverse_iterator
	rbegin() BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	rbegin() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reverse_iterator
	rend() BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	rend() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	cbegin() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_iterator
	cend() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	crbegin() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reverse_iterator
	crend() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool
	empty() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR size_type
	size() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_NODISCARD BKSGE_CONSTEXPR size_type
	max_size() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_CXX14_CONSTEXPR void
	swap(VectorBase& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value);

	BKSGE_CONSTEXPR VectorValue<T, N>
	as_array(void) const;

private:
	VectorValue<T, N>	m_value;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
};

/**
 *	@brief	swap
 */
template <typename T, std::size_t N>
BKSGE_CXX14_CONSTEXPR void
swap(VectorBase<T, N>& lhs, VectorBase<T, N>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs));

/**
 *	@brief	operator==
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR bool
operator==(VectorBase<T, N> const& lhs, VectorBase<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

template <typename T, std::size_t N>
BKSGE_CONSTEXPR bool
operator==(VectorBase<T, N> const& lhs, VectorValue<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	operator!=
 */
template <typename T, std::size_t N>
BKSGE_CONSTEXPR bool
operator!=(VectorBase<T, N> const& lhs, VectorBase<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

template <typename T, std::size_t N>
BKSGE_CONSTEXPR bool
operator!=(VectorBase<T, N> const& lhs, VectorValue<T, N> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits, typename T, std::size_t N>
std::basic_ostream<CharT, Traits>&
operator<<(
	std::basic_ostream<CharT, Traits>& os,
	VectorBase<T, N> const& rhs);

}	// namespace detail

}	// namespace math

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR T&
get(bksge::math::detail::VectorBase<T, N>& v) BKSGE_NOEXCEPT;

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CONSTEXPR T const&
get(bksge::math::detail::VectorBase<T, N> const& v) BKSGE_NOEXCEPT;

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR T&&
get(bksge::math::detail::VectorBase<T, N>&& v) BKSGE_NOEXCEPT;

template <std::size_t I, typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CONSTEXPR T const&&
get(bksge::math::detail::VectorBase<T, N> const&& v) BKSGE_NOEXCEPT;

}	// namespace bksge

namespace std
{

/**
 *	@brief	tuple_size
 */
template <typename T, std::size_t N>
struct tuple_size<bksge::math::detail::VectorBase<T, N>>
	: public bksge::integral_constant<std::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::math::detail::VectorBase<T, N>>
{
	static_assert(I < N, "VectorBase index out of bounds");
	using type = T;
};

}	// namespace std

#include <bksge/core/math/detail/vector_base_inl.hpp>

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_HPP
