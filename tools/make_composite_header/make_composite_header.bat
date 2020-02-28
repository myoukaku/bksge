@echo off
SET PATH=C:\python27;%PATH%

call :func bksge/fnd/algorithm            "Algorithm library"
call :func bksge/fnd/bit                  "Bit library"
call :func bksge/fnd/cmath                "CMath library"
call :func bksge/fnd/cstddef              "CStdDef library"
call :func bksge/fnd/functional           "Functional library"
call :func bksge/fnd/ios                  "Ios library"
call :func bksge/fnd/iterator/type_traits "Iterator Type Traits"
call :func bksge/fnd/iterator             "Iterator library"
call :func bksge/fnd/memory               "Memory library"
call :func bksge/fnd/numeric              "Numeric library"
call :func bksge/fnd/optional             "Optional library"
call :func bksge/fnd/random/engines       "Random Engines"
call :func bksge/fnd/random               "Random library"
call :func bksge/fnd/ratio                "Ratio library"
call :func bksge/fnd/serialization        "Serialization library"
call :func bksge/fnd/stdexcept            "StdExcept library"
call :func bksge/fnd/tmp                  "TMP(Template Meta Programming) library"
call :func bksge/fnd/tpp                  "TPP(Template Parameter Pack) library"
call :func bksge/fnd/tuple                "Tuple library"
call :func bksge/fnd/type_traits          "Type Traits library"
call :func bksge/fnd/units                "Units library"
call :func bksge/fnd/utility              "Utility library"
call :func bksge/fnd                      "Foundation library"

call :func bksge/core/input               "Input library"
call :func bksge/core/math                "Math library"
call :func bksge/core/render              "Render library"
call :func bksge/core/window              "Window library"
call :func bksge/core                     "Core library"

call :func2 bksge/bksge   bksge           "Bksge library"

exit /b

:func
python make_composite_header.py -r ../../include/ -f %1.hpp -d %1/*.hpp -b %2 -a myoukaku
exit /b

:func2
python make_composite_header.py -r ../../include/ -f %1.hpp -d %2/*.hpp -b %3 -a myoukaku
exit /b
