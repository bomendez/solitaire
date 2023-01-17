//
//  constant.h
//  Contains all constant values
//
//  Created by Bo Mendez on 10/6/22.
//

#ifndef constant_h
#define constant_h

#include <stdio.h>

namespace constant {
const int NUM_RANKS = 13;
const int NUM_SUITS = 4;
const string CARD_RANK[NUM_RANKS] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const string SUITS[NUM_SUITS] = {"H", "D", "S", "C"};
const int NUM_PILES = 16;
const int NUM_FREEPILES = 4;
const int NUM_HOMEPILES = 4;
const int NUM_TABLEAUPILES = 8;
const int NUM_INPUT = 2;
}

#endif /* constant_h */
