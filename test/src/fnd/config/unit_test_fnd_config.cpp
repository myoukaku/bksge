﻿/**
 *	@file	unit_test_fnd_config.cpp
 *
 *	@brief	config のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <bksge/fnd/preprocessor/stringize.hpp>

#pragma message("BKSGE_PLATFORM         = " BKSGE_PLATFORM)
#pragma message("BKSGE_ARCHITECTURE     = " BKSGE_ARCHITECTURE)
#pragma message("BKSGE_COMPILER         = " BKSGE_COMPILER)
#pragma message("BKSGE_COMPILER_VERSION = " BKSGE_PP_STRINGIZE(BKSGE_COMPILER_VERSION))
#pragma message("BKSGE_STDLIB           = " BKSGE_STDLIB)
#pragma message("BKSGE_CXX_STANDARD     = " BKSGE_PP_STRINGIZE(BKSGE_CXX_STANDARD))
