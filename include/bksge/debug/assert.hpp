/**
 *	@file	assert.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

// NO INCLUDE GUARD

#undef BKSGE_ASSERT
#undef BKSGE_ASSERT_MSG

#if defined(BKSGE_DISABLE_ASSERTS)

#	define BKSGE_ASSERT(expr)          ((void)0)
#	define BKSGE_ASSERT_MSG(expr, msg) ((void)0)

#else

#	include <bksge/debug/detail/seed.hpp>
#	include <bksge/debug/detail/binary_expression.hpp>
#	include <bksge/debug/detail/value_expression.hpp>
#	include <bksge/debug/detail/operators.hpp>
#	include <bksge/debug/detail/assertion_check.hpp>
#	include <bksge/config.hpp>

#	define BKSGE_ASSERT(expr)                     \
	BKSGE_ASSERT_MSG(expr, "")                    \
	/**/

#	define BKSGE_ASSERT_MSG(expr, msg)            \
	((void)bksge::debug::detail::assertion_check( \
		(expr),                                   \
		__FILE__,                                 \
		__LINE__,                                 \
		BKSGE_CURRENT_FUNCTION,                   \
		#expr,                                    \
		bksge::debug::detail::seed()->*expr,      \
		msg))                                     \
	/**/

#endif
