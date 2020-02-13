@echo off
SET PATH=C:\python27;%PATH%

python check_file_comment.py -r ../../include/bksge/
python check_file_comment.py -r ../../test/src/
python check_file_comment.py -r ../../src/bksge/
python check_file_comment.py -r ../../samples/
