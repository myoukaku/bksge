/**
 *	@file	unwrap_ref_decay.hpp
 *
 *	@brief	unwrap_ref_decay クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_UNWRAP_REF_DECAY_HPP
#define BKSGE_FND_FUNCTIONAL_UNWRAP_REF_DECAY_HPP

#include <bksge/fnd/functional/unwrap_reference.hpp>
#include <bksge/fnd/type_traits/decay.hpp>

namespace bksge
{

template <typename T>
struct unwrap_ref_decay : public bksge::unwrap_reference<bksge::decay_t<T>>
{};

template <typename T>
using unwrap_ref_decay_t = typename unwrap_ref_decay<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_UNWRAP_REF_DECAY_HPP
