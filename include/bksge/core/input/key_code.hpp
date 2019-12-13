/**
 *	@file	key_code.hpp
 *
 *	@brief	KeyCode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_KEY_CODE_HPP
#define BKSGE_CORE_INPUT_KEY_CODE_HPP

namespace bksge
{

namespace input
{

/**
 *	@brief	キーコードの定義
 */
enum class KeyCode
{
	kUnassigned,
	kEscape,
	k1,
	k2,
	k3,
	k4,
	k5,
	k6,
	k7,
	k8,
	k9,
	k0,
	kMinus,           // - on main keyboard
	kEquals,
	kBack,            // backspace
	kTab,
	kQ,
	kW,
	kE,
	kR,
	kT,
	kY,
	kU,
	kI,
	kO,
	kP,
	kLBracket,
	kRBracket,
	kReturn,          // Enter on main keyboard
	kLControl,
	kA,
	kS,
	kD,
	kF,
	kG,
	kH,
	kJ,
	kK,
	kL,
	kSemicolon,
	kApostrophe,
	kGrave,           // accent
	kLShift,
	kBackslash,
	kZ,
	kX,
	kC,
	kV,
	kB,
	kN,
	kM,
	kComma,
	kPeriod,          // . on main keyboard
	kSlash,           // / on main keyboard
	kRShift,
	kMultiply,        // * on numeric keypad
	kLMenu,           // left Alt
	kSpace,
	kCapital,
	kF1,
	kF2,
	kF3,
	kF4,
	kF5,
	kF6,
	kF7,
	kF8,
	kF9,
	kF10,
	kNumlock,
	kScroll,          // Scroll Lock
	kNumpad7,
	kNumpad8,
	kNumpad9,
	kSubtract,        // - on numeric keypad
	kNumpad4,
	kNumpad5,
	kNumpad6,
	kAdd,             // + on numeric keypad
	kNumpad1,
	kNumpad2,
	kNumpad3,
	kNumpad0,
	kDecimal,         // . on numeric keypad
	kOem_102,         // < > | on UK/Germany keyboards
	kF11,
	kF12,
	kF13,             //                     (NEC PC98)
	kF14,             //                     (NEC PC98)
	kF15,             //                     (NEC PC98)
	kKana,            // (Japanese keyboard)
	kAbnt_c1,         // / ? on Portuguese (Brazilian) keyboards
	kConvert,         // (Japanese keyboard)
	kNoconvert,       // (Japanese keyboard)
	kYen,             // (Japanese keyboard)
	kAbnt_c2,         // Numpad . on Portuguese (Brazilian) keyboards
	kNumpadEquals,    // = on numeric keypad (NEC PC98)
	kPrevtrack,       // Previous Track (KC_CIRCUMFLEX on Japanese keyboard)
	kAt,              //                     (NEC PC98)
	kColon,           //                     (NEC PC98)
	kUnderline,       //                     (NEC PC98)
	kKanji,           // (Japanese keyboard)
	kStop,            //                     (NEC PC98)
	kAx,              //                     (Japan AX)
	kUnlabeled,       //                        (J3100)
	kNextTrack,       // Next Track
	kNumpadEnter,     // Enter on numeric keypad
	kRControl,
	kMute,            // Mute
	kCalculator,      // Calculator
	kPlayPause,       // Play / Pause
	kMediaStop,       // Media Stop
	kVolumeDown,      // Volume -
	kVolumeUp,        // Volume +
	kWebHome,         // Web home
	kNumpadComma,     // , on numeric keypad (NEC PC98)
	kDivide,          // / on numeric keypad
	kSysrq,
	kRMenu,           // right Alt
	kPause,           // Pause
	kHome,            // Home on arrow keypad
	kUp,              // UpArrow on arrow keypad
	kPrior,           // PgUp on arrow keypad
	kLeft,            // LeftArrow on arrow keypad
	kRight,           // RightArrow on arrow keypad
	kEnd,             // End on arrow keypad
	kDown,            // DownArrow on arrow keypad
	kNext,            // PgDn on arrow keypad
	kInsert,          // Insert on arrow keypad
	kDelete,          // Delete on arrow keypad
	kLWin,            // Left Windows key
	kRWin,            // Right Windows key
	kApps,            // AppMenu key
	kPower,           // System Power
	kSleep,           // System Sleep
	kWake,            // System Wake
	kWebSearch,       // Web Search
	kWebFavorites,    // Web Favorites
	kWebRefresh,      // Web Refresh
	kWebStop,         // Web Stop
	kWebForward,      // Web Forward
	kWebBack,         // Web Back
	kMyComputer,      // My Computer
	kMail,            // Mail
	kMediaSelect,     // Media Select

	kMax,	// 総数

	// 以下はエイリアス
	kBackspace			= kBack,            // backspace
	kNumpadStar			= kMultiply,        // * on numeric keypad
	kLAlt				= kLMenu,           // left Alt
	kCapsLock			= kCapital,         // CapsLock
	kNumpadMinus		= kSubtract,        // - on numeric keypad
	kNumpadPlus			= kAdd,             // + on numeric keypad
	kNumpadPeriod		= kDecimal,         // . on numeric keypad
	kNumpadSlash		= kDivide,          // / on numeric keypad
	kRAlt				= kRMenu,           // right Alt
	kUpArrow			= kUp,              // UpArrow on arrow keypad
	kLeftArrow			= kLeft,            // LeftArrow on arrow keypad
	kRightArrow			= kRight,           // RightArrow on arrow keypad
	kDownArrow			= kDown,            // DownArrow on arrow keypad
	kPgUp				= kPrior,           // PgUp on arrow keypad
	kPgDn				= kNext,            // PgDn on arrow keypad
	kCircumflex			= kPrevtrack,		 // ^
};

}	// namespace input

using input::KeyCode;

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_KEY_CODE_HPP
