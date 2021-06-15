/**
 *	@file	unit_test_fnd_config_deprecated.cpp
 *
 *	@brief	BKSGE_DEPRECATED のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4996)
BKSGE_WARNING_DISABLE_GCC("-Wattributes")
BKSGE_WARNING_DISABLE_GCC("-Wdeprecated-declarations")
BKSGE_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")

namespace bksge_config_deprecated_test
{

// 非推奨なクラス
class BKSGE_DEPRECATED("please use new_class class") old_class{};

// 非推奨な型の別名
//using old_type BKSGE_DEPRECATED("please use new_type type") = int;

// 非推奨な変数
BKSGE_DEPRECATED("please use new_variable variable")
int old_variable;

struct X
{
	// 非推奨な非静的メンバ変数
	BKSGE_DEPRECATED("please use new_member_variable")
	int old_member_variable;
};

// 非推奨な関数
BKSGE_DEPRECATED("please use new_func() function")
void old_func() {}

// 非推奨な列挙型
enum class BKSGE_DEPRECATED("please use new_enum") old_enum{};

template <typename T>
class class_templ;

// 非推奨なテンプレートの特殊化
template <>
class BKSGE_DEPRECATED("don't use class_templ<int> specialization") class_templ<int> {};

void func()
{
#if 1
	old_class c;
	(void)c;
//	old_type t;

	old_variable = 1;

	X x;
	x.old_member_variable = 1;
	(void)x;

	old_func();

	old_enum e;
	(void)e;

	class_templ<int> ct;
	(void)ct;
#endif
}

}	// namespace bksge_config_deprecated_test

BKSGE_WARNING_POP()
