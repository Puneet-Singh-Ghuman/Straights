#include "Card.h"
#include "ComputerPlayer.h"

bool ComputerPlayer::turn(Card *card, std::vector<Card *>& cardsonTable){
    std::vector<Card *> legalPlays = Player::getLegalPlays(cardsonTable);

    if(legalPlays.size() <= 0){
        std::vector<Card *> hand = Player::hand();
        if(hand[0] != nullptr){
            discardCard(hand[0]);
        }
    } else {
        playCard(legalPlays[0]);
    }

    return true;
}
