#!/usr/bin/python

import sys

def is_subsequence(C,A):
	j = 0
	for i in range(len(A)):
		if A[i] == C[j]:
			j+=1
			if j == len(C):
				return True
	return False

if len(sys.argv) != 4:
	print "usage:",sys.argv[0],"inputfile outputfile youroutputfile"
	exit(0)
f = open(sys.argv[1], "r")
A = f.readline().strip()
B = f.readline().strip()
f.close()

f = open(sys.argv[2], "r")
l = int(f.readline().strip())
f.close()

f = open(sys.argv[3], "r")
ml = int(f.readline().strip())
C = f.readline().strip()
f.close()

if ml != l: 
	print "0 The length of the LCS is not correct"
	exit(0)

if len(C) != ml: 
	print "0 The length of your string is not", ml
	exit(0)

if not is_subsequence(C, A):
	print "0 Your output string is not a subsequence of the first input string"
	exit(0)

if not is_subsequence(C, B):
	print "0 Your output string is not a subsequence of the second input string"
	exti(0)

print "1 Correct"
