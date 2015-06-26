/**********************************************************
 * test.cpp
 *		  	
 * This file performs some basic tests of each class
 *		  	
 *   Author: Com L. 
 *   Date: Summer 2015
 */
		  	
#include "card.h"
#include "deck.h" 
#include "player.h"
#include <iostream> // std::cout
#include <iomanip> //std::setprecision
#include <ctime> //std::clock()


using namespace std; 

#define CARD 0
#define DECK 1
#define PLAYER 2
#define TEST_NUM PLAYER


int main ()
{
	#if TEST_NUM == CARD
	/*testing card class functionality */ 
	card a; 
	a.number = 1;
	a.color = wild; 
	cout << "Card A: " << a << endl; 

	card b; 
	b.number = 1; 
	b.color  = wild; 
	cout << "Card B: " << b << endl; 

	card c; 
	c.number = 2; 
	c.color  = red; 
	cout << "Card C: " << c << endl; 
	
	cout << "check if a and c are compatible:"; 
	if (a == c) 
		cout << "true" << endl; 
	else
		cout << "false" << endl; 
	#endif
	/*testing deck class functionality */ 


	#if TEST_NUM == DECK
	/* deck constructor */ 
	deck main_deck; 
	main_deck.create(); 
	cout << "DECK" << endl;
	main_deck.print_deck();  


	/* deck copy cctor */ 
	deck new_deck(main_deck); 
	cout << "NEW DECK" << endl; 
	//new_deck.print_deck(); 

	/*deck equal operator */ 
	new_deck = main_deck; 
	
	/*shuffle function */ 
	clock_t c_start = clock(); 
	new_deck.shuffle(); 
	clock_t c_end = clock(); 
	cout << "shuffle" << endl; 
	cout << fixed << setprecision(2) << "CPU time used: " << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms" << endl; 
	//new_deck.print_deck(); 

	/* quick shuffle function */ 
	c_start = clock(); 
	main_deck.quick_shuffle(); 
	c_end = clock(); 
	cout << "quick shuffle" << endl; 
	cout << fixed << setprecision(2) << "CPU time used: " << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms" << endl;
	cout << endl << endl; 
	cout << "before draw" << endl; 
	main_deck.print_deck();

	
	/* draw function */ 
	for (int i = 0 ; i < 107; i++) 
	{
		main_deck.draw(); 
	}
	cout << "after draw" << endl; 
	main_deck.print_deck(); 

	for (int i = 0 ; i < 150 ; i++) 
		main_deck.add_card(card()); 
	cout << "after add" << endl; 
	main_deck.print_deck(); 
	#endif

	#if TEST_NUM == PLAYER
	/* testing player class implementation */ 

	/* testing adding cards to player's hand */ 
	player COM1; 
	cout << "PLAYER w/ one card " << endl; 
	COM1.hand_add(card()); 
	COM1.print(); 
	cout << "PLAYER w/ more cards " << endl; 

	card a; 
	a.number = 1;
	a.color = wild; 
	card b; 
	b.number = 3; 
	b.color  = yellow; 
	card c; 
	c.number = 2; 
	c.color  = red; 
	
	COM1.hand_add(a); 
	COM1.hand_add(b); 
	COM1.hand_add(c); 

	COM1.print(); 

	
	/* testing copy cctor */ 
	cout << "copy cctor test player COM3(COM1);" << endl; 
	player COM3(COM1); 
	COM3.print();

	/* testing operator equal */ 
	cout << "operator equal COM4 = COM3" << endl; 
	player COM4; 
	COM4 = COM3; 
	COM4.print();


	/*testing removing cards from player's hand */ 
	cout << "removing cards from player " << endl; 

	player COM2; 
	COM2.hand_add(card()); 
	COM2.hand_add(a); 
	COM2.hand_add(b); 
	COM2.hand_add(c); 
	COM2.print();
	cout << endl; 
	
	for (int i = 3 ; i >= 0 ; i--)
	{
		COM2.hand_remove(i); 
		COM2.print(); 
		cout << endl; 

	} 

	
	for (int i = 0 ; i < 10 ; i ++) 
	{
		COM2.hand_add(card()); 
	}
	COM2.print(); 
	cout << endl; 
	for (int i = 0 ; i < 10 ; i ++)
	{ 
		COM2.hand_remove(0);  
	}
	COM2.print(); 
	cout << endl;


	#endif

	return 0; 


}


