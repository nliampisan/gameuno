/**********************************************************
 * player.h
 *		  	
 * Player class
 *		  	
 *   Author: Com L. 
 *   Date: Summer 2015
 */



/* class player 

public : 
	play cards to center
	draw card
	pass turn
	
	show amount of cards left 
	show cards in hand (for playing to center) 
 
	
private: 
	cards on the hand ( limit to the half the deck of cards) 
	an array 

*/ 
#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
class player
{
	public: 
		player(); 
		player(const player & other); 
		const player & operator= (const player & other); 
		~player(); 
		void hand_add(card temp); 
		card hand_remove(int pos); 
		void uno(); 
		void print() const; 
		int get_size() const; 
		card peek(int pos) const; 
	private:
		class card_elem
		{
		  public: 
			card_elem()
			{
				next = NULL; 	
			}
			card data; 
			card_elem * next; 
		};


		card_elem * head; 
		int size; 
		void copy(const player & other); 
		void clear(); 

		
}; 

#endif 
