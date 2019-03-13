@echo off
SET PATH=%PATH%;C:\python27

python check_file_comment.py -r ../../include/bksge/
python check_file_comment.py -r ../../test/src/
