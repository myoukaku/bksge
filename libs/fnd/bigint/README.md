[![bigint](https://github.com/myoukaku/bksge/actions/workflows/bigint.yml/badge.svg)](https://github.com/myoukaku/bksge/actions/workflows/bigint.yml)

# Bksge.BigInt

このライブラリは、固定長の整数型と無限長の整数型を提供します。

| 型名 | 符号 | ビット長 |
| ---- | ---- | ---- |
| int128_t   | 符号付き| 128ビット |
| int256_t   | 符号付き| 256ビット |
| int512_t   | 符号付き| 512ビット |
| int1024_t  | 符号付き| 1024ビット |
| int2048_t  | 符号付き| 2048ビット |
| uint128_t  | 符号無し| 128ビット |
| uint256_t  | 符号無し| 256ビット |
| uint512_t  | 符号無し| 512ビット |
| uint1024_t | 符号無し| 1024ビット |
| uint2048_t | 符号無し| 2048ビット |
| bigint     | 符号付き| 無限ビット |

無限長の符号なし型は提供されません。

固定長の型は、ビット長以外の追加のメモリを必要としません。例えばint128_tは128ビットしか使いません。

### 依存ライブラリ

* Bksge.Bit
* Bksge.Concepts
* Bksge.Config
* Bksge.CStdDef
* Bksge.CString
* Bksge.Debug
* Bksge.Functional
* Bksge.Iterator
* Bksge.Memory
* Bksge.Numeric
* Bksge.Random
* Bksge.Ranges
* Bksge.TypeTraits
* Bksge.Utility
* Bksge.Vector

