/**
 *	@file	tuple_sort_type.hpp
 *
 *	@brief	tuple_sort_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_SORT_TYPE_HPP
#define BKSGE_FND_TUPLE_TUPLE_SORT_TYPE_HPP

#include <bksge/fnd/tuple/fwd/tuple_sort_type_fwd.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	Tupleの要素をCompareに従って並べ替えたTuple型を取得する
 *
 *	Compareを指定しなかったときは、
 *	Tupleの各要素をTとすると、T::valueが昇順になるように並べ替える。
 */
template <typename Tuple, typename Compare>
struct tuple_sort_type;

/**
 *	@brief	tuple_sort_type でデフォルトで使われる比較演算
 */
struct value_less
{
	template <typename T1, typename T2>
	using type = std::integral_constant<bool, (T1::value < T2::value)>;
};

}	// namespace bksge

#include <bksge/fnd/tuple/inl/tuple_sort_type_inl.hpp>

#endif // BKSGE_FND_TUPLE_TUPLE_SORT_TYPE_HPP
