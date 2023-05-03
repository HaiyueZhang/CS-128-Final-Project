#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "deck.hpp"

using namespace std;

// Types of moves allowed
enum class Move {kDraw, kFold}; 

// Active players for the game
class Player {
    public:
        // Parameterized constructor for Player
        //
        // @param name the name of the player
        Player(string name);
        
        // Getter for name_
        //
        // @return name_
        string GetName() const {return name_;}

        // Getter for cards_
        //
        // @return cards_
        vector<int> GetCards() const {return cards_;}

        // Getter for score_
        //
        // @return score_
        int GetScore() const {return score_;}

        // Add score for the round's loser
        //
        // @param score the score to be added
        void AddScore(int score) {score_ += score;}

        // Add card to player's deck
        //
        // @param the card to be added
        void AddCard(int card) {cards_.push_back(card);}
        
        // Take player's choice of move as user input and return it as Move value
        //
        // @return the player's choice of move
        Move PlayerChoice();

        // Unit-test function for PlayerChoice()
        //
        // @param input the input string taken from the user
        // @return "draw" or "fold" for valid inputs, and "invalid" for invalid input
        string PlayerChoiceTest(string input);

        // Clear all the cards the player has
        void ClearCards();
        
        // Check whether one player get a pair
        //
        // @return the value of the pair card if the player has a pair, and 0 otherwise
        int CheckPair();

        // The number of cards in a full deck
        static constexpr int kFullDeck = 55;

    private:
        // The name of the player
        string name_;
        // The list of cards the player has
        vector<int> cards_;
        // The total score of the player
        int score_;
};

#endif