[![array](https://github.com/myoukaku/bksge/actions/workflows/array.yml/badge.svg)](https://github.com/myoukaku/bksge/actions/workflows/array.yml)

# Bksge.Array

このライブラリはstd::arrayの独自実装またはラッパーです。
ほとんどの場面でstd::arrayと同じように使えます。

### std::arrayからの変更点

* 可能な限りconstexprをつけた
* C++の特定のバージョン以降で追加された関数をC++のバージョンに関係なく使えるようにした

### 依存ライブラリ

* Bksge.Algorithm
* Bksge.Compare
* Bksge.Config
* Bksge.CStdDef
* Bksge.CString
* Bksge.Iterator
* Bksge.StdExcept
* Bksge.Tuple
* Bksge.TypeTraits
* Bksge.Utility)
