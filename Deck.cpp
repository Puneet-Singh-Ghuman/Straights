#include "Card.h"
#include "Deck.h"
#include <random>

int seed = 0;

Deck::Deck(){}

Deck::~Deck(){}

void Deck::initialize(){
    for(int i = 0; i < SUIT_COUNT; ++i){
        for(int j = 0; j < RANK_COUNT; ++j){
           cards_.emplace_back(std::make_unique<Card>(static_cast<Suit>(i), static_cast<Rank>(j))); 
        }
    }
}

Card* Deck::getCard(int index){
    return cards_[index].get();
}

void Deck::shuffle(int seed){
    static std::mt19937 rng(seed);

	int n = 52;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = cards_[n].release();
		cards_[n].reset(cards_[k].release()); 
		cards_[k].reset(c);
	}

}

void Deck::clearData(){
    for(size_t i = 0; i < cards_.size(); ++i){
        Card *c = cards_[i].release();
        delete c;
    }
    cards_.clear();
}
