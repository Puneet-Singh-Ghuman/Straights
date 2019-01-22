#include "Model.h"
#include <cstdlib>
#include <iostream>
Model::Model(int seed) : firstPlayer_(-1), currentPlayer_(-1), 
                         seed_(seed), state_(NOT_VALID), turn_(NONE){
                         
    deck_ = std::make_unique<Deck>();                         
}

Model::~Model(){
    clearData();
}

void Model::setupPlayers(std::vector<std::string>& types){
    for(int i = 0; i < 4; ++i){
        if(types[i] == "h"){
            players_.emplace_back(std::make_unique<HumanPlayer>());
        }

        if(types[i] == "c"){
            players_.emplace_back(std::make_unique<ComputerPlayer>());
        }
    }

    seed_ = std::stoi(types[4]);
    state_ = ROUND_BEGIN;
}

void Model::initializeDeck(){
    deck_ = std::make_unique<Deck>(); 
    deck_->initialize();
}

void Model::distributeCards(){
    Card SEVEN_OF_SPADES = Card(SPADE, SEVEN);
    for(int i = 0; i < 4; i++){
        for(int j = 13*i; j < 13*(i+1); ++j){
            Card *c = deck_->getCard(j);
            players_[i]->addCard(c);

            if(*c == SEVEN_OF_SPADES){
                firstPlayer_ = i + 1;
                currentPlayer_ = i;
            }
        }
    }

    state_ = ROUND_IN_PROGRESS;
}

void Model::shuffle(){
    deck_->shuffle(seed_);
}

void Model::nextPlayer(){
    ++currentPlayer_;
    if(currentPlayer_ >= 4){
        currentPlayer_ = currentPlayer_ % 4;
    }
}

std::vector<Card *> Model::getLegalPlays(){
    return players_[currentPlayer_]->getLegalPlays(playedCards_);
}

void Model::updatePlayedCards(){
    playedCards_.clear();
    for(int i = 0; i < 4; i++){
        std::vector<Card *> v = players_[i]->playedCards();
        playedCards_.insert(playedCards_.end(), v.begin(), v.end());
    }
    
}

bool Model::playTurn(Card* c){
    if(isRoundFinished()){
        state_ = ROUND_ENDED;
        updateScoresAndResetPlayers();
        notify();
        if(currentPlayer_ >= 0){
        if(players_[currentPlayer_]->isHuman()) {
            currentPlayer_--;
            if(currentPlayer_ < 0) currentPlayer_ = 3;
        }
        }
        return true;
    }

    if(isRoundFinished() && checkIfGameEnded()){
        state_ = GAME_ENDED;
        return false;
    }

    std::vector<Card *> legalPlays = this->getLegalPlays();
    int i = legalPlays.size();
    bool flag = players_[currentPlayer_]->turn(c, playedCards_);
    if(flag == true){
        numTurns_++;
        if(isRoundFinished()) state_ = ROUND_ENDED;
        if(i > 0){
            turn_ = PLAY;
            updatePlayedCards();
        }
        else{
            turn_ = DISCARD;
        }
    }
    notify();
    return flag;
}

void Model::resetTableDeck(){
    playedCards_.clear();
    numTurns_ = 0;
    turn_ = NONE;
}

void Model::stateIS(State state){
    state_ = state;
}

void Model::seedIS(int s){
    seed_ = s;
}

int Model::seed() const{
    return seed_;
}

void Model::updateScoresAndResetPlayers(){
    for(int i = 0; i < 4; ++i){
        players_[i]->newRound();
    }
}

void Model::ragequit(){
    ComputerPlayer *c = new ComputerPlayer;
    std::vector<Card *> hand = players_[currentPlayer_]->hand();
    std::vector<Card *> played = players_[currentPlayer_]->playedCards();
    std::vector<Card *> discarded = players_[currentPlayer_]->discardedCards();

    for(size_t i = 0; i < hand.size(); ++i){
        c->addCard(hand[i]);
    }

    for(size_t i = 0; i < played.size(); ++i){
        c->addPlayedCard(played[i]);
    }

    for(size_t i = 0; i < discarded.size(); ++i){
        c->addDiscardedCard(discarded[i]);
    }

    players_[currentPlayer_].reset(c);
}

void Model::clearData(){
    playedCards_.clear();
    if(players_.size() > 0){
        for(int i = 0; i < 4; ++i){
            Player *p = players_[i].release();
            delete p;
        }
        players_.clear();
    }

    if(deck_.get() != nullptr){
        (deck_.get())->clearData();
        Deck *d = deck_.release();
        delete d;
    }

    firstPlayer_ = -1;
    currentPlayer_ = -1;
    numTurns_ = 0;
    seed_ = -1;
    state_ = NOT_VALID;
    turn_ = NONE;
}

bool Model::checkIfGameEnded() const{
    for(int i = 0; i < 4; ++i){
        if(players_[i]->totalScore() >= 80){
            return true;
        }
    }

    return false;
}

bool Model::isRoundFinished() const{
    return numTurns_ == 52;
}

Player* Model::currentPlayer() const{
    return players_[currentPlayer_].get();
}

Player* Model::getPlayer(int index) const{
    return players_[index].get();
}

int Model::getCurrentPlayerNumber() const{
    return currentPlayer_;
}

int Model::getFirstPlayerNumber() const{
    return firstPlayer_;
}

Model::State Model::getState() const{
    return state_;
}

Model::Turn Model::getTurn() const{
    return turn_;
}

std::vector<Card *> Model::getDeck() const{
    std::vector<Card *> v;
    for(int i = 0; i < 52; ++i){
        v.emplace_back(deck_->getCard(i));
    }

    return v;
}

std::vector<bool> Model::cardsOnTable() const{
    std::vector<bool> v;
    for(int i = 0; i < 52; ++i){
        v.push_back(false);
    }

    for(size_t i = 0; i < playedCards_.size(); ++i){
        if(playedCards_[i]->getSuit() == CLUB){
            v[(int)playedCards_[i]->getRank()] = true;
        }
        else if(playedCards_[i]->getSuit() == DIAMOND){
            v[(int)playedCards_[i]->getRank() + 13] = true;
        }
        else if(playedCards_[i]->getSuit() == HEART){
            v[(int)playedCards_[i]->getRank() + 26] = true;
        }
        else if(playedCards_[i]->getSuit() == SPADE){
            v[(int)playedCards_[i]->getRank() + 39] = true;
        }
    }

    return v;
}

std::vector<int> Model::winners() const{
    std::vector<int> points;
    for(int i = 0; i < 4; ++i){
        points.push_back(players_[i]->totalScore());

    }

    int min = points[0];
    for(int i = 1; i < 4; ++i){
        if(points[i] < min){
            min = points[i];
        }
    }

    std::vector<int> winners;
    for(int i = 0; i < 4; ++i){
        if(points[i] == min){
            winners.push_back(i+1);
        }
    }

    return winners;
} 
