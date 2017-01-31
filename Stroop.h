/*
 Stroop.h
 Created by: Minh D. Nguyen
 Header file for Stroop Test Game
*/

#include<iostream>
using namespace std;
#include "helper.h"

const string NAMES[] = {"BLACK", "RED", "GREEN", "YELLOW", "BLUE",
			"MAGENTA", "CYAN"};

struct Game{
  double time;
  bool fail;
  int difficulty;
  bool casual;
  bool custom;
};

struct Color {
  string word;
  int color;
};

void play_game();
int print_color(int num, string name, int score, int names, Game game);
char wait(double time, int num);
void print_score(int score);
void fail();
void display(int i);
void instructions();
Game menu(int i, int j, Color easy_colors[], Color medium_colors[],
	  Color hard_colors[]);
Game set_difficulty(Game game, int j, Color easy_colors[], 
		    Color medium_colors[], Color hard_colors[]);
