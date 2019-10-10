/**
 *	@file	unit_test_config.cpp
 *
 *	@brief	config のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <bksge/preprocessor/stringize.hpp>

#pragma message("BKSGE_PLATFORM     = " BKSGE_PLATFORM)
#pragma message("BKSGE_ARCHITECTURE = " BKSGE_ARCHITECTURE)
#pragma message("BKSGE_COMPILER     = " BKSGE_COMPILER)
#pragma message("BKSGE_STDLIB       = " BKSGE_STDLIB)
#pragma message("BKSGE_CXX_STANDARD = " BKSGE_PP_STRINGIZE(BKSGE_CXX_STANDARD))
