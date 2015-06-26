
/**
 * @file card.h
 * Definition of the card class for the deck class
 *
 * @author Com L. 
 * @date Summer 2015
 */
#ifndef _CARD_H_
#define _CARD_H_

#include <ostream>


enum COLOR { wild, red, green, blue, yellow}; 
/**
 * Represents a card in a deck 
 */
class card
{
	public:
		int number; // 0-9 numbers, +2, skip, reverse, all color, +4 (all color) 
		COLOR color; // 5 colors: red, green, blue, yellow, and no color 

		/**
		 * Equality operator.
		 * @param other Other card to check equality with. (can be put as next card)
		 */
		bool operator==(card const & other) const;

		/**
		 * Inequality operator.
		 * @param other Other card to check inequality with.
		 */
		bool operator!=(card const & other) const;

		
		card(); 

		card(int num, COLOR col); 
}; 

/**
 * Stream operator that allows a card to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param temp_card to write to the stream.
 */
std::ostream & operator<<(std::ostream & out, card const & temp_card);


#endif // _CARD_H_

	
