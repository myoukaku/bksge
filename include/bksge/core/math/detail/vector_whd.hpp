/**
 *	@file	vector_whd.hpp
 *
 *	@brief	VectorWHD の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_WHD_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_WHD_HPP

#include <bksge/core/math/detail/vector_base.hpp>
#include <bksge/core/math/detail/def_helper_macros.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, bksge::size_t N>
class VectorWHD;

template <typename T>
class VectorWHD<T, 1> : public bksge::math::detail::VectorBase<T, 1>
{
	using BaseType = bksge::math::detail::VectorBase<T, 1>;
public:
	using BaseType::BaseType;

	BKSGE_CORE_MATH_NAMED_ACCESS(w, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(width, 0);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((w));
};

template <typename T>
class VectorWHD<T, 2> : public bksge::math::detail::VectorBase<T, 2>
{
	using BaseType = bksge::math::detail::VectorBase<T, 2>;
public:
	using BaseType::BaseType;

	BKSGE_CORE_MATH_NAMED_ACCESS(w, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(h, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(width,  0);
	BKSGE_CORE_MATH_NAMED_ACCESS(height, 1);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((w)(h));
};

template <typename T>
class VectorWHD<T, 3> : public bksge::math::detail::VectorBase<T, 3>
{
	using BaseType = bksge::math::detail::VectorBase<T, 3>;
public:
	using BaseType::BaseType;

	BKSGE_CORE_MATH_NAMED_ACCESS(w, 0);
	BKSGE_CORE_MATH_NAMED_ACCESS(h, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(d, 2);
	BKSGE_CORE_MATH_NAMED_ACCESS(width,  0);
	BKSGE_CORE_MATH_NAMED_ACCESS(height, 1);
	BKSGE_CORE_MATH_NAMED_ACCESS(depth,  2);
	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR((w)(h)(d));
};

}	// namespace detail

}	// namespace math

}	// namespace bksge

#include <bksge/core/math/detail/undef_helper_macros.hpp>

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_WHD_HPP
