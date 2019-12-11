//Name= Elham Hojati
//Lab501 or Lab503

#ifndef  PROJECT2
#define PROJECT2

#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;
typedef vector<string> row;
typedef vector<row> position;
typedef string square;
typedef char color;


struct mov {
	square src;
	square dst;
	// compare for order.     
	bool operator <(const mov& mv) const
	{

		return (src < mv.src) || ((!(mv.src < src)) && (dst < mv.dst));
	}
};


//_________________________________________________________________________
// Function declaration
position readPosition(string s);

//_________________________________________________________________________

set<mov> legalMoves(position p, color c);
//bool occupied(int i, int j, position  p, color  c);
//set<mov> legalMoves(int r, int f, position p);

//set<mov>	legalMovesBishop(int r, int f, position p);
//set<mov>	legalMovesKnight(int r, int f, position p);
//set<mov>	legalMovesRook(int r, int f, position p);
//set<mov>	legalMovesQueen(int r, int f, position p);
//set<mov>	legalMovesKing(int r, int f, position p);
//set<mov>	legalMovesPawn(int r, int f, position p);

#endif

#pragma once
