# Lab Group 39 Final Project: Drawing or Folding
## Game Overview
This is a card game. There are 55 cards comprised of $1 \times$ card 1, $2 \times$ card 2, .... $10 \times$ card 10. This game needs at least two players. Each player will have a different card at first. Then, they can draw one card or fold (which ends their turn). If they get a pair, the round is over and they score according to the points of the paired card. If not, play passes to the next player. If they fold, they will score points equal to the lowest card in their own stack. When someone scores over the target score, they will lose the game. 
### How to Play
First, the deck is shuffled. It will then draw out a certain number of cards during each turn depending on the amount of players. For instance, if there are four players, the program will draw out four cards and each player will receive one card. If there is a paired number within the four cards, the process is repeated until each player receives a different card.

On your turn, you have two choices: drawing (taking a card) or folding (ending the round). If you either get a pair or fold, the round is over and you will score points. If not, play passes to the next player.

Drawing: When you draw a card, your goal is to not get a pair. If you draw a pair, the round ends, and you score points equal to the number on the paired card.

Folding: You can give fold instead of taking a card. This will also end the round. You score points equal to the lowest card in your own stack. In different situations, folding can be better than drawing, which depends on your probability of drawing a pair.

Ending the round: When one person draws a paired card or folds, the round ends. The scored paired cards will remove one card from the deck. Discarding all cards from the players' stacks, collect all cards left together to prepare for the new round. When the new round starts, the reshuffle the deck and the game will continue.

Losing the game: There are no winners; there is just one loser. The game ends when one player reaches the target score, which equals the number of players times 5. 

## Running the Code
Run the file driver.cc to begin playing the game. You will be prompted to enter the number of players (between 2 and 5, inclusive) and their names. Afterwards, the game will run by itself. Each turn will be printed out.

## How to Run the Test Suite
Download all the files included in the final project folder and run tests.cc. We used the C++ framework Catch2 to write our test cases.