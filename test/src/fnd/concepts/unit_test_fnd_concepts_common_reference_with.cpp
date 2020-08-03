/**
 *	@file	unit_test_fnd_concepts_common_reference_with.cpp
 *
 *	@brief	common_reference_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_COMMON_REFERENCE_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::common_reference_with<T1, T2>, "")
#else
#  define BKSGE_COMMON_REFERENCE_WITH_TEST(B, T1, T2)	\
	static_assert(B == bksge::common_reference_with<T1, T2>::value, "")
#endif

namespace bksge_concepts_test
{

namespace common_reference_with_test
{

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const volatile);

BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               , int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               , int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               , int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               , int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         , int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         , int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         , int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         , int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int const volatile*);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const volatile&);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               , int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const volatile&&);

BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const volatile);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int const volatile*);

BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const volatile&);

BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               *, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const volatile&&);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const volatile);

BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int const volatile*);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const volatile&);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const volatile&&);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int               );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const         );
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int       volatile);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const volatile);

BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &&, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &&, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &&, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int               &&, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int const volatile*);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int               &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const         &);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int       volatile&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const volatile&);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int               &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const         &&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int       volatile&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const volatile&&);

BKSGE_COMMON_REFERENCE_WITH_TEST(false, int, void);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, int, int());

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int               *, void const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void const volatile*);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int const volatile*);


BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void               *, void const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void const volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void               *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void const         *);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void       volatile*);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void const volatile*);

BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int      *&, void      *&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int      *&, void const*&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const*&, void      *&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  int const*&, void const*&);

struct A { A(int) { } };
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  A, int);

struct B { };
BKSGE_COMMON_REFERENCE_WITH_TEST(false, A, B);

struct C { C(A&) { } };
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  A&, C);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  A&, C&&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  A&, const C&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  A&, C&);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, const A&, C);
BKSGE_COMMON_REFERENCE_WITH_TEST(false, const A&, const C&);

struct D;
struct E { E(D&) { } };
struct D { D(E&) { } };
BKSGE_COMMON_REFERENCE_WITH_TEST(false, D&, E&); // ambiguous conversion

struct F;
struct G { G(const F&) { } };
struct F { F(const G&) { } };

}	// namespace common_reference_with_test

}	// namespace bksge_concepts_test

namespace bksge
{

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	bksge_concepts_test::common_reference_with_test::F,
	bksge_concepts_test::common_reference_with_test::G,
	Qual1, Qual2>
{
	using type = Qual1<Qual2<bksge_concepts_test::common_reference_with_test::F>>;
};

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	bksge_concepts_test::common_reference_with_test::G,
	bksge_concepts_test::common_reference_with_test::F,
	Qual1, Qual2>
{
	using type = Qual1<Qual2<bksge_concepts_test::common_reference_with_test::F>>;
};

}	// namespace bksge

namespace bksge_concepts_test
{

namespace common_reference_with_test
{

BKSGE_COMMON_REFERENCE_WITH_TEST(false, F&, G&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  F, G);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  F, const G);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  const F, const G);

struct Base { };
struct Derived : Base { };
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  Derived&, Base&);
BKSGE_COMMON_REFERENCE_WITH_TEST(true,  Derived*, Base*);

}	// namespace common_reference_with_test

}	// namespace bksge_concepts_test

#undef BKSGE_COMMON_REFERENCE_WITH_TEST
