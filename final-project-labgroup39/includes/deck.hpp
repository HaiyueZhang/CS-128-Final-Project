#ifndef DECK_HPP
#define DECK_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

// A deck of cards shared by all the players
class Deck {
    public:
        // Default constructor for the deck
        // Initialize the deck with 55 cards consisting of 1 X 1, 2 X 2, ... 10 X 10.
        Deck();

        // Getter for cards_
        //
        // @return cards_
        vector<int> GetCards() {return cards_;}

        // Getter for current_index_
        //
        // @return current_index_
        int GetCurrentIndex() {return current_index_;}

        // Randomize the order of the cards in the deck
        void Shuffle(); 

        // Returns the value of the next card in the deck and increment the current index by 1
        //
        // @return the value of the next card
        int GetNextCard();

        // Set the current_index_ to 0.
        void ReInitCurrentIndex() {current_index_ = 0;}

        // Test helper function
        // Check that cards_ has the indicated amount of a certain card
        //
        // @param value the value of the card
        // @param amount the amount of the card contained in cards_
        // @return true if cards_ contain the correct amount of the card, false otherwise
        bool ContainCards(int value, int amount);

        // The number of cards in a full deck
        static constexpr int kFullDeck = 55; 
        
    private:
        // The list of cards in the deck
        vector<int> cards_;
        // Index of current card   
        int current_index_; 
};

#endif