/**
 *	@file	deduce_visit_result.hpp
 *
 *	@brief	DeduceVisitResult の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_DEDUCE_VISIT_RESULT_HPP
#define BKSGE_FND_VARIANT_DETAIL_DEDUCE_VISIT_RESULT_HPP

namespace bksge
{

namespace variant_detail
{

// Used to enable deduction (and same-type checking) for std::visit:
template <typename T>
struct DeduceVisitResult { using type = T; };

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_DEDUCE_VISIT_RESULT_HPP
