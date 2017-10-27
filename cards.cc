#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include "cards.h"

Game game;

int main(int argc, char** argv) {
	Deck& main_deck = game.GetDeck();
    bool running = true;
    game.DealTable();
    while(running) {
      printf("A - add player\nC - clear game\nD - deal card\nE - exit\nL - list players\n(R - remove player)\nS - shuffle deck\nV - view deck\nChoice: ");

      char choice;
      std::cin >> choice;

      switch(choice) {
        case 'A':
        {
          std::string player_name;
          printf("Enter player name: ");
          std::cin >> player_name;
          game.AddPlayer(player_name);
          printf("Player added!\n");
          break;
        }
        case 'C':
        {
          game.ClearGame();
          printf("Game cleared!\n");
          break;
        }
        case 'D':
        {
          game.DealCard();
          printf("Dealt!\n");
          break;
        }
        case 'E':
        {
          running = false;
          printf("Bye!\n");
          break;
        }
        case 'L':
        {
          std::vector<Player> player_list = game.GetPlayers();

          if(player_list.size() == 0)
            printf("No players!\n");

          for(std::vector<Player>::iterator it = player_list.begin(); it != player_list.end(); ++it) {
            printf("==== %s ====\n", (*it).GetName().c_str());
            std::vector<Card> card_list = (*it).GetCards();
            if(card_list.size() == 0)
              printf("No cards!\n");
            for(std::vector<Card>::iterator itt = card_list.begin(); itt != card_list.end(); ++itt) {
              printf("%s %s\n", (*itt).GetRankName(), (*itt).GetSuitName());
            }
          }
          break;
        }
        case 'R':
        {
          printf("Unimplemented!\n");
          break;
        }
        case 'S':
        {
          main_deck.Shuffle();
          printf("Deck Shuffled!\n");
          break;
        }
        case 'V':
        {
          printf("========\n");
          std::vector<Card> card_list = main_deck.GetCards();
          if(card_list.size() == 0)
            printf("No cards!\n");
          for(std::vector<Card>::iterator itt = card_list.begin(); itt != card_list.end(); ++itt) {
            printf("%s %s\n", (*itt).GetRankName(), (*itt).GetSuitName());
          }
          printf("========\n");
          break;
        }
        default:
          printf("Invalid choice!\n");
          break;
      }
    }
}; 
