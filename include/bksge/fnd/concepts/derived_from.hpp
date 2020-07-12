/**
 *	@file	derived_from.hpp
 *
 *	@brief	derived_from の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DERIVED_FROM_HPP
#define BKSGE_FND_CONCEPTS_DERIVED_FROM_HPP

#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/add_cv.hpp>
#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Derived, typename Base>
concept derived_from =
	bksge::is_base_of<Base, Derived>::value &&
	bksge::is_convertible<const volatile Derived*, const volatile Base*>::value;

#endif

template <typename Derived, typename Base>
struct derived_from_t
	: public bksge::conjunction<
		bksge::is_base_of<Base, Derived>,
		bksge::is_convertible<
			bksge::add_pointer_t<bksge::add_cv_t<Derived>>,
			bksge::add_pointer_t<bksge::add_cv_t<Base>>
		>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DERIVED_FROM_HPP
