set CMAKE_GENERATOR_LIST="Visual Studio 15 2017","Visual Studio 16 2019"
set PLATFORM_LIST=Win32,x64
set CXX_STANDARD_LIST=14,17,20
set CONFIGURATION=Debug

mkdir build
cd build

for %%a in (%CMAKE_GENERATOR_LIST%) do (
	for %%b in (%PLATFORM_LIST%) do (
		for %%c in (%CXX_STANDARD_LIST%) do (
			call :func %%a %%b %%c
		)
	)
)
exit /b 0



:func
	set CMAKE_GENERATOR=%~1
	set PLATFORM=%~2
	set CXX_STANDARD=%~3
	set DIRNAME="%CMAKE_GENERATOR%_%PLATFORM%_CXX%CXX_STANDARD%"
	mkdir %DIRNAME%
	cd %DIRNAME%
	cmake ..\..\ -G "%CMAKE_GENERATOR%" -A "%PLATFORM%" -DCMAKE_CXX_STANDARD="%CXX_STANDARD%" -DCMAKE_BUILD_TYPE="%CONFIGURATION%" -DCMAKE_CONFIGURATION_TYPES=Debug;Release
	cd ..
exit /b 0
