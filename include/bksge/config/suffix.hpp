/**
 *	@file	suffix.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_HPP
#define BKSGE_CONFIG_SUFFIX_HPP

#include <bksge/config/suffix/alignas.hpp>
#include <bksge/config/suffix/alignof.hpp>
#include <bksge/config/suffix/carries_dependency.hpp>
#include <bksge/config/suffix/constexpr.hpp>
#include <bksge/config/suffix/current_function.hpp>
#include <bksge/config/suffix/deprecated.hpp>
#include <bksge/config/suffix/endian.hpp>
#include <bksge/config/suffix/extern_template.hpp>
#include <bksge/config/suffix/fallthrough.hpp>
#include <bksge/config/suffix/final.hpp>
#include <bksge/config/suffix/inline_var.hpp>
#include <bksge/config/suffix/likely.hpp>
#include <bksge/config/suffix/nodiscard.hpp>
#include <bksge/config/suffix/noexcept.hpp>
#include <bksge/config/suffix/noreturn.hpp>
#include <bksge/config/suffix/override.hpp>
#include <bksge/config/suffix/pragma.hpp>
#include <bksge/config/suffix/unreachable.hpp>
#include <bksge/config/suffix/warning.hpp>

//#define BKSGE_HEADER_ONLY

#if defined(BKSGE_HEADER_ONLY)
#  define BKSGE_INLINE	inline
#else
#  define BKSGE_INLINE
#endif

#endif // BKSGE_CONFIG_SUFFIX_HPP
