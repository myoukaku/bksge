﻿/**
 *	@file	current_function.hpp
 *
 *	@brief	BKSGE_CURRENT_FUNCTION の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_CURRENT_FUNCTION_HPP
#define BKSGE_FND_CONFIG_SUFFIX_CURRENT_FUNCTION_HPP

/**
 *	@brief	BKSGE_CURRENT_FUNCTION 関数名を取得します
 */

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)

# define BKSGE_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

# define BKSGE_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

# define BKSGE_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

# define BKSGE_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

# define BKSGE_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

# define BKSGE_CURRENT_FUNCTION __func__

#elif defined(__cplusplus) && (__cplusplus >= 201103)

# define BKSGE_CURRENT_FUNCTION __func__

#else

# define BKSGE_CURRENT_FUNCTION "(unknown)"

#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_CURRENT_FUNCTION_HPP