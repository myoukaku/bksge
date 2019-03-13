# -*- coding: utf-8 -*-

import os
import os.path
import codecs
#import sys
import argparse
import subprocess

parser = argparse.ArgumentParser(description='')
parser.add_argument("-r", "--root_path")
parser.add_argument("-p", "--project")

args = parser.parse_args()

root_path = args.root_path
project   = args.project

for root, dirs, files in os.walk(root_path):
	for file in files:
		name, ext = os.path.splitext(file)
		if ext != ".hpp":
			continue

		file_path = os.path.join(root, file)
		s = codecs.open(file_path, "r", "utf-8-sig").read()
		if "NO INCLUDE GUARD" in s:
			continue

		path = os.path.relpath(file_path, root_path)
		label = "_".join([project, path])
		label = label.upper()
		label = label.replace("\\", "_")
		label = label.replace(".", "_")
		if not "#ifndef " + label in s or not "#define " + label in s or not "#endif // " + label in s:
			subprocess.Popen("start " + file_path, shell=True)
