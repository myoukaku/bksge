# -*- coding: utf-8 -*-

import os
import os.path
import codecs
#import sys
import argparse
import glob

parser = argparse.ArgumentParser(description='')
parser.add_argument("-r", "--root_path")
parser.add_argument("-f", "--file_path")
parser.add_argument("-d", "--search_directory")
parser.add_argument("-b", "--brief")
parser.add_argument("-a", "--author")

args = parser.parse_args()

root_path = args.root_path
file_path = args.file_path
search_directory = args.search_directory
brief = unicode(args.brief, "'shift-jis'")
author = unicode(args.author, "'shift-jis'")

file_path = os.path.join(root_path, file_path)
f = codecs.open(file_path, "w", "utf-8-sig");

header_comment = u"/**\r\n\
 *	@file	{0}\r\n\
 *\r\n\
 *	@brief	{1}\r\n\
 *\r\n\
 *	@author	{2}\r\n\
 */\r\n\
\r\n\
".format(os.path.basename(file_path), brief, author)

f.write(header_comment)

include_guard = os.path.relpath(file_path, root_path)
include_guard = include_guard.upper().replace("\\", "_").replace(".", "_")

f.write("#ifndef " + include_guard + "\r\n")
f.write("#define " + include_guard + "\r\n")
f.write("\r\n")

search_directory = os.path.join(root_path, search_directory)

files = glob.glob(search_directory)
for file in files:
	p = os.path.relpath(file, root_path)
	p = p.replace("\\", "/")
	f.write("#include <" + p + ">\r\n")

f.write("\r\n")
f.write("#endif // " + include_guard + "\r\n")
