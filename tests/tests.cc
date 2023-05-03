// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Labgroup39                     Environment : ubuntu:bionic                //
//  Date ......: 2021/12/2                      Compiler ...: clang-10                     //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "application.hpp"
#include "deck.hpp"
#include "player.hpp"

#include <string>
#include <vector>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// Debug lines
// -fsanitize=address,null -fno-omit-frame-pointer -fsanitize=undefined

// DECK //

TEST_CASE("Deck constructor", "[Deck]") {
    SECTION("Deck size is correct") {
        Deck d;
        REQUIRE(d.GetCards().size() == Deck::kFullDeck);
    }
    SECTION("Deck contains the right amount of each card") {
        Deck d;
        const int kMaxCard = 10;
        for (int card = 1; card <= kMaxCard; ++card) { // 1X1, 2X2, 3X3,..., 10X10
            REQUIRE(d.ContainCards(card, card));
        }
    }
    SECTION("Shuffle : the order is randomized") {
        // Note that this test is based on probability
        // So there is a very small chance that it fails when it should succeed
        Deck first;
        Deck second;
        bool same = true;
        for (int i = 0; i < Deck::kFullDeck; ++i) {
            if (first.GetCards().at(i) != second.GetCards().at(i)) same = false;
        }
        REQUIRE_FALSE(same);
    }
}

TEST_CASE("Deck::GetNextCard", "[GetNextCard]") {
    SECTION("Valid card") {
        Deck d = Deck();
        bool valid = true;
        for (int i = 0; i < Deck::kFullDeck; ++i) {
            int card = d.GetNextCard();
            if (card < 1 || card > 10) valid = false;
        }
        REQUIRE(valid);
    }
    SECTION("Deck size is correct") {
        Deck d = Deck();
        for (int i = 0; i < Deck::kFullDeck; ++i) {
            d.GetNextCard();
        }
        REQUIRE_THROWS_AS(d.GetNextCard(), out_of_range);
    }
}

// Player

TEST_CASE("Player Constructor", "[Player]") {
    SECTION("The variables are initialized correctly") {
        Player p("test");
        REQUIRE(p.GetName() == "test");
        REQUIRE(p.GetScore() == 0);
        REQUIRE(p.GetCards().size() == 0);
    }
}

TEST_CASE("Player::PlayerChoice", "[PlayerChoice]") {
    Player p("test");
    SECTION("Valid inputs") {
        REQUIRE(p.PlayerChoiceTest("draw") == "draw"); 
        REQUIRE(p.PlayerChoiceTest("DrAW") == "draw");
        REQUIRE(p.PlayerChoiceTest("fold") == "fold");
        REQUIRE(p.PlayerChoiceTest("FOLD") == "fold");   
    }
    SECTION("Invalid inputs") {
        REQUIRE(p.PlayerChoiceTest("dra") == "invalid");
        REQUIRE(p.PlayerChoiceTest("drawZ") == "invalid");
        REQUIRE(p.PlayerChoiceTest("") == "invalid");
        REQUIRE(p.PlayerChoiceTest("8") == "invalid");
    }
}

TEST_CASE("Player::ClearCards", "[ClearCards]") {
    Player p("test");
    p.AddCard(1);
    p.AddCard(4);
    p.AddCard(10);
    REQUIRE(p.GetCards().size() == 3);
    p.ClearCards();
    REQUIRE(p.GetCards().empty());
}

TEST_CASE("Player::CheckPair", "[CheckPair]") {
    Player p("test");
    SECTION("No pairs") {
        p.AddCard(5);
        p.AddCard(1);
        REQUIRE(p.CheckPair() == 0);
        p.AddCard(10);
        REQUIRE(p.CheckPair() == 0);
    }
    SECTION("Has a pair") {
        p.AddCard(5);
        p.AddCard(2);
        p.AddCard(5);
        REQUIRE(p.CheckPair() == 5);
    }
}

// Application

TEST_CASE("Application Constructor", "[Application]") {
    SECTION("Variables are intialized correctly") {
        Application game;
        REQUIRE(game.GetPlayerNum() == 0);
        REQUIRE(game.GetLosingScore() == 0);
        REQUIRE(game.GetPlayers().empty());
        REQUIRE(game.GetDeck().GetCards().size() == Deck::kFullDeck);
    }
}

TEST_CASE("Application::InitPlayers", "[InitPlayers]") {
    SECTION("Input for player_num_ is not an integer") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        REQUIRE_THROWS_AS(game.InitPlayersTest("a092", names), runtime_error);
        REQUIRE_THROWS_AS(game.InitPlayersTest("092z", names), runtime_error);
        REQUIRE_THROWS_AS(game.InitPlayersTest("0.0", names), runtime_error);
        REQUIRE_THROWS_AS(game.InitPlayersTest("", names), runtime_error);
    }
    SECTION("Input for player_num_ is below kMinPlayer") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        REQUIRE_THROWS_AS(game.InitPlayersTest("-19", names), runtime_error);
        REQUIRE_THROWS_AS(game.InitPlayersTest("1", names), runtime_error);
    }
    SECTION("Input for player_num_ is above kMaxPlayer") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        REQUIRE_THROWS_AS(game.InitPlayersTest("6", names), runtime_error);
    }
    SECTION("Input size mismatch") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        REQUIRE_THROWS_AS(game.InitPlayersTest("2", names), runtime_error);
        REQUIRE_THROWS_AS(game.InitPlayersTest("4", names), runtime_error);
        REQUIRE_THROWS_AS(game.InitPlayersTest("5", names), runtime_error);
    }
    SECTION("Empty player name") {
        Application game;
        vector<string> names = {"a", "b", ""};
        REQUIRE_THROWS_AS(game.InitPlayersTest("3", names), runtime_error);
    }
    SECTION("Valid input : 2 players") {
        Application game;
        vector<string> names = {"a", "b"};
        game.InitPlayersTest("2", names);
        REQUIRE(game.GetPlayers().at(0).GetName() == "a");
        REQUIRE(game.GetPlayers().at(1).GetName() == "b");
        REQUIRE(game.GetLosingScore() == 10);
    }
    SECTION("Valid input : 5 players") {
        Application game;
        vector<string> names = {"a", "b", "c", "d", "e"};
        game.InitPlayersTest("5", names);
        REQUIRE(game.GetPlayers().at(0).GetName() == "a");
        REQUIRE(game.GetPlayers().at(4).GetName() == "e");
        REQUIRE(game.GetLosingScore() == 25);
    }
}

TEST_CASE("Application::CheckTie", "[CheckTie]") {
    SECTION("No tie") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        game.InitPlayersTest("3", names);
        Player a("a");
        Player b("b"); 
        Player c("c"); 
        a.AddCard(1);
        b.AddCard(3);
        c.AddCard(5);
        vector<Player> players = {a, b, c};
        game.SetPlayers(players);
        REQUIRE(game.CheckTie().empty());
    }
    SECTION("Tie") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        game.InitPlayersTest("3", names);
        Player a("a");
        Player b("b"); 
        Player c("c"); 
        a.AddCard(1);
        b.AddCard(3);
        c.AddCard(1);
        vector<Player> players = {a, b, c};
        game.SetPlayers(players);
        REQUIRE(game.CheckTie().at(0) == 0);
        REQUIRE(game.CheckTie().at(1) == 2);
    }
}

TEST_CASE("Application::MinCard", "[MinCard]") {
    SECTION("Only one card") {
        Application game;
        vector<string> names = {"a", "b"};
        game.InitPlayersTest("2", names);
        Player a("a");
        Player b("b"); 
        a.AddCard(3);
        b.AddCard(10);
        vector<Player> players = {a, b};
        game.SetPlayers(players);
        REQUIRE(game.MinCard(0) == 3);
        REQUIRE(game.MinCard(1) == 10);
    }
    SECTION("Many cards") {
        Application game;
        vector<string> names = {"a", "b"};
        Player a("a");
        Player b("b"); 
        b.AddCard(7);
        b.AddCard(3);
        b.AddCard(10);
        vector<Player> players = {a, b};
        game.SetPlayers(players);
        REQUIRE(game.MinCard(1) == 3);
    }
}

TEST_CASE("Application::CheckEnd()", "[CheckEnd]") {
    SECTION("There is no loser yet") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        Player a("a");
        Player b("b");
        Player c("c");
        a.AddScore(3);
        b.AddScore(10);
        vector<Player> players = {a, b, c};
        game.SetPlayers(players);
        REQUIRE_FALSE(game.CheckEnd());
    }
    SECTION("Loser with score_ == losing_score_") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        Player a("a");
        Player b("b");
        Player c("c");
        a.AddScore(3);
        b.AddScore(15);
        vector<Player> players = {a, b, c};
        game.SetPlayers(players);
        game.SetLosingScore(15);
        game.SetPlayerNum(3);
        REQUIRE(game.CheckEnd());
    }
    SECTION("Loser with score_ > losing_score_") {
        Application game;
        vector<string> names = {"a", "b", "c"};
        Player a("a");
        Player b("b");
        Player c("c");
        a.AddScore(3);
        b.AddScore(16);
        vector<Player> players = {a, b, c};
        game.SetPlayers(players);
        game.SetLosingScore(15);
        game.SetPlayerNum(3);
        REQUIRE(game.CheckEnd());
    }
}

TEST_CASE("Application::ClearAllCards", "[ClearAllCards]") {
    Application game;
    vector<string> names = {"a", "b"};
    game.InitPlayersTest("2", names);
    Player a("a");
    Player b("b"); 
    a.AddCard(3);
    a.AddCard(6);
    a.AddCard(7);
    b.AddCard(2);
    b.AddCard(5);
    b.AddCard(10);
    vector<Player> players = {a, b};
    game.SetPlayers(players);
    game.ClearAllCards();
    REQUIRE(game.GetPlayers().at(0).GetCards().empty());
    REQUIRE(game.GetPlayers().at(1).GetCards().empty());
}

TEST_CASE("Application::IsInteger()", "[IsInteger]") {
    SECTION("Is integer") {
        Application game;
        REQUIRE(game.IsInteger("0"));
        REQUIRE(game.IsInteger("99"));
    }
}
