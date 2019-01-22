#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"

class Card;

class ComputerPlayer : public Player {
    public:
        //Pre-condition: None
        //Post-conditon: ComputerPlayer object exists
        //Requires: None
        //Modifies: private variables for Parent Player
        //Throws: none
        //Ensures: ComputerPlayer Object exists
        ComputerPlayer() = default;
        
        //Pre-condition: None
        //Post-conditon: ComputerPlayer object does not exist 
        //Requires: None
        //Modifies: private variables for Parent Player
        //Throws: none
        //Ensures: ComputerPlayer Object is deleted 
        ~ComputerPlayer() = default;
        
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

