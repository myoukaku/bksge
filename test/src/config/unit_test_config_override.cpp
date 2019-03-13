/**
 *	@file	unit_test_config_override.cpp
 *
 *	@brief	BKSGE_OVERRIDE のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>

namespace bksge_config_override_test
{

class base
{
	virtual void final_func() BKSGE_FINAL;
	
	virtual void virtual_func();

	virtual void virtual_func2();

	void non_virtual_func();
};

class derived : public base
{
	// NG, finalとして宣言されている関数をオーバーライドすることはできない
	//void final_func() BKSGE_OVERRIDE;
	
	// OK
	void virtual_func() BKSGE_OVERRIDE;

	// NG, 基底クラスの関数と引数が違っており、オーバーライドできていない
	//void virtual_func2(int) BKSGE_OVERRIDE;

	// NG, 基底クラスの関数ではないので、オーバーライドできていない
	//void func() BKSGE_OVERRIDE;

	// NG, 基底クラスの関数は仮想ではないので、オーバーライドできていない
	//void non_virtual_func() BKSGE_OVERRIDE;
};

}	// namespace bksge_config_override_test
