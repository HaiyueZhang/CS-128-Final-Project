#include <map>
#include "player.hpp"

using namespace std;

Player::Player(string name): name_(name), score_(0) {}


Move Player::PlayerChoice() { 
    string choice;
    cout << "Draw or fold?" << endl;
    while(true) {
        cin >> choice; 
        for (size_t i = 0; i < choice.length(); ++i) { // Changes to lowercase
            choice.at(i) = tolower(choice.at(i));
        }
        if (choice == "draw") return Move::kDraw;
        if (choice == "fold") return Move::kFold;
        // If the user input is invalid, require it again
        cout << "Please only enter draw or fold.";
    }
    return PlayerChoice(); // IS THIS RECURSIVE STEP NECESSARY?
}

string Player::PlayerChoiceTest(string input) {
    for (size_t i = 0; i < input.length(); ++i) { // Changes to lowercase
        input.at(i) = tolower(input.at(i));
    }
    if (input == "draw") return "draw";
    if (input == "fold") return "fold";
    return "invalid";
    // Must not reach here
    throw std::runtime_error("must not reach here");
}

void Player::ClearCards() {
    cards_.clear();
}

int Player::CheckPair() {
    map<int, bool> m;
    for (size_t i = 0; i < cards_.size(); ++i) {
        if (m.find(cards_.at(i)) != m.end()) { // If a pair is found, return the value of the pair card
            return cards_.at(i);
        }
        m[cards_.at(i)] = true; // Else, add the value of the indexed card to the map
    }
    return 0; // If a pair is not found, return 0
}