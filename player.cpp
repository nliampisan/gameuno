/**********************************************************
 * player.cpp
 *		  	
 * Player class implementation
 *		  	
 *   Author: Com L. 
 *   Date: Summer 2015
 */

#include "card.h"
#include "player.h"
#include <iostream>
using namespace std; 

 
player::player()
{
	head = NULL; 
	size = 0; 
}


player::player(const player & other) 
{
	copy(other); 	
}


const player & player::operator= (const player & other)
{
	if ( this != &other)
	{
		clear(); 
		copy(other); 
	}
	
	return *this; 

} 


player::~player()
{
	clear(); 
}

 
void player::hand_add(card temp_card)
{
	//insert at the front of the linked list

	//create new code and assign data to it 
	card_elem * temp_ptr; 
	temp_ptr = new card_elem(); 
	temp_ptr->data = temp_card; 
	//link the node to the original list
	temp_ptr->next = head; 
	//change the head to point to new element
	head = temp_ptr; 
	//increment size
	size++; 

}

card player::hand_remove(int pos)
{
	// error checking 
	if (pos < 0 || pos >= size ) 
	{
		return card(); 
	}	
		
	//O(n) remove (b/c of O(n) to find

	card_elem * prev_ptr = head;
	card_elem * target = prev_ptr->next; 
	card temp_card; 
	int temp_pos = pos; 
	
	// delete at front (case without previous ) 
	if (pos == 0 ) 
	{
		//save data to return
		temp_card = head->data; 
		// move head to the next one over
		head = head->next; 
		// delete target element
		delete prev_ptr; 
		//decrement size
		size--; 
		return temp_card; 
	}
	//find previous element 
	while (temp_pos > 1 ) 
	{
		prev_ptr = prev_ptr->next; 
		target = prev_ptr->next; 
		temp_pos--; 
		
	}
	//connect previous element to next element 
	prev_ptr->next = target->next; 
	//save data into temp_card
	temp_card = target->data; 
	//delete the target element 
	delete target; 
	//decrement size
	size--; 
	// return the target element 
 	return temp_card; 

}


 
void player::uno()
{

}

void player::print() const
{
	int temp_size = size;
	
	int i = 0;  
	card_elem *temp_ptr = head; 
	while (temp_size > 0) 
	{
		cout <<  i << ":  " << temp_ptr->data << endl; 
		temp_ptr = temp_ptr->next; 
		i++; 
		temp_size--; 
	}

}



void player::copy(const player & other)
{
	size = other.size;
	 
	//create the head of target player   
	if (size > 0 ) 
	{
		head = new card_elem();
		//fill head with data	
		head->data = other.head->data; 
	}
	else
	{
		head = NULL; 
		return; 
	}
	
	//other_ptr to traverse the other list
	card_elem * other_ptr = other.head->next; 
	//create a temp_ptr to create the rest of linked list
	card_elem * temp_ptr; 
	//create a previous ptr to point next to correct one
	card_elem * prev_ptr = head; 
	for (int i=1 ; i<size; i++) 
	{
		// create new elem
		temp_ptr = new card_elem(); 
		//link the previous to current
		prev_ptr->next = temp_ptr; 
		// fill it with data
		temp_ptr->data = other_ptr->data; 
		// move to next one in the list
		prev_ptr = temp_ptr; 
		temp_ptr = NULL; 
		other_ptr = other_ptr->next; 
	}

}
 
void player::clear()
{
	card_elem * temp_ptr = head; 
	card_elem * next_ptr; 
	while (size > 0) 
	{
		next_ptr = temp_ptr->next; 
		delete temp_ptr; 
		temp_ptr = next_ptr; 
		size--; 
	}
	head = NULL; 
}

int player::get_size() const
{	
	return size; 
}


//could have fast run time if returned a card and position in list
// position in list can be used be hand_remove to remove the element
card player::peek(int pos) const
{
	int temp_pos = pos; 
	card_elem * temp_elem = head; 
	while (temp_pos > 0 ) 
	{
		temp_elem = temp_elem->next; 
		temp_pos--; 		
	}

	return temp_elem->data; 

}




