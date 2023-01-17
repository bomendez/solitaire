//
//  main.c
//  Solitaire
//
//  Created by Bo Mendez on 10/2/22.
//

#include <stdio.h>
#include <string.h>

#include "card.h"
#include "pile.h"
#include "homePile.h"
#include "tableauPile.h"
#include "freePile.h"
#include "board.h"
#include "test.h"

int main(int argc, char* argv[]) {
    Test* test = new Test();
    test->CardTests();
    test->FreePileTests();
    test->TableauPileTests();
    
    Board* board = new Board();
    board->print();
    
    while (!board->isWon()) {
        int pileFrom, pileTo;
        
        cout << "enter two pile numbers: ";
        scanf("%d %d", &pileFrom, &pileTo);
        
        board->moveCards(pileFrom,pileTo);
        board->print();
    }
    
    cout << "Congratulations, you win!" << endl;
    
    return 0;
}
