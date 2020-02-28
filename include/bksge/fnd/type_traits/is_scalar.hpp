/**
 *	@file	is_scalar.hpp
 *
 *	@brief	is_scalar の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_SCALAR_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_SCALAR_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがスカラ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_scalarは、型Tがスカラ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	スカラ型は、算術型、列挙型、ポインタ型、メンバポインタ型、nullptr_t、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_scalar
	: public detail::constant_wrapper<
		std::is_scalar<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_SCALAR_HPP
