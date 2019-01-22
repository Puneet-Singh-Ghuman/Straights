#ifndef MODEL_H
#define MODEL_H
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Subject.h"
#include <vector>
#include <memory>

class Model : public Subject {
    public:
        enum State {NOT_VALID, ROUND_BEGIN, ROUND_IN_PROGRESS, ROUND_ENDED, GAME_ENDED};
        enum Turn {NONE, PLAY, DISCARD};
        //Pre-condition: None
        //Post-conditon: Model object exists
        //Requires: valid int as argument 
        //Modifies: None 
        //Throws: none
        //Ensures: Model Object exists
        Model(int);
        
        //Pre-condition: None
        //Post-conditon: Model object does not exist
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: Deck Object is Deleted 
        ~Model();
        
        //Pre-condition: None
        //Post-conditon: state_ is GAME_ENDED
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: true if game ended, false otherwise 
        bool checkIfGameEnded() const;
        
        //Pre-condition: None
        //Post-conditon: state_ is ROUND_ENDED 
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: true if round ended, else false 
        bool isRoundFinished() const;
        
        //Pre-condition: None
        //Post-conditon: None
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: vector of winners 
        std::vector<int> winners() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: players_[currentPlayer_] 
        Player* currentPlayer() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: valid int as argument 
        //Modifies: None 
        //Throws: none
        //Ensures: cuurent player is returned
        //Returns: players_[int] 
        Player* getPlayer(int) const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: deck_ is in valid state 
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: vector of Card* equivalent of deck_'s state 
        std::vector<Card *> getDeck() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: all legal plays for players_[currentPlayer_] 
        std::vector<Card *> getLegalPlays();
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None 
        //Returns: state_
        State getState() const;
        
        //Pre-condition: None
        //Post-conditon: 
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: vector of boolean values representing state of playedCards_ 
        std::vector<bool> cardsOnTable() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None 
        //Returns: currentPlayer_
        int getCurrentPlayerNumber() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: None
        //Returns: firstPlayer_ 
        int getFirstPlayerNumber() const;
        
        //Pre-condition: Deck exists
        //Post-conditon: Deck initialized to default
        //Requires: None
        //Modifies: deck_ 
        //Throws: none
        //Ensures: none
        void initializeDeck();
        
        //Pre-condition: None
        //Post-conditon: playedCards_ is empty
        //Requires: None
        //Modifies: playedCards_ 
        //Throws: none
        //Ensures: playedCards_.size() = 0
        void resetTableDeck();
        
        //Pre-condition: None
        //Post-conditon: players_ is initialized
        //Requires: vector of char is valid with only elements either c or h
        //Modifies: players_ 
        //Throws: none
        //Ensures:Players are initialized 
        void setupPlayers(std::vector<std::string>&);
        
        //Pre-condition: deck_ is initialized
        //Post-conditon: Deck object exists
        //Requires: None
        //Modifies: deck_ 
        //Throws: none
        //Ensures: cards are shuffled with seed_ 
        void shuffle();
        
        //Pre-condition: None
        //Post-conditon: players_ hand() is updated
        //Requires: deck_ shuffled
        //Modifies: players_ 
        //Throws: none
        //Ensures:Cards are distributed among players to start play 
        void distributeCards();
        
        //Pre-condition: None
        //Post-conditon: state_ = state 
        //Requires: None
        //Modifies: state_ 
        //Throws: none
        //Ensures: state_ is set to new state 
        void stateIS(State state);
        
        //Pre-condition: None
        //Post-conditon: currentPlayer_ increased by 1
        //Requires: None
        //Modifies: currentPlayer_ 
        //Throws: none
        //Ensures:play moves to next Player 
        void nextPlayer();
       
        //Pre-condition: state is ROUND_ENDED
        //Post-conditon: All player scores updated with round score and players reset 
        //Requires: None
        //Modifies: players_ 
        //Throws: none
        //Ensures: players_ is set for new round
        void updateScoresAndResetPlayers();
       
        //Pre-condition: None
        //Post-conditon: playedCards_ is updated with latest turn 
        //Requires: None
        //Modifies: playedCards_ 
        //Throws: none
        //Ensures: playedCards_ contain the card played by player
        void updatePlayedCards();
       
        //Pre-condition: None
        //Post-conditon: Card* is played or discarded by Current player
        //Requires: Card* is valid pointer to valid object 
        //Modifies:  players_[currentPlayer_] 
        //Throws: none
        //Ensures: 
        //Returns: true if valid play, false otherwise
        bool playTurn(Card *);
       
        //Pre-condition: Current Player object exists and is Human
        //Post-conditon: Human Player is changed to Computer Player
        //Requires: None
        //Modifies: players_[currentPlayer_] 
        //Throws: none
        //Ensures: players_[currentPlayer_] is computerized
        void ragequit();
       
        //Pre-condition: None
        //Post-conditon: playedCards_ is empty 
        //Requires: None
        //Modifies: playedCards_ 
        //Throws: none
        //Ensures: playedCards_ is empty
        void clearData();


        int seed() const;
        void seedIS(int);
        Turn getTurn() const;
    private:
        std::vector<std::unique_ptr<Player> > players_;
        std::unique_ptr<Deck> deck_;
        int firstPlayer_;
        int currentPlayer_;
        int numTurns_;
        std::vector<Card *> playedCards_;
        int seed_;
        State state_;
        Turn turn_;
};

#endif
