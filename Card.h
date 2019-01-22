#ifndef CARD_H
#define CARD_H

#include <ostream>
#include <istream>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card{
	friend std::istream &operator>>(std::istream &, Card &);

public:
	//Pre-condition: None
    //Post-conditon: Card object exists
    //Requires: None
    //Modifies: initializes hand_, playedCards_, discardedCards_ for object
    //Throws: none
    //Ensures: private fields are initialized
        
    Card(Suit, Rank);
	//Pre-condition: None
    //Post-conditon: None 
    //Requires: None
    //Modifies:None
    //Throws: none
    //Ensures:None
    //Returns: suit_ 
        
    Suit getSuit() const;
	//Pre-condition: None
    //Post-conditon: None 
    //Requires: None
    //Modifies: None
    //Throws: none
    //Ensures:None
    //Returns: rank_
        
    Rank getRank() const;
	
private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);


#endif
