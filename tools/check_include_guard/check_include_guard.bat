@echo off
SET PATH=%PATH%;C:\python27

python check_include_guard.py -r ../../include/bksge -p bksge
python check_include_guard.py -r ../../test/src/ -p unit_test
