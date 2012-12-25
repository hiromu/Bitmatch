#!/usr/bin/env python
import sys
import random

def apply(mine, target, diff):
	if mine == [1, 1, 1, 1] or target == [1, 1, 1, 1]:
		return -1

	if diff < 0:
		for i in range(0, 4):
			if i - diff < 4:
				mine[i] = mine[i - diff]
			else:
				mine[i] = 0
	elif diff > 0:
		for i in range(3, -1, -1):
			if i - diff > -1:
				mine[i] = mine[i - diff]
			else:
				mine[i] = 0

	count = 0
	for i in range(0, 4):
		target[i] ^= mine[i]
		if target[i]:
			count += 1
	return count

while True:
	turn = int(raw_input())
	finger = [[], []]
	for i in range(0, 2):
		for j in range(0, 2):
			finger[i].append([int(k) for k in raw_input().split()])

	maximum = -1
	response = []
	for i in range(0, 2):
		for j in range(0, 2):
			for k in range(-3, 4):
				result = apply(finger[0][i], finger[1][j], k)
				if result > maximum:
					maximum = result
					response = [(i, j, k)]
				elif result == maximum:
					response.append((i, j, k))
	
	if maximum != -1:
		print ' '.join([str(i) for i in random.choice(response)])
	else:
		print '2 2 0'
	sys.stdout.flush()
