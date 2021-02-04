﻿/**
 *	@file	factorial_impl.hpp
 *
 *	@brief	factorial 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FACTORIAL_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FACTORIAL_IMPL_HPP

#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uintmax_t.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <bool Unsigned, bksge::size_t N>
struct max_factorial_t;

template <> struct max_factorial_t<false, 1> { static const unsigned int value = 5; };
template <> struct max_factorial_t<true,  1> { static const unsigned int value = 5; };
template <> struct max_factorial_t<false, 2> { static const unsigned int value = 7; };
template <> struct max_factorial_t<true,  2> { static const unsigned int value = 8; };
template <> struct max_factorial_t<false, 4> { static const unsigned int value = 12; };
template <> struct max_factorial_t<true,  4> { static const unsigned int value = 12; };
template <> struct max_factorial_t<false, 8> { static const unsigned int value = 20; };
template <> struct max_factorial_t<true,  8> { static const unsigned int value = 20; };

template <typename T>
BKSGE_CONSTEXPR unsigned int max_factorial() BKSGE_NOEXCEPT
{
	return max_factorial_t<bksge::is_unsigned<T>::value, sizeof(T)>::value;
}

template <>
inline BKSGE_CONSTEXPR unsigned int max_factorial<float>() BKSGE_NOEXCEPT
{
	return 34;
}
template <>
inline BKSGE_CONSTEXPR unsigned int max_factorial<double>() BKSGE_NOEXCEPT
{
	return 170;
}
template <>
inline BKSGE_CONSTEXPR unsigned int max_factorial<long double>() BKSGE_NOEXCEPT
{
	return 170;
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, T)>
inline BKSGE_CONSTEXPR T
unchecked_factorial_impl(unsigned int n, bksge::detail::overload_priority<2>) BKSGE_NOEXCEPT
{
	BKSGE_CONSTEXPR bksge::uintmax_t tbl[] =
	{
		1,                      //  0!
		1,                      //  1!
		2,						//  2!
		6,						//  3!
		24,						//  4!
		120,					//  5!
		720,					//  6!
		5040,					//  7!
		40320,					//  8!
		362880,					//  9!
		3628800,				// 10!
		39916800,				// 11!
		479001600,				// 12!
		6227020800,				// 13!
		87178291200,			// 14!
		1307674368000,			// 15!
		20922789888000,			// 16!
		355687428096000,		// 17!
		6402373705728000,		// 18!
		121645100408832000,		// 19!
		2432902008176640000,	// 20!
	};
	return static_cast<T>(tbl[n]);
}

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T
unchecked_factorial_impl(unsigned int n, bksge::detail::overload_priority<1>) BKSGE_NOEXCEPT
{
	BKSGE_CONSTEXPR long double tbl[] =
	{
		1.0,
		1.0,
		2.0,
		6.0,
		24.0,
		120.0,
		720.0,
		5040.0,
		40320.0,
		362880.0,
		3628800.0,
		39916800.0,
		479001600.0,
		6227020800.0,
		87178291200.0,
		1307674368000.0,
		20922789888000.0,
		355687428096000.0,
		6402373705728000.0,
		121645100408832000.0,
		0.243290200817664e19,
		0.5109094217170944e20,
		0.112400072777760768e22,
		0.2585201673888497664e23,
		0.62044840173323943936e24,
		0.15511210043330985984e26,
		0.403291461126605635584e27,
		0.10888869450418352160768e29,
		0.304888344611713860501504e30,
		0.8841761993739701954543616e31,
		0.26525285981219105863630848e33,
		0.822283865417792281772556288e34,
		0.26313083693369353016721801216e36,
		0.868331761881188649551819440128e37,
		0.29523279903960414084761860964352e39,
		0.103331479663861449296666513375232e41,
		0.3719933267899012174679994481508352e42,
		0.137637530912263450463159795815809024e44,
		0.5230226174666011117600072241000742912e45,
		0.203978820811974433586402817399028973568e47,
		0.815915283247897734345611269596115894272e48,
		0.3345252661316380710817006205344075166515e50,
		0.1405006117752879898543142606244511569936e52,
		0.6041526306337383563735513206851399750726e53,
		0.265827157478844876804362581101461589032e55,
		0.1196222208654801945619631614956577150644e57,
		0.5502622159812088949850305428800254892962e58,
		0.2586232415111681806429643551536119799692e60,
		0.1241391559253607267086228904737337503852e62,
		0.6082818640342675608722521633212953768876e63,
		0.3041409320171337804361260816606476884438e65,
		0.1551118753287382280224243016469303211063e67,
		0.8065817517094387857166063685640376697529e68,
		0.427488328406002556429801375338939964969e70,
		0.2308436973392413804720927426830275810833e72,
		0.1269640335365827592596510084756651695958e74,
		0.7109985878048634518540456474637249497365e75,
		0.4052691950487721675568060190543232213498e77,
		0.2350561331282878571829474910515074683829e79,
		0.1386831185456898357379390197203894063459e81,
		0.8320987112741390144276341183223364380754e82,
		0.507580213877224798800856812176625227226e84,
		0.3146997326038793752565312235495076408801e86,
		0.1982608315404440064116146708361898137545e88,
		0.1268869321858841641034333893351614808029e90,
		0.8247650592082470666723170306785496252186e91,
		0.5443449390774430640037292402478427526443e93,
		0.3647111091818868528824985909660546442717e95,
		0.2480035542436830599600990418569171581047e97,
		0.1711224524281413113724683388812728390923e99,
		0.1197857166996989179607278372168909873646e101,
		0.8504785885678623175211676442399260102886e102,
		0.6123445837688608686152407038527467274078e104,
		0.4470115461512684340891257138125051110077e106,
		0.3307885441519386412259530282212537821457e108,
		0.2480914081139539809194647711659403366093e110,
		0.188549470166605025498793226086114655823e112,
		0.1451830920282858696340707840863082849837e114,
		0.1132428117820629783145752115873204622873e116,
		0.8946182130782975286851441715398316520698e117,
		0.7156945704626380229481153372318653216558e119,
		0.5797126020747367985879734231578109105412e121,
		0.4753643337012841748421382069894049466438e123,
		0.3945523969720658651189747118012061057144e125,
		0.3314240134565353266999387579130131288001e127,
		0.2817104114380550276949479442260611594801e129,
		0.2422709538367273238176552320344125971528e131,
		0.210775729837952771721360051869938959523e133,
		0.1854826422573984391147968456455462843802e135,
		0.1650795516090846108121691926245361930984e137,
		0.1485715964481761497309522733620825737886e139,
		0.1352001527678402962551665687594951421476e141,
		0.1243841405464130725547532432587355307758e143,
		0.1156772507081641574759205162306240436215e145,
		0.1087366156656743080273652852567866010042e147,
		0.103299784882390592625997020993947270954e149,
		0.9916779348709496892095714015418938011582e150,
		0.9619275968248211985332842594956369871234e152,
		0.942689044888324774562618574305724247381e154,
		0.9332621544394415268169923885626670049072e156,
		0.9332621544394415268169923885626670049072e158,
		0.9425947759838359420851623124482936749562e160,
		0.9614466715035126609268655586972595484554e162,
		0.990290071648618040754671525458177334909e164,
		0.1029901674514562762384858386476504428305e167,
		0.1081396758240290900504101305800329649721e169,
		0.1146280563734708354534347384148349428704e171,
		0.1226520203196137939351751701038733888713e173,
		0.132464181945182897449989183712183259981e175,
		0.1443859583202493582204882102462797533793e177,
		0.1588245541522742940425370312709077287172e179,
		0.1762952551090244663872161047107075788761e181,
		0.1974506857221074023536820372759924883413e183,
		0.2231192748659813646596607021218715118256e185,
		0.2543559733472187557120132004189335234812e187,
		0.2925093693493015690688151804817735520034e189,
		0.339310868445189820119825609358857320324e191,
		0.396993716080872089540195962949863064779e193,
		0.4684525849754290656574312362808384164393e195,
		0.5574585761207605881323431711741977155627e197,
		0.6689502913449127057588118054090372586753e199,
		0.8094298525273443739681622845449350829971e201,
		0.9875044200833601362411579871448208012564e203,
		0.1214630436702532967576624324188129585545e206,
		0.1506141741511140879795014161993280686076e208,
		0.1882677176888926099743767702491600857595e210,
		0.237217324288004688567714730513941708057e212,
		0.3012660018457659544809977077527059692324e214,
		0.3856204823625804217356770659234636406175e216,
		0.4974504222477287440390234150412680963966e218,
		0.6466855489220473672507304395536485253155e220,
		0.8471580690878820510984568758152795681634e222,
		0.1118248651196004307449963076076169029976e225,
		0.1487270706090685728908450891181304809868e227,
		0.1992942746161518876737324194182948445223e229,
		0.269047270731805048359538766214698040105e231,
		0.3659042881952548657689727220519893345429e233,
		0.5012888748274991661034926292112253883237e235,
		0.6917786472619488492228198283114910358867e237,
		0.9615723196941089004197195613529725398826e239,
		0.1346201247571752460587607385894161555836e242,
		0.1898143759076170969428526414110767793728e244,
		0.2695364137888162776588507508037290267094e246,
		0.3854370717180072770521565736493325081944e248,
		0.5550293832739304789551054660550388118e250,
		0.80479260574719919448490292577980627711e252,
		0.1174997204390910823947958271638517164581e255,
		0.1727245890454638911203498659308620231933e257,
		0.2556323917872865588581178015776757943262e259,
		0.380892263763056972698595524350736933546e261,
		0.571338395644585459047893286526105400319e263,
		0.8627209774233240431623188626544191544816e265,
		0.1311335885683452545606724671234717114812e268,
		0.2006343905095682394778288746989117185662e270,
		0.308976961384735088795856467036324046592e272,
		0.4789142901463393876335775239063022722176e274,
		0.7471062926282894447083809372938315446595e276,
		0.1172956879426414428192158071551315525115e279,
		0.1853271869493734796543609753051078529682e281,
		0.2946702272495038326504339507351214862195e283,
		0.4714723635992061322406943211761943779512e285,
		0.7590705053947218729075178570936729485014e287,
		0.1229694218739449434110178928491750176572e290,
		0.2004401576545302577599591653441552787813e292,
		0.3287218585534296227263330311644146572013e294,
		0.5423910666131588774984495014212841843822e296,
		0.9003691705778437366474261723593317460744e298,
		0.1503616514864999040201201707840084015944e301,
		0.2526075744973198387538018869171341146786e303,
		0.4269068009004705274939251888899566538069e305,
		0.7257415615307998967396728211129263114717e307,
	};
	return static_cast<T>(tbl[n]);
}

template <typename T>
inline BKSGE_CONSTEXPR T
unchecked_factorial(unsigned int n) BKSGE_NOEXCEPT
{
	return unchecked_factorial_impl<T>(n, bksge::detail::overload_priority<2>{});
}

template <typename T>
inline BKSGE_CONSTEXPR T
factorial_impl(unsigned int n) BKSGE_NOEXCEPT
{
	if (n > max_factorial<T>())
	{
		return bksge::numeric_limits<T>::infinity();
	}

	return unchecked_factorial<T>(n);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FACTORIAL_IMPL_HPP
