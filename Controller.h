#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include <vector>
class Controller{
    private:
        Model* model_;
    public:

        //Pre-condition: None
        //Post-conditon: Controller object exists
        //Requires: Model* ve a valid pointer to a valid object 
        //Modifies: None 
        //Throws: none
        //Ensures: Controller Object exists
        Controller(Model* );
       
        //Pre-condition: None
        //Post-conditon: Controller object does not exist
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: Controller Object is deleted
        ~Controller();
       
        //Pre-condition: None
        //Post-conditon: State of program is corresponding to begin of round
        //Requires: vector in arguement be a valid vector with only h or c as elements
        //Modifies: model_ 
        //Throws: none
        //Ensures: Model is initialized properly
        void setupGame(std::vector<std::string>);
       
        //Pre-condition: None
        //Post-conditon: Cards are distributed to players and state is changed
        //Requires: None
        //Modifies: model_ 
        //Throws: None
        //Ensures: Model is in correct State
        void startNewRound();
       
        //Pre-condition: None
        //Post-conditon: Play goes to next Player
        //Requires: None
        //Modifies: model_ 
        //Throws: none
        //Ensures: Play continues
        void continueRound();
       
        //Pre-condition: None
        //Post-conditon: Players scores are updated and players prep for new round
        //Requires: None
        //Modifies: model_ 
        //Throws: none
        //Ensures: Game is in correct state to start new round
        void updateScoresAndResetPlayers();
       
        //Pre-condition: None
        //Post-conditon: Player cards are changed after valid turn 
        //Requires:Card* be a valid pointer to valid card object 
        //Modifies: model_ 
        //Throws: none
        //Ensures: Correct turn is played
        //Returns: true if play on card is valid, false otherwise
        bool playTurn(Card* );
       
        //Pre-condition: None
        //Post-conditon: Current HumanPlayer is replaced by Computer Player
        //Requires: None
        //Modifies: model_ 
        //Throws: none
        //Ensures: Current Human player is computerized
        void rageQuit();
       
        //Pre-condition: None
        //Post-conditon: Model is cleaned up
        //Requires: None
        //Modifies: model_ 
        //Throws: none
        //Ensures: All data in model_ is deleted
        void endGame();
       
        //Pre-condition: None
        //Post-conditon: New state of game is equal to argument
        //Requires: valid State provided as argument
        //Modifies: model_ 
        //Throws: none
        //Ensures: New state of game is the state provided
        void setState(Model::State);
};
#endif
