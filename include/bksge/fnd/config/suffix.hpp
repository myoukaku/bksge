/**
 *	@file	suffix.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_HPP
#define BKSGE_FND_CONFIG_SUFFIX_HPP

#include <bksge/fnd/config/suffix/alignas.hpp>
#include <bksge/fnd/config/suffix/alignof.hpp>
#include <bksge/fnd/config/suffix/carries_dependency.hpp>
#include <bksge/fnd/config/suffix/constexpr.hpp>
#include <bksge/fnd/config/suffix/current_function.hpp>
#include <bksge/fnd/config/suffix/deprecated.hpp>
#include <bksge/fnd/config/suffix/endian.hpp>
#include <bksge/fnd/config/suffix/extern_template.hpp>
#include <bksge/fnd/config/suffix/fallthrough.hpp>
#include <bksge/fnd/config/suffix/final.hpp>
#include <bksge/fnd/config/suffix/inline_var.hpp>
#include <bksge/fnd/config/suffix/likely.hpp>
#include <bksge/fnd/config/suffix/nodiscard.hpp>
#include <bksge/fnd/config/suffix/noexcept.hpp>
#include <bksge/fnd/config/suffix/noreturn.hpp>
#include <bksge/fnd/config/suffix/override.hpp>
#include <bksge/fnd/config/suffix/pragma.hpp>
#include <bksge/fnd/config/suffix/unreachable.hpp>
#include <bksge/fnd/config/suffix/warning.hpp>

//#define BKSGE_HEADER_ONLY

#if defined(BKSGE_HEADER_ONLY)
#  define BKSGE_INLINE	inline
#else
#  define BKSGE_INLINE
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_HPP
