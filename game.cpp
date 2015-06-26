/**********************************************************
 * game.cpp
 *		  	
 * game play implementation 
 *		  	
 *   Author: Com L. 
 *   Date: Summer 2015
 */

/* this cpp file will be the main function for the game
   -asking players to play cards into the a middle temp field
   -ask player for a color if wild card is played 
   -distributing cards
   -show the amount of cards left for each player 

*/ 

// NOTE : must clear screen before next player plays their cards

/* will create the game by asking
	- amount of players
	- amount of AI players
*/ 


// NOTE
//In a two-player game, the Reverse has the same effect as a Skip, allowing the player who discards it to take another turn

/* turns 
 (turn++)%amount_players
on player zero's turn reset back to zero 

*/

/* ACTION CARDS
Draw-2 : next player draws 2 and loses a turn 
SKIP: next player loses turn (+2 instead of plus one) 
REVERSE: switch the direction (from ++ to -- ) , in two player same as skip
WILD: choose a color
Draw-3 WILD: choose a color, next player draws 4 and loses a turn 
*/

#include "card.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <fstream> // for opening and closing files
#include <string> 
#include <cstdlib> // std::system() ; std::rand()
#include <limits> // std::numeric_limits
using namespace std; 

#define TEXTFILE "intro.txt"
#define PRINT_ALL_PLAYERS 0
#define TEMP_DECK 1
#define TURN 2
#define TEST -1

/* function from http://www.cplusplus.com/doc/tutorial/files/ */ 
void display_intro(string filename)
{
	string line; 
	fstream myfile; 
	myfile.open(filename.c_str()); 
	/*c_str() is to fix the problem of C++ type mismatch of 
 	‘std::string {aka std::basic_string<char>}’ and ‘const char*’
	http://stackoverflow.com/questions/17750699/c-displaying-a-text-file-echo-a-text-file
	*/
	if (myfile.is_open())
	{
		while( getline(myfile, line)) 
		{
			cout << line << endl; 
		}
		myfile.close(); 
	}
	else
	{
		cout << "error unable to open file " << endl; 
	}

}

void confirm_turn (int x)
{
	/* http://www.cplusplus.com/forum/articles/7312/ */
	cout << "Confirm Player" << x << " by typing " << "'" << x << "'" << " and pressing enter" << ": " ;
	int temp; 
	while( temp != x)
	{
		cin >> temp; 
	}
}

/* http://stackoverflow.com/questions/5938052/assigning-values-to-enumerated-types*/ 
COLOR FromString (const string & str)
{
	if ( str == "red") 
		return red; 
	else if (str == "green")
		return green; 
	else if (str == "blue")
		return blue; 
	else if (str == "yellow") 
		return yellow; 
	else
		return wild; 
} 


int main()
{ 
	/*clear screen */
	/* http://stackoverflow.com/questions/2347770/how-do-you-clear-console-screen-in-c */ 
	system("clear"); // note will only work in LINUX env't
	/* display an introduction to the game in the beginning */ 
	display_intro(TEXTFILE); 
	/* ask user for amount of players */ 
	int amount_players; 
	int flag = 0; 
	while (flag == 0 ) 
	{
		cout << "Please enter amount of players: "; 
		cin >> amount_players; 
		if (amount_players >= 2 && amount_players <= 5) 
		{
			cout << amount_players << " players entering game .... " << endl; 
			flag = 1; 
			break; 
		}
		else
		{
			cout << "invalid amount of players" << endl; 
		}	
	}
	/* create the components of the game */ 
	/* creating deck */ 
	deck main_deck; 
	main_deck.create(); 
	main_deck.quick_shuffle();
	/* creating player array */ 
	player * play_array; 
	play_array = new player[amount_players]; 
	/* distributing 7 starting cards to each player */ 
	for (int i =0 ; i < amount_players ; i ++) 
	{
		for (int k= 0 ; k< 7 ; k++) 
		{
			card temp_card; 
			temp_card = main_deck.draw(); 
			play_array[i].hand_add(temp_card); 
		}
	}
	/* all cards that are played will go to temp_deck */ 
	deck temp_deck; 
	/* create the first starting card, by drawing from deck */ 
	card played_card; 
	card temp_card; 
	int card_flag = 0 ; 
	while (card_flag == 0 ) 
	{
		temp_card = main_deck.draw(); 
		/* if first card is not wild, then okay*/ 
		if (temp_card.color != wild) 
		{
			card_flag = 1; 
			played_card = temp_card; 
		}
		/* if first card is wild, redraw */ 
		else
		{
			temp_deck.add_card(temp_card); 
		}
	}


	#if TEST == PRINT_ALL_PLAYERS
	/*print out testing */ 
	for (int i =0; i < amount_players ; i++) 
	{
		cout << "player: " << i << endl; 
		play_array[i].print(); 
	}
	#endif
	/* randomize who starts first */ 
	/*change the seed , so randomized number is different each time*/ 
	/* fix is from  http://stackoverflow.com/questions/13896450/rand-returns-the-same-number-each-time-the-program-is-run */ 
	srand(time(NULL));
	int turn = rand() % amount_players; 
	cout << "PLAYER " << turn << " is randomly selected to play first" << endl; 
	confirm_turn(turn); 

	bool force_draw_bool = false; 
	int turn_flag = 1; 
	int win = 0 ;
	/* keep playing until a player wins */ 
	while (win == 0 ) 
	{
		// clear screen
		system("clear");  


		#if TEST == TEMP_DECK
		temp_deck.print_deck(); 
		#endif 

		// Fixed error , at first created a new player each time , therefore did not update
		// Have to use player pointer instead
		player * curr_player = &play_array[turn%amount_players]; 


		// checked for forced draw cards 
		cout << "PLAYER " << turn%amount_players << endl;

		if (force_draw_bool)
		{
		// checked for Draw-2
		if (played_card.number == 10) 
		{
			cout << "Forced Draw-2" << endl; 
			card draw_2; 
			for (int i = 0 ; i < 2; i ++) 
			{
				draw_2 = main_deck.draw(); 
				curr_player->hand_add(draw_2); 
			} 		
		}
		
		// check for Draw-4 
		if (played_card.number == 14) 
		{
			cout << "Forced Draw-4" << endl; 
			card draw_4; 
			for (int i = 0 ; i < 4; i ++) 
			{
				draw_4 = main_deck.draw(); 
				curr_player->hand_add(draw_4); 
			} 

		}
			force_draw_bool = false; 
		}


		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl; 
		for (int i= 0 ; i < amount_players; i ++ ) 
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   " ; 
		}
		cout << endl; 
		// print out the temporary card 
		cout << "Played Card: " << played_card << endl; 
		// print out cards in player's hand
		cout << "PLAYER " << turn%amount_players << endl; 
		
		curr_player->print(); 
		int check_flag = 0 ; 
		int index; 
		int size = curr_player->get_size(); 
		// ask for which card to play into middle
		while (check_flag == 0) 
		{
			cout << "which card do you want to play? " << endl; 
			cout << "If you want to draw a card please enter '-1' " << endl; 
			cout << "Type the index of the card and press enter: ";
			cin >> index; 
			//check if index is to draw a card
			if (index == -1) 
			{
				card draw_temp; 
				draw_temp = main_deck.draw(); 
				cout << "DRAWN CARD: " << draw_temp << endl; 
				if (draw_temp == played_card && draw_temp.color != wild) 
				{
					
					int play_draw_flag = 0 ; 
					while (play_draw_flag == 0 ) 
					{

					string temp_play; 
					cout << "Do you want to play the drawn card [y/n] : " ;
					cin >> temp_play; 
					if (temp_play == "y")
					{
						played_card = draw_temp; 
						temp_deck.add_card(draw_temp); 
						if (played_card.number >= 10 && played_card.number <= 14) 
						{
						force_draw_bool = true; 
						}	
						play_draw_flag = 1; 
					}
					if (temp_play == "n")
					{
						curr_player->hand_add(draw_temp);
						play_draw_flag = 1; 
					}
				

					}			
					 
				}
				else
				{
					curr_player->hand_add(draw_temp);
				}
				check_flag = 1; 

			}
			//check if index is valid
			if (index >= 0 && index < size) 
			{
				// check if card is compatilbe with played card
				card temp = curr_player->peek(index); 
				if (temp == played_card)
				{
					//remove from player's hand
					curr_player->hand_remove(index); 
					// add to the discarded pile
					temp_deck.add_card(temp); 
					// change the played card
					played_card = temp; 
					// check if card is a wild card 
					if(played_card.color == wild)
					{
						int check_color = 0; 
						COLOR temp_color; 
						string str_color; 
						while (check_color == 0) 
						{
							// ask for new color
							cout << "Please choose a color (red , green, blue, yellow) :"; 
							cin >> str_color; 
							// change string to enum type COLOR
							temp_color = FromString(str_color); 
							// check if valid color
							if (temp_color != wild)
							{
								played_card.color = temp_color; 
								check_color = 1; 
							}
							else
							{
								cout << "invalid color" << endl;
							}
							 
						}
					}
					if (played_card.number >= 10 && played_card.number <= 14) 
					{
						force_draw_bool = true; 
					}		
					check_flag = 1;
				} 
				else
				{
					cout << "card cannot be played " << endl; 
				}
			}
			else
			{
				cout<<"invalid index " << endl; 
			}
		}
		
		
		

		// check if there is a winner, and break while loop 
		if ( curr_player->get_size() == 0 ) 
		{
			win =1; 
			cout << "PLAYER " << turn%amount_players << " has won the game." << endl;
			break; 
		}



		// NOTE: would be better if changed turn_flag to boolean of CW or CCW
		// check for action cards that influence the turn here
		// skip case
		if (played_card.number == 11 && force_draw_bool == true ) 
		{
			if (turn_flag == 1) 
				turn = turn+2; 
			else
				turn = turn-2;  
		}
		// reverse case 
		else if (played_card.number == 12 && force_draw_bool == true) 
		{
			// if only two players, behaves like a skip card
			if (amount_players == 2) 
			{
				turn = turn+2; 
			}
			else
			{
				// changes the rotation of game (from CW to CCW or vice versa) 
				if (turn_flag ==1) 
				{
					turn_flag = -1; 
					turn--; 
				}
				else
				{
					turn_flag = 1; 
					turn++; 
				}

			}
		}
		// for other cards 
		else
		{
			// depending on going Clockwise or CounterClockwise
			if (turn_flag == 1) 
				turn++;
			else
				turn--;
		}

		
		system("clear") ;
		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl; 
		for (int i= 0 ; i < amount_players; i ++ ) 
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   " ; 
		}
		cout << endl; 
	
		// print out the temporary card 
		cout << "Played Card: " << played_card << endl; 
		confirm_turn(turn%amount_players); 	

		/*
		// when main deck is running out of cards
		if (main_deck.get_size() < 10)
		{
			// flush remaining cards from main to temp deck
			for (int i =0 ; i < main_deck.get_size() ; i++) 
			{
				temp_deck.add_card(main_deck.draw()); 
			}
			//recreate main_deck and shuffle it
			main_deck = temp_deck;
			main_deck.quick_shuffle();
			// clear temp deck   
			temp_deck = deck(); 

		}*/
		

	}


	
	return 0; 
}



