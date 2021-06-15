/**
 *	@file	is_bigint.hpp
 *
 *	@brief	is_bigint クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_IS_BIGINT_HPP
#define BKSGE_FND_BIGINT_DETAIL_IS_BIGINT_HPP

#include <bksge/fnd/bigint/fwd/basic_bigint_fwd.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
struct is_bigint
	: public bksge::false_type {};

template <bksge::size_t Bits, bool Signed>
struct is_bigint<bksge::basic_bigint<Bits, Signed>>
	: public bksge::true_type {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_IS_BIGINT_HPP
