#include "deck.hpp"

using namespace std;

Deck::Deck(): cards_(vector<int>(kFullDeck)) {
    int index = 0;
    for (int i = 1; i < 11; ++i) {
        for (int j = 0; j < i; ++j) {
            cards_.at(index) = i;
            ++index;
        }
    } 
    Shuffle();
    current_index_ = 0;
}

void Deck::Shuffle() {
    vector<int> TempDeck; // Create a new empty deck
    while(TempDeck.size() < kFullDeck) {
        int randindex = rand() % cards_.size(); // Between 0 and deck's size
        int card = cards_.at(randindex);
        TempDeck.push_back(card);
        cards_.erase(cards_.begin() + randindex);
    }
    cards_ = TempDeck;
}

int Deck::GetNextCard() {
    int c = cards_.at(current_index_);
    ++current_index_;
    return c;
}

bool Deck::ContainCards(int value, int amount) {
    int count = 0;
    for (auto card : cards_) {
        if (card == value) ++count;
    }
    return count == amount;
}