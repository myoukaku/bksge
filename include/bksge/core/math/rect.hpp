/**
 *	@file	rect.hpp
 *
 *	@brief	Rect の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_RECT_HPP
#define BKSGE_CORE_MATH_RECT_HPP

#include <bksge/core/math/fwd/rect_fwd.hpp>
#include <bksge/core/math/fwd/vector2_fwd.hpp>
#include <bksge/core/math/fwd/size2_fwd.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/config.hpp>
#include <iosfwd>		// basic_ostream

namespace bksge
{

namespace math
{

template <typename T>
class Rect
{
public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 *
	 *	全て0に初期化します。
	 */
	BKSGE_CONSTEXPR Rect(void)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	指定した2つの点をちょうど格納できる矩形を求めます
	 */
	BKSGE_CXX14_CONSTEXPR Rect(Vector2<T> const& p1, Vector2<T> const& p2)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	/**
	 *	@brief	左上の座標と幅と高さを指定するコンストラクタです
	 */
	BKSGE_CXX14_CONSTEXPR Rect(Vector2<T> const& pos, Size2<T> const& size)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	template <typename U>
	BKSGE_CONSTEXPR Rect(Rect<U> const& rhs)
		BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_CONSTEXPR T left(void) const;
	BKSGE_CONSTEXPR T top(void) const;
	BKSGE_CONSTEXPR T right(void) const;
	BKSGE_CONSTEXPR T bottom(void) const;

	BKSGE_CONSTEXPR T width(void) const;
	BKSGE_CONSTEXPR T height(void) const;

	BKSGE_NODISCARD BKSGE_CONSTEXPR T const*
	data() const BKSGE_NOEXCEPT_OR_NOTHROW;

	BKSGE_CXX14_CONSTEXPR void swap(Rect& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value);

private:
	struct inter_ctor_tag {};

	BKSGE_CXX14_CONSTEXPR
	Rect(inter_ctor_tag, T l, T t, T r, T b)
		BKSGE_NOEXCEPT_OR_NOTHROW;

private:
	T	 m_left;		///< 左
	T	 m_top;			///< 上
	T	 m_right;		///< 右
	T	 m_bottom;		///< 下

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_left);
		ar & BKSGE_SERIALIZATION_NVP(m_top);
		ar & BKSGE_SERIALIZATION_NVP(m_right);
		ar & BKSGE_SERIALIZATION_NVP(m_bottom);
	}
};

/**
 *	@brief	swap
 */
template <typename T>
BKSGE_CXX14_CONSTEXPR void
swap(Rect<T>& lhs, Rect<T>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs));

/**
 *	@brief	operator==
 */
template <typename T>
BKSGE_CONSTEXPR bool
operator==(Rect<T> const& lhs, Rect<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	operator!=
 */
template <typename T>
BKSGE_CONSTEXPR bool
operator!=(Rect<T> const& lhs, Rect<T> const& rhs)
BKSGE_NOEXCEPT_OR_NOTHROW;

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Rect<T> const& rhs);

}	// namespace math

}	// namespace bksge

#include <bksge/core/math/inl/rect_inl.hpp>

#include <functional>
#include <cstddef>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

template <typename T>
struct hash<bksge::math::Rect<T>>
{
	std::size_t operator()(bksge::math::Rect<T> const& arg) const
	{
		return bksge::hash_combine(
			arg.left(),
			arg.top(),
			arg.right(),
			arg.bottom());
	}
};

}	// namespace std

#endif // BKSGE_CORE_MATH_RECT_HPP
