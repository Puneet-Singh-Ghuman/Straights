#ifndef DECK_H
#define DECK_H
#include <vector>
#include <memory>

class Card;

extern int seed;

class Deck{
    private:
        std::vector<std::unique_ptr<Card> > cards_;

    public:
        
        //Pre-condition: None
        //Post-conditon: Deck object exists
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: Deck Object exists
        Deck();
        
        //Pre-condition: None
        //Post-conditon: Deck object does not exist
        //Requires: None
        //Modifies: None 
        //Throws: none
        //Ensures: Deck Object is deleted  
        ~Deck();
       
        //Pre-condition: Deck Object exists
        //Post-conditon: None
        //Requires: method be called on valid Deck object 
        //Modifies: cards_
        //Throws: none
        //Ensures: cards_ contain valid Card Obejcts in correct order  
        void initialize();
       
        //Pre-condition: None
        //Post-conditon: Deck object does not exist
        //Requires: int >=0 
        //Modifies: None 
        //Throws: none
        //Ensures: Respective Card object is returned
        //Returns: Valid Card object  
        Card * getCard(int);
       
        //Pre-condition: cards_ are initialized using initialize() method 
        //Post-conditon: cards_ are arranged in different order
        //Requires: 
        //Modifies: cards_ 
        //Throws: none
        //Ensures: Cards in Deck are shuffled accroding to provided seed  
        void shuffle(int seed = 0);
        void clearData();
};

#endif
