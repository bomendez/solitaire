//
//  test.h
//  Tests for Solitaire
//
//  Created by Bo Mendez on 10/11/22.
//

#ifndef test_h
#define test_h

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "card.h"
#include "pile.h"
#include "homePile.h"
#include "tableauPile.h"
#include "freePile.h"
#include "board.h"

Card HA("H", "A", 1);
Card H2("H", "2", 1);
Card H3("H", "3", 1);
Card DA("D", "A", 1);
Card D2("D", "2", 1);
Card D3("D", "3", 1);
Card S3("S", "3", 0);

Pile* homePile1 = new HomePile(1);
Pile* freePile2 = new FreePile(2);
Pile* tableauPile3 = new TableauPile(3);

class Test {
public:
    Test();
    ~Test();
    void Assert(bool, const std::string&);
    void CardTests();
    void HomePileTests();
    void FreePileTests();
    void TableauPileTests();
    void BoardTests();
};

Test::Test() {
    Assert(true, "true is true");
}

Test::~Test() {
    delete homePile1;
    delete freePile2;
    delete tableauPile3;
}

void Test::Assert(bool val, const std::string& msg)
{
    if (!val)
        std::cout << "FAIL: " << msg << std::endl;
}

void Test::CardTests() {
    string cardHA = "HA+";
    Assert(HA.toString() == cardHA, "printing red card");
    string cardS3 = "S3-";
    Assert(S3.toString() == cardS3, "printing black card");
}

void Test::HomePileTests() {
    Assert(homePile1->toString() == "#1 [ ]", "print empty homePile");
    Assert(homePile1->validRemove() == 0, "cannot remove from empty pile");
    Assert(homePile1->validAdd(HA) == 1, "can add Ace to empty homePile");
    Assert(homePile1->validAdd(H2) == 0, "cannot add 2 to empty homePile");
    
    Assert(homePile1->getCards().size() == 0, "empty homePile has 0 cards");
    homePile1->addCard(HA);
    Assert(homePile1->getCards().size() == 1, "homePile has 1 card");
    Assert(homePile1->getCards()[0] == HA, "added correct card to homePile");
    string home1Card = "#1 [ HA+ ]";
    Assert(homePile1->toString() == home1Card, "prints cards as homePile");
    Assert(homePile1->validAdd(HA) == 0, "cannot place HA on HA");
    Assert(homePile1->validAdd(H3) == 0, "cannot place H3 on HA");
    
    homePile1->removeCard();
    Assert(homePile1->getCards().size() == 0, "remove card from homePile");
}

void Test::FreePileTests() {
    vector<Card> cards;
    cards.push_back(HA);
    
    
    Assert(freePile2->getCards().size() == 0, "empty freePile has 0 cards");
    Assert(freePile2->toString() == "#2 [ ]", "print empty freePile");
    Assert(freePile2->validAdd(H3) == 1, "can add any card to empty freePile");
    Assert(freePile2->validRemove() == 0, "cannot remove from empty freePile");
    
    Pile* freePile1 = new FreePile(cards, 1);
    string constructor2 = "#1 [ HA+ ]";
    Assert(freePile1->getCards().size() == 1, "freePile with vector constructor has 1 card");
    Assert(freePile1->toString() == constructor2, "print homePile with vector constructor");
    Assert(freePile1->validAdd(H2) == 0, "cannot add to non-empty freePile");
    Assert(freePile1->validRemove() == 1, "can remove from non-empty freePile");
    
    freePile2->addCard(HA);
    Assert(freePile2->getCards().size() == 1, "freePile has 1 card after adding");
    freePile2->removeCard();
    Assert(freePile2->getCards().size() == 0, "freePile has 0 cards after remove");
    
    delete freePile1;
}

void Test::TableauPileTests() {
    vector<Card> cards;
    cards.push_back(HA);
    cards.push_back(H2);
    cards.push_back(H3);
    cards.push_back(DA);
    cards.push_back(D2);
    cards.push_back(D3);
    
    Assert(tableauPile3->toString() == "#3 [ ]", "printing tableauPile with int constructor");
    Assert(tableauPile3->getCards().size() == 0, "empty tableauPile has 0 cards");
    
    Assert(tableauPile3->validAdd(HA) == 1, "can add to empty tableauPile");
    Assert(tableauPile3->validRemove() == 0, "cannot remove from empty tableauPile");
    
    tableauPile3->addCard(HA);
    Assert(tableauPile3->getCards().size() == 1, "tableauPile has 1 card after add");
    tableauPile3->removeCard();
    Assert(tableauPile3->getCards().size() == 0, "tableauPile has 0 cards after remove");
    
    Pile* tableauPile1 = new TableauPile(cards, 1);
    Assert(tableauPile1->getCards().size() == 6, "tableauPile with vector constructor has correct size cards");
    Assert(tableauPile1->validRemove() == 1, "can remove any card from tableauPile");
    
    tableauPile1->removeCard(); // top card is D2-
    Assert(tableauPile1->validAdd(D3) == 0, "cannot place card of same color on tableauPile");
    Assert(tableauPile1->validAdd(HA) == 0, "cannot place card of lower rank on tableauPile");
}

void Test::BoardTests() {
    Board* board = new Board();
    
    Assert(board->isWon() == 0, "game not won");
    
    Assert(board->getPile(1)->getCards().size() == 0, "freePile empty");
    Assert(board->getPile(5)->getCards().size() == 0, "freePile empty");
    Assert(board->getPile(9)->getCards().size() >= 6, "tableauPile filled with >= 6 cards");
    Assert(board->getPile(9)->getCards().size() < 8, "tableauPile filled with < 8 cards");
    
    int sizeBeforeMove = board->getPile(9)->getCards().size();
    board->moveCards(9, 1);
    Assert(board->getPile(9)->getCards().size() == sizeBeforeMove - 1, "pileFrom has 1 less card after move");
    Assert(board->getPile(1)->getCards().size() == 1, "pileTo has 1 card after move");
    board->moveCards(9, 1);
    Assert(board->getPile(9)->getCards().size() == sizeBeforeMove - 1, "pileFrom has same # cards after invalid move");
    Assert(board->getPile(1)->getCards().size() == 1, "pileTo has same # cards after invalid move");
    
    delete board;
}

#endif /* test_h */
