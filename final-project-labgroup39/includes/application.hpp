#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "player.hpp"
#include "deck.hpp"

using namespace std;

class Application {
    public:
        // Whole game is running here
        void RunGame();

        // Visual display of the game
        // Print the current information (name, score, cards) of each player
        void DisplayInfo();

        // Default constructor for the application.
        Application(); 

        // Getter for player_num_
        //
        // @return player_num_
        int GetPlayerNum() {return player_num_;}

        // Getter for losing_score_
        //
        // @return losing_score_
        int GetLosingScore() {return losing_score_;}

        // Getter for players_
        //
        // @return players_
        vector<Player> GetPlayers() {return players_;}

        // Getter for deck_
        //
        // @return deck_
        Deck GetDeck() {return deck_;}

        // Setter for player_num_
        //
        // @param num int to initialize player_num_
        void SetPlayerNum(int num) {player_num_ = num;}

        // Setter for losing_score_
        //
        // @param score score to initialize losing_score_
        void SetLosingScore(int score) {losing_score_ = score;}

        // Setter for players_
        //
        // @param players vector of players to initialize players_
        void SetPlayers(vector<Player> players) {players_ = players;}

        // Proc user input for the number of the players and their names
        void InitPlayers();

        // Unit-test function for InitPlayers()
        //
        // @param num the user input for the number of players
        // @param names vector of user inputs for player names
        void InitPlayersTest(string num, vector<string> names);

        // Deal the first card to each player
        void DealFirstCard();

        // Deal new cards until each player has a different initial card
        void BreakTie();

        // Check if two players are dealt the same card
        //
        // @return a vector pair of indicies of the player with the same card
        vector<int> CheckTie();

        // Clear all of the players' cards
        void ClearAllCards();

        // Handles the player's choice of move.
        // If Fold, the player will score the lowest scoring card he/she has and the round ends.
        // If Draw, the player draws another card.
        // If the newly drawn card completes a pair, the player scores the value of the paired card and the round ends.
        //
        // @param m the player's move
        // @param index the player index
        void HandleChoice(Move m, int index);

        // Return the lowest value card the player has
        //
        // @param index the player index
        // @return the lowest value card the player has
        int MinCard(int index);

        // Check if there is a losing player.
        //
        // @return true if any player has scored the losing_score_ or more, false otherwise.
        bool CheckEnd();

        // Check if the deck has run out.
        // If so, abort the current round and start a new round with a new deck.
        // The player index does not change.
        // @param cards_to_deal the number of cards to deal
        // @return true if the deck has run out, false otherwise
        bool CheckRunOut(int cards_to_deal);

        // Check if the input is int
        //
        // @param str the input string to check
        // @return true if the input is int, false otherwise
        bool IsInteger(const string& str);
 
    private:
        // The number of players
        int player_num_;
        // The losing score
        int losing_score_;
        // The vector conataining all the players
        vector<Player> players_;
        // The deck used for the game
        Deck deck_;

        // The minimum number of players allowed
        static constexpr int kMinPlayer = 2; 
        // The maximum number of players allowed
        static constexpr int kMaxPlayer = 5; 
};

#endif
