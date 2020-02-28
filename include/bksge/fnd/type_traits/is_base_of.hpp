/**
 *	@file	is_base_of.hpp
 *
 *	@brief	is_base_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_BASE_OF_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_BASE_OF_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Baseが型Derivedの基底クラスか調べる。
 *
 *	@tparam		Base
 *	@tparam		Derived
 *
 *	@require	BaseとDerivedが非共用体のクラスであり、異なる型である場合(cv修飾は無視される)、
 *				Derivedは完全型でなければならない。
 *
 *	is_base_ofは、型Baseが型Derivedの基底クラス (cv修飾は無視される) である、もしくは2つが同じクラス型ならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	派生時のprivate、protected指定は、派生関係の判定に影響しない。
 */
template <typename Base, typename Derived>
struct is_base_of
	: public detail::constant_wrapper<
		std::is_base_of<Base, Derived>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_BASE_OF_HPP
