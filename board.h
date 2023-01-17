//
//  board.h
//  Handles all actions taken by the board
//
//  Created by Bo Mendez on 10/4/22.
//

#ifndef board_h
#define board_h

#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "pile.h"
#include "homePile.h"
#include "tableauPile.h"
#include "freePile.h"
#include "card.h"
#include "constant.h"

using namespace std;

class Board {
public:
    // Constructor
    Board();
    
    // Destructor
    ~Board();
    
    // Methods
    Pile* getPile(int);
    void print();
    void moveCards(int, int);
    bool isWon();

private:
    vector<Pile*> piles;
    vector<Card> deck;
    void buildDeck();
    void shuffle();
    void addPiles();
    void dealCards();
};

// Constructor
Board::Board() {
    buildDeck();
    shuffle();
    addPiles();
    dealCards();
}

// Destructor
Board::~Board() {
    
    for (int i = 0; i < piles.size(); i++) {
        delete piles.at(i);
    }
}

// public methods
Pile* Board::getPile(int pileNum) {
    int vectorNum = pileNum - 1;
    if (vectorNum > 0 && vectorNum < constant::NUM_PILES) {
        return piles.at(vectorNum);
    }
    throw out_of_range {"pile number out of range"};
}

void Board::print() {
    for (int i = 0; i < constant::NUM_FREEPILES; i++) {
        cout << piles.at(i)->toString() << endl;
    }
    cout << " " << endl;
    for (int i = 4; i < constant::NUM_FREEPILES + constant::NUM_HOMEPILES; i++) {
        cout << piles.at(i)->toString() << endl;
    }
    cout << " " << endl;
    for (int i = 8; i < constant::NUM_PILES; i++) {
        cout << piles.at(i)->toString() << endl;
    }
}

void Board::moveCards(int indxFrom, int indxTo) {
    if (indxFrom > 0 && indxFrom <= constant::NUM_PILES &&
        indxTo > 0 && indxTo <= constant::NUM_PILES) {
        int pileFrom = indxFrom - 1;
        int pileTo = indxTo - 1;
        Card cardToMove = piles.at(pileFrom)->getCards().back();
        
        if (piles.at(pileFrom)->validRemove() && piles.at(pileTo)->validAdd(cardToMove)) {
            piles.at(pileFrom)->removeCard();
            piles.at(pileTo)->addCard(cardToMove);
        }
    }
}

bool Board::isWon() {
    for (int currPile = constant::NUM_HOMEPILES; currPile < constant::NUM_TABLEAUPILES; currPile++) {
        if (piles.at(currPile)->getCards().size() != constant::NUM_RANKS) {
            return false;
        }
    }
    return true;
}

// private methods
void Board::buildDeck() {
    bool isRed;
    for (int suit = 0; suit < constant::NUM_SUITS; suit++) {
        isRed = (suit < 2) ? true : false;
        
        for (int rank = 0; rank < constant::NUM_RANKS; rank++) {
            Card* card = new Card(constant::SUITS[suit], constant::CARD_RANK[rank], isRed);
            deck.push_back(*card);
        }
    }
}

void Board::shuffle() {
    int indx1;
    int indx2;
    
    int i = 0;
    while (i < deck.size()) {
        indx1 = rand() % deck.size();
        indx2 = rand() % deck.size();
        
        // print indicies - for testing
//        cout << indx1 << endl;
//        cout << indx2 << endl;
        
        iter_swap(deck.begin() + indx1, deck.begin() + indx2);
        i++;
    }
    
    // print cards - for testing
//    for (Card card : deck) {
//        cout << card.toString() << endl;
//    }
}

void Board::addPiles() {
    for (int i = 1; i <= constant::NUM_PILES; i++) {
        if (i <= 4) {
            Pile* freePile = new FreePile(i);
            piles.push_back(freePile);
        } else if (i <= 8) {
            Pile* homePile = new HomePile(i);
            piles.push_back(homePile);
        } else {
            Pile* tableauPile = new TableauPile(i);
            piles.push_back(tableauPile);
        }
    }
}

void Board::dealCards() {
    int pileIt = constant::NUM_TABLEAUPILES;
    
    while (!deck.empty()) {
        if (pileIt == 16) pileIt = constant::NUM_TABLEAUPILES;
        piles.at(pileIt)->addCard(deck.back());
        deck.pop_back();
        pileIt++;
    }
}

#endif /* board_h */
