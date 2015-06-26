/**********************************************************
 * deck.cpp
 *		  	
 * deck class implementation
 *		  	
 *   Author: Com L. 
 *   Date: Summer 2015
 */


/* Game UNO - wikipedia
deck consists of 108 cards 
	25 of each color ( red, green, blue, and yellow) 
	each color having two of each rank except zero 
	zero to nine
	"Skip"
	"Draw Two" 
	"Reverse " 
	"Wild " 
	"Wild Draw Four" 

*/ 


/* 
zero - 4 cards (RGBY) 
one till nine - 4 cards (RGBY) & 4 cards (RGBY)
ten "Skip" -  4 cards (RGBY) & 4 cards (RGBY)
eleven "Draw Two" -  4 cards (RGBY) & 4 cards (RGBY)
twelve "Reverse " -  4 cards (RGBY) & 4 cards (RGBY)
thirteen "Wild " -  4 cards (RGBY)
fourteen "Wild Draw Four" -  4 cards (RGBY)


01234 =  wild + RGBY
zero = wild 
one = red
two = green
three = blue 
four = yellow 

*/ 




#define DECK_SIZE 108

#include "deck.h"
#include "card.h"
#include <iostream> // std:: cout
#include <cstdlib> // std::rand, std::srand
using namespace std; 

deck::deck() 
{
	ptr_deck = new card[DECK_SIZE];
	size = 0;

	
}

void deck::create()
{
	int num = 0 ; 
	

	// card rank 0
	for (int col = 1 ; col <= 4  ; col++) 
	{
		ptr_deck[size].number = num; 
		ptr_deck[size].color = static_cast<COLOR>(col);  
		size++; 			
	}
	
	// card rank 1 till 9 , "draw-two", "skip", "reverse"
	for (num = 1; num <= 12; num++) 
	{
		for (int x = 0 ; x < 2 ; x++ )
		{
			for (int col = 1 ; col <= 4  ; col++) 
			{
				ptr_deck[size].number = num; 
				ptr_deck[size].color = static_cast<COLOR>(col);  	
				size++; 		
			}	
		}

	}

	// card "wild", "wild-draw-four"
	for (num = 13 ; num <= 14 ; num++) 
	{
		for (int x = 0 ; x < 4 ; x++) 
		{
			ptr_deck[size].number = num; 
			ptr_deck[size].color = wild;  
			size++; 
		}			
	}


}

deck::deck(const deck & other)
{
	copy(other); 
}


const deck & deck::operator= (const deck & other) 
{
	if (this != &other) 
	{
		clear(); 
		copy(other); 
	}
	return *this; 
} 



deck::~deck() 
{
	clear(); 
}




void deck::shuffle() 
{
	/* Own method */ 
	/* rand whether to swap or not  ( greater than 50% swap)*/ 
	/* rand on which position to swap (rand from 0 to 107 inclusive)*/ 

	/*Researched method = GeeksforGeeks.org */  
	/* O(n^2) shuffle : simple method */ 
	/* create temp array which is a copy of original */ 
	/* copy randomly selected element in temp to arr[0] */ 
	/* repeat the process */ 
	/* time complexity of this solution will be O(n^2)  */ 
	

	// create a temp deck 
	card * temp_deck = new card[size]; 
	for (int i =0; i<size; i++) 
	{
		temp_deck[i] = ptr_deck[i]; 
	}


	int temp_size = size; 
	int temp_pos; 
	int pos; 
	for (int i = 0 ; i <size; i++ ) 
	{
		// randomly find a position in temp_deck
		srand(time(NULL)); // change the seed , so randomized number is different each time
		pos = rand() % temp_size; 
		//assign random element to deck[i]
		ptr_deck[i] = temp_deck[pos]; 
				
		// removing element from temp_deck (O(n) to shift) 
		temp_size--; 
		for (temp_pos = pos ; temp_pos < temp_size ; temp_pos++) 
		{
			temp_deck[temp_pos] = temp_deck[temp_pos+1];
		}
	}
	
	delete [] temp_deck; 
	


}
card deck::draw() 
{
	if (size <= 0) 
	{
		// do this inside gameplay
		//recreate 
		//must take into account cards in player's hands 
		return card(); 
	}
	card temp_card = ptr_deck[size-1]; 
	size--; 
	return temp_card; 
} 


int deck::add_card(card temp_card)
{
	// O(1) insert 
	if(size < DECK_SIZE)
	{
		ptr_deck[size] = temp_card; 
		size++; 
		return 0; 
	}	
	else
		return -1; 
}


void deck::quick_shuffle() 
{
/* O(n) shuffle : fisher -yates shuffle algorithm (GeeksforGreeks.org) 
	given rand() generates a random number in O(1)
	start from last element 
	swap it with randomly selected from whole array including last
	now consider array from 0 to n-2(size reduced by 1 ) 
	repeat the process until we hit first element 
*/ 
	int pos; 
	int temp_size = size-1; 
	card temp_card; 
	while(temp_size > 0 )
	{
		//generate random
		srand(time(NULL)); // change the seed , so randomized number is different each time
		pos = rand() % temp_size;
		// swap elements 
		temp_card = ptr_deck[temp_size]; 
		ptr_deck[temp_size] = ptr_deck[pos]; 
		ptr_deck[pos] = temp_card; 
		// reduce size by 1 
		temp_size--; 
	}

}



void deck::print_deck()
{
	for (int i= 0 ; i< size ; i++) 
	{
		cout << i << ": " << ptr_deck[i] << endl; 
	}
}

void deck::copy(const deck & other)
{
	size = other.size; 
	ptr_deck = new card[size]; 
	for (int i =0 ; i < size ; i++) 
	{
		ptr_deck[i] = other.ptr_deck[i]; 
	}
}


void deck::clear() 
{
	delete []ptr_deck; 
	ptr_deck = NULL; 
	size = 0; 
}


int deck::get_size()
{
	return size; 
}
