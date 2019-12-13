/**
 *	@file	def_helper_macros.hpp
 *
 *	@brief	BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR の定義
 *
 *	@author	myoukaku
 */

// NO INCLUDE GUARD

#include <bksge/core/math/detail/vector_value.hpp>
#include <bksge/fnd/preprocessor/seq/cat.hpp>
#include <bksge/fnd/preprocessor/seq/elem.hpp>
#include <bksge/fnd/preprocessor/seq/size.hpp>
#include <bksge/fnd/preprocessor/seq/for_each_product.hpp>
#include <bksge/fnd/preprocessor/punctuation/comma_if.hpp>
#include <bksge/fnd/preprocessor/repetition/repeat.hpp>
#include <bksge/fnd/config.hpp>

#define BKSGE_CORE_MATH_NAMED_ACCESS(Name, I)	            \
	BKSGE_CXX14_CONSTEXPR typename BaseType::reference	\
	Name(void) BKSGE_NOEXCEPT	                        \
	{	                                                \
		return (*this)[I];	                            \
	}	                                                \
		                                                \
	BKSGE_CONSTEXPR typename BaseType::const_reference	\
	Name(void) const BKSGE_NOEXCEPT	                    \
	{	                                                \
		return (*this)[I];	                            \
	}

#define BKSGE_CORE_MATH_SWIZZLE_ELEM(z, n, data)			        \
	BKSGE_PP_COMMA_IF(n) this->BKSGE_PP_SEQ_ELEM(n, data)()

#define BKSGE_CORE_MATH_SWIZZLE_BODY(r, seq)	                                        \
	BKSGE_CONSTEXPR bksge::math::detail::VectorValue<T, BKSGE_PP_SEQ_SIZE(seq)>	\
	BKSGE_PP_SEQ_CAT(seq)(void) const BKSGE_NOEXCEPT	                        \
	{	                                                                        \
		return bksge::math::detail::VectorValue<T, BKSGE_PP_SEQ_SIZE(seq)>{{	\
				BKSGE_PP_REPEAT(	                                            \
					BKSGE_PP_SEQ_SIZE(seq),	                                    \
					BKSGE_CORE_MATH_SWIZZLE_ELEM,	                                \
					seq) }};	                                                \
	}

#define BKSGE_CORE_MATH_DECLARE_SWIZZLE_OPERATOR(seq)									\
	BKSGE_PP_SEQ_FOR_EACH_PRODUCT(BKSGE_CORE_MATH_SWIZZLE_BODY, (seq)(seq)(seq)(seq))	\
	BKSGE_PP_SEQ_FOR_EACH_PRODUCT(BKSGE_CORE_MATH_SWIZZLE_BODY, (seq)(seq)(seq))		    \
	BKSGE_PP_SEQ_FOR_EACH_PRODUCT(BKSGE_CORE_MATH_SWIZZLE_BODY, (seq)(seq))
