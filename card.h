//
//  Card.h
//  Handles actions taken by cards
//
//  Created by Bo Mendez on 10/2/22.
//

#ifndef card_h
#define card_h

#include <iostream>
#include <string>

using namespace std;

class Card {
public:
    // Constructors
    Card(string suit, string value, bool isRed);
    Card(const Card& copy);
    
    // Methods
    string toString() const;
    string getSuit() const {return suit_;}
    string getValue() const {return value_;}
    const string getIsRed() const {
        if (isRed_) return "+";
        return "-";
    }
    bool operator==(const Card& other);
    
private:
    string suit_;
    string value_;
    bool isRed_;
};

// Constructors
Card::Card(string suit, string value, bool isRed) : suit_(suit), value_(value), isRed_(isRed) {}

Card::Card(const Card& copy) {
    suit_ = copy.suit_;
    value_ = copy.value_;
    isRed_ = copy.isRed_;
    *this = copy;
}

// Methods
string Card::toString() const{
    return suit_ + value_ + getIsRed();
}

bool Card::operator==(const Card& other) {
    if (this->suit_ == other.suit_ && this->value_ == other.value_) {
        return true;
    }
    return false;
}

#endif /* card_h */
