#include "TextView.h"
#include <iostream>
#include <string>

TextView::TextView(Model* model, Controller* contoller) : model_(model), controller_(contoller){}

TextView::~TextView(){}

void TextView::printDeck(){
    std::vector<Card *> deck = model_->getDeck();
    for(int i = 0; i < 52; ++i){
        if(i % 13 != 0){
            std::cout << " ";
        }
        std::cout << *deck[i];

        if(i % 13 == 12){
            std::cout << std::endl;
        }
    }

}

void TextView::printcardsOnTable(){
    std::vector<bool> cardsOnTable = model_->cardsOnTable();
    std::cout << "Cards on the table:" << std::endl;
        for(int i = 0; i < 52; ++i){
                if(i == 0){
                    std::cout << "Clubs:";
                    if(cardsOnTable[0] == true){
                        std::cout << " A";
                    }
                }

                else if(i == 13){
                    std::cout << std::endl;
                    std::cout << "Diamonds:";
                    if(cardsOnTable[13] == true){
                        std::cout << " A";
                    }
                }

                else if(i == 26){
                    std::cout << std::endl;
                    std::cout << "Hearts:";
                    if(cardsOnTable[26] == true){
                        std::cout << " A";
                    }
                }

                else if(i == 39){
                    std::cout << std::endl;
                    std::cout << "Spades:";
                    if(cardsOnTable[39] == true){
                        std::cout << " A";
                    }
                }

                else{
                    if(cardsOnTable[i] == true){
                        if( i % 13 == 0) std::cout << " A";
                        else if( i % 13 == 10) std::cout << " J";
                        else if( i % 13 == 11) std::cout << " Q";
                        else if( i % 13 == 12) std::cout << " K";    
                        else {
                            if(i > 0 && i <= 12) std::cout << " " << std::to_string(i+1);
                            else if(i > 13 && i <=25){
                                std::cout << " " << std::to_string(i-13+1);
                            }
                            else if(i > 26 && i <=38){
                                std::cout << " " << std::to_string(i-26+1);
                            }
                            else if(i > 39){
                                std::cout << " " << std::to_string(i-39+1);
                            }
                        }

                    }

                    else {
                            // 
                    }
                }
        }

        std::cout << std::endl;
        std::cout << "Your hand:";
        std::vector<Card *> playerHand = model_->currentPlayer()->hand();
        for(size_t i = 0; i < playerHand.size(); ++i){
            std::cout << " " << *playerHand[i]; 
        }

        std::cout << std::endl;
        std::cout << "Legal plays:";
        std::vector<Card *> legalplay = model_->getLegalPlays();
        for(size_t i = 0; i < legalplay.size(); ++i){
            std::cout << " " << *legalplay[i];
        }

        std::cout << std::endl << ">";

}

void TextView::processCommand(bool& flag, bool& toquit, bool& ragequit){
    Command c;
    std::cin >> c;
    if(c.type == PLAY || c.type == DISCARD){
        if(c.type == DISCARD){
            std::vector<Card *> legalplay = model_->getLegalPlays();
            if(legalplay.size() > 0){
                std::cout << "You have a legal play. You may not discard." << std::endl << ">";
                return;
            }
        }
        flag = controller_->playTurn(&c.card);
        if(flag == false){
            if(c.type == PLAY){
                std::cout << "This is not a legal play." << std::endl << ">";
            }

            else {
                std::cout << "You have a legal play. You may not discard." << std::endl << ">";
            }
        }
        else {
            if(c.type == PLAY){
                std::cout << "Player " << std::to_string(model_->getCurrentPlayerNumber()+1) << " plays " << c.card <<".";
            }

            else{
                std::cout << "Player " << std::to_string(model_->getCurrentPlayerNumber()+1) << " discards " << c.card << ".";
            }
            
            std::cout << std::endl;
        }
    }

    else if(c.type == DECK){
            printDeck();
    }

    else if(c.type == QUIT){
            controller_->endGame();
            toquit = true;
            flag = true; 
    }

    else if(c.type == RAGEQUIT){
            std::cout << "Player " << std::to_string(model_->getCurrentPlayerNumber()+1) << " ragequits.";
            std::cout << " A computer will now take over." << std::endl; 
            controller_->rageQuit();
            flag = true;
            ragequit = true;
    }
}

void TextView::render(){
   
    while(true){
        if(model_->getState() == Model::NOT_VALID){
            std::vector<char> p;
            for(int i = 1; i < 5; ++i){
                char ch;
                std::cout << "Is player " << std::to_string(i) << " a human(h) or a computer(c)?" << std::endl << ">";
                std::cin >> ch;
                // if ch is invalid THROW SOMETHING !!
                assert(ch == 'h' || ch == 'c');
                p.push_back(ch); 
            }

            controller_->setupGame(p);
        }

        else if(model_->getState() == Model::ROUND_BEGIN){
            controller_->startNewRound();

            std::cout << "A new round begins. It's player " << std::to_string(model_->getFirstPlayerNumber());
            std::cout << "'s turn to play." << std::endl;

        }
        else if(model_->getState() == Model::ROUND_IN_PROGRESS){
                if(model_->currentPlayer()->isHuman() == true){
                  printcardsOnTable();

                  bool flag = false;
                  bool toquit = false;
                  bool quitingonrage = false;
                  while(!flag){
                      processCommand(flag, toquit, quitingonrage);
                  }

                  if(toquit == true){
                    return;
                  }

                  if(quitingonrage == true){
                    continue;
                  }
                }

                else{
                  Player *p = model_->currentPlayer();
                  int curPlayer = model_->getCurrentPlayerNumber();
                  int initalplayedcards = p->playedCardsSize();
                  bool check = controller_->playTurn(nullptr);

                  int newplayedcards = p->playedCardsSize();
                  if(newplayedcards > initalplayedcards && check == true){
                    std::cout << "Player " << std::to_string(curPlayer+1) << " plays ";
                    Card* c = p->getLastPlayed();
                    std::cout << *c << "." << std::endl;
                  }

                  else{
                    std::cout << "Player " << std::to_string(curPlayer+1) << " discards ";
                    Card* c = p->getLastDiscarded();
                    std::cout << *c << "." << std::endl;
                  }
                }

                controller_->continueRound();
        }
        else if(model_->getState() == Model::ROUND_ENDED){
            for(int i = 0; i < 4; ++i){
                Player *p = model_->getPlayer(i);
                std::vector<Card *> discardCards = p->discardedCards();
                std::cout << "Player " << std::to_string(i+1) << "'s discards:";
                Card *c;
                for(size_t j = 0; j < discardCards.size(); j++){
                    c = discardCards[j];
                    std::cout << " " << *c;
                }
                std::cout << std::endl;
                std::cout << "Player " <<  std::to_string(i+1)  << "'s score: ";
                std::cout << p->oldScore() << " + " << p->roundScore() << " = " << p->totalScore();
                std::cout << std::endl;
            }

            controller_->updateScoresAndResetPlayers();
            bool check = model_->checkIfGameEnded();
            if(check){
                controller_->endGame();
            }

            else{
                controller_->setState(Model::ROUND_BEGIN);
            }
        }

        else if(model_->getState() == Model::GAME_ENDED){
                std::vector<int> winners = model_->winners();
                for(size_t i = 0; i < winners.size(); ++i){
                    std::cout << "Player " << std::to_string(winners.at(i)) << " wins!";
                    std::cout << std::endl;
                }

                return;
        }
    }
}
