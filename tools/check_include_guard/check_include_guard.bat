@echo off
SET PATH=C:\python27;%PATH%

python check_include_guard.py -r ../../include/bksge -p bksge
python check_include_guard.py -r ../../test/src/ -p unit_test
