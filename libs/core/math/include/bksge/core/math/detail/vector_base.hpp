/**
 *	@file	vector_base.hpp
 *
 *	@brief	VectorBase の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_HPP

#include <bksge/core/math/detail/vector_functions.hpp>
#include <bksge/fnd/array/array.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <bksge/fnd/serialization/array.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

class VectorBaseTag{};

template <typename T, bksge::size_t N>
class VectorBase;

template <typename T>
class VectorBase<T, 4> : private VectorBaseTag, public bksge::array<T, 4>
{
private:
	using BaseType = bksge::array<T, 4>;
	
public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	VectorBase() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	VectorBase(T const& x) BKSGE_NOEXCEPT
		: BaseType{{x, x, x, x}}
	{}

	/**
	 *	@brief	値4つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	VectorBase(T const& v1, T const& v2, T const& v3, T const& v4) BKSGE_NOEXCEPT
		: BaseType{{v1, v2, v3, v4}}
	{}
};

template <typename T>
class VectorBase<T, 3> : private VectorBaseTag, public bksge::array<T, 3>
{
private:
	using BaseType = bksge::array<T, 3>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	VectorBase() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	VectorBase(T const& x) BKSGE_NOEXCEPT
		: BaseType{{x, x, x}}
	{}

	/**
	 *	@brief	値3つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	VectorBase(T const& v1, T const& v2, T const& v3) BKSGE_NOEXCEPT
		: BaseType{{v1, v2, v3}}
	{}
};

template <typename T>
class VectorBase<T, 2> : private VectorBaseTag, public bksge::array<T, 2>
{
private:
	using BaseType = bksge::array<T, 2>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	VectorBase() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	VectorBase(T const& x) BKSGE_NOEXCEPT
		: BaseType{{x, x}}
	{}

	/**
	 *	@brief	値2つのコンストラクタ
	 */
	BKSGE_CONSTEXPR
	VectorBase(T const& v1, T const& v2) BKSGE_NOEXCEPT
		: BaseType{{v1, v2}}
	{}
};

template <typename T>
class VectorBase<T, 1> : private VectorBaseTag, public bksge::array<T, 1>
{
private:
	using BaseType = bksge::array<T, 1>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	BKSGE_CONSTEXPR
	VectorBase() BKSGE_NOEXCEPT
		: BaseType{}
	{}

	/**
	 *	@brief	値1つのコンストラクタ
	 */
	explicit BKSGE_CONSTEXPR
	VectorBase(T const& x) BKSGE_NOEXCEPT
		: BaseType{{x}}
	{}
};

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept IsVectorLike = bksge::is_base_of<VectorBaseTag, T>::value;

#else

template <typename T>
using IsVectorLike = bksge::is_base_of<VectorBaseTag, T>;

#endif

/**
 *	@brief	unary operator+
 */
template <BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike)>
inline BKSGE_CONSTEXPR VectorLike
operator+(VectorLike const& v) BKSGE_NOEXCEPT
{
	return v;
}

/**
 *	@brief	unary operator-
 */
template <BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike)>
inline BKSGE_CONSTEXPR VectorLike
operator-(VectorLike const& v) BKSGE_NOEXCEPT
{
	return bksge::math::detail::negate_per_elem(v);
}

/**
 *	@brief	Vector += Vector
 */
template <BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike)>
inline BKSGE_CXX14_CONSTEXPR VectorLike&
operator+=(VectorLike& lhs, VectorLike const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs + rhs;
}

/**
 *	@brief	Vector + Vector -> Vector
 */
template <BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike)>
inline BKSGE_CONSTEXPR VectorLike
operator+(VectorLike const& lhs, VectorLike const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::plus_per_elem(lhs, rhs);
}

/**
 *	@brief	Vector -= Vector
 */
template <BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike)>
inline BKSGE_CXX14_CONSTEXPR VectorLike&
operator-=(VectorLike& lhs, VectorLike const& rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs - rhs;
}

/**
 *	@brief	Vector - Vector -> Vector
 */
template <BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike)>
inline BKSGE_CONSTEXPR VectorLike
operator-(VectorLike const& lhs, VectorLike const& rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::minus_per_elem(lhs, rhs);
}

/**
 *	@brief	Vector *= スカラー
 */
template <
	BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, U)
>
inline BKSGE_CXX14_CONSTEXPR VectorLike&
operator*=(VectorLike& lhs, U rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Vector * スカラー
 */
template <
	BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, U)
>
inline BKSGE_CONSTEXPR VectorLike
operator*(VectorLike const& lhs, U rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::multiplies_per_elem(lhs, VectorBase<U, bksge::tuple_size<VectorLike>::value>{rhs});
}

/**
 *	@brief	スカラー * Vector 
 */
template <
	BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, U)
>
inline BKSGE_CONSTEXPR VectorLike
operator*(U lhs, VectorLike const& rhs) BKSGE_NOEXCEPT
{
	return rhs * lhs;
}

/**
 *	@brief	Vector /= スカラー
 */
template <
	BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, U)
>
inline BKSGE_CXX14_CONSTEXPR VectorLike&
operator/=(VectorLike& lhs, U rhs) BKSGE_NOEXCEPT
{
	return lhs = lhs / rhs;
}

/**
 *	@brief	Vector / スカラー
 */
template <
	BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, U)
>
inline BKSGE_CONSTEXPR VectorLike
operator/(VectorLike const& lhs, U rhs) BKSGE_NOEXCEPT
{
	return bksge::math::detail::divides_per_elem(lhs, VectorBase<U, bksge::tuple_size<VectorLike>::value>{rhs});
}

/**
 *	@brief	Lerp
 */
template <
	BKSGE_REQUIRES_PARAM(IsVectorLike, VectorLike),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, U)
>
inline BKSGE_CONSTEXPR VectorLike
Lerp(VectorLike const& from, VectorLike const& to, U const& t) BKSGE_NOEXCEPT
{
	return bksge::math::detail::lerp_per_elem(from, to, t);
}

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits, typename T, bksge::size_t N>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(
	bksge::basic_ostream<CharT, Traits>& os,
	VectorBase<T, N> const& rhs)
{
	os << "{ ";

	for (bksge::size_t i = 0; i < N; ++i)
	{
		os << rhs[i];

		if (i < (N - 1))
		{
			os << ", ";
		}
	}

	os << " }";

	return os;
}

}	// namespace detail

}	// namespace math

template <bksge::size_t I, typename T, bksge::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR T&
get(bksge::math::detail::VectorBase<T, N>& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "Vector index out of bounds");
	return v[I];
}

template <bksge::size_t I, typename T, bksge::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR T const&
get(bksge::math::detail::VectorBase<T, N> const& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "Vector index out of bounds");
	return v[I];
}

template <bksge::size_t I, typename T, bksge::size_t N>
BKSGE_NODISCARD inline BKSGE_CXX14_CONSTEXPR T&&
get(bksge::math::detail::VectorBase<T, N>&& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "Vector index out of bounds");
	return bksge::move(v[I]);
}

template <bksge::size_t I, typename T, bksge::size_t N>
BKSGE_NODISCARD inline BKSGE_CONSTEXPR T const&&
get(bksge::math::detail::VectorBase<T, N> const&& v) BKSGE_NOEXCEPT
{
	static_assert(I < N, "Vector index out of bounds");
	return bksge::move(v[I]);
}

}	// namespace bksge

#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>

namespace BKSGE_TUPLE_NAMESPACE
{

/**
 *	@brief	tuple_size
 */
template <typename T, bksge::size_t N>
struct tuple_size<bksge::math::detail::VectorBase<T, N>>
	: public bksge::integral_constant<bksge::size_t, N>
{};

/**
 *	@brief	tuple_element
 */
template <bksge::size_t I, typename T, bksge::size_t N>
struct tuple_element<I, bksge::math::detail::VectorBase<T, N>>
{
	static_assert(I < N, "Vector index out of bounds");
	using type = T;
};

}	// namespace BKSGE_TUPLE_NAMESPACE

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/functional/hash.hpp>

namespace BKSGE_HASH_NAMESPACE
{

/**
 *	@brief	hash
 */
template <typename T, bksge::size_t N>
struct hash<bksge::math::detail::VectorBase<T, N>>
{
private:
	template <bksge::size_t... Is>
	bksge::size_t hash_impl(bksge::math::detail::VectorBase<T, N> const& arg, bksge::index_sequence<Is...>) const
	{
		return bksge::hash_combine(arg[Is]...);
	}

public:
	bksge::size_t operator()(bksge::math::detail::VectorBase<T, N> const& arg) const
	{
		return hash_impl(arg, bksge::make_index_sequence<N>());
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_BASE_HPP
