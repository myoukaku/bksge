/**
 *	@file	transform3_inl.hpp
 *
 *	@brief	Transform3 の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_INL_TRANSFORM3_INL_HPP
#define BKSGE_CORE_MATH_INL_TRANSFORM3_INL_HPP

#include <bksge/core/math/transform3.hpp>
//#include <bksge/foundation/serialization/nvp.hpp>

namespace bksge
{

namespace math
{

template <typename T>
inline BKSGE_CONSTEXPR
Transform3<T>::Transform3(void) BKSGE_NOEXCEPT_OR_NOTHROW
	: m_position(PositionType::Zero())
	, m_rotation(RotationType::Identity())
	, m_scale(ScaleType::Identity())
{
}

template <typename T>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Transform3<T>::Transform3(Transform3<U> const& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
	: m_position(rhs.position())
	, m_rotation(rhs.rotation())
	, m_scale(rhs.scale())
{
}

template <typename T>
inline BKSGE_CONSTEXPR
Transform3<T>::Transform3(
	PositionType const& position,
	RotationType const& rotation,
	ScaleType const& scale) BKSGE_NOEXCEPT_OR_NOTHROW
	: m_position(position)
	, m_rotation(rotation)
	, m_scale(scale)
{
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Transform3<T>::position(void) const -> PositionType const&
{
	return m_position;
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Transform3<T>::rotation(void) const -> RotationType const&
{
	return m_rotation;
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Transform3<T>::scale(void) const -> ScaleType const&
{
	return m_scale;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR auto
Transform3<T>::position(void) -> PositionType&
{
	return m_position;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR auto
Transform3<T>::rotation(void) -> RotationType&
{
	return m_rotation;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR auto
Transform3<T>::scale(void) -> ScaleType&
{
	return m_scale;
}

template <typename T>
inline BKSGE_CONSTEXPR auto
Transform3<T>::GetMatrix4x4(void) const -> Matrix4x4Type
{
	return Matrix4x4Type::Compose(
		m_position,
		m_scale,
		m_rotation);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
Transform3<T>::swap(Transform3& other)
	BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
{
	using std::swap;
	swap(m_position, other.m_position);
	swap(m_scale,    other.m_scale);
	swap(m_rotation, other.m_rotation);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
swap(Transform3<T>& lhs, Transform3<T>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(Transform3<T> const& lhs, Transform3<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return
		lhs.position() == rhs.position() &&
		lhs.rotation() == rhs.rotation() &&
		lhs.scale()    == rhs.scale();
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(Transform3<T> const& lhs, Transform3<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename T>
inline std::basic_ostream<CharT, Traits>&
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

#endif // BKSGE_CORE_MATH_INL_TRANSFORM3_INL_HPP
