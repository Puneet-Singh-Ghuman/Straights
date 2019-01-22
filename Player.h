#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

class Card;

class Player{
    private:
        std::vector<Card *> hand_;
        std::vector<Card *> playedCards_;
        std::vector<Card *> discardedCards_;
        int roundScore_;
        int oldScore_;
   
        int currentIndex(Card *);
    
    public:
        //Pre-condition: None
        //Post-conditon: Player object exists
        //Requires: None
        //Modifies: initializes hand_, playedCards_, discardedCards_ for object
        //Throws: none
        //Ensures: private fields are initialized
        Player();
        
        //Pre-condition: None
        //Post-conditon: Player object does not exist
        //Requires: Player or derived class object exist
        //Modifies: hand_, playedCards_, discardedCards_ for object
        //Throws: none
        //Ensures: Object is deleted
        virtual ~Player() = 0;

        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: false
        virtual bool isHuman() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: roundScore_ + oldScore_
        int totalScore() const;

        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: roundScore_
        int roundScore() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: oldScore_
        int oldScore() const;

        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: hand_
        std::vector<Card *> hand();
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: playedCards_
        std::vector<Card *> playedCards();
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: discardedCards_
        std::vector<Card *> discardedCards();
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: size of hand_
        int handSize() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: size of playedCards_
        int playedCardsSize() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: method be called on valid object
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: size of discardedCards_
        int discardedCardsSize() const;

        //Pre-condition: None
        //Post-conditon: None 
        //Requires: playedCards_ be non-empty
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: last index of playedCards_
        Card* getLastPlayed() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: playedCards_ be non-empty
        //Modifies: None
        //Throws: none
        //Ensures: None
        //Returns: last index of discardedCards_
        Card* getLastDiscarded() const;
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: Card* be a pointer to valid Card object
        //Modifies: hand_
        //Throws: none
        //Ensures: Card* is added to hand_
        void addCard(Card *);
       
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: Card* be a pointer to valid Card object
        //Modifies: playedCards_
        //Throws: none
        //Ensures: Card* is added to playedCards_
        void addPlayedCard(Card *);
       
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: Card* be a pointer to valid Card object
        //Modifies: discardedCards_
        //Throws: none
        //Ensures: Card* is added to discardedCards_
        void addDiscardedCard(Card *);
       
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: Card* be a pointer to valid Card object
        //Modifies: hand_, playedCards_ 
        //Throws: none
        //Ensures: Card* is removed from hand_ and added to playedCards_
        //Returns: true if valid Card*, else false
        bool playCard(Card *);

        //Pre-condition: None
        //Post-conditon: None 
        //Requires: Card* be a pointer to valid Card object
        //Modifies: hand_, discardedCards_ 
        //Throws: none
        //Ensures: Card* is removed from hand_ and added to discardedCards_
        //Returns: true if valid Card*, else false
        bool discardCard(Card *);
       
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: vector be a valid vector of Card *
        //Modifies: None 
        //Throws: none
        //Ensures: Cards defined as legal are returned
        //Returns: vector of Cards which contain all legal cards
        std::vector<Card *> getLegalPlays(std::vector<Card *>&);
        
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: None 
        //Modifies: oldScore_, roundScore_, hand_, playedCards_, discardedCards_ 
        //Throws: none
        //Ensures: None
        //Returns: None 

        void newRound();
       
        void endGame();
        //Pre-condition: None
        //Post-conditon: None 
        //Requires: vector of Card* be a valid vector pointing to valid objects 
        //Modifies: oldScore_, roundScore_, hand_, playedCards_, discardedCards_ 
        //Throws: none
        //Ensures: Card* is removed from hand_ and added to discardedCards_
        //Returns: true if Card* was played legally, else false 
        virtual bool turn(Card *, std::vector<Card *>&) = 0;
};

#endif
