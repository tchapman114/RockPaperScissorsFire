// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>  //for files
#include <string>
#include <algorithm>
using namespace std;

//CONSTANT
const string OUT_FILE = "results.txt";
const string FILENAME = "prevResults.txt";	//infile
const int ROWS = 15;
const int COLS = 2;


//Function prototype
//void PrevResults(string prevResults);
//void Results(int wins, int losses, int totalGames);

//functions must be created befor Main()

//This will display the menu for users
// (TARA CHAPMAN) -> ShowUsage()
//When 'S' is entered in from the main selection
void ShowUsage() {		//a function to show the user how to use the program.
	cout << endl;
	cout << "To show the game menu press 'S'" << endl;
	cout << "To play the game press 'P'" << endl;
	cout << "To display current game results press 'R'" << endl;
	cout << "To check your player level(Newbie, Beginner, Expert, Champion)  press 'Z'" << endl;
	cout << "To veiw previous player's scores press 'X'" << endl;
	cout << "To quit press 'Q' " << endl;
	cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEALING WITH FILES(CHRISTOPHER/TARA)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//To show previous players and their winning/lossing scores
bool GetPreviousPlayers(string FILENAME, string names[ROWS], int scores[ROWS][COLS]) {	//returns true or false
	//opening file
	ifstream infile;
	infile.open(FILENAME);

	if (!infile)//if file does not open
	{
		cout << "Error with file name.." << endl;
		return false;
	}

	//NESTED LOOP (TARA)
	for (int i = 0; i < ROWS; i++)	//first loop assigned names to a single array, 1st collum
	{// (15 total loopings)
		infile >> names[i];
		for (int j = 0; j < COLS; j++)	//second loop finds scores
		{
			infile >> scores[i][j];	//parallel array
		}
	}
	return true;
	//closing file.. no longer need data from file. they are stored in arrays
	infile.close();
}

//(CHRISOPHER)
//Printing to file.......
void Results(const int& iUserWin, const int& iUserLose, const int& iUserTies, const int& iTotalGames)
{
	//File stream variable
	ofstream outFile;

	//Opens output file
	outFile.open(OUT_FILE);

	//Outputs results to file
	outFile << "Game Results" << endl;
	outFile << "---------------------------------" << endl;
	outFile << "The total number of wins is: " << iUserWin << endl;
	outFile << "The total number of losses is: " << iUserLose << endl;
	outFile << "The total number of ties is: " << iUserTies << endl;
	outFile << "Total games played is: " << iTotalGames << endl;

	//Closes output file
	outFile.close();
}

//DISPLAYING prevous players and scores from file
// when user enter 'X'
//TARA
void DisplayPrevPlayers(string names[ROWS], int scores[ROWS][COLS]) {
	//Heading for collums
	// '\t' is tab.......
	cout << left << setw(10) << "Players:\tWins\tLoss" << endl << endl;
	//ouput data from file, which is stored in arrays
	for (int i = 0; i < ROWS; i++)
	{
		cout << setw(10) << setfill(' ') << left << names[i] << "\t"; //printing out names (TAB)
		for (int j = 0; j < COLS; j++) {	//printing out 4 scores per name
			cout << scores[i][j] << "\t"; //spaced out by 1 tab
		}
		//printing out the last collum(which is average)
		cout << endl;	//goes to next line till all 10 bowlers are ouputed
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FINDING WINNER(TARA CHAPMAN/TIMOTHY CUTTS)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//when user enters 'P' from the main selection
void PlayGame(int& iUserWin, int& iUserLose, int& iUserTies, int& iTotalGames) {
	//declaring varibles
	char userSelection;
	static int winsTillFire = 0;
	static int fire = 0;
	//array randomSelection; timothy
	char randomSelection[3] = { 'R', 'P', 'S' };//..... timothy


	//testing purpose
	//char randomSelection = 'P';	//DELETE AFTER ARRAY IS CREATED... timothy

	//asking user for input to play game (TARA)
	cout << "Game on!" << endl;

	//Checks if use has any fire tokens
	if (fire > 0)
		cout << endl << "You have " << fire << " fire token(s) to use." << endl;

	cout << "Please enter your choice (R = ROCK, P = PAPER, S = SCISSORS, F = FIRE): ";

	cin >> userSelection;
	//USING AN ARRAY FOR RandomSelection...... Timothy
	srand((unsigned int)time(0)); //for random seed  Timothy
	int indexSelection;//variable for random index  Timothy	
	indexSelection = rand() % 3; //random selector  Timothy
	randomSelection[indexSelection]; //sets the random index to computers choice variable  Timothy


	//(TARA)
	//switch stament to determine winner of the round
	switch (userSelection)
	{
	case 'R':	//when user selects rock
	case 'r': //Including both cap and lower case input
		if (randomSelection[indexSelection] == 'P') {	//LOSE
			iUserLose++;
			iTotalGames++;
			cout << "Computer selected PAPER, you lose." << endl;
		}
		else if (randomSelection[indexSelection] == 'R')	//TIE
		{
			iUserWin = iUserWin;
			iTotalGames++;
			iUserTies++;
			cout << "Computer selected ROCK, it is a tie. Try again!" << endl;
		}
		else if (randomSelection[indexSelection] == 'S')	//WIN
		{
			iUserWin++;
			iTotalGames++;
			winsTillFire++;
			cout << "Computer selected SCISSORS, you win!" << endl;
			if ((winsTillFire % 3) == 0)
			{
				fire += 1;
				cout << "You earned 1 fire token." << endl;
			}
		}
		break;
	case 'P':	//user selects paper
	case 'p':
		if (randomSelection[indexSelection] == 'S') {
			iUserLose++;
			iTotalGames++;
			cout << "Computer selected SCISSORS, you lose." << endl;
		}
		else if (randomSelection[indexSelection] == 'P')
		{
			iUserWin = iUserWin;
			iTotalGames++;
			iUserTies++;
			cout << "Computer selected PAPER, it is a tie. Try again!" << endl;
		}
		else if (randomSelection[indexSelection] == 'R')
		{
			iUserWin++;
			iTotalGames++;
			winsTillFire++;
			cout << "Computer selected ROCK, you win!" << endl;
			if ((winsTillFire % 3) == 0)
			{
				fire += 1;
				cout << "You earned 1 fire token." << endl;
			}
		}
		break;
	case 'S':
	case 's':	//user selects scissors
		if (randomSelection[indexSelection] == 'R') {
			iUserLose++;
			iTotalGames++;
			cout << "Computer selected ROCK, you lose." << endl;
		}
		else if (randomSelection[indexSelection] == 'S')
		{
			iUserWin = iUserWin;
			iTotalGames++;
			iUserTies++;
			cout << "Computer selected SCISSORS, it is a tie. Try again!" << endl;
		}
		else if (randomSelection[indexSelection] == 'P')
		{
			iUserWin++;
			iTotalGames++;
			winsTillFire++;
			cout << "Computer selected PAPER, you win!" << endl;
			if ((winsTillFire % 3) == 0)
			{
				fire += 1;
				cout << "You earned 1 fire token." << endl;
			}
		}
		break;
	case 'F':
	case 'f':
		if (fire > 0)
		{
			iUserWin++;
			iTotalGames++;
			fire -= 1;
			cout << "You used fire. Automatic win!" << endl;
		}
		else
			cout << "You do not have any fire tokens." << endl;
		break;
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DISPLAYING RESULTS TO CONSOLE(TARA): This function display the number of wins, loss, and games
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//When user selects 'R'
void DisplayResults(const int iUserWin, const int& iUserLose, const int& iUserTies, const int& iTotalGames) {
	if (iUserWin >= 0) {
		cout << "The total number of wins: " << iUserWin << endl;
	}
	if (iUserLose >= 0) {
		cout << "The total number of losses: " << iUserLose << endl;
	}
	if (iUserTies >= 0) {
		cout << "The total number of ties: " << iUserTies << endl;
	}
	if (iUserLose >= 0 && iUserWin >= 0 && iUserTies >= 0) {	//total number of games:
		cout << "The total number of games played: " << iTotalGames;
	}
	if (iUserWin < 0 && iUserLose < 0 && iUserTies < 0) {	//no games played yet
		cout << "No game has been played yet. Please select 'P' from the main menu." << endl;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DISPLAYING PLAYER PLACEMENT(TARA): This function displays if player is nebie, beginner,expert,champion
// "0-5 Total Wins = Newbie 5-10 Total Wins = Beginner 20 Total Wins = Expert 40 total Wins = Champion" 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayerLevel(const int iUserWin) {
	if (iUserWin <= 5) {
		cout << "Player Level: Newbie" << endl;
		cout << "Keep practicing!" << endl;
	}
	else if (iUserWin <= 10) {
		cout << "Player Level: Beginner" << endl;
		cout << "Keep up the good work!" << endl;
	}
	else if (iUserWin <= 20) {
		cout << "Player Level: Expert" << endl;
		cout << "Wow, you're a pro!" << endl;
	}
	else if (iUserWin <= 50) {
		cout << "Player Level: Champion" << endl;
		cout << "CONGRATS, you are a rock, paper, scissors champion!" << endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN (TARA/CHRISOPHER/TIMOTHY)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{	//delaring varibles
	string MainSelection;
	int iUserWin = 0;	//initally setting score to 0
	int iUserLose = 0;
	int iUserTies = 0;
	int iTotalGames = 0;
	string names[ROWS]; //14 rows/elements
	int scores[ROWS][COLS] = { 0 };

	//displaying a header... (TARA CHAPMAN)
	cout << setw(80) << setfill('*') << "" << endl;
	cout << setw(55) << setfill('*') << right << "Lets play Rock, Paper, Scissors!" << left << setw(25) << setfill('*') << "" << endl;	//centering my text within 80 collumns
	cout << setw(48) << setfill('*') << right << "Watch out for FIRE!" << left << setw(33) << setfill('*') << "" << endl;
	cout << setw(80) << setfill('*') << "" << endl;	//setw() = sets a number of collumns, setfill()= allows you to fill in thoes blank collumns when needed

	//Display Game Rules (TARA CHAPMAN)
	cout << "Game Rules: " << endl;
	cout << "1. Once you select 'P' to play, you must type in a single character to play" << endl;
	cout << "2. Rock beats scissors." << endl;
	cout << "3. Paper beats rock." << endl;
	cout << "4. Scissors beats paper." << endl;
	cout << "5. If the computer selects fire, player automatically loses that round.\n" << endl;
	cout << "Player Levels:" << endl;
	cout << "Atleast  5 Wins = Newbie\nAtleast 10 Wins = Beginner\nAtleast 20 Wins = Expert\nAtleast 50 Wins = Champion" << endl;
	ShowUsage();

	//start of do..while single loop (TARA CHAPMAN)
	do
	{
		cout << "\nPlease enter selection: ";
		cin >> MainSelection;	//input
		transform(MainSelection.begin(), MainSelection.end(), MainSelection.begin(), toupper);	//transforming input into CAPS. this makes it easier to include both lower and cap in loop.

		if (MainSelection == "S") {
			ShowUsage();	//calling function
		}
		else if (MainSelection == "P") {
			PlayGame(iUserWin, iUserLose, iUserTies, iTotalGames);	//calling function to determine winner of round
			Results(iUserWin, iUserLose, iUserTies, iTotalGames); //printing to file
		}
		else if (MainSelection == "R") {
			DisplayResults(iUserWin, iUserLose, iUserTies, iTotalGames);	//printing to console
		}
		else if (MainSelection == "X") {
			GetPreviousPlayers(FILENAME, names, scores);
			DisplayPrevPlayers(names, scores);
		}
		else if (MainSelection == "Z") {
			PlayerLevel(iUserWin);
		}

	} while (MainSelection != "Q");	//Do until user quits

	cout << "Thanks for playing!";

}
///////////////////////////////////////////////////////////////////////////////////////
//COMMENTED OUT CODE
///////////////////////////////////////////////////////////////////////////////////////
//christopher
//string results = "results.txt";

//Sample Variables. Will be deleted.
//int wins = 4;
//int losses = 2;
//int games = wins + losses;

//PrevResults(OUT_FILE);
//cout << endl;
//Results(wins, losses, games);
//cout << endl << endl;
