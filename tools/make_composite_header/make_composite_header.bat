@echo off
SET PATH=%PATH%;C:\python27

call :func bksge/cmath                "CMath library"
call :func bksge/input                "Input library"
call :func bksge/math                 "Math library"
call :func bksge/memory               "Memory library"
call :func bksge/render               "Render library"
call :func bksge/serialization        "Serialization library"
call :func bksge/stdexcept            "StdExcept library"
call :func bksge/type_traits          "Type Traits library"
call :func bksge/utility              "Utility library"
call :func bksge/window               "Window library"

call :func2 bksge/bksge   bksge       "Bksge library"

exit /b

:func
python make_composite_header.py -r ../../include/ -f %1.hpp -d %1/*.hpp -b %2 -a myoukaku
exit /b

:func2
python make_composite_header.py -r ../../include/ -f %1.hpp -d %2/*.hpp -b %3 -a myoukaku
exit /b
