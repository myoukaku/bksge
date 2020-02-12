/**
 *	@file	operators.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEBUG_DETAIL_OPERATORS_HPP
#define BKSGE_FND_DEBUG_DETAIL_OPERATORS_HPP

#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <utility>	// declval

namespace bksge
{

namespace debug
{

namespace detail
{

namespace op
{

#define BKSGE_ASSERT_DETAIL_FOR_EACH_CONST_OP(action)\
	action(->*, MEMP)                 \
	action(* , MUL)                   \
	action(/ , DIV)                   \
	action(% , MOD)                   \
	action(+ , ADD)                   \
	action(- , SUB)                   \
	action(<<, LSH)                   \
	action(>>, RSH)                   \
	action(< , LT)                    \
	action(<=, LE)                    \
	action(> , GT)                    \
	action(>=, GE)                    \
	action(==, EQ)                    \
	action(!=, NE)                    \
	action(&& , AND)                  \
	action(|| , OR)                   \
	action(& , BAND)                  \
	action(^ , XOR)                   \
	action(| , BOR)                   \
/**/


#define BKSGE_ASSERT_DETAIL_DEFINE_CONST_OPER(oper, name)				\
template <typename Lhs, typename Rhs>				\
struct name											\
{													\
    using optype = decltype(std::declval<Lhs>() oper std::declval<Rhs>());	\
    using result_type = bksge::remove_reference_t<optype>;	\
                                                    \
    static result_type                              \
    eval(Lhs const& lhs, Rhs const& rhs)			\
    {                                               \
        return lhs oper rhs;                        \
    }                                               \
													\
	static char const* label(void)					\
	{												\
		return #oper;								\
	}												\
};                                                  \
/**/

BKSGE_ASSERT_DETAIL_FOR_EACH_CONST_OP(BKSGE_ASSERT_DETAIL_DEFINE_CONST_OPER)

#undef BKSGE_ASSERT_DETAIL_DEFINE_CONST_OPER

}	// namespace op

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_FND_DEBUG_DETAIL_OPERATORS_HPP
