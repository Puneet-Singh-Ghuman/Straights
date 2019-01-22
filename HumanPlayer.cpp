#include "Card.h"
#include "HumanPlayer.h"

bool HumanPlayer::isHuman() const{
    return true;
}

bool HumanPlayer::turn(Card *card, std::vector<Card *>& cardsonTable){
    std::vector<Card *> currentHand = Player::hand();
    std::vector<Card *> legalPlays = Player::getLegalPlays(cardsonTable);
    bool validPlay = false;

    for(auto i = legalPlays.begin(); i != legalPlays.end(); ++i){
        if( **i == *card){
            validPlay = true;
            break;
        }
    }

    if(legalPlays.empty()){
        return discardCard(card);
    } else if(validPlay){
        return playCard(card);
    } else {
        return false;

    }
}
