//
//  pile.h
//  Abstract class for all Piles
//
//  Created by Bo Mendez on 10/2/22.
//
#ifndef pile_h
#define pile_h

#include <stdio.h>
#include <string>
#include <vector>

#include "card.h"
#include "constant.h"

using namespace std;

class Pile {
public:
    // Constructors
    Pile(int pileNum);
    Pile(Pile& copy);
    Pile(const vector<Card>& cards, int pileNum);
    
    // Destructor
    virtual ~Pile();
    
    // Methods
    virtual bool validAdd(Card);
    virtual bool validRemove();
    virtual void addCard(Card);
    virtual Card removeCard();
    virtual string toString() const;
    virtual vector<Card> getCards() {return cards_;}
    
protected:
    vector<Card> cards_;
    int pileNum_;
};

// Constructors
Pile::Pile(int pileNum) {
    pileNum_ = pileNum;
}

Pile::Pile(const vector<Card>& cards, int pileNum) {
    pileNum_ = pileNum;
    
    for (int i = 0; i < cards.size(); i++) {
        cards_.push_back(cards[i]);
    }
}

string Pile::toString() const {
    string out;
    
    out += "#" + to_string(pileNum_) + " [ ";
    
    for (int i = 0; i < cards_.size(); i++) {
        out += cards_[i].toString() + " ";
    }
    
    out += "]";
    
    return out;
}

// Destructor
Pile::~Pile() {
    for (int i = 0; i < cards_.size(); i++) {
        cards_.clear();
    }
}

// Methods
bool Pile::validAdd(Card card) {
    return true;
}

bool Pile::validRemove() {
    if (cards_.size() == 0) {
        return false;
    }
    return true;
}

void Pile::addCard(Card card) {
    cards_.push_back(card);
}

Card Pile::removeCard() {
    if (this->cards_.size() != 0) {
        Card poppedCard = cards_.back();
        cards_.pop_back();
        return poppedCard;
    }
    else throw runtime_error{"Cannot remove from empty pile"};
}

#endif /* pile_h */
