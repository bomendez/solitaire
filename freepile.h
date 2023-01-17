//
//  freePile.hpp
//  Handles actions on the Free Pile
//
//  Created by Bo Mendez on 10/4/22.
//

#ifndef freePile_hpp
#define freePile_hpp

#include <stdio.h>

class FreePile : public Pile {
public:
    // Constructor
    FreePile(int pileNum) : Pile(pileNum) {}
    FreePile(FreePile& copy);
    FreePile(const vector<Card>& cards, int pileNum) : Pile(cards, pileNum) {}
    
    // Methods
    bool validAdd(Card card);
};

// Constructors
FreePile::FreePile(FreePile& copy) : Pile(copy.pileNum_) {
    cards_ = copy.cards_;
    pileNum_ = copy.pileNum_;
    *this = copy;
}

// Methods
bool FreePile::validAdd(Card card) {
    if (cards_.size() == 0) {
        return true;
    }
    return false;
}

#endif /* freePile_hpp */
