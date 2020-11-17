/**
 *	@file	transform3.hpp
 *
 *	@brief	Transform3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_TRANSFORM3_HPP
#define BKSGE_CORE_MATH_TRANSFORM3_HPP

#include <bksge/core/math/fwd/transform3_fwd.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/quaternion.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/config.hpp>
#include <iosfwd>		// basic_ostream

namespace bksge
{

namespace math
{

/**
 *	@brief
 */
template <typename T>
class Transform3
{
public:
	using PositionType  = bksge::Vector3<T>;
	using RotationType  = bksge::Quaternion<T>;
	using ScaleType     = bksge::Scale3<T>;
	using Matrix4x4Type	= bksge::Matrix4x4<T>;

	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	Transform3(void) BKSGE_NOEXCEPT
		: m_position()
		, m_rotation(RotationType::Identity())
		, m_scale(ScaleType::Identity())
	{}

	/**
	 *	@brief	変換コンストラクタ
	 */
	template <
		typename U,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, U>::value
		>
	>
	BKSGE_CONSTEXPR
	Transform3(Transform3<U> const& rhs) BKSGE_NOEXCEPT
		: m_position(rhs.position())
		, m_rotation(rhs.rotation())
		, m_scale(rhs.scale())
	{}

	/**
	 *	@brief
	 */
	BKSGE_CONSTEXPR
	Transform3(
		PositionType const& position,
		RotationType const& rotation,
		ScaleType const& scale) BKSGE_NOEXCEPT
		: m_position(position)
		, m_rotation(rotation)
		, m_scale(scale)
	{}

	/**
	 *	@brief
	 */
	//BKSGE_CONSTEXPR Transform3(
	//	Matrix4x4Type const& matrix) BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR PositionType const&	position(void) const BKSGE_NOEXCEPT
	{
		return m_position;
	}

	BKSGE_CONSTEXPR RotationType const&	rotation(void) const BKSGE_NOEXCEPT
	{
		return m_rotation;
	}

	BKSGE_CONSTEXPR ScaleType const& scale(void) const BKSGE_NOEXCEPT
	{
		return m_scale;
	}

	BKSGE_CXX14_CONSTEXPR PositionType& position(void) BKSGE_NOEXCEPT
	{
		return m_position;
	}

	BKSGE_CXX14_CONSTEXPR RotationType& rotation(void) BKSGE_NOEXCEPT
	{
		return m_rotation;
	}

	BKSGE_CXX14_CONSTEXPR ScaleType& scale(void) BKSGE_NOEXCEPT
	{
		return m_scale;
	}

	BKSGE_CONSTEXPR Matrix4x4Type GetMatrix4x4(void) const
	{
		return Matrix4x4Type::Compose(
			m_position,
			m_scale,
			m_rotation);
	}

	BKSGE_CXX14_CONSTEXPR void swap(Transform3& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
	{
		bksge::ranges::swap(m_position, other.m_position);
		bksge::ranges::swap(m_scale,    other.m_scale);
		bksge::ranges::swap(m_rotation, other.m_rotation);
	}

private:
	PositionType		m_position;
	RotationType		m_rotation;
	ScaleType			m_scale;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_position);
		ar & BKSGE_SERIALIZATION_NVP(m_rotation);
		ar & BKSGE_SERIALIZATION_NVP(m_scale);
	}
};

/**
 *	@brief	operator==
 */
template <typename T>
BKSGE_CONSTEXPR bool
operator==(Transform3<T> const& lhs, Transform3<T> const& rhs) BKSGE_NOEXCEPT
{
	return
		lhs.position() == rhs.position() &&
		lhs.rotation() == rhs.rotation() &&
		lhs.scale()    == rhs.scale();
}

/**
 *	@brief	operator!=
 */
template <typename T>
BKSGE_CONSTEXPR bool
operator!=(Transform3<T> const& lhs, Transform3<T> const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Transform3<T> const& rhs)
{
	return
		os << "{ "
			<< rhs.position()  << ", "
			<< rhs.rotation()   << ", "
			<< rhs.scale()
		<< " }";
}

}	// namespace math

}	// namespace bksge

#include <bksge/fnd/functional/hash_combine.hpp>
#include <functional>
#include <cstddef>

namespace std
{

/**
 *	@brief	hash
 */
template <typename T>
struct hash<bksge::math::Transform3<T>>
{
	std::size_t operator()(bksge::math::Transform3<T> const& arg) const
	{
		return bksge::hash_combine(
			arg.position(),
			arg.rotation(),
			arg.scale());
	}
};

}	// namespace std

#endif // BKSGE_CORE_MATH_TRANSFORM3_HPP
