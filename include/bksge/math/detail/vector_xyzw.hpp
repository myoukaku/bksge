/**
 *	@file	vector_xyzw.hpp
 *
 *	@brief	VectorXYZW の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_DETAIL_VECTOR_XYZW_HPP
#define BKSGE_MATH_DETAIL_VECTOR_XYZW_HPP

#include <bksge/math/detail/vector_base.hpp>
#include <bksge/math/detail/def_helper_macros.hpp>
#include <bksge/config.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
class VectorXYZW;

template <typename T>
class VectorXYZW<T, 1> : public VectorBase<T, 1>
{
	using BaseType = VectorBase<T, 1>;
public:
	using BaseType::BaseType;

	BKSGE_MATH_NAMED_ACCESS(x, 0);
	BKSGE_MATH_DECLARE_SWIZZLE_OPERATOR((x));
};

template <typename T>
class VectorXYZW<T, 2> : public VectorBase<T, 2>
{
	using BaseType = VectorBase<T, 2>;
public:
	using BaseType::BaseType;

	BKSGE_MATH_NAMED_ACCESS(x, 0);
	BKSGE_MATH_NAMED_ACCESS(y, 1);
	BKSGE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y));
};

template <typename T>
class VectorXYZW<T, 3> : public VectorBase<T, 3>
{
	using BaseType = VectorBase<T, 3>;
public:
	using BaseType::BaseType;

	BKSGE_MATH_NAMED_ACCESS(x, 0);
	BKSGE_MATH_NAMED_ACCESS(y, 1);
	BKSGE_MATH_NAMED_ACCESS(z, 2);
	BKSGE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y)(z));
};

template <typename T>
class VectorXYZW<T, 4> : public VectorBase<T, 4>
{
	using BaseType = VectorBase<T, 4>;
public:
	using BaseType::BaseType;

	BKSGE_MATH_NAMED_ACCESS(x, 0);
	BKSGE_MATH_NAMED_ACCESS(y, 1);
	BKSGE_MATH_NAMED_ACCESS(z, 2);
	BKSGE_MATH_NAMED_ACCESS(w, 3);
	BKSGE_MATH_DECLARE_SWIZZLE_OPERATOR((x)(y)(z)(w));
};

}	// namespace detail

}	// namespace math

}	// namespace bksge

#include <bksge/math/detail/undef_helper_macros.hpp>

#endif // BKSGE_MATH_DETAIL_VECTOR_XYZW_HPP
