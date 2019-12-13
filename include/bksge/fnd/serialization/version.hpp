/**
 *	@file	version.hpp
 *
 *	@brief	version の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_VERSION_HPP
#define BKSGE_FND_SERIALIZATION_VERSION_HPP

#include <cstdint>

namespace bksge
{

namespace serialization
{

using version_t = std::uint32_t;

namespace detail
{

template <typename T>
struct Version
{
	static const version_t value = 0;
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#define BKSGE_SERIALIZATION_CLASS_VERSION(TYPE, VERSION_NUMBER)	\
namespace bksge { namespace serialization { namespace detail {	\
template <> struct Version<TYPE>	                            \
{	                                                            \
	static const version_t value = VERSION_NUMBER;	            \
};	                                                            \
}}}	                                                            \
/**/

#endif // BKSGE_FND_SERIALIZATION_VERSION_HPP
