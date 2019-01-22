#ifndef TEXTVIEW_H_
#define TEXTVIEW_H_
#include "Card.h"
#include "Command.h"
#include "Player.h"
#include "Model.h"
#include "Controller.h"
#include <vector>
#include <cassert>

class TextView {
    private:
        Model* model_;
        Controller* controller_;

    public:
        //Pre-condition: None
        //Post-conditon: View object exists
        //Requires: Model* and Controller* be pointers pointing to valid objects 
        //Modifies: None 
        //Throws: none
        //Ensures: Deck Object exists
        TextView(Model* , Controller*);
        
        //Pre-condition: None
        //Post-conditon: View object does not exist 
        //Requires: Model* and Controller* be pointers pointing to valid objects 
        //Modifies: None 
        //Throws: none
        //Ensures: View Object is deleted 
        ~TextView();
        
        //Pre-condition: None
        //Post-conditon: Correct output printed on std::cout 
        //Requires: model_->state_ be in correct state  
        //Modifies: model_ 
        //Throws: none
        //Ensures: Output printed is coherent to game's state 
        void render();
        
        //Pre-condition: None
        //Post-conditon: Cards Played by players are printed in correct order 
        //Requires: model_->cardsonTable() sends correct input 
        //Modifies: None 
        //Throws: none
        //Ensures: Played cards printed on std::cout 
        void printcardsOnTable();
        
        //Pre-condition: None
        //Post-conditon: Correct Action is taken by program in accordance to command 
        //Requires: None 
        //Modifies: model_ 
        //Throws: none
        //Ensures: None 
        void processCommand(bool &,bool &, bool &);
        
        //Pre-condition: None
        //Post-conditon: State of deck is printed 
        //Requires: None 
        //Modifies: None 
        //Throws: none
        //Ensures: Deck is printed in correct order 
        void printDeck();
};

#endif
