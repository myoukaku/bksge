/**
 *	@file	extern_template.hpp
 *
 *	@brief	BKSGE_EXTERN_TEMPLATE の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SUFFIX_EXTERN_TEMPLATE_HPP
#define BKSGE_CONFIG_SUFFIX_EXTERN_TEMPLATE_HPP

#if !defined(BKSGE_EXTERN_TEMPLATE)
#	if defined(BKSGE_HAS_CXX11_EXTERN_TEMPLATE)
#		define BKSGE_EXTERN_TEMPLATE(...) extern template __VA_ARGS__
#	else
#		define BKSGE_EXTERN_TEMPLATE(...)
#		define BKSGE_NO_EXTERN_TEMPLATE
#	endif
#endif

#endif // BKSGE_CONFIG_SUFFIX_EXTERN_TEMPLATE_HPP
