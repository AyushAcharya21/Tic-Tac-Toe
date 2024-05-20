/*Name: Ayush Acharya
 *Program Name: Tic Tac Toe game
 *Date: June 10, 2023
 *Description: Allows the user to play 2 players tic tac toe game, save games, print out all saved games, sort and print out saved games and clear all saved games.
*/


#include <fstream>// Including the library for file input/output
#include <iostream> // Including the library for standard input/output
#include <sstream>  // Including the library for string stream operations
#include <vector>
using namespace std; // Using the standard namespace

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; //Array representing the tic tac board
vector <int> SSGames;//Vector that stores the sorted saved games



/*checkBoardFull: Checks if the board is full
 *No params
 *Return Type: bool
 */
bool checkBoardFull() {
  //Using a for loop to go through board array
  for (int i = 0; i < 9; i++) {
    //If board is empty, that means the board is full. Hence, returning false.
    if (board[i] == ' ') {
      return false;
    }
  }
  return true;//Else returning true, indicating the box is full
}




/*turnsCounter: Counts the number of turns it took for either of the players to win
 *Params: int turns (variable to store the num of turns), char currentPlayer (identifies the winner player)
 *Return Type: int
 */
int turnsCounter(char currentPlayer) {
  int turns = 0; //Initializing turns as 0
  //Using a for loop to go through the board
  for (int i = 0; i < 9; i++) {
    //If board contains the mark of the winner player, it counts as a try
    if (board[i] == currentPlayer) {
      turns++;//Incrementing turns variable
    }
  }
  return turns;//Returning turns
}




/*printBoard: Prints out the tic tac toe board
 *No params
 *Return Type: void
 */
void printBoard() {
  cout << "Player 1 (X)  -  Player 2 (O)\n\n\n";

  cout << "     |     |     \n";
  cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";

  cout << "_____|_____|_____\n";
  cout << "     |     |     \n";

  cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";

  cout << "_____|_____|_____\n";
  cout << "     |     |     \n";

  cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";

  cout << "     |     |     \n\n";
}



/*note: Note for user in certain conditions
 *No params
 *Return Type: void
 */
void note() {
  cout << "Press enter to continue...";
  cin.ignore();//Ignoring the previous input
  cin.get();//Geting a new input
  cout << "\033[2J\033[1;1H";//Print command that clears the screen
}



/*printDefBoard: Prints out the default tic tac toe board that guides the user how to play or place a move
 *No params
 *Return Type: void
 */
void printDefBoard() {
  cout << "     |     |     \n";
  cout << "  1  |  2  |  3  \n";
  cout << "_____|_____|_____\n";
  cout << "     |     |     \n";
  cout << "  4  |  5  |  6  \n";
  cout << "_____|_____|_____\n";
  cout << "     |     |     \n";
  cout << "  7  |  8  |  9  \n";
  cout << "     |     |     \n";
}



/*printBoardToFile: Allows to save/print the tic tac toe board into a txt file
 *Param: Instance of an ofstream file called file
 *Return Type: void
 */
void printBoardToFile(ofstream &file) {
  file << "     |     |     \n";
  file << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2]
       << "\n";
  file << "_____|_____|_____\n";
  file << "     |     |     \n";
  file << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5]
       << "\n";
  file << "_____|_____|_____\n";
  file << "     |     |     \n";
  file << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8]
       << "\n";
  file << "     |     |     \n";
}



/*checkWin: Checks for win
 *No params
 *Return Type: bool
 */
bool checkWin() {

  //These if statements check for horizontal win, vertical win, and diagonal win in tic tac toe
  if ((board[0] == board[1] && board[1] == board[2] && board[0] != ' ') ||
      (board[3] == board[4] && board[4] == board[5] && board[3] != ' ') ||
      (board[6] == board[7] && board[7] == board[8] && board[6] != ' ') ||

      (board[0] == board[3] && board[3] == board[6] && board[0] != ' ') ||
      (board[1] == board[4] && board[4] == board[7] && board[1] != ' ') ||
      (board[2] == board[5] && board[5] == board[8] && board[2] != ' ') ||

      (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') ||
      (board[2] == board[4] && board[4] == board[6]) && board[2] != ' ') {
    return true;
  }
  return false;
}



/*saveGame: Prints out the default tic tac toe board that guides the user how to play
 *Params: int turns (number of turns it took to win), char currentPlayer (identifies the winning player)
 *Return Type: void
 */
void saveGame(char currentPlayer) {
  ofstream file("savedGames.txt", ios::out | ios::app); //Opening the file named savedGames.txt in append mode using ofStream library (input)
  SSGames.push_back(turnsCounter(currentPlayer));
  
  printBoardToFile(file);//Using printBoardToFile method to print out the tic tac toe board in the file
  file << "No. of turns took to win: " << turnsCounter(currentPlayer) << "\n";//Saving the number of turns into the file
  file << "Winner: Player " << currentPlayer << "\n";//Saving the winner player into the file
  file << "-----------------\n\n\n";
  file.close();//Closing the file; no longer required
  cout << "\033[2J\033[1;1H";//Clearing the screen
  cout << "***Game saved sucessfully!***\n\n";
  note();//Using the note method
}



/*clearSavedGames: Allows to clear all the saved games from a file
 *No params
 *Return Type: void
 */
void clearSavedGames() {
  ofstream file("savedGames.txt", ios::out | ios::trunc); // Defining an ofStream file object called file to access "savedGames.txt". Using ios::out flag to open the file and ios::truc flag to truncate/clear the file.
  file.close();//Closing the file; no longer required
  cout << "\033[2J\033[1;1H";//Clearing the screen
  cout << "***All saved games cleared!***\n\n\n";
  note();
}



/*sortSavedGames: Uses bubble sort algorithm to sort the SSGames vector. Contrary to saveGame (which acts like ROM), this method acts like the RAM and prints out info about games saved from the start of the program to the end only
 *No params
 *Return Type: void
 */
void sortSavedGames() {

  //Checking if the vector is empty. If yes, that means the user hasn't played or saved a game after they ran the program
  if (SSGames.empty() == true)
  {
    cout << "\033[2J\033[1;1H";//Clearing the screen
    cout <<"*****You haven't played or saved a game after you ran the program*****\n\n";
    note();
    return;
  }  
  vector <int> tempVector = SSGames; //Creating a temporary vector to save unsorted SSGames

  //Bubble sort algorithm:
  for (int i = 0; i<SSGames.size()-1; i++){
    for (int j = 0; j<SSGames.size()-i-1; j++){
      if (SSGames[j] > SSGames[j+1]){
        int temp = SSGames[j];
        SSGames[j] = SSGames[j+1];
        SSGames[j+1] = temp;
      }
    }
  }
  cout << "\033[2J\033[1;1H";//Clearing the screen
  cout << "\n";

  //External for loop is used to keep track of the value stored in each element of the SSGames vector i.e number of turns
  for (int k = 0; k<SSGames.size(); k++){
    //Internal for loop is used to keep track of the game number
    for (int l = 0; l<SSGames.size(); l++){
      //If the value of the unsorted vector and sorted vector match, that means the sorted vector's value at a certain index was once stored in the index of the unsorted vector
      //This is used to find the corresponding game number for each number of turns (from least to greatest)
      if (SSGames[k] == tempVector[l]){
        cout << "Game " << l+1 << ": " << SSGames[k] << " turns\n"; 
      }
    }
  }
  cout << "\n";
  note();//Using the note method
  
}



/*printSavedGames: Prints out all the saved games from a text file
 *No params
 *Return Type: void
 */
void printSavedGames() {
  ifstream file("savedGames.txt");//Creating an ifstream file object called file that accesses savedGames.txt

  stringstream buffer;//Creating a stringstream object called buffer
  buffer << file.rdbuf();//Reading the entire file into a string stream
  file.close();//Closing the file

  //Checking if the file is empty
  if (buffer.str().empty() == true) {
    cout << "\033[2J\033[1;1H";//Clearing the screen
    cout << "***No saved games found!***\n\n\n";
    note();//Using the note method
    return;
  }
  cout << "\033[2J\033[1;1H";//Clearing the screen
  cout << "\nAll Saved Games: \n\n";
  cout << buffer.str(); //Printing the contents of the string stream (saved games)
  note();//Using the note method
}



/*playRecursive: Recursive method to play the game. Recursively switches between players till either of the players win or it's a draw
 *Parmams: char currentPlayer (the current player playing), int turns (the number of turns)
 *Return Type: void
 */
void playRecursive(char currentPlayer) {

  //Asking the current player to place their move and storing their move
  cout << "Player " << currentPlayer << ", Enter Place: ";
  int playerMove;
  cin >> playerMove;

  //If the placed move isn't already placed, places the move
  if (board[playerMove - 1] == ' ') {
    board[playerMove - 1] = currentPlayer;//The placed element on the board is set to 'X' or 'O'

    //Clearing the screen and printing the board
    cout << "\033[2J\033[1;1H";
    printDefBoard();
    cout << "\n";
    printBoard();

    //Right after a player places their move, checking for win using the checkWin method
    if (checkWin() == true) {

      //If the player has won, clears the screen, prints out the boards along with the declaration of the winner
      cout << "\033[2J\033[1;1H";
      printDefBoard();
      cout << "\n";
      printBoard();
      cout << "******************\n";
      cout << "* Player " << currentPlayer << " Wins! *\n";
      cout << "******************\n\n\n";

      //Asking the user if they want to save this game they just won and storing it in saveChoice
      cout << "Enter 1 if you want to save this game or 0 to continue: ";
      int saveChoice;
      cin >> saveChoice;

      //If they chose to save the game,
      if (saveChoice == 1) {
        saveGame(currentPlayer);//Using saveGame method to save the game into a text file
      } else {
        //Clearing the screen and using the note method
        cout << "\033[2J\033[1;1H";
        note();
      }

      //If checkWin happened to be false, there's a chance that the game was a draw. So, using the checkBoardFull method to see if the board is full (which represents a draw)
    } else if (checkBoardFull() == true) {
      cout << "It's a draw!\n";

    //If it's not a draw, that means the user hasn't won nor it's a draw. The board is not full and the players can play.
    } else {
      //Hence switching players
      if (currentPlayer == 'X') {
        currentPlayer = 'O';
      } else {
        currentPlayer = 'X';
      }
      playRecursive(currentPlayer);//Calling the playRecursive method recursively, altering players' turn
    }
  } else {
    //If the placed move wasn't empty, that means that place must have been already placed
    cout << "\033[2J\033[1;1H";
    cout << "***Place already taken!***\n\n\n";
    note();
    printDefBoard();
    cout << "\n";
    printBoard();
    playRecursive(currentPlayer);//Recursively calling the playRecursive method till the user inputs a place that hasn't been already placed
  }
}



/*play: Sets up the game by clearing the screen, printing board, and using the playRecursive method
 *No params
 *Return Type: void
 */
void play() {
  //Clearing the screen and printing boards
  cout << "\033[2J\033[1;1H";
  printDefBoard();
  cout << "\n";
  printBoard();

  char currentPlayer = 'X';//Initializing the current player to be 'X'

  playRecursive(currentPlayer);//Calling the playRecursive method to commence the game
}



/*Main method: Combines all the methods and commences the game
 *No params
 *Return Type: int
 */
int main() {
  cout << "\033[2J\033[1;1H";
  cout << "****** Tic Tac Toe ******\n\n";
  
  //The game runs infinitly until the user chooses to exit the game
  while (true) {
    //Asking the user for a choice from the following options and saving it in choice
    cout << "*********************************\n";
    cout << "* 1. Play                       *\n";
    cout << "* 2. Print All Saved Games      *\n";
    cout << "* 3. Sort And Print Saved Games *\n";
    cout << "* 4. Clear All Saved Games      *\n";
    cout << "* 5. Exit                       *\n";
    cout << "*********************************\n";
    cout << "\n\nEnter your choice: ";
    int choice;
    cin >> choice;

    //Using a switch case statement to handle all possibilties of choice
    switch (choice) {
    case 1://Plays the game using play method
      for (int i = 0; i < 9; i++) {
        board[i] = ' ';
      }
      play();
      break;
    case 2://Printing all saved games using printSavedGames method
      printSavedGames();
      break;
    case 3://Sorting the games played after the user ran the program using sortSavedGames method
      sortSavedGames();
      break;
    case 4://Clearing all saved game using clearSavedGames
      clearSavedGames();
      break;
    case 5://Stoping the program with a return statement
      cout << "\033[2J\033[1;1H";
      cout << "Exiting the program...";
      return 0;
    default://If the user inputs anything else, outputting "Invalid choice" and using the note method before the user is asked again to pick one of the choices above
      cout << "\033[2J\033[1;1H";
      cout << "***Invalid choice!***\n\n\n";
      note();
      break;
    }
  }
}
