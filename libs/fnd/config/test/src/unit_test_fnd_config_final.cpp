﻿/**
 *	@file	unit_test_fnd_config_final.cpp
 *
 *	@brief	BKSGE_FINAL のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

namespace bksge_config_final_test
{

class base
{
	virtual void final_func() BKSGE_FINAL;
	
	virtual void virtual_func();

	// NG, 仮想でない関数にfinal宣言することはできない
	//void non_virtual_func() BKSGE_FINAL;
};

class derived : public base
{
	// NG, finalとして宣言されている関数をオーバーライドすることはできない
	//void final_func();
	
	void virtual_func();
};

class non_base BKSGE_FINAL {};

// NG, finalとして宣言されているクラスを継承することはできない
//class derived2 : public non_base {};

}	// namespace bksge_config_final_test
