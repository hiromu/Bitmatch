#!/usr/bin/env python
import os
import sys
import time
import signal
import threading
import subprocess

TIMEOUT = 3
LIMIT = 1000

class BitMatch:
    def __init__(self, userA, userB):
        self.turn = 0
        self.finger = [[[0, 0, 0, 1], [1, 0, 0, 0]], [[1, 0, 0, 0], [0, 0, 0, 1]]]

        self.user = []
        self.user.append(subprocess.Popen(userA, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=open('/dev/null', 'w')))
        self.user.append(subprocess.Popen(userB, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=open('/dev/null', 'w')))
    
    def show(self):
        print 'A          B'

        for i in range(0, 2):
            for j in range(0, 4):
                s = ''
                if self.finger[0][i][j]:
                    s += '----'
                else:
                    s += '-   '
                s += '    '
                if self.finger[1][(i + 1) % 2][j]:
                    s += '----'
                else:
                    s += '   -'
                print s
            print ''

    def get_output(self, user_index, output):
        res = ''
        while True:
            c = self.user[user_index].stdout.read(1)
            if c == '\n':
                break
            res += c
        print '%s: %s\n' % (['A', 'B'][user_index], res)
        output.append(res)

    def execute(self, user_index):
        if self.user[user_index].poll():
            return False

        print 'Input:'
        print self.turn
        self.user[user_index].stdin.write('%d\n' % self.turn)
        if user_index == 0:
            for i in range(0, 2):
                print ' '.join([str(j) for j in self.finger[user_index][i]])
                self.user[user_index].stdin.write(' '.join([str(j) for j in self.finger[user_index][i]]) + '\n')
            for i in range(0, 2):
                print ' '.join([str(j) for j in self.finger[(user_index + 1) % 2][i]])
                self.user[user_index].stdin.write(' '.join([str(j) for j in self.finger[(user_index + 1) % 2][i]]) + '\n')
        elif user_index == 1:
            for i in range(0, 2):
                print ' '.join(reversed([str(j) for j in self.finger[user_index][i]]))
                self.user[user_index].stdin.write(' '.join(reversed([str(j) for j in self.finger[user_index][i]])) + '\n')
            for i in range(0, 2):
                print ' '.join(reversed([str(j) for j in self.finger[(user_index + 1) % 2][i]]))
                self.user[user_index].stdin.write(' '.join(reversed([str(j) for j in self.finger[(user_index + 1) % 2][i]])) + '\n')
        print ''
        self.user[user_index].stdin.flush()

        res = []
        thread = threading.Thread(target=self.get_output, args=(user_index, res))
        thread.start()
        start = time.time()

        while True:
            if not thread.is_alive():
                break
            if time.time() - start > TIMEOUT:
                return False
            time.sleep(0.01)

        if len(res) != 1:
            return False
        try:
            res = [int(i) for i in res[0].split()]
            if user_index == 1:
                res[2] = -res[2]
            return tuple(res)
        except TypeError:
            return False

        return res

    def apply(self, user_index, response):
        if len(response) != 3:
            return
        for i in range(0, 2):
            if response[i] not in range(0, 2):
                return
        if response[2] not in range(-3, 4):
            return

        hand = self.finger[user_index][response[0]][:]
        target = self.finger[(user_index + 1) % 2][response[1]]
        if hand == [1, 1, 1, 1] or target == [1, 1, 1, 1]:
            return

        if response[2] < 0:
            for i in range(0, 4):
                if i - response[2] < 4:
                    hand[i] = hand[i - response[2]]
                else:
                    hand[i] = 0
        elif response[2] > 0:
            for i in range(3, -1, -1):
                if i - response[2] > -1:
                    hand[i] = hand[i - response[2]]
                else:
                    hand[i] = 0

        for i in range(0, 4):
            target[i] ^= hand[i]

        for i in range(0, 2):
            if self.finger[(user_index + 1) % 2][i] != [1, 1, 1, 1]:
                return
        return True

    def run(self):
        while True:
            if self.turn >= LIMIT:
                return self.finish()

            print 'Turn: %04d' % self.turn
            for i in range(0, 2):
                self.show()
                res = self.execute(i)
                if not res:
                    return self.finish((i + 1) % 2)
                res = self.apply(i, res)
                if res:
                    return self.finish(i)
            self.turn += 1

    def finish(self, user_index=None):
        if user_index != None:
            print 'Congraturations! The winner is user %s!\n' % ['A', 'B'][user_index]
        else:
            print 'Turn Limit Exceeded! Game Over!\n'
        print 'Result:'
        self.show()

        for i in range(0, 2):
            if not self.user[i].poll():
                self.user[i].send_signal(signal.SIGKILL)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit(-1)

    game = BitMatch(sys.argv[1], sys.argv[2])
    game.run()
    sys.exit()
