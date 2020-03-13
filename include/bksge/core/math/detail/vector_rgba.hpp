/**
 *	@file	vector_rgba.hpp
 *
 *	@brief	VectorRGBA の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_RGBA_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_RGBA_HPP

#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/def_helper_macros.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
class VectorRGBA;

template <typename T>
class VectorRGBA<T, 1> : public bksge::math::detail::VectorBase<T, 1>
{
	using BaseType = bksge::math::detail::VectorBase<T, 1>;
public:
	using BaseType::BaseType;

	BKSGE_CORE_MATH_NAMED_ACCESS(r, 0);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((r));
};

template <typename T>
class VectorRGBA<T, 2> : public bksge::math::detail::VectorBase<T, 2>
{
	using BaseType = bksge::math::detail::VectorBase<T, 2>;
public:
	using BaseType::BaseType;

	BKSGE_CORE_MATH_NAMED_ACCESS(r, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(g, 1);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((r)(g));
};

template <typename T>
class VectorRGBA<T, 3> : public bksge::math::detail::VectorBase<T, 3>
{
	using BaseType = bksge::math::detail::VectorBase<T, 3>;
public:
	using BaseType::BaseType;

	BKSGE_CORE_MATH_NAMED_ACCESS(r, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(g, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(b, 2);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((r)(g)(b));
};

template <typename T>
class VectorRGBA<T, 4> : public bksge::math::detail::VectorBase<T, 4>
{
	using BaseType = bksge::math::detail::VectorBase<T, 4>;
public:
	using BaseType::BaseType;

	BKSGE_CORE_MATH_NAMED_ACCESS(r, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(g, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(b, 2);
	BKSGE_CORE_MATH_NAMED_ACCESS(a, 3);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((r)(g)(b)(a));
};

}	// namespace detail

}	// namespace math

}	// namespace bksge

#include <bksge/core/math/detail/undef_helper_macros.hpp>

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_RGBA_HPP
