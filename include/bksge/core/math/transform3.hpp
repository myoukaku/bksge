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
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/config.hpp>
#include <iosfwd>		// basic_ostream
#include <type_traits>

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
	Transform3(void) BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	変換コンストラクタ
	 */
	template <
		typename U,
		typename = bksge::enable_if_t<
			std::is_constructible<T, U>::value
		>
	>
	BKSGE_CONSTEXPR
	Transform3(Transform3<U> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief
	 */
	BKSGE_CONSTEXPR
	Transform3(
		PositionType const& position,
		RotationType const& rotation,
		ScaleType const& scale) BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief
	 */
	//BKSGE_CONSTEXPR Transform3(
	//	Matrix4x4Type const& matrix) BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_CONSTEXPR PositionType const&	position(void) const;
	BKSGE_CONSTEXPR RotationType const&	rotation(void) const;
	BKSGE_CONSTEXPR ScaleType const&	scale(void) const;

	BKSGE_CXX14_CONSTEXPR PositionType&		position(void);
	BKSGE_CXX14_CONSTEXPR RotationType&		rotation(void);
	BKSGE_CXX14_CONSTEXPR ScaleType&		scale(void);

	BKSGE_CONSTEXPR Matrix4x4Type		GetMatrix4x4(void) const;

	BKSGE_CXX14_CONSTEXPR void swap(Transform3& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value);

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
 *	@brief	swap
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR void
swap(Transform3<T>& lhs, Transform3<T>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs));

/**
 *	@brief	operator==
 */
template <typename T>
BKSGE_CONSTEXPR bool
operator==(Transform3<T> const& lhs, Transform3<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	operator!=
 */
template <typename T>
BKSGE_CONSTEXPR bool
operator!=(Transform3<T> const& lhs, Transform3<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Transform3<T> const& rhs);

}	// namespace math

}	// namespace bksge

#include <functional>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

/**
 *	@brief	hash
 */
template <typename T>
struct hash<bksge::math::Transform3<T>>
{
	bksge::size_t operator()(bksge::math::Transform3<T> const& arg) const
	{
		return bksge::hash_combine(
			arg.position(),
			arg.rotation(),
			arg.scale());
	}
};

}	// namespace std

#include <bksge/core/math/inl/transform3_inl.hpp>

#endif // BKSGE_CORE_MATH_TRANSFORM3_HPP
