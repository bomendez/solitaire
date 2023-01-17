//
//  tableauPile.h
//  Handles actions on Tableau Piles
//
//  Created by Bo Mendez on 10/3/22.
//

#ifndef tableauPile_hpp
#define tableauPile_hpp

#include <stdio.h>
#include <vector>

#include "constant.h"

class TableauPile : public Pile {
public:
    // Constructor
    TableauPile(int pileNum) : Pile(pileNum) {}
    TableauPile(TableauPile& copy);
    TableauPile(const vector<Card>& cards, int pileNum) : Pile(cards, pileNum) {}
    
    // Methods
    bool validAdd(Card);
private:
    int findRank(Card);
};

// Constructors
TableauPile::TableauPile(TableauPile& copy) : Pile(copy.pileNum_) {
    cards_ = copy.cards_;
    pileNum_ = copy.pileNum_;
    *this = copy;
}

// card is added if the following is true:
// 1) card is a different color than the last card in this pile
// 2) card is exactly one rank less than the last card in this pile
bool TableauPile::validAdd(Card card) {
    int otherIndx = findRank(card);
    
    if (cards_.size() == 0) { // empty pile
        return true;
    }
    if ((cards_.at(0).getIsRed() != card.getIsRed())) { // if different colors
        int topCardIndx = findRank(cards_.back());

        if (otherIndx > 0) { // >0 already checked if pile is empty
            if (otherIndx == topCardIndx - 1) {
                return true;
            }
        }
    }
    return false;
}

int TableauPile::findRank(Card card) {
    for (int i = 0; i < constant::NUM_RANKS; i++) {
        if (card.getValue() == constant::CARD_RANK[i]) {
            return i;
        }
    }
    return -1;
}


#endif /* tableauPile_hpp */
