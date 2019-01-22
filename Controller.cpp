#include "Controller.h"
Controller::Controller(Model* model) : model_(model){}

Controller::~Controller(){}

void Controller::setupGame(std::vector<std::string> type){
    model_->setupPlayers(type);
    model_->initializeDeck();

    startNewRound();
}

void Controller::startNewRound(){
    model_->resetTableDeck();
    model_->shuffle();

    updateScoresAndResetPlayers();
    // This should find the first player as well
    model_->distributeCards();

    if(model_->currentPlayer()->isHuman()){
        return;
    }

    else{
        continueRound(); 
    }
}

void Controller::continueRound(){
    if(model_->getState() == Model::GAME_ENDED ){
            return;
        }
    
    if(model_->currentPlayer()->isHuman() == false){
        playTurn(nullptr);
    } else {
        return;
    }

    if(model_->getState() == Model::NOT_VALID) return;

    if(model_->currentPlayer()->isHuman()) return;
    // advance to next Player
    model_->nextPlayer();

    if(model_->currentPlayer()->isHuman() == false){
        continueRound();
    } else {
        return;
    }
}

void Controller::updateScoresAndResetPlayers(){
    model_->updateScoresAndResetPlayers();
}

bool Controller::playTurn(Card* c){
    bool b =  model_->playTurn(c);
    if(c != nullptr){
        model_->nextPlayer();
    } else{
        return b;
    }

    continueRound();
    return b;
}

void Controller::rageQuit(){
    model_->ragequit();
    continueRound();
}

void Controller::endGame(){
    model_->clearData();
}

void Controller::setState(Model::State state){
    model_->stateIS(state);
}
