/**
 *	@file	unit_test_fnd_config.cpp
 *
 *	@brief	config のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

#define STRINGIZE(text) STRINGIZE_I(text)
#define STRINGIZE_I(text) #text

#pragma message("BKSGE_PLATFORM         = " BKSGE_PLATFORM)
#pragma message("BKSGE_ARCHITECTURE     = " BKSGE_ARCHITECTURE)
#pragma message("BKSGE_COMPILER         = " BKSGE_COMPILER)
#pragma message("BKSGE_COMPILER_VERSION = " STRINGIZE(BKSGE_COMPILER_VERSION))
#pragma message("BKSGE_STDLIB           = " BKSGE_STDLIB)
#pragma message("BKSGE_CXX_STANDARD     = " STRINGIZE(BKSGE_CXX_STANDARD))

#undef STRINGIZE
#undef STRINGIZE_I
