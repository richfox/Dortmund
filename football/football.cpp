// football.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "football.h"


void Formation::set_defence_player(int player)
{
	_defencer = player;
}

void Formation::set_midfield_player(int player)
{
	_midfielder = player;
}

void Formation::set_forward_player(int player)
{
	_forward = player;
}

int Formation::get_defence_player()
{
	return _defencer;
}

int Formation::get_midfield_player()
{
	return _midfielder;
}

int Formation::get_forward_player()
{
	return _forward;
}