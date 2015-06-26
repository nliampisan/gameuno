/**
 * @file card.cpp
 *
* @author Com L. 
 * @date Summer 2015
 */
#include "card.h"

card::card() : number(0), color(wild) 
{

}

card::card(int num, COLOR col) : number(num), color(col) 
{

}

bool card::operator==(card const & other) const 
{
	return number == other.number || color == other.color || color == wild || other.color == wild; 

}


bool card::operator!=(card const & other) const 
{
	return !(*this == other) ;
}


std::ostream & operator<<(std::ostream & out, card const & temp_card)
{
	out << "Number:"; 
	// << (int) temp_card.number << " Color: "; 
	switch (temp_card.number)
	{
		case 10: out<< "DRAW-2" ; break; 
		case 11: out<< "SKIP"; break; 
		case 12: out<< "REVERSE"; break; 
		case 13: out<< "WILD" ; break; 
		case 14: out<< "DRAW-4-WILD" ; break; 
		default: out << (int) temp_card.number; break; 
	}

	out << "   Color:" ; 
	switch (temp_card.color) 
	{
		case wild : out << "wild";  break; 
		case red : out << "red";  break;
		case green : out << "green";  break;
		case blue : out << "blue";  break;
		case yellow : out << "yellow";  break;
		default: out << "N/A"; break; 
	}
	return out;
}


