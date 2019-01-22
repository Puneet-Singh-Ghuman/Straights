#include "Card.h"
#include "Player.h"
Player::Player() : roundScore_(0), oldScore_(0){}

Player::~Player(){}

bool Player::isHuman() const{
    return false;
}

int Player::totalScore() const{
    return roundScore() + oldScore();
}

int Player::roundScore() const{
    return roundScore_;
}

int Player::oldScore() const{
    return oldScore_;
}

int Player::currentIndex(Card *card){
    std::vector<Card *>::iterator i;
    int index = 0;
    for(i = hand_.begin(); i != hand_.end(); ++i, ++index){
        if(*(*i) == *card){
            return index;
        }
    }

    return -1;
}

std::vector<Card *> Player::hand(){
    return hand_;
}

std::vector<Card *> Player::playedCards(){
    return playedCards_;
}

std::vector<Card *> Player::discardedCards(){
    return discardedCards_;
}

int Player::handSize() const{
    return hand_.size();

}

int Player::playedCardsSize() const{
    return playedCards_.size();

}

int Player::discardedCardsSize() const{
    return discardedCards_.size();
}

Card* Player::getLastPlayed() const{
    return playedCards_[playedCards_.size() - 1];
}

Card* Player::getLastDiscarded() const{
    return discardedCards_[discardedCards_.size() - 1];
}

void Player::addCard(Card *card){
    hand_.emplace_back(card);
}

bool Player::playCard(Card *card){
    int i = currentIndex(card);
    if(i >= 0){
        playedCards_.push_back(hand_[i]);
        hand_.erase(hand_.begin() + i);
        return true; 
    }
    else {
        return false;
    }
}

bool Player::discardCard(Card *card){
    int i = currentIndex(card);
    if(i >= 0){
        discardedCards_.push_back(hand_[i]);
        hand_.erase(hand_.begin() + i);
        roundScore_ = roundScore_ + card->getRank() + 1;
        return true; 
    }
    else {
        return false;
    }
}

std::vector<Card *> Player::getLegalPlays(std::vector<Card *>& tableDeck){
    Card SEVEN_OF_SPADES = Card(SPADE, SEVEN);
    std::vector<Card *> legalPlays;
    bool isLegal = false;
    
    for(size_t i = 0; i < hand_.size(); i++){
        if(hand_[i]->getRank() == SEVEN){
            isLegal = true;

        } else {
            for(size_t j = 0; j < tableDeck.size(); ++j){
                if((hand_[i]->getSuit() == tableDeck[j]->getSuit()) &&
                   (((int)hand_[i]->getRank() - (int)tableDeck[j]->getRank() == -1) ||
                     (int)hand_[i]->getRank() - (int)tableDeck[j]->getRank() == 1 )
                  ){
                    isLegal = true;
                }
            }
        }

        if(*hand_[i] == SEVEN_OF_SPADES){
            legalPlays.clear();
            legalPlays.push_back(hand_[i]);
            return legalPlays;
        }

        if(isLegal){
            legalPlays.push_back(hand_[i]);
            isLegal = false;
        }
    }

    return legalPlays;
}

void Player::newRound(){
    oldScore_ += roundScore_;
    roundScore_ = 0;
    hand_.clear();
    playedCards_.clear();
    discardedCards_.clear();
}

void Player::addPlayedCard(Card *c){
    playedCards_.emplace_back(c);
}

void Player::addDiscardedCard(Card *c){
    discardedCards_.emplace_back(c);
    roundScore_ = roundScore_ + c->getRank() + 1;
}

void Player::endGame(){
    oldScore_ = 0;
    roundScore_ = 0;
    hand_.clear();
    playedCards_.clear();
    discardedCards_.clear();
}
