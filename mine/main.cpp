#include <cstdlib>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>

#ifndef TEST
#define NODEBUG
#endif
#include <cassert>

const int kSearchDepth = 3;
const int kNegativeInfinity = INT_MIN;
const int kInfinity = INT_MAX;
const int kMyWeight     = 2;
const int kOppWeight    = 2;
const int kWinWeight    = 10;

enum Finger {
    kMyLeftIndex    = 1<<0,
    kMyLeftMiddle   = 1<<1,
    kMyLeftRing     = 1<<2,
    kMyLeftLittle   = 1<<3,
    kMyRightIndex   = 1<<4,
    kMyRightMiddle  = 1<<5,
    kMyRightRing    = 1<<6,
    kMyRightLittle  = 1<<7,
    kOppLeftIndex   = 1<<8,
    kOppLeftMiddle  = 1<<9,
    kOppLeftRing    = 1<<10,
    kOppLeftLittle  = 1<<11,
    kOppRightIndex  = 1<<12,
    kOppRightMiddle = 1<<13,
    kOppRightRing   = 1<<14,
    kOppRightLittle = 1<<15,
};

enum WhichPlayer {
    kMy     = 0,
    kOpp    = 8,
};

enum WhichHand {
    kLeft   = 0,
    kRight  = 4,
};

enum WhichFinger {
    kIndex  = 0,
    kMiddle = 1,
    kRing   = 2,
    kLittle = 3,
};

enum WhichTurn {
    kMyTurn     = 0,
    kOppTurn    = 1,
};

const WhichPlayer which_player[] = {
    kMy,
    kOpp,
};

const WhichHand which_hand[] = {
    kLeft,
    kRight,
};

const WhichFinger which_finger[] = {
    kIndex,
    kMiddle,
    kRing,
    kLittle,
};

char check(unsigned short state, char my_hand, char opp_hand) {
    if ((((state >> (kMy + which_hand[my_hand]))&0x0f) == 0x0f)||(((state >> (kOpp + which_hand[opp_hand]))&0x0f) == 0x0f))
        return 0;
    else
        return 1;
}

unsigned short exchange(unsigned short state) {
    return ((state & 0x00ff) << 8)|((state & 0xff00) >> 8);
}

unsigned short process(unsigned short state, char my_hand, char opp_hand, short shift) {
    unsigned short i, my_base, opp_base, my_fingers;
    my_base     = kMy   + which_hand[my_hand];
    opp_base    = kOpp  + which_hand[opp_hand];
    my_fingers  = (state >> my_base) & 0x0f;
    if (shift < 0)
        state ^= (((my_fingers >> (shift * -1)) & 0x0f) << opp_base);
    else
        state ^= (((my_fingers << shift) & 0x0f) << opp_base);
    return state;
}

int evaluate(unsigned short state) {
    int i, j, value = 0;
    if ((state & 0xff00) == 0xff00)
        return kWinWeight;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (((state>>(which_player[i] + which_hand[j]))&0x0f) == 0x0f) {
                i?value+=kOppWeight:value-=kMyWeight;
            }
        }
    }
    return value;
}

int search(int depth, unsigned short state, char turn) {
    int value, i, j, k;
    if (depth == 0)
        return 0;
    else {
        if (turn == kOppTurn) {
            state = exchange(state);
            value = evaluate(state) * depth;
        } else {
            value = evaluate(state) * depth;
            state = exchange(state);
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                if (check(state, i, j)) {
                    for (k = -3; k <= 3; k++) {
                        value += search(depth-1, process(state, i, j, k), turn^1);
                    }
                }
            }
        }
        return value;
    }
}

int main(void) {
    using namespace std;
    int i, j, k, turn, finger;
    char my_hand, opp_hand, shift, operation;
    unsigned short input_state, search_state;
    int value_table[2][2][7], max_value;
    vector<char> candidates;

#ifdef TEST
    cout << "Test functions." << endl;
    cout << "evaluate" << endl;
    if (evaluate(0x0000) == 0)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (evaluate(0x00ff) == kMyWeight * -2)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (evaluate(0xff00) == kWinWeight)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (evaluate(0xffff) == kWinWeight)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (evaluate(0x000f) == kMyWeight * -1)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (evaluate(0x0f0f) == kOppWeight + kMyWeight * -1)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    cout << "exchange" << endl;
    if (exchange(0xff00) == 0x00ff)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (exchange(0x4444) == 0x4444)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (exchange(0x2534) == 0x3425)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (exchange(0x1122) == 0x2211)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    cout << "process" << endl;
    if (process(0x0000, 0, 0, 0) == 0x0000)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0000, 0, 1, 3) == 0x0000)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0000, 1, 1, -3) == 0x0000)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0011, 0, 0, 0) == 0x0111)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0011, 0, 0, 1) == 0x0211)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0111, 0, 0, 0) == 0x0011)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0011, 0, 1, 0) == 0x1011)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0052, 1, 0, 3) == 0x0852)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0452, 1, 0, 2) == 0x0052)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x0ceb, 1, 0, -2) == 0x0feb)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (process(0x1c7b, 1, 1, 1) == 0xfc7b)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    cout << "check" << endl;
    if (check(0x0000, 0, 0) == 1)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (check(0x4444, 1, 0) == 1)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (check(0xf01f, 1, 1) == 0)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (check(0xce14, 1, 0) == 1)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (check(0xff00, 1, 0) == 0)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (check(0x00ff, 1, 1) == 0)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    cout << "search" << endl;
    if (search(0, 0x0000, kMyTurn) == 0)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (search(1, 0x34eb, kMyTurn) == 0)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (search(1, 0x3feb, kMyTurn) == kOppWeight)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (search(1, 0xfffb, kMyTurn) == kWinWeight)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    if (search(1, 0x3feb, kOppTurn) == kMyWeight * -1)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
#else
    while(1) {
        cin >> turn;
        input_state = 0;
        max_value = kNegativeInfinity;
        candidates.clear();
        for(i = 0; i < 2; i++) {
            for(j = 0; j < 2; j++) {
                for(k = 0; k < 4; k++) {
                    cin >> finger;
                    input_state |= (finger << (which_player[i] + which_hand[j] + which_finger[k]));
                }
            }
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                for (k = -3; k <= 3; k++) {
                    if (check(input_state, i, j)) {
                        search_state = process(input_state, i, j, k);
                        if ((search_state & 0xff00) == 0xff00) {
                            value_table[i][j][k+3] = kInfinity;
                        } else {
                            value_table[i][j][k+3] = search(kSearchDepth, search_state, kMyTurn);
                        }
                        max_value = max(max_value, value_table[i][j][k+3]);
                    } else {
                        value_table[i][j][k+3] = kNegativeInfinity;
                    }
                }
            }
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                for (k = 0; k < 7; k++) {
                    if(value_table[i][j][k] == max_value) {
                        candidates.push_back(i|(j<<1)|(k<<2));
                    }
                }
            }
        }
        srand((unsigned int)time(NULL));
        operation = candidates.at(rand() % candidates.size());

        cout << (operation&1) << " " << ((operation >> 1)&1) << " " << ((operation >> 2) - 3) << endl;
        cout << flush;
    }
#endif
    return 0;
}
