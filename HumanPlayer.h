#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class Card;

class HumanPlayer : public Player{
    public:
        //Pre-condition: None
        //Post-conditon: HumanPlayer object exists
        //Requires: None
        //Modifies: private variables for Parent Player
        //Throws: none
        //Ensures: HumanPlayer Object exists
        HumanPlayer() = default;
        
        //Pre-condition: None
        //Post-conditon: HumanPlayer object does not exist 
        //Requires: None
        //Modifies: private variables for Parent Player
        //Throws: none
        //Ensures: HumanPlayer Object is deleted 
        ~HumanPlayer() = default;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: true 
        virtual bool isHuman() const override;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: vector of Card* be a valid vector pointing to valid objects 
        //Modifies: oldScore_, roundScore_, hand_, playedCards_, discardedCards_ 
        //Throws: none
        //Ensures: Card* is removed from hand_ and added to discardedCards_
        //Returns: true if Card* was played legally, else false 
        virtual bool turn(Card *, std::vector<Card *>&);
};

#endif
