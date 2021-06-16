/**
 *	@file	tag.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TAG_HPP
#define BKSGE_FND_ITERATOR_TAG_HPP

#include <iterator>

namespace bksge
{

using std::input_iterator_tag;
using std::output_iterator_tag;
using std::forward_iterator_tag;
using std::bidirectional_iterator_tag;
using std::random_access_iterator_tag;

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 201806)
using std::contiguous_iterator_tag;
#else
struct contiguous_iterator_tag : public random_access_iterator_tag {};
#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TAG_HPP
