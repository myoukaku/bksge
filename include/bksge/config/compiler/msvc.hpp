/**
 *	@file	msvc.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_COMPILER_MSVC_HPP
#define BKSGE_CONFIG_COMPILER_MSVC_HPP

#define BKSGE_MSVC _MSC_VER

#if _MSC_FULL_VER > 100000000
#  define BKSGE_MSVC_FULL_VER _MSC_FULL_VER
#else
#  define BKSGE_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#endif

#define BKSGE_COMPILER "Microsoft Visual C++"
#define BKSGE_COMPILER_VERSION BKSGE_MSVC_FULL_VER

#pragma warning(disable : 4503) // 修飾された名前の長さが限界を超えました。名前は切り捨てられます。

// pragma once
#define BKSGE_HAS_PRAGMA_ONCE

#if _MSC_FULL_VER < 180020827
#  define BKSGE_NO_FENV_H
#endif

#if _MSC_VER < 1400
// although a conforming signature for swprint exists in VC7.1
// it appears not to actually work:
#  define BKSGE_NO_SWPRINTF
#endif

#if _MSC_VER < 1500  // 140X == VC++ 8.0
#  define BKSGE_NO_MEMBER_TEMPLATE_FRIENDS
#endif

#if _MSC_VER < 1600  // 150X == VC++ 9.0
   // A bug in VC9:
#  define BKSGE_NO_ADL_BARRIER
#endif

// intrinsic wchar_t
#if !defined(_NATIVE_WCHAR_T_DEFINED)
#  define BKSGE_NO_INTRINSIC_WCHAR_T
#endif

//
// check for exception handling support:
#if !defined(_CPPUNWIND) && !defined(BKSGE_NO_EXCEPTIONS)
#  define BKSGE_NO_EXCEPTIONS
#endif

#if (_MSC_VER >= 1400) && !defined(_DEBUG)
#   define BKSGE_HAS_NRVO
#endif

#if _MSC_VER >= 1600  // 160X == VC++ 10.0
#  define BKSGE_HAS_PRAGMA_DETECT_MISMATCH
#endif

//
// disable Win32 API's if compiler extensions are
// turned off:
//
#if !defined(_MSC_EXTENSIONS) && !defined(BKSGE_DISABLE_WIN32)
#  define BKSGE_DISABLE_WIN32
#endif

// RTTI support
#if !defined(_CPPRTTI) && !defined(BKSGE_NO_RTTI)
#  define BKSGE_NO_RTTI
#endif

// BKSGE_CXX_STANDARD
#if !defined(BKSGE_CXX_STANDARD)
#  if _MSVC_LANG > 201703L
#    define BKSGE_CXX_STANDARD 20
#  elif _MSVC_LANG >= 201703L
#    define BKSGE_CXX_STANDARD 17
#  elif _MSVC_LANG >= 201402L
#    define BKSGE_CXX_STANDARD 14
#  elif  _MSVC_LANG >= 201103L
#    define BKSGE_CXX_STANDARD 11
#  else
#    define BKSGE_CXX_STANDARD  3
#  endif
#endif  // BKSGE_CXX_STANDARD

#if (_MSC_VER >= 1600)
#  define BKSGE_HAS_STDINT_H
#endif

// Visual Studio 2003 (Visual C++ 7.1)
#if (_MSC_VER >= 1400)
#  define BKSGE_HAS_CXX11_EXTERN_TEMPLATE					// テンプレートのインスタンス化抑止
#  define BKSGE_HAS_CXX11_LONG_LONG							// long long型
#endif

// Visual Studio 2005 (Visual C++ 8)
#if (_MSC_VER >= 1500)
#  define BKSGE_HAS_CXX11_VARIADIC_MACROS					// 可変引数マクロ
#  define BKSGE_HAS_CXX11_RIGHT_ANGLE_BRACKETS				// テンプレートの右山カッコ
#  define BKSGE_HAS_CXX11_OVERRIDE							// override
#endif

// Visual Studio 2010 (Visual C++ 10)
#if (_MSC_VER >= 1600)
#  define BKSGE_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS			// ローカル型と無名型をテンプレート引数として使用することを許可
#  define BKSGE_HAS_CXX11_AUTO_DECLARATIONS					// 型推論
#  define BKSGE_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS		// friend宣言できる対象を拡張
#  define BKSGE_HAS_CXX11_STATIC_ASSERT						// コンパイル時アサート
#  define BKSGE_HAS_CXX11_NULLPTR							// nullptr
#  define BKSGE_HAS_CXX11_TRAILING_RETURN_TYPE				// 戻り値の型を後置する関数宣言構文
#endif

// Visual Studio 2012 (Visual C++ 11)
#if (_MSC_VER >= 1700)
#  define BKSGE_HAS_CXX11_LAMBDAS							// ラムダ式
#  define BKSGE_HAS_CXX11_DECLTYPE							// 式の型を取得
#  define BKSGE_HAS_CXX11_FINAL								// final
#  define BKSGE_HAS_CXX11_RANGE_BASED_FOR					// 範囲for文
#  define BKSGE_HAS_CXX11_SCOPED_ENUMS						// スコープを持つ列挙型
#  define BKSGE_HAS_CXX11_FORWARD_DECLARE_ENUMS				// enumの先行宣言
#endif

// Visual Studio 2013 (Visual C++ 12)
#if (_MSC_FULL_VER >= 180020827)
#  define BKSGE_HAS_CXX11_DELETED_FUNCTIONS					// 関数のdelete宣言
#  define BKSGE_HAS_CXX11_DELEGATING_CONSTRUCTORS			// 移譲コンストラクタ
#  define BKSGE_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS		// 明示的な型変換演算子
#  define BKSGE_HAS_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS	// 関数テンプレートに関する既定のテンプレート引数
#  define BKSGE_HAS_CXX11_RAW_STRINGS						// 生文字列リテラル
#  define BKSGE_HAS_CXX11_ALIAS_TEMPLATES					// エイリアステンプレート
#  define BKSGE_HAS_CXX11_VARIADIC_TEMPLATES				// 可変引数テンプレート
#  define BKSGE_HAS_CXX11_NSDMI								// 非静的メンバ変数の初期化
#  define BKSGE_HAS_CXX11_INITIALIZER_LISTS					// 初期化子リスト
#  define BKSGE_HAS_CXX11_UNIFORM_INITIALIZATION			// 一様初期化

#  define BKSGE_HAS_EXPM1
#  define BKSGE_HAS_LOG1P
#endif

// Visual Studio 2015 (Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190023026)
#  define BKSGE_HAS_CXX11_RVALUE_REFERENCES					// 右辺値参照
#  define BKSGE_HAS_CXX11_DEFAULTED_FUNCTIONS				// 関数のdefault宣言
#  define BKSGE_HAS_CXX11_INHERITING_CONSTRUCTORS			// 継承コンストラクタ
#  define BKSGE_HAS_CXX11_NOEXCEPT							// noexcept
#  define BKSGE_HAS_CXX11_REF_QUALIFIERS					// メンバ関数の左辺値／右辺値修飾
#  define BKSGE_HAS_CXX11_USER_DEFINED_LITERALS				// ユーザー定義リテラル
#  define BKSGE_HAS_CXX11_ALIGNAS							// アライメント指定
#  define BKSGE_HAS_CXX11_ALIGNOF							// アライメント取得
#  define BKSGE_HAS_CXX11_INLINE_NAMESPACES					// インライン名前空間
#  define BKSGE_HAS_CXX11_CHAR16_T							// char16_t
#  define BKSGE_HAS_CXX11_CHAR32_T							// char32_t
#  define BKSGE_HAS_CXX11_UNICODE_LITERALS					// UTF-8文字列リテラル
#  define BKSGE_HAS_CXX11_UNIVERSAL_CHARACTER_NAME			// 文字列リテラル中のユニバーサルキャラクタ名
#  define BKSGE_HAS_CXX11_ATTRIBUTES						// 属性構文
#  define BKSGE_HAS_CXX11_NORETURN							// [[noreturn]]属性
#  define BKSGE_HAS_CXX11_CARRIES_DEPENDENCY				// [[carries_dependency]]属性
#  define BKSGE_HAS_CXX11_THREAD_LOCAL						// スレッドローカルストレージ
#  define BKSGE_HAS_CXX11_UNRESTRICTED_UNIONS				// 共用体の制限解除
#  define BKSGE_HAS_CXX11_THREADSAFE_STATIC_INIT			// ブロックスコープを持つstatic変数初期化のスレッドセーフ化
#  define BKSGE_HAS_CXX11_EXTENDED_SIZEOF					// 拡張sizeof
#  define BKSGE_HAS_CXX14_BINARY_LITERALS					// 2進数リテラル
#  define BKSGE_HAS_CXX14_DECLTYPE_AUTO						// 通常関数の戻り値型推論
#  define BKSGE_HAS_CXX14_RETURN_TYPE_DEDUCTION				// 通常関数の戻り値型推論
#  define BKSGE_HAS_CXX14_INIT_CAPTURES						// ラムダ式の初期化キャプチャ
#  define BKSGE_HAS_CXX14_GENERIC_LAMBDAS					// ジェネリックラムダ
#  define BKSGE_HAS_CXX14_DEPRECATED						// [[deprecated]]属性
#  define BKSGE_HAS_CXX14_SIZED_DEALLOCATION				// サイズ付きデアロケーション
#  define BKSGE_HAS_CXX14_DIGIT_SEPARATORS					// 数値リテラルの桁区切り文字
# if (BKSGE_CXX_STANDARD >= 14)
#  define BKSGE_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST	// 波括弧初期化の型推論の新規則
#  define BKSGE_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME		// テンプレートテンプレートパラメータにtypenameを許可
#  define BKSGE_HAS_CXX17_ENUMERATOR_ATTRIBUTES				// 列挙子に属性の付加を許可
#  define BKSGE_HAS_CXX17_NAMESPACE_ATTRIBUTES				// 名前空間に属性の付加を許可
#  define BKSGE_HAS_CXX17_U8_CHARACTER_LITERALS				// UTF-8文字リテラル
#  define BKSGE_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES	// 不明な属性を無視する
#  define BKSGE_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS	// const修飾されたメンバポインタの制限を修正
# endif
#endif

// Visual Studio 2015 Update 1	(Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190023506)
#endif

// Visual Studio 2015 Update 2	(Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190023918)
#  define BKSGE_HAS_CXX14_VARIABLE_TEMPLATES				// 変数テンプレート
#endif

// Visual Studio 2015 Update 3	(Visual C++ 14.0)
#if (_MSC_FULL_VER >= 190024210)
#  define BKSGE_HAS_CXX11_SFINAE_EXPR						// 任意の式によるSFINAE
#  define BKSGE_HAS_CXX11_CONSTEXPR							// 定数式
# if (BKSGE_CXX_STANDARD >= 17)
#  define BKSGE_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS		// 入れ子名前空間の定義
# endif
#endif

// Visual Studio 2017 (15.0)	(Visual C++ 14.10)
#if (_MSC_FULL_VER >= 191025017)
#  define BKSGE_HAS_CXX14_CONSTEXPR							// constexprの制限緩和
#  define BKSGE_HAS_CXX14_AGGREGATE_NSDMI					// 宣言時のメンバ初期化を持つ型の集成体初期化
# if (BKSGE_CXX_STANDARD >= 14)
#  define BKSGE_HAS_CXX17_RANGE_BASED_FOR					// 範囲for文の制限を緩和
# endif
# if (BKSGE_CXX_STANDARD >= 17)
#  define BKSGE_HAS_CXX17_STATIC_ASSERT						// メッセージなしのstatic_assert
#  define BKSGE_HAS_CXX17_FALLTHROUGH						// [[fallthrough]]属性
# endif
#endif

// Visual Studio 2017 Update 3 (15.3.3)	(Visual C++ 14.11)
#if (_MSC_FULL_VER >= 191125507)
# if (BKSGE_CXX_STANDARD >= 14)
#  define BKSGE_HAS_CXX17_HAS_INCLUDE						// プリプロセッサでの条件式__has_include
# endif
# if (BKSGE_CXX_STANDARD >= 17)
#  define BKSGE_HAS_CXX17_IF_CONSTEXPR						// if constexpr文
#  define BKSGE_HAS_CXX17_CAPTURE_STAR_THIS					// ラムダ式での*thisのコピーキャプチャ
#  define BKSGE_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES		// 属性の名前空間指定に繰り返しをなくす
#  define BKSGE_HAS_CXX17_INIT_ENUM_CLASS					// enum class変数の初期値として整数を指定
#  define BKSGE_HAS_CXX17_CONSTEXPR_LAMBDA					// constexprラムダ
#  define BKSGE_HAS_CXX17_NODISCARD							// [[nodiscard]]属性
#  define BKSGE_HAS_CXX17_MAYBE_UNUSED						// [[maybe_unused]]属性
#  define BKSGE_HAS_CXX17_STRUCTURED_BINDINGS				// 構造化束縛
#  define BKSGE_HAS_CXX17_SELECTION_WITH_INIT				// if文とswitch文の条件式と初期化を分離
# endif
#endif

// Visual Studio 2017 Update 4 (15.4.4)	(Visual C++ 14.11)
#if (_MSC_FULL_VER >= 191125542)
#endif

// Visual Studio 2017 Update 4 (15.4.5)	(Visual C++ 14.11)
#if (_MSC_FULL_VER >= 191125547)
#endif

// Visual Studio 2017 Update 5 (v15.5)	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225830)
#endif

// Visual Studio 2017 Update 5 (15.5.2)	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225831)
#  define BKSGE_HAS_CXX17_HEX_FLOAT							// 浮動小数点数の16進数リテラル
# if (BKSGE_CXX_STANDARD >= 17)
#  define BKSGE_HAS_CXX17_NONTYPE_TEMPLATE_ARGS				// 非型テンプレートパラメータの定数式を評価
#  define BKSGE_HAS_CXX17_FOLD_EXPRESSIONS					// 畳み込み式
#  define BKSGE_HAS_CXX17_EXCEPTION_SPECIFICATIONS			// 非推奨だった例外仕様を削除
#  define BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE			// 例外仕様を型システムの一部にする
#  define BKSGE_HAS_CXX17_ALIGNED_NEW						// アライメント指定されたデータの動的メモリ確保
#  define BKSGE_HAS_CXX17_INLINE_VARIABLES					// インライン変数
#  define BKSGE_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS			// テンプレートテンプレート引数のマッチングにおいて、互換性のあるテンプレートを除外
# endif
#endif

// Visual Studio 2017 Update 5 (15.5.(3-4))	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225834)
#endif

// Visual Studio 2017 Update 5 (15.5.(5-7))	(Visual C++ 14.12)
#if (_MSC_FULL_VER >= 191225835)
#endif

// Visual Studio 2017 Update 6 (15.6.(0-2))	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326128)
# if (BKSGE_CXX_STANDARD >= 17)
#  define BKSGE_HAS_CXX17_GUARANTEED_COPY_ELISION				// 値のコピー省略を保証
# endif
#endif

// Visual Studio 2017 Update 6 (15.6.(3-5))	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326129)
#endif

// Visual Studio 2017 Update 6 (15.6.6)	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326131)
#endif

// Visual Studio 2017 Update 6 (15.6.7)	(Visual C++ 14.13)
#if (_MSC_FULL_VER >= 191326132)
#endif

// Visual Studio 2017 Update 7 (15.7.(0-1))	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426428)
# if (BKSGE_CXX_STANDARD >= 17)
#  define BKSGE_HAS_CXX17_VARIADIC_USING						// using宣言でのパック展開
#  define BKSGE_HAS_CXX17_AGGREGATE_BASES						// 集成体初期化の波カッコを省略
#  define BKSGE_HAS_CXX17_DEDUCTION_GUIDES						// クラステンプレートのテンプレート引数推論
#  define BKSGE_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO		// 非型テンプレート引数のauto宣言
#  define BKSGE_HAS_CXX17_INHERITING_CONSTRUCTORS				// 継承コンストラクタの新仕様
#  define BKSGE_HAS_CXX17_EXPRESSION_EVALUATION_ORDER			// 厳密な式の評価順
# endif
#endif

// Visual Studio 2017 Update 7 (15.7.2)	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426429)
#endif

// Visual Studio 2017 Update 7 (15.7.3)	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426430)
#endif

// Visual Studio 2017 Update 7 (15.7.4)	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426431)
#endif

// Visual Studio 2017 Update 7 (15.7.(5-6))	(Visual C++ 14.14)
#if (_MSC_FULL_VER >= 191426433)
#endif

// Visual Studio 2017 Update 8 (15.8.(0-3))	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526726)
#endif

// Visual Studio 2017 Update 8 (15.8.4)	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526729)
#endif

// Visual Studio 2017 Update 8 (15.8.(5-7))	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526730)
#endif

// Visual Studio 2017 Update 8 (15.8.(8-9))	(Visual C++ 14.15)
#if (_MSC_FULL_VER >= 191526732)
#endif

// Visual Studio 2017 Update 9 (15.9.(0-1))	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627023)
#endif

// Visual Studio 2017 Update 9 (15.9.(2-3))	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627024)
#endif

// Visual Studio 2017 Update 9 (15.9.4)	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627025)
#endif

// Visual Studio 2017 Update 9 (15.9.(5-6))	(Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627026)
#endif

// Visual Studio 2017 Update 9 (15.9.(7-10)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627027)
#endif

// Visual Studio 2017 Update 9 (15.9.11) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627030)
#endif

// Visual Studio 2017 Update 9 (15.9.(12-13)) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627031)
#endif

// Visual Studio 2017 Update 9 (15.9.14) (Visual C++ 14.16)
#if (_MSC_FULL_VER >= 191627032)
#endif

// Visual Studio 2019 (16.0.Prev(1-4)) (Visual C++ 14.20)
#if (_MSC_FULL_VER >= 192027027)
#endif

// Visual Studio 2019 (16.0.(0-4)) (Visual C++ 14.20)
#if (_MSC_FULL_VER >= 192027508)
#endif

// Visual Studio 2019 Update 1 (16.1.(0-6)) (Visual C++ 14.21)
#if (_MSC_FULL_VER >= 192127702)
# if (BKSGE_CXX_STANDARD >= 20)
#  define BKSGE_HAS_CXX20_DESIGNATED_INITIALIZERS	// 指示付き初期化子
#  define BKSGE_HAS_CXX20_CAPTURE_COPY_THIS			// ラムダ式のキャプチャとして[=, this]を許可する
# endif
#endif

// Visual Studio 2019 Update 2 (16.2.(0-5)) (Visual C++ 14.22)
#if (_MSC_FULL_VER >= 192227905)
# if (BKSGE_CXX_STANDARD >= 20)
#  define BKSGE_HAS_CXX20_TEMPLATE_LAMBDA			// ジェネリックラムダのテンプレート構文
# endif
#endif

// Visual Studio 2019 Update 3 (16.3.(0-2)) (Visual C++ 14.23)
#if (_MSC_FULL_VER >= 192328105)
#endif

// Visual Studio 2019 Update 3 (16.3.(3-7)) (Visual C++ 14.23)
#if (_MSC_FULL_VER >= 192328106)
#endif

#if (BKSGE_CXX_STANDARD >= 17)
#  define BKSGE_HAS_CXX17_CONSTEXPR
#endif

#define BKSGE_NO_COMPLETE_VALUE_INITIALIZATION
#define BKSGE_NO_TWO_PHASE_NAME_LOOKUP					// Two-phase name lookup
//#define BKSGE_HAS_CXX11_PRAGMA_OPERATOR				// Pragma演算子

#if 0

// C++11
#define BKSGE_HAS_CXX11_RVALUE_REFERENCES				// N2118	__cpp_rvalue_references					右辺値参照
#define BKSGE_HAS_CXX11_REF_QUALIFIERS					// N2439	__cpp_ref_qualifiers					メンバ関数の左辺値／右辺値修飾
#define BKSGE_HAS_CXX11_NSDMI							// N2756	__cpp_nsdmi								非静的メンバ変数の初期化
#define BKSGE_HAS_CXX11_VARIADIC_TEMPLATES				// N2242	__cpp_variadic_templates				可変引数テンプレート
#define BKSGE_HAS_CXX11_INITIALIZER_LISTS				// N2672	__cpp_initializer_lists					初期化子リスト
#define BKSGE_HAS_CXX11_STATIC_ASSERT					// N1720	__cpp_static_assert						コンパイル時アサート
#define BKSGE_HAS_CXX11_AUTO_DECLARATIONS				// N2546	none									型推論
#define BKSGE_HAS_CXX11_TRAILING_RETURN_TYPE			// N2541	none									戻り値の型を後置する関数宣言構文
#define BKSGE_HAS_CXX11_LAMBDAS							// N2927	__cpp_lambdas							ラムダ式
#define BKSGE_HAS_CXX11_DECLTYPE						// N2343	__cpp_decltype							式の型を取得
#define BKSGE_HAS_CXX11_RIGHT_ANGLE_BRACKETS			// N1757	none									テンプレートの右山カッコ
#define BKSGE_HAS_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS	// 			none									関数テンプレートに関する既定のテンプレート引数
#define BKSGE_HAS_CXX11_SFINAE_EXPR						// N2634	none									任意の式によるSFINAE
#define BKSGE_HAS_CXX11_ALIAS_TEMPLATES					// N2258	__cpp_alias_templates					エイリアステンプレート
#define BKSGE_HAS_CXX11_EXTERN_TEMPLATE					// N1987	none									テンプレートのインスタンス化抑止
#define BKSGE_HAS_CXX11_NULLPTR							// N2431	none									nullptr
#define BKSGE_HAS_CXX11_SCOPED_ENUMS					// N2347	none									スコープを持つ列挙型
#define BKSGE_HAS_CXX11_FORWARD_DECLARE_ENUMS			// N2764	none									enumの先行宣言
#define BKSGE_HAS_CXX11_ATTRIBUTES						// N2761	__cpp_attributes						属性構文
#define BKSGE_HAS_CXX11_NORETURN						// N2761	__has_cpp_attribute(noreturn)			[[noreturn]]属性
#define BKSGE_HAS_CXX11_CARRIES_DEPENDENCY				// N2761	__has_cpp_attribute(carries_dependency)	[[carries_dependency]]属性
#define BKSGE_HAS_CXX11_CONSTEXPR						// N2235	__cpp_constexpr							定数式
#define BKSGE_HAS_CXX11_ALIGNAS							// N2341	none									アライメント指定
#define BKSGE_HAS_CXX11_ALIGNOF							// N2341	none									アライメント取得
#define BKSGE_HAS_CXX11_DELEGATING_CONSTRUCTORS			// N1986	__cpp_delegating_constructors			移譲コンストラクタ
#define BKSGE_HAS_CXX11_INHERITING_CONSTRUCTORS			// N2540	__cpp_inheriting_constructors			継承コンストラクタ
#define BKSGE_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS	// N2437	none									明示的な型変換演算子
#define BKSGE_HAS_CXX11_CHAR16_T						// N2249	__cpp_unicode_characters				char16_t
#define BKSGE_HAS_CXX11_CHAR32_T						// N2249	__cpp_unicode_characters				char32_t
#define BKSGE_HAS_CXX11_UNICODE_LITERALS				// N2442	__cpp_unicode_literals					UTF-8文字列リテラル
#define BKSGE_HAS_CXX11_RAW_STRINGS						// N2442	__cpp_raw_strings						生文字列リテラル
#define BKSGE_HAS_CXX11_UNIVERSAL_CHARACTER_NAME		// N2170 	none									文字列リテラル中のユニバーサルキャラクタ名
#define BKSGE_HAS_CXX11_USER_DEFINED_LITERALS			// N2765	__cpp_user_defined_literals				ユーザー定義リテラル
// TODO													// N2342											Standard-layout and trivial types
#define BKSGE_HAS_CXX11_DELETED_FUNCTIONS				// N2346	none									関数のdelete宣言
#define BKSGE_HAS_CXX11_DEFAULTED_FUNCTIONS				// N2346	none									関数のdefault宣言
#define BKSGE_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS	// N1791	none									friend宣言できる対象を拡張
#define BKSGE_HAS_CXX11_EXTENDED_SIZEOF					// N2253	none									拡張sizeof
#define BKSGE_HAS_CXX11_INLINE_NAMESPACES				// N2535	none									インライン名前空間
#define BKSGE_HAS_CXX11_UNRESTRICTED_UNIONS				// N2544	none									共用体の制限解除
#define BKSGE_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS		// N2657	none									ローカル型と無名型をテンプレート引数として使用することを許可
#define BKSGE_HAS_CXX11_RANGE_BASED_FOR					// N2930	__cpp_range_based_for					範囲for文
#define BKSGE_HAS_CXX11_OVERRIDE						// N3272	none									override
#define BKSGE_HAS_CXX11_FINAL							// N3272	none									final
#define BKSGE_HAS_CXX11_NOEXCEPT						// N3050	none									noexcept
#define BKSGE_HAS_CXX11_THREAD_LOCAL					// N2659	none									スレッドローカルストレージ
#define BKSGE_HAS_CXX11_THREADSAFE_STATIC_INIT			// N2660	__cpp_threadsafe_static_init			ブロックスコープを持つstatic変数初期化のスレッドセーフ化
#define BKSGE_HAS_CXX11_LONG_LONG						// N1811	none									long long型
#define BKSGE_HAS_CXX11_VARIADIC_MACROS					// N1653	none									可変引数マクロ
#define BKSGE_HAS_CXX11_PRAGMA_OPERATOR					// N1653	none									Pragma演算子
#define BKSGE_HAS_CXX11_UNIFORM_INITIALIZATION			// N2640	none									一様初期化

// C++14
#define BKSGE_HAS_CXX14_BINARY_LITERALS					// N3472	__cpp_binary_literals					2進数リテラル
#define BKSGE_HAS_CXX14_DECLTYPE_AUTO					// N3638	__cpp_decltype_auto						通常関数の戻り値型推論
#define BKSGE_HAS_CXX14_RETURN_TYPE_DEDUCTION			// N3638	__cpp_return_type_deduction				通常関数の戻り値型推論
#define BKSGE_HAS_CXX14_INIT_CAPTURES					// N3610	__cpp_init_captures						ラムダ式の初期化キャプチャ
#define BKSGE_HAS_CXX14_GENERIC_LAMBDAS					// N3649	__cpp_generic_lambdas					ジェネリックラムダ
#define BKSGE_HAS_CXX14_DEPRECATED						// N3760	__has_cpp_attribute(deprecated)			[[deprecated]]属性
#define BKSGE_HAS_CXX14_SIZED_DEALLOCATION				// N3778	__cpp_sized_deallocation				サイズ付きデアロケーション
#define BKSGE_HAS_CXX14_DIGIT_SEPARATORS				// N3781	none									数値リテラルの桁区切り文字
#define BKSGE_HAS_CXX14_VARIABLE_TEMPLATES				// N3651	__cpp_variable_templates				変数テンプレート
#define BKSGE_HAS_CXX14_CONSTEXPR						// N3652	__cpp_constexpr							constexprの制限緩和
#define BKSGE_HAS_CXX14_AGGREGATE_NSDMI					// N3653	__cpp_aggregate_nsdmi					宣言時のメンバ初期化を持つ型の集成体初期化

// C++17
#define BKSGE_HAS_CXX17_HEX_FLOAT						// P0245R1	__cpp_hex_float							浮動小数点数の16進数リテラル
#define BKSGE_HAS_CXX17_U8_CHARACTER_LITERALS			// N4267	none									UTF-8文字リテラル
#define BKSGE_HAS_CXX17_INLINE_VARIABLES				// P0386R2	__cpp_inline_variables					インライン変数
#define BKSGE_HAS_CXX17_ALIGNED_NEW						// P0035R4	__cpp_aligned_new						アライメント指定new
#define BKSGE_HAS_CXX17_GUARANTEED_COPY_ELISION			// P0135R1	__cpp_guaranteed_copy_elision			値のコピー省略を保証
#define BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE			// P0012R1	__cpp_noexcept_function_type			例外仕様を型システムの一部にする
#define BKSGE_HAS_CXX17_EXPRESSION_EVALUATION_ORDER		// P0145R3	none									厳密な式の評価順
#define BKSGE_HAS_CXX17_FOLD_EXPRESSIONS				// N4295	__cpp_fold_expressions					畳み込み式
#define BKSGE_HAS_CXX17_CAPTURE_STAR_THIS				// P0018R3	__cpp_capture_star_this					ラムダ式での*thisのコピーキャプチャ
#define BKSGE_HAS_CXX17_CONSTEXPR_LAMBDA				// P0170R1	__cpp_constexpr							constexprラムダ
#define BKSGE_HAS_CXX17_IF_CONSTEXPR					// P0292R2	__cpp_if_constexpr						if constexpr文
#define BKSGE_HAS_CXX17_SELECTION_WITH_INIT				// P0305R1	none									if文とswitch文の条件式と初期化を分離
#define BKSGE_HAS_CXX17_RANGE_BASED_FOR					// P0184R0	__cpp_range_based_for					範囲for文の制限を緩和
#define BKSGE_HAS_CXX17_STATIC_ASSERT					// N3928	__cpp_static_assert						メッセージなしのstatic_assert
#define BKSGE_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST	// N3922	none									波括弧初期化の型推論の新規則
#define BKSGE_HAS_CXX17_DEDUCTION_GUIDES				// P0091R3	__cpp_deduction_guides					クラステンプレートのテンプレート引数推論
#define BKSGE_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO	// P0127R2	__cpp_nontype_template_parameter_auto	非型テンプレート引数のauto宣言
#define BKSGE_HAS_CXX17_NAMESPACE_ATTRIBUTES			// N4266	__cpp_namespace_attributes				名前空間に属性の付加を許可
#define BKSGE_HAS_CXX17_ENUMERATOR_ATTRIBUTES			// N4266	__cpp_enumerator_attributes				列挙子に属性の付加を許可
#define BKSGE_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS	// N4230	none									入れ子名前空間の定義
#define BKSGE_HAS_CXX17_INHERITING_CONSTRUCTORS			// P0136R1	__cpp_inheriting_constructors			継承コンストラクタの新仕様
#define BKSGE_HAS_CXX17_VARIADIC_USING					// P0195R2	__cpp_variadic_using					using宣言でのパック展開
#define BKSGE_HAS_CXX17_FALLTHROUGH						// P0188R1	__has_cpp_attribute(fallthrough)		[[fallthrough]]属性
#define BKSGE_HAS_CXX17_NODISCARD						// P0189R1	__has_cpp_attribute(nodiscard)			[[nodiscard]]属性
#define BKSGE_HAS_CXX17_MAYBE_UNUSED					// P0212R1	__has_cpp_attribute(maybe_unused)		[[maybe_unused]]属性
#define BKSGE_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES		// P0028R4	none									属性の名前空間指定に繰り返しをなくす
#define BKSGE_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES// P0283R2	none									不明な属性を無視する
#define BKSGE_HAS_CXX17_STRUCTURED_BINDINGS				// P0217R3	__cpp_structured_bindings				構造化束縛
#define BKSGE_HAS_CXX17_AGGREGATE_BASES					// P0017R1	__cpp_aggregate_bases					集成体初期化の波カッコを省略
#define BKSGE_HAS_CXX17_INIT_ENUM_CLASS					// P0138R2	none									enum class変数の初期値として整数を指定する際の規則を調整
#define BKSGE_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME		// N4051	none									テンプレートテンプレートパラメータにtypenameを許可
#define BKSGE_HAS_CXX17_NONTYPE_TEMPLATE_ARGS			// N4268	__cpp_nontype_template_args				非型テンプレートパラメータの定数式を評価する
#define BKSGE_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS			// P0522R0	__cpp_template_template_args			テンプレートテンプレート引数のマッチングにおいて、互換性のあるテンプレートを除外
#define BKSGE_HAS_CXX17_EXCEPTION_SPECIFICATIONS		// P0003R5	none									非推奨だった例外仕様を削除
#define BKSGE_HAS_CXX17_HAS_INCLUDE						// P0061R1	__has_include							プリプロセッサでの条件式__has_include
// P0398R0	Explicit default constructors and copy-list-initialization						none
// P0134R0	Introducing a name for brace-or-equal-initializers for non-static data members	none

// C++20
#define BKSGE_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER	// P0683R1	ビットフィールドのメンバ変数初期化
#define BKSGE_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS	// P0704R1	const修飾されたメンバポインタの制限を修正
#define BKSGE_HAS_CXX20_CAPTURE_COPY_THIS					// P0409R2	ラムダ式のキャプチャとして[=, this]を許可する
// P0306R4		__VA_OPT__ for preprocessor comma elision
// P1042R1
#define BKSGE_HAS_CXX20_DESIGNATED_INITIALIZERS				// P0329R4	指示付き初期化子
#define BKSGE_HAS_CXX20_TEMPLATE_LAMBDA						// P0428R2	ジェネリックラムダのテンプレート構文
// P0702R1		List deduction of vector
// P0734R0		Concepts
// P0857R0
// P1084R2
// P1141R2
// P0848R3
// P1616R1
// P1452R2
#define BKSGE_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER			// P0614R1	初期化式をともなう範囲for文
// P0588R1		Simplifying implicit lambda capture
// P0846R0		ADL and function templates that are not visible
// P0641R2		const mismatch with defaulted copy constructor
// P0859R0		Less eager instantiation of constexpr functions
// P0515R3	__cpp_impl_three_way_comparison >= 201711	Consistent comparison (operator<=>)
// P0905R1
// P1120R0
// P1185R2
// P1186R3
// P1630R1
// P0692R1		Access checking on specializations
// P0624R2		Default constructible and assignable stateless lambdas
// P0315R4		Lambdas in unevaluated contexts
// P0840R2		Language support for empty objects
// P0962R1		Relaxing the range-for loop customization point finding rules
// P0969R0		Allow structured bindings to accessible members
// P0961R1		Relaxing the structured bindings customization point finding rules
// P0634R3		Down with typename!
// P0780R2		Allow pack expansion in lambda init-capture
// P0479R5		Proposed wording for likelyand unlikely attributes
// P0806R2		[=]によるthisの暗黙のキャプチャを非推奨化
// P0732R2	__cpp_nontype_template_parameter_class >= 201806	Class Types in Non-Type Template Parameters
// P0528R3		Atomic Compare-and-Exchange with Padding Bits
// P0722R3	__cpp_impl_destroying_delete >= 201806	Efficient sized delete for variable sized classes
// P1064R0		Allowing Virtual Function Calls in Constant Expressions
// P1008R1		Prohibit aggregates with user-declared constructors
// P0892R2	__cpp_conditional_explicit >= 201806	explicit(bool)
// P1236R1		Signed integers are two's complement
// P0482R6	__cpp_char8_t >= 201811	char8_t
// P1073R3		Immediate functions (consteval)
// P0595R2		std::is_constant_evaluated
// P1094R2		Nested inline namespaces
// P1002R1		Relaxations of constexpr restrictions
// P1327R1
// P1330R0
// P1331R2	__cpp_constexpr >= 201907	
// P1668R1
// P0784R7
// P0941R2		Feature test macros
// P1103R3		Modules
// P1766R1
// P1811R0
// P1703R1
// P0912R5		Coroutines
// P0960R3	__cpp_aggregate_paren_init >= 201902	Parenthesized initialization of aggregates
// P1041R4		Stronger Unicode requirements
// P1139R2
// P1091R3		Structured binding extensions
// P1381R1
// P1161R3		Deprecate a[b,c]
// P1152R4		Deprecating some uses of volatile
// P1301R4		[[nodiscard("with reason")]]
// P1099R5		using enum
// P1816R0		Class template argument deduction for aggregates
// P1814R0		Class template argument deduction for alias templates
// P0388R4		Permit conversions to arrays of unknown bound
// P1143R2	__cpp_constinit >= 201907	constinit
// P1825R0		More implicit moves (merge P0527R1 and P1155R3)

#endif

#endif // BKSGE_CONFIG_COMPILER_MSVC_HPP
