/**
 *	@file	vector_value.hpp
 *
 *	@brief	VectorValue の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_VALUE_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_VALUE_HPP

#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
class VectorValue
{
public:
	using size_type              = std::size_t;
	using reference              = T&;
	using const_reference        = T const&;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reference
	operator[](size_type pos) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems[pos];
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reference
	operator[](size_type pos) const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems[pos];
	}

public:
	T	m_elems[N];

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_elems);
	}
};

}	// namespace detail

}	// namespace math

}	// namespace bksge

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <functional>
#include <cstddef>

namespace std
{

/**
 *	@brief	hash
 */
template <typename T, std::size_t N>
struct hash<bksge::math::detail::VectorValue<T, N>>
{
private:
	template <typename Vector, std::size_t... Is>
	std::size_t hash_impl(Vector const& arg, bksge::index_sequence<Is...>) const
	{
		return bksge::hash_combine(arg[Is]...);
	}

public:
	std::size_t operator()(bksge::math::detail::VectorValue<T, N> const& arg) const
	{
		return hash_impl(arg, bksge::make_index_sequence<N>());
	}
};

}	// namespace std

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_VALUE_HPP
