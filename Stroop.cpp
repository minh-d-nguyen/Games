/* 
   The Stroop Test Game
   Developed by: Minh D. Nguyen, Duc M. Nguyen, Emily Colwell, and Jonathan Minoff
   at Tufts Polyhack 2015
*/

#include<iostream>
#include<thread>
#include<chrono>
#include<ctime>
using namespace std;
#include "helper.h"
#include "Stroop.h"

int main() {
    hide_cursor();
    play_game();
    return 0;
}

/*
 Function: play_game
 Paramenter: None
 Return: None
 Purpose: Created the environment for the game to be played
*/
void play_game()
{
    Color easy_colors[3];
    Color medium_colors[5];
    Color hard_colors[7];
    Game game = menu(0, 0, easy_colors, medium_colors, hard_colors);
    int score = 0;
    time_t timer;
    time_t start;
    time(&start);
    time(&timer);
    double seconds = difftime(timer, start);
    while(seconds < 10){
        int color = random_int(0, 2 * game.difficulty + 2);
        int chance = random_int(0,2);
        if (chance > 0) {
            int name = random_int(0,2 * game.difficulty + 2);
            if(game.difficulty == 0){
                score = print_color(easy_colors[color].color,
                                    easy_colors[name].word, score, easy_colors[name].color, game);
            } else if(game.difficulty == 1){
                score = print_color(medium_colors[color].color,
                                    medium_colors[name].word, score, medium_colors[name].color, game);
            } else if(game.difficulty == 2){
                score = print_color(hard_colors[color].color,
                                    hard_colors[name].word, score, hard_colors[name].color, game);
            }
        } else {
            if(game.difficulty == 0){
                score = print_color(easy_colors[color].color,
                                    easy_colors[color].word, score,
                                    easy_colors[color].color, game);
            } else if(game.difficulty == 1){
                score = print_color(medium_colors[color].color,
                                    medium_colors[color].word, score,
                                    medium_colors[color].color, game);
            } else if(game.difficulty == 2){
                score = print_color(hard_colors[color].color,
                                    hard_colors[color].word, score,
                                    hard_colors[color].color, game);
            }
        }
        time(&timer);
        seconds = difftime(timer, start);
    }
    print_score(score);
}

/*
 Function: print_score
 Paramenter: score
 Return: None
 Purpose: Print out the result of the player and (possibly) an offensive remark
*/
void print_score(int score){
	cout << "Score: " << score << endl;
	if (score >= 5) {
		cout << "Nice job!" << endl;
	}
	else if (score >= 0) {
		cout << "You are not so good with colors, are you?" <<endl;
	}
	else {
		cout << "Are you color-blind?" << endl;
	}
}

/*
 Function: print_color
 Paramenter: The color index (num), the name of the color (name), the current score (score), the true index of the
             color (names), and the Game module
 Return: The new score
 Purpose: Print out an individual color name in a random color, then get the user input and modify the score
 */
int print_color(int num, string name, int score, int names, Game game){
	int new_score = score;
	screen_clear();
	cout << "\033[1;"<< 30 + num <<"m"<< name <<"\033[0m" << endl;
	cout << "Score: " << score << endl;
	
    char input = wait(game.time, num);
	if (input != 'y' && input != 'n') {
		new_score--;
		if(game.fail)
			fail();
	}
	else if (input == 'y') {
		if (num == names) {
			new_score++;
		}
		else {
			new_score--;
			if(game.fail)
				fail();
		}
	}
	else if (input == 'n') {
		if (num != names) {
			new_score++;
		}
		else {
			new_score--;
			if(game.fail)
				fail();
		}
	}
	return new_score;
}

/*
 Function: wait
 Paramenter: The waiting time (time), and the color index (num)
 Return: The input of the player
 Purpose: Get the input from the player in waiting time
*/
char wait(double time, int num){
	clock_t start = clock();
	double seconds = 0;
	char input = ' ';
	for(int i = 0; i < 80; i++){
		cout << "\033[1;"<< 30 + num <<"m"<< "X" <<"\033[0m";
	}
	while((seconds < time) && (input != 'y') && (input != 'n')){
		cout << endl;
		input = getacharnow(0);
		seconds = (double) (((float)clock() - start) / CLOCKS_PER_SEC);
		place_char(' ', 2, 81 - 80 * (seconds / time));
	}
	return input;
}

/*
 Function: instructions
 Paramenter: None
 Return: None
 Purpose: Print out the instructions of the game
 */
void instructions(){
	screen_clear();
	cout << "\t\t\t\t~~~Instructions~~~" << endl << endl << endl;
	cout << "Press the y button if the color matches the word." << endl;
	cout << "Press the n button if the color does not match the word." <<endl;
	cout << "You have 60 seconds to acquire as many points as possible." << endl;
	cout << "If you choose correctly, you gain 1 point. If you choose" <<
	endl << "incorrectly or do not make a choice fast enough, " <<
	"you lose one point." << endl << endl;
	cout << "On easy difficulty, you have 5 seconds, and only 3 colors will appear." << endl;
	cout << "On medium, you get 3 seconds, and 5 colors will appear." << endl;
	cout << "On hard mode, you only have one second to deal with seven colors." << endl;
	cout << endl << "Press any key to continue" << endl;
	getachar();
	return;
}

/*
 Function: menu
 Paramenter: The game's possible info such as difficulty, number of colors, etc.
 Return: The game info that the player chose
 Purpose: Print out the menu and let the player choose the game's difficulty
 */
Game menu(int i, int j, Color easy_colors[], Color medium_colors[],
		Color hard_colors[]){
	cout << "message" << endl;
	Game game;
	int k = 0;
	screen_clear();
	cout << "\t\t\tWelcome to the Stroop test game" << endl;
	cout << "\t\t\tUse up and down to select" << endl << endl << endl;
	cout << "\t\t\t\t";
	
	display(i);
	
	cout << "\t\t";
	cout << "Left and Right to change difficulty: ";
	if((j % 3) == 0)
		cout << "Easy";
	else if((j % 3)== 1)
		cout << "Medium";
	else if((j % 3) == 2)
		cout << "Hard";
	char input = getachar();
	switch(input){
		case KEY_UP:	i = 1 - i; return menu(i, j, easy_colors,
				medium_colors, hard_colors); break;
		case KEY_DOWN:	i = 1 - i; return menu(i, j, easy_colors,
				medium_colors, hard_colors); break;
		case KEY_RIGHT:	j++; return menu(i, j, easy_colors,
				medium_colors, hard_colors); break;
		case KEY_LEFT:	j+=2; return menu(i, j, easy_colors,
				medium_colors, hard_colors); break;
		default:	k = i + 1;
		switch(k){
			case 1:		game = set_difficulty(game, j, easy_colors, medium_colors, hard_colors); break;
			case 2:		instructions(); return menu(i, j, easy_colors,
				medium_colors, hard_colors); break;
		}
	}
	return game;
}

/*
 Function: set_difficulty
 Paramenter: The game module and the game's info
 Return: The game module with its chosen info
 Purpose: Set the difficulty level in the game module
 */
Game set_difficulty(Game game, int j, Color easy_colors[],
		    Color medium_colors[], Color hard_colors[]){
	cout << "potato " << j << endl;
	bool go = true;
	int i = 0, k = 0;
	switch(j % 3){
		case 0: game.time = 3; game.fail = false;
			for(i = 0; i < 3; i++){
				do{
					go = true;
					k = random_int(0, 6);
					for(int q = 0; q < i; q++){
						if(easy_colors[q].color == k)
							go = false;
					}
				} while (!go);
				easy_colors[i].word = NAMES[k];
				easy_colors[i].color = k;
			} break;
		case 1: game.time = 2; game.fail = false;
			for(i = 0; i < 5; i++){
				do{
					go = true;
					k = random_int(0, 6);
					for(int q = 0; q < i; q++){
						if(medium_colors[q].color == k)
							go = false;
					}
				} while (!go);
				medium_colors[i].word = NAMES[k];
				medium_colors[i].color = k;
			} break;
		case 2: game.time = 1; game.fail = true;
			for(i = 0; i < 7; i++){
				hard_colors[i].word = NAMES[i];
				hard_colors[i].color = i;
			} break;
	}
	game.difficulty = (j % 3);
	return game;
}

/*
 Function: display
 Paramenter: The line number (i)
 Return: None
 Purpose: Print out the menu of the game
*/
void display(int i){
	if(i == 0)
		cout << "--";
	else
		cout << "  ";
	cout << "Play";
	if(i == 0)
		cout << "--";
	cout << endl;
	cout << "\t\t\t";
	if(i == 1)
		cout << "    --";
	else
		cout << "      ";
	cout << "Instructions";
	if(i == 1)
		cout << "--";
	cout << endl;
	cout << endl << endl << endl << endl;
}

/*
 Function: fail
 Paramenter: None
 Return: None
 Purpose: Print a big FAIL to the screen whenever the player screws up
 */
void fail(){
	screen_clear();
	cout << "\033[1;"<< 31 <<"m";
	clock_t start = clock();
	double seconds = 0;
	cout << 
"FFFFFFFFFFFFF           A               IIIIIIIIIIIIIIII   L" << endl; cout <<
"F                      A A                      I          L" << endl; cout <<
"F                     A   A                     I          L" << endl; cout <<
"F                    A     A                    I          L" << endl; cout <<
"F                   A       A                   I          L" << endl; cout <<
"FFFFFFFFFFFFF      A         A                  I          L" << endl; cout <<
"F                 AAAAAAAAAAAAA                 I          L" << endl; cout <<
"F                A             A                I          L" << endl; cout <<
"F               A               A               I          L" << endl; cout <<
"F              A                 A              I          L" << endl; cout <<
"F             A                   A             I          L" << endl; cout <<
"F            A                     A    IIIIIIIIIIIIIIII   LLLLLLLLLLLLLLL"
	<<"\033[0m" << endl;
	while(seconds < .1){
		seconds = (double) (((float)clock() - start) / CLOCKS_PER_SEC);
	}
}
