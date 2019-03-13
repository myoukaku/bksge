# -*- coding: utf-8 -*-

import os
import os.path
import codecs
#import sys
import argparse
import subprocess

parser = argparse.ArgumentParser(description='')
parser.add_argument("-r", "--root_path")

args = parser.parse_args()

root_path = args.root_path

for root, dirs, files in os.walk(root_path):
	for file in files:
		name, ext = os.path.splitext(file)
		if ext not in [".hpp", ".cpp"]:
			continue

		file_path = os.path.join(root, file)
		file_name = os.path.basename(file_path)
		s = codecs.open(file_path, "r", "utf-8-sig").read()
		if not "@file	" + file_name in s:
			subprocess.Popen("start " + file_path, shell=True)
