/*Alexandra Macedo 
Februrary 20, 2015

This program simulates a Monte Carlo roulette. It randomly
generates a number between 0 and 36, assigns the correct color,
and either causes the player win 1 peso, lose 1 peso, break even,
or enter a different status of play (i.e. NORMAL, PRISON1, PRISON2).
The total money the player wins or loses is accumulated to calculate
the amount of money that they win or lose per game, on average.
On average, every game a player loses .0005 pesos (.05 cents).*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*Colors of roulette and status of the turn.*/
enum color_t { RED, BLACK, GREEN };
enum status_t { NORMAL, PRISON1, PRISON2 };

/*Number of times the game will run*/
const int RUNS = 15000;

/*This functions passes the number from the roulette board
and assigns a 0 to green, an even number to black, and an
odd number to red.*/
color_t getColor(int r){
	if (r == 0){
		return GREEN;
	}
	else if (r % 2 == 0){
		return BLACK;
	}
	else {
		return RED;
	}
}

/*This program simulates spinning the roulette. It generates
a random number between 0 and 36 and calls the previous function
to assign the value a color. Depending on the color, the player
will win money, lose money, break even, or enter another status of play.
At the end of each turn, the number, color, and fate of the
spin will be displayed.*/
int spinRoulette(status_t s){
	
	/*Money and bet are initialized*/
	int money = 0;
	int bet = 1;
	
	/*Number is randomized and color is assigned*/
	int n = rand() % 37;
	color_t color = getColor(n);

	/*The player first enters with NORMAL status, where red will
	earn the player one peso, black will cause them to lose on
	peso, and green will cause them to enter PRISON1*/
	if (s == NORMAL){
		if (color == RED){
			money += bet;
			cout << n << " Red. Win!" << endl;
		}
		else if (color == BLACK){
			money -= bet;
			cout << n << " Black. Lose!" << endl;
		}
		else if (color == GREEN){
			s = PRISON1;
			cout << "0 Green! Prison 1." << endl;			
		}
	}

	/*If the player is sent to PRISON1, a red will cause them
	to break even (no loss or gain), a black will cause them to
	lose 1 peso, and a green will cause them to enter PRISON2.*/
	while (s == PRISON1){
		if (s == PRISON1){
			/*Wheel is respun and color is assigned to the random number*/
			int n = rand() % 37;
			color_t color = getColor(n);

			if (color == RED){
				s = NORMAL;
				cout << n << " Red. Break Even!" << endl;
			}
			else if (color == BLACK){
				s = NORMAL;
				money -= bet;
				cout << n << " Black. Lose!" << endl;
			}
			else if (color == GREEN){
				s = PRISON2;
				cout << "0 Green! Prison 2." << endl;
			}
		}

		/*If the player is sent to PRISON2, a red will cause them 
		to go back to PRISON1, a black will cause them to lose 1
		peso, and a green will cause them to win 648 pesos.*/
		if (s == PRISON2){
			/*Wheel is respun and color is assigned to the random number*/
			int n = rand() % 37;
			color_t color = getColor(n);

			if (color == RED){
				s = PRISON1;
				cout << n << " Red. Back to Prison 1." << endl;
			}
			else if (color == BLACK){
				s = NORMAL;
				money -= bet;
				cout << n << " Black. Lose!" << endl;
			}
			else if (color == GREEN){
				s = NORMAL;
				money += 648 * bet;
				cout << "0 Green. JACKPOT!" << endl;
			}

		}
	}
	return money;
}

/*This program will simulate Monte Carlo Roulette. It will
call the function to spin the roulette for however many RUNS
are specified. It will also used the returned money gained or
lost from each spin of the roulette and accumulate it. It
will use this number to find the average money won/lost
per game.*/
int main(){
	
	/*This seeds the random number generator to be random with
	respect to time passed since 1970.*/
	 //srand( static_cast<int>( time(0) ) );

	 /*Initiaization of money*/
	int money = RUNS;
	for (int i = 1; i <= RUNS; i++){
		money += spinRoulette(NORMAL);
	}

	cout << "Money left: " << money << endl;
	double average= double(money - RUNS) / RUNS;
	cout << "Average win/loss: " << average << endl;

	return 0;
}