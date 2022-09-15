#include <vector>
#include <iostream>
#include <map>
#include "application.hpp"

using namespace std;

void Application::RunGame() {
    InitPlayers();
    DealFirstCard();
    DisplayInfo();
    while(true) {
        for (int i = 0; i < player_num_; ++i) {
            cout << "It's " << players_.at(i).GetName() << "'s turn." << endl;
            Move m = players_.at(i).PlayerChoice();
            HandleChoice(m, i);
            if (CheckEnd()) {
                return;
            }
            DisplayInfo();
        }
    }
}

void Application::DisplayInfo() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "The losing score is " << losing_score_ << endl; // Display the losing score
    for (int i = 0; i < player_num_; ++i){ // Display the score of each player
        cout << players_.at(i).GetName() << ": " << players_.at(i).GetScore() << "  ";
    }
    cout << endl;
    cout << "Players' cards: " << endl; // Display the cards of each player
    for (int i = 0; i < player_num_; ++i) {
        vector<int> temp = players_.at(i).GetCards();
        cout << players_.at(i).GetName() << ": ";
        for (size_t j = 0; j < temp.size(); ++j) {
            cout << temp.at(j) << " ";
        }  
        cout << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

Application::Application() {
    player_num_ = 0;
    losing_score_ = 0;
}

void Application::InitPlayers() {
    // initialize player_num_
    cout << "How many players will participate in this game?" << endl;
    string input;
    while (true) { // Check if the input is valid
        cin >> input;
        if (!IsInteger(input)) cout << "Please only enter integer" << endl; 
        else if (stoi(input) < kMinPlayer) cout << "There must be at least " << kMinPlayer << " players. Please re-enter" << endl; 
        else if (stoi(input) > kMaxPlayer) cout << "There must be no more than " << kMaxPlayer << " players. Please re-enter" << endl;
        else break;
    }
    player_num_ = stoi(input);
    // initialize name_ for each player
    for (int i = 0; i < player_num_; ++i) {
        cout << "Enter player" << i + 1 << "'s name_: " << endl;
        string name_;
        while (true) { // ensure that the input is not empty
            cin >> name_;
            if (name_.empty()) cout << "Player name cannot be empty" << endl;
            else break;
        }
        Player p(name_);
        players_.push_back(p);
    }
    // initialize losing_score_
    losing_score_ = player_num_ * 5;
} 

void Application::InitPlayersTest(string num, vector<string> names) {
    // initialize player_num_
    if (!IsInteger(num)) throw runtime_error("Not Integer"); // throw runtime_error for invalid input
    if (stoi(num) < kMinPlayer) throw runtime_error("Below minimum"); // throw runtime_error for invalid input
    if (stoi(num) > kMaxPlayer) throw runtime_error("Above maximum"); // throw runtime_error for invalid input
    player_num_ = stoi(num);
    // Check for testing error
    if (player_num_ != (int) names.size()) throw runtime_error("Testing error : num != names.size()");
    // initialize name_ for each player
    for (int i = 0; i < player_num_; ++i) {
        if (names.at(i).empty()) throw runtime_error("Empty player name"); // throw runtime_error for empty player name
        Player p(names.at(i));
        players_.push_back(p);
    }
    // initialize losing_score_
    losing_score_ = player_num_ * 5;
}

void Application::DealFirstCard() {
    for (int i = 0; i < player_num_; ++i) {
        int card = deck_.GetNextCard();
        players_.at(i).AddCard(card);
    }
    BreakTie();
}

void Application::BreakTie() {
    vector<int> tie = CheckTie();
    if (tie.size() > 0) {
        if (CheckRunOut(2)) return;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    while (tie.size() > 0) { // If two players have the same card, deal them new cards.
        if (CheckRunOut(2)) return;
        cout << players_.at(tie.at(0)).GetName() << " and " << players_.at(tie.at(1)).GetName()
        << " have the same card : " << players_[tie[0]].GetCards().at(0) << endl;
        cout << "Find them new cards" << endl;
        for (size_t i = 0; i < tie.size(); ++i) {
            players_.at(tie.at(i)).ClearCards();
            int card = deck_.GetNextCard();
            players_.at(tie.at(i)).AddCard(card);
        }
        tie = CheckTie(); // Repeat until each player is dealt a different card
    }   
}

vector<int> Application::CheckTie() {
    map<int, int> m;
    vector<int> result;
    for (int i = 0; i < player_num_; ++i) { 
        vector<int> playerCards = players_.at(i).GetCards();
        int card = playerCards.at(0);
        if (m.find(card) != m.end()) { // If another player already has the same card, 
            // Return the player numbers of the tied players as a vector
            result.push_back(m[card]);
            result.push_back(i);
            return result;
        }
        m[card] = i; // Else, add the value of the card and the player number to the map
    }
    return result; // If there is no tie, return an empty vector
}  

void Application::ClearAllCards() {
    for (int i = 0; i < player_num_; ++i) {
        players_.at(i).ClearCards();
    }
}

void Application::HandleChoice(Move m, int index) {
    if (m == Move::kFold) { // Handle fold
        int min = MinCard(index);
        players_.at(index).AddScore(min);
        ClearAllCards();
        cout << players_.at(index).GetName() << " chooses Fold and gains " << min 
            << " points, ending the round." << endl;
        if (CheckRunOut(player_num_)) return;
        DealFirstCard();
    } else if (m == Move::kDraw) { // Handle draw
        int card = deck_.GetNextCard();
        players_.at(index).AddCard(card);
        int p = players_.at(index).CheckPair();
        if (p > 0) { // If player has a pair, he/she loses the round
            players_.at(index).AddScore(p);
            ClearAllCards();
            cout << players_.at(index).GetName() << " gets a pair and gains " << p 
                << " points, ending the round." << endl;
            if (CheckRunOut(player_num_)) return;
            DealFirstCard();
        }
    }
}

int Application::MinCard(int index) {
    int min = INT32_MAX;
    vector<int> pcards = players_.at(index).GetCards();
    for (size_t i = 0; i < pcards.size(); ++i) {
        if (pcards.at(i) < min) {
            min = pcards.at(i);
        }
    }
    return min;
}

bool Application::CheckEnd() {
    for (int i = 0; i < player_num_; ++i) {
        int score = players_.at(i).GetScore();
        if (score >= losing_score_) {
            cout << players_.at(i).GetName() << " loses with " << score << " points." << endl;
            return true;
        }
    }
    return false;
}

bool Application::CheckRunOut(int cards_to_deal) {
    if (deck_.GetCurrentIndex() > Deck::kFullDeck - cards_to_deal) {
        cout << "The deck has run out." << endl;
        cout << "The round ends with no loser and the deck has been reshuffled." << endl;
        deck_.Shuffle();
        deck_.ReInitCurrentIndex();
        ClearAllCards();
        DealFirstCard();
        return true;
    }
    return false;
}

// Check if the input is int
bool Application::IsInteger(const string& str) {
            return !str.empty() && find_if(str.begin(), str.end(), [](unsigned char c) {return !isdigit(c);}) == str.end();
}