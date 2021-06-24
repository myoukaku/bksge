[![cmath](https://github.com/myoukaku/bksge/actions/workflows/cmath.yml/badge.svg)](https://github.com/myoukaku/bksge/actions/workflows/cmath.yml)

# Bksge.CMath

このライブラリはstd::cmathの独自実装またはラッパーです。
ほとんどの場面でstd::cmathと同じように使えます。

### std::cmathからの変更点

* 可能な限りconstexprをつけた
* C++の特定のバージョン以降で追加された関数をC++のバージョンに関係なく使えるようにした
* 関数を追加

### 追加した関数

* almost_equal
* decompose_float
* degrees_to_radians
* double_factorial
* factorial
* frac
* is_even
* is_integer
* is_negative
* is_odd
* is_positive
* radians_to_degrees
* repeat
* round_down
* round_half_even
* round_up
* rsqrt
* saturate
* smoothstep
* step

### 依存ライブラリ

* Bksge.Algorithm
* Bksge.Array
* Bksge.Bit
* Bksge.Concepts
* Bksge.Config
* Bksge.CStdDef
* Bksge.CStdInt
* Bksge.Numbers
* Bksge.StdExcept
* Bksge.TypeTraits
* Bksge.Utility

