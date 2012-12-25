#!/usr/bin/env python
import sys
import random

while True:
	turn = int(raw_input())
	finger = [[], []]
	for i in range(0, 2):
		for j in range(0, 2):
			finger[i].append([int(k) for k in raw_input().split()])

	print '%d %d %d' % (random.randint(0, 1), random.randint(0, 1), random.randint(-3, 3))
	sys.stdout.flush()
