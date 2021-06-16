/**
 *	@file	expression_base.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEBUG_DETAIL_EXPRESSION_BASE_HPP
#define BKSGE_FND_DEBUG_DETAIL_EXPRESSION_BASE_HPP

#include <bksge/fnd/debug/detail/binary_expression_fwd.hpp>
#include <bksge/fnd/debug/detail/value_expression_fwd.hpp>
#include <bksge/fnd/debug/detail/operators.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace debug
{

namespace detail
{

template <typename ExprType, typename ValType>
class expression_base
{
public:

#define BKSGE_ASSERT_DETAIL_ADD_OP_SUPPORT(oper, name)	\
    template <typename T> BKSGE_CONSTEXPR	\
    binary_expression<ExprType, value_expression<T>, op::name<ValType, bksge::remove_reference_t<T>>>  \
    operator oper(T&& rhs) const                                 \
    {                                                           \
        return binary_expression<ExprType, value_expression<T>, op::name<ValType, bksge::remove_reference_t<T>>> \
            (bksge::forward<ExprType const>(*static_cast<ExprType const*>(this)),                \
              value_expression<T>(bksge::forward<T>(rhs)));                           \
    }                                                           \
/**/

	BKSGE_ASSERT_DETAIL_FOR_EACH_CONST_OP(BKSGE_ASSERT_DETAIL_ADD_OP_SUPPORT)

#undef BKSGE_ASSERT_DETAIL_ADD_OP_SUPPORT
};

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_FND_DEBUG_DETAIL_EXPRESSION_BASE_HPP
