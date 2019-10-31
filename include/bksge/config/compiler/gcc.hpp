/**
 *	@file	gcc.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_COMPILER_GCC_HPP
#define BKSGE_CONFIG_COMPILER_GCC_HPP

#define BKSGE_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#define BKSGE_COMPILER "gcc"
#define BKSGE_COMPILER_VERSION BKSGE_GCC_VERSION

#if !defined(__CUDACC__)
#define BKSGE_GCC BKSGE_GCC_VERSION
#endif

// BKSGE_CXX_STANDARD
#if !defined(BKSGE_CXX_STANDARD)
#  if __cplusplus > 201703L
#    define BKSGE_CXX_STANDARD 20
#  elif __cplusplus >= 201703L
#    define BKSGE_CXX_STANDARD 17
#  elif __cplusplus >= 201402L
#    define BKSGE_CXX_STANDARD 14
#  elif  __cplusplus >= 201103L
#    define BKSGE_CXX_STANDARD 11
#  else
#    define BKSGE_CXX_STANDARD  3
#  endif
#endif  // BKSGE_CXX_STANDARD

#if __GNUC__ == 3
#  if defined (__PATHSCALE__)
#     define BKSGE_NO_TWO_PHASE_NAME_LOOKUP
#     define BKSGE_NO_IS_ABSTRACT
#  endif

#  if __GNUC_MINOR__ < 4
#     define BKSGE_NO_IS_ABSTRACT
#  endif
#endif
#if __GNUC__ < 4
//
// All problems to gcc-3.x and earlier here:
//
#define BKSGE_NO_TWO_PHASE_NAME_LOOKUP
#  ifdef __OPEN64__
#     define BKSGE_NO_IS_ABSTRACT
#  endif
#endif

// GCC prior to 3.4 had #pragma once too but it didn't work well with filesystem links
#if BKSGE_GCC_VERSION >= 30400
#define BKSGE_HAS_PRAGMA_ONCE
#endif

#if BKSGE_GCC_VERSION < 40400
// Previous versions of GCC did not completely implement value-initialization:
// GCC Bug 30111, "Value-initialization of POD base class doesn't initialize
// members", reported by Jonathan Wakely in 2006,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=30111 (fixed for GCC 4.4)
// GCC Bug 33916, "Default constructor fails to initialize array members",
// reported by Michael Elizabeth Chastain in 2007,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=33916 (fixed for GCC 4.2.4)
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
#define BKSGE_NO_COMPLETE_VALUE_INITIALIZATION
#endif

#if !defined(__EXCEPTIONS) && !defined(BKSGE_NO_EXCEPTIONS)
# define BKSGE_NO_EXCEPTIONS
#endif

//
// Threading support: Turn this on unconditionally here (except for
// those platforms where we can know for sure). It will get turned off again
// later if no threading API is detected.
//
#if !defined(__MINGW32__) && !defined(linux) && !defined(__linux) && !defined(__linux__)
# define BKSGE_HAS_THREADS
#endif

//
// gcc implements the named return value optimization since version 3.1
//
#define BKSGE_HAS_NRVO

//
// RTTI and typeinfo detection is possible post gcc-4.3:
//
#if BKSGE_GCC_VERSION > 40300
#  ifndef __GXX_RTTI
#     ifndef BKSGE_NO_TYPEID
#        define BKSGE_NO_TYPEID
#     endif
#     ifndef BKSGE_NO_RTTI
#        define BKSGE_NO_RTTI
#     endif
#  endif
#endif


// C++11
#if (BKSGE_CXX_STANDARD >= 11)
#  if (BKSGE_GCC_VERSION >= 40300) && defined(__cpp_rvalue_references) && (__cpp_rvalue_references >= 200610)
#    define BKSGE_HAS_CXX11_RVALUE_REFERENCES
#  endif
#  if (BKSGE_GCC_VERSION >= 40801) && defined(__cpp_ref_qualifiers) && (__cpp_ref_qualifiers >= 200710)
#    define BKSGE_HAS_CXX11_REF_QUALIFIERS
#  endif
#  if (BKSGE_GCC_VERSION >= 40700) && defined(__cpp_nsdmi) && (__cpp_nsdmi >= 200809)
#    define BKSGE_HAS_CXX11_NSDMI
#  endif
#  if (BKSGE_GCC_VERSION >= 40300) && defined(__cpp_variadic_templates) && (__cpp_variadic_templates >= 200704)
#    define BKSGE_HAS_CXX11_VARIADIC_TEMPLATES
#  endif
#  if (BKSGE_GCC_VERSION >= 40400) && defined(__cpp_initializer_lists) && (__cpp_initializer_lists >= 200806)
#    define BKSGE_HAS_CXX11_INITIALIZER_LISTS
#  endif
#  if (BKSGE_GCC_VERSION >= 40300) && defined(__cpp_static_assert) && (__cpp_static_assert >= 200410)
#    define BKSGE_HAS_CXX11_STATIC_ASSERT
#  endif
#  if (BKSGE_GCC_VERSION >= 40400)
#    define BKSGE_HAS_CXX11_AUTO_DECLARATIONS
#  endif
#  if (BKSGE_GCC_VERSION >= 40400)
#    define BKSGE_HAS_CXX11_TRAILING_RETURN_TYPE
#  endif
#  if (BKSGE_GCC_VERSION >= 40500) && defined(__cpp_lambdas) && (__cpp_lambdas >= 200907)
#    define BKSGE_HAS_CXX11_LAMBDAS
#  endif
#  if (BKSGE_GCC_VERSION >= 40300) && defined(__cpp_decltype) && (__cpp_decltype >= 200707)
#    define BKSGE_HAS_CXX11_DECLTYPE
#  endif
#  if (BKSGE_GCC_VERSION >= 40300)
#    define BKSGE_HAS_CXX11_RIGHT_ANGLE_BRACKETS
#  endif
#  if (BKSGE_GCC_VERSION >= 40300)
#    define BKSGE_HAS_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  endif
#  if (BKSGE_GCC_VERSION >= 40300)
#    define BKSGE_HAS_CXX11_SFINAE_EXPR
#  endif
#  if (BKSGE_GCC_VERSION >= 40700) && defined(__cpp_alias_templates) && (__cpp_alias_templates >= 200704)
#    define BKSGE_HAS_CXX11_ALIAS_TEMPLATES
#  endif
#  if (BKSGE_GCC_VERSION >= 40000)
#    define BKSGE_HAS_CXX11_EXTERN_TEMPLATE
#  endif
#  if (BKSGE_GCC_VERSION >= 40600)
#    define BKSGE_HAS_CXX11_NULLPTR
#  endif
#  if (BKSGE_GCC_VERSION >= 40400)
#    define BKSGE_HAS_CXX11_SCOPED_ENUMS
#  endif
#  if (BKSGE_GCC_VERSION >= 40600)
#    define BKSGE_HAS_CXX11_FORWARD_DECLARE_ENUMS
#  endif
#  if (BKSGE_GCC_VERSION >= 40800) && defined(__cpp_attributes) && (__cpp_attributes >= 200809)
#    define BKSGE_HAS_CXX11_ATTRIBUTES
#  endif
#  if (BKSGE_GCC_VERSION >= 40800) && (BKSGE_HAS_CPP_ATTRIBUTE(noreturn) >= 200809)
#    define BKSGE_HAS_CXX11_NORETURN
#  endif
#  if (BKSGE_GCC_VERSION >= 40800) && (BKSGE_HAS_CPP_ATTRIBUTE(carries_dependency) >= 200809)
#    define BKSGE_HAS_CXX11_CARRIES_DEPENDENCY
#  endif
#  if (BKSGE_GCC_VERSION >= 40600) && defined(__cpp_constexpr) && (__cpp_constexpr >= 200704)
#    define BKSGE_HAS_CXX11_CONSTEXPR
#  endif
#  if (BKSGE_GCC_VERSION >= 40800)
#    define BKSGE_HAS_CXX11_ALIGNAS
#    define BKSGE_HAS_CXX11_ALIGNOF
#  endif
#  if (BKSGE_GCC_VERSION >= 40700) && defined(__cpp_delegating_constructors) && (__cpp_delegating_constructors >= 200604)
#    define BKSGE_HAS_CXX11_DELEGATING_CONSTRUCTORS
#  endif
#  if (BKSGE_GCC_VERSION >= 40800) && defined(__cpp_inheriting_constructors) && (__cpp_inheriting_constructors >= 200802)
#    define BKSGE_HAS_CXX11_INHERITING_CONSTRUCTORS
#  endif
#  if (BKSGE_GCC_VERSION >= 40500)
#    define BKSGE_HAS_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  endif
#  if (BKSGE_GCC_VERSION >= 40400) && defined(__cpp_unicode_characters) && (__cpp_unicode_characters >= 200704)
#    define BKSGE_HAS_CXX11_CHAR16_T
#    define BKSGE_HAS_CXX11_CHAR32_T
#  endif
#  if (BKSGE_GCC_VERSION >= 40500) && defined(__cpp_unicode_literals) && (__cpp_unicode_literals >= 200710)
#    define BKSGE_HAS_CXX11_UNICODE_LITERALS
#  endif
#  if (BKSGE_GCC_VERSION >= 40500) && defined(__cpp_raw_strings) && (__cpp_raw_strings >= 200710)
#    define BKSGE_HAS_CXX11_RAW_STRINGS
#  endif
#  if (BKSGE_GCC_VERSION >= 40500)
#    define BKSGE_HAS_CXX11_UNIVERSAL_CHARACTER_NAME
#  endif
#  if (BKSGE_GCC_VERSION >= 40700) && defined(__cpp_user_defined_literals) && (__cpp_user_defined_literals >= 200809)
#    define BKSGE_HAS_CXX11_USER_DEFINED_LITERALS
#  endif
#  if (BKSGE_GCC_VERSION >= 40400)
#    define BKSGE_HAS_CXX11_DELETED_FUNCTIONS
#    define BKSGE_HAS_CXX11_DEFAULTED_FUNCTIONS
#  endif
#  if (BKSGE_GCC_VERSION >= 40700)
#    define BKSGE_HAS_CXX11_EXTENDED_FRIEND_DECLARATIONS
#  endif
#  if (BKSGE_GCC_VERSION >= 40400)
#    define BKSGE_HAS_CXX11_EXTENDED_SIZEOF
#  endif
#  if (BKSGE_GCC_VERSION >= 40400)
#    define BKSGE_HAS_CXX11_INLINE_NAMESPACES
#  endif
#  if (BKSGE_GCC_VERSION >= 40600)
#    define BKSGE_HAS_CXX11_UNRESTRICTED_UNIONS
#  endif
#  if (BKSGE_GCC_VERSION >= 40500)
#    define BKSGE_HAS_CXX11_LOCAL_TYPE_TEMPLATE_ARGS
#  endif
#  if (BKSGE_GCC_VERSION >= 40600) && defined(__cpp_range_based_for) && (__cpp_range_based_for >= 200907)
#    define BKSGE_HAS_CXX11_RANGE_BASED_FOR
#  endif
#  if (BKSGE_GCC_VERSION >= 40700)
#    define BKSGE_HAS_CXX11_OVERRIDE
#    define BKSGE_HAS_CXX11_FINAL
#  endif
#  if (BKSGE_GCC_VERSION >= 40600)
#    define BKSGE_HAS_CXX11_NOEXCEPT
#  endif
#  if (BKSGE_GCC_VERSION >= 40800)
#    define BKSGE_HAS_CXX11_THREAD_LOCAL
#  endif
#  if (BKSGE_GCC_VERSION >= 40300) && defined(__cpp_threadsafe_static_init) && (__cpp_threadsafe_static_init >= 200806)
#    define BKSGE_HAS_CXX11_THREADSAFE_STATIC_INIT
#  endif
#  if (BKSGE_GCC_VERSION >= 40300)
#    define BKSGE_HAS_CXX11_LONG_LONG
#  endif
#  if (BKSGE_GCC_VERSION >= 40300)
#    define BKSGE_HAS_CXX11_VARIADIC_MACROS
#    define BKSGE_HAS_CXX11_PRAGMA_OPERATOR
#  endif
#endif

#define BKSGE_HAS_CXX11_UNIFORM_INITIALIZATION

// C++14
#if (BKSGE_CXX_STANDARD >= 14)
#  if (BKSGE_GCC_VERSION >= 40900) && defined(__cpp_binary_literals) && (__cpp_binary_literals >= 201304)
#    define BKSGE_HAS_CXX14_BINARY_LITERALS
#  endif
#  if (BKSGE_GCC_VERSION >= 40800) && defined(__cpp_decltype_auto) && (__cpp_decltype_auto >= 201304)
#    define BKSGE_HAS_CXX14_DECLTYPE_AUTO
#  endif
#  if (BKSGE_GCC_VERSION >= 40900) && defined(__cpp_return_type_deduction) && (__cpp_return_type_deduction >= 201304)
#    define BKSGE_HAS_CXX14_RETURN_TYPE_DEDUCTION
#  endif
#  if (BKSGE_GCC_VERSION >= 40900) && defined(__cpp_init_captures) && (__cpp_init_captures >= 201304)
#    define BKSGE_HAS_CXX14_INIT_CAPTURES
#  endif
#  if (BKSGE_GCC_VERSION >= 40900) && defined(__cpp_generic_lambdas) && (__cpp_generic_lambdas >= 201304)
#    define BKSGE_HAS_CXX14_GENERIC_LAMBDAS
#  endif
#  if (BKSGE_GCC_VERSION >= 40900) && (BKSGE_HAS_CPP_ATTRIBUTE(deprecated) >= 201309)
#    define BKSGE_HAS_CXX14_DEPRECATED
#  endif
#  if (BKSGE_GCC_VERSION >= 50000) && defined(__cpp_sized_deallocation) && (__cpp_sized_deallocation >= 201309)
#    define BKSGE_HAS_CXX14_SIZED_DEALLOCATION
#  endif
#  if (BKSGE_GCC_VERSION >= 40900) && defined(__cpp_digit_separator) && (__cpp_digit_separator >= 201309)
#    define BKSGE_HAS_CXX14_DIGIT_SEPARATORS
#  endif
#  if (BKSGE_GCC_VERSION >= 50000) && defined(__cpp_variable_templates) && (__cpp_variable_templates >= 201304)
#    define BKSGE_HAS_CXX14_VARIABLE_TEMPLATES
#  endif
#  if (BKSGE_GCC_VERSION >= 50000) && defined(__cpp_constexpr) && (__cpp_constexpr >= 201304)
#    define BKSGE_HAS_CXX14_CONSTEXPR
#  endif
#  if (BKSGE_GCC_VERSION >= 50000) && defined(__cpp_aggregate_nsdmi) && (__cpp_aggregate_nsdmi >= 201304)
#    define BKSGE_HAS_CXX14_AGGREGATE_NSDMI
#  endif
#endif

// C++17
#if (BKSGE_CXX_STANDARD >= 17)
#  if (BKSGE_GCC_VERSION >= 30000) && defined(__cpp_hex_float) && (__cpp_hex_float >= 201603)
#    define BKSGE_HAS_CXX17_HEX_FLOAT
#  endif
#  if (BKSGE_GCC_VERSION >= 60000) && defined(__cpp_unicode_characters) && (__cpp_unicode_characters >= 201411)
#    define BKSGE_HAS_CXX17_U8_CHARACTER_LITERALS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_inline_variables) && (__cpp_inline_variables >= 201606)
#    define BKSGE_HAS_CXX17_INLINE_VARIABLES
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_aligned_new) && (__cpp_aligned_new >= 201606)
#    define BKSGE_HAS_CXX17_ALIGNED_NEW
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_guaranteed_copy_elision) && (__cpp_guaranteed_copy_elision >= 201606)
#    define BKSGE_HAS_CXX17_GUARANTEED_COPY_ELISION
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_noexcept_function_type) && (__cpp_noexcept_function_type >= 201510)
#    define BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE
#  endif
#  if (BKSGE_GCC_VERSION >= 70000)
#    define BKSGE_HAS_CXX17_EXPRESSION_EVALUATION_ORDER
#  endif
#  if (BKSGE_GCC_VERSION >= 60000) && defined(__cpp_fold_expressions) && (__cpp_fold_expressions >= 201411)
#    define BKSGE_HAS_CXX17_FOLD_EXPRESSIONS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_capture_star_this) && (__cpp_capture_star_this >= 201603)
#    define BKSGE_HAS_CXX17_CAPTURE_STAR_THIS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_constexpr) && (__cpp_constexpr >= 201603)
#    define BKSGE_HAS_CXX17_CONSTEXPR_LAMBDA
#    define BKSGE_HAS_CXX17_CONSTEXPR
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_if_constexpr) && (__cpp_if_constexpr >= 201606)
#    define BKSGE_HAS_CXX17_IF_CONSTEXPR
#  endif
#  if (BKSGE_GCC_VERSION >= 70000)
#    define BKSGE_HAS_CXX17_SELECTION_WITH_INIT
#  endif
#  if (BKSGE_GCC_VERSION >= 60000) && defined(__cpp_range_based_for) && (__cpp_range_based_for >= 201603)
#    define BKSGE_HAS_CXX17_RANGE_BASED_FOR
#  endif
#  if (BKSGE_GCC_VERSION >= 60000) && defined(__cpp_static_assert) && (__cpp_static_assert >= 201411)
#    define BKSGE_HAS_CXX17_STATIC_ASSERT
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_deduction_guides) && (__cpp_deduction_guides >= 201606)
#    define BKSGE_HAS_CXX17_DEDUCTION_GUIDES
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_nontype_template_parameter_auto) && (__cpp_nontype_template_parameter_auto >= 201606)
#    define BKSGE_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO
#  endif
#  if (BKSGE_GCC_VERSION >= 40900) && defined(__cpp_namespace_attributes) && (__cpp_namespace_attributes >= 201411 )
#    define BKSGE_HAS_CXX17_NAMESPACE_ATTRIBUTES
#  endif
#  if (BKSGE_GCC_VERSION >= 60000) && defined(__cpp_enumerator_attributes) && (__cpp_enumerator_attributes >= 201411 )
#    define BKSGE_HAS_CXX17_ENUMERATOR_ATTRIBUTES
#  endif
#  if (BKSGE_GCC_VERSION >= 60000) && defined(__cpp_nested_namespace_definitions) && (__cpp_nested_namespace_definitions >= 201411 )
#    define BKSGE_HAS_CXX17_NESTED_NAMESPACE_DEFINITIONS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_inheriting_constructors) && (__cpp_inheriting_constructors >= 201511 )
#    define BKSGE_HAS_CXX17_INHERITING_CONSTRUCTORS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_variadic_using) && (__cpp_variadic_using >= 201611 )
#    define BKSGE_HAS_CXX17_VARIADIC_USING
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && (BKSGE_HAS_CPP_ATTRIBUTE(fallthrough) >= 201603 )
#    define BKSGE_HAS_CXX17_FALLTHROUGH
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && (BKSGE_HAS_CPP_ATTRIBUTE(nodiscard) >= 201603 )
#    define BKSGE_HAS_CXX17_NODISCARD
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && (BKSGE_HAS_CPP_ATTRIBUTE(maybe_unused) >= 201603 )
#    define BKSGE_HAS_CXX17_MAYBE_UNUSED
#  endif
#  if (BKSGE_GCC_VERSION >= 70000)
#    define BKSGE_HAS_CXX17_USING_ATTRIBUTE_NAMESPACES
#  endif
#    define BKSGE_HAS_CXX17_IGNORING_UNRECOGNIZED_ATTRIBUTES
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_structured_bindings) && (__cpp_structured_bindings >= 201606 )
#    define BKSGE_HAS_CXX17_STRUCTURED_BINDINGS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_aggregate_bases) && (__cpp_aggregate_bases >= 201603 )
#    define BKSGE_HAS_CXX17_AGGREGATE_BASES
#  endif
#  if (BKSGE_GCC_VERSION >= 70000)
#    define BKSGE_HAS_CXX17_INIT_ENUM_CLASS
#  endif
#  if (BKSGE_GCC_VERSION >= 50000)
#    define BKSGE_HAS_CXX17_TEMPLATE_TEMPLATE_TYPENAME
#  endif
#  if (BKSGE_GCC_VERSION >= 60000) && defined(__cpp_nontype_template_args) && (__cpp_nontype_template_args >= 201411 )
#    define BKSGE_HAS_CXX17_NONTYPE_TEMPLATE_ARGS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000) && defined(__cpp_template_template_args) && (__cpp_template_template_args >= 201611 )
#    define BKSGE_HAS_CXX17_TEMPLATE_TEMPLATE_ARGS
#  endif
#  if (BKSGE_GCC_VERSION >= 70000)
#    define BKSGE_HAS_CXX17_EXCEPTION_SPECIFICATIONS
#  endif
#  if (BKSGE_GCC_VERSION >= 50000) && defined(__has_include)
#    define BKSGE_HAS_CXX17_HAS_INCLUDE
#  endif
#endif

#if (BKSGE_GCC_VERSION >= 50000)
#  define BKSGE_HAS_CXX17_AUTO_DEDUCTION_BRACED_INIT_LIST
#endif

// C++20
#if (BKSGE_CXX_STANDARD >= 20)
#  if (BKSGE_GCC_VERSION >= 80000)
#    define BKSGE_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER
#    define BKSGE_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS
#    define BKSGE_HAS_CXX20_CAPTURE_COPY_THIS
#    define BKSGE_HAS_CXX20_TEMPLATE_LAMBDA
#    define BKSGE_HAS_CXX20_DESIGNATED_INITIALIZERS
#  endif
#  if (BKSGE_GCC_VERSION >= 90000)
#    define BKSGE_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER
#  endif
#endif

#if defined(__MINGW32__)
// Currently (June 2017) thread_local is broken on mingw for all current compiler releases, see
// https://sourceforge.net/p/mingw-w64/bugs/527/
// Not setting this causes program termination on thread exit.
#  undef BKSGE_HAS_CXX11_THREAD_LOCAL
#endif

#endif // BKSGE_CONFIG_COMPILER_GCC_HPP
