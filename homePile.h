//
//  homePile.h
//  Handles actions for the Home Pile
//
//  Created by Bo Mendez on 10/3/22.
//
#ifndef homePile_h
#define homePile_h

#include <stdio.h>
#include <vector>

#include "constant.h"

class HomePile : public Pile {
public:
    // Constructor
    HomePile(int pileNum) : Pile(pileNum) {}
    HomePile(const HomePile& copy);
    
    // Methods
    bool validAdd(Card card);
private:
    int findRank(Card card);
};

// Constructors
HomePile::HomePile(const HomePile& copy) : Pile(copy.pileNum_) {
    cards_ = copy.cards_;
    pileNum_ = copy.pileNum_;
    *this = copy;
}

// Methods

// card is added if the following is true:
// 1) card is the same suit as the last card in this pile
// 2) card is exactly one rank larger than the last card in this pile
bool HomePile::validAdd(Card card) {
    int otherIndx = findRank(card);
    
    // empty pile must place Ace
    if (cards_.size() == 0) {
        if (otherIndx == 0) {
            return true;
        } return false;
    }
    
    int topCardIndx = findRank(cards_.back());
    
    // check in range
    if (otherIndx < 0 || topCardIndx < 0 || otherIndx >= constant::NUM_RANKS || topCardIndx >= constant::NUM_RANKS) { return false; }
    
    if ((cards_.at(0).getSuit() == card.getSuit())) { // if same suit
        
        cout << "Other Rank " + constant::CARD_RANK[otherIndx] << endl;
        cout << "Top Card Rank " + constant::CARD_RANK[topCardIndx] << endl;
        cout << otherIndx << endl;
        if (otherIndx > 0) { // >0 already checked if pile is empty
            if (otherIndx == topCardIndx + 1) {
                return true;
            }
        }
    }
    return false;
}

int HomePile::findRank(Card card) {
    for (int i = 0; i < constant::NUM_RANKS; i++) {
        if (card.getValue() == constant::CARD_RANK[i]) {
            return i;
        }
    }
    return -1;
}

#endif /* homePile_h */
