// ----------------------------------------------------------------------------------------------------------------------
//  Author   : Jake Lancaster
//  File     : CMCheckers.cpp
//  Created  : 11/29/2018
//  Detail   : Cylindrical Mule Checkers.
//           : Cylindrical Mule Checkers (CMCheckers). CMCheckers is a game similar to Checkers.
// ----------------------------------------------------------------------------------------------------------------------


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


//--- Constants -- //
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72;
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;
const int EMPTY = 0;
const int MAX_BOARD_PROMPTS = 3;


void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);//done works
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);//done almost works needs formatting
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);// done needs testing
bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex);//not yet done
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]); //done not tested
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);//done not tested
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc); // done not tested
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard); //done not tested needs formatting
bool IsWhitePiece(int squareToCheck);
bool IsRedPiece(int squareToCheck);
bool IsPieceValid(int squareToCheck, int player);
int PromptForBoardDiamention();
int PromptMoveFrom(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int potentialJumps);
int CalculateDistance(int numRowsInBoard, int fromSquareNum, int toSquareNum);
int PromptMoveTo(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, string promptMessage);
void PromptAndExit();



int main()
{
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	int xIndicesMove[MAX_PIECES];
	int yIndicesMove[MAX_PIECES];
	// One array will hold the x index the other the y index of the location on the board of a checker.The checkers described in these two lists will be the checkers that can be moved.Checkers that can be moved include : a Soldier or Mule that can move one square diagonally forward, and a King that can be moved one square diagonally forward or one square diagonally backward.
	int xIndicesJump[MAX_PIECES];
	int           yIndicesJump[MAX_PIECES];
	int player = WHITEPLAYER;
	int potentialJumps;
	int potentialmoves;
	int fromSquareNum;
	bool keepMoving;
	bool jumped;
	int toSquareNum;
	bool legalMove;
	//One array will hold the x index the other the y index of the location on the board of a checker.The checkers described in these two lists will be the checkers that can jump one of the opponent’s checkers.

	int numRowsInBoard = PromptForBoardDiamention();

	// Initialize board to empty.
	for (int y = 0; y < numRowsInBoard; y++)
	{
		for (int x = 0; x < numRowsInBoard; x++)
		{
			myCMCheckersBoard[y][x] = EMPTY;
		}
	}
	InitializeBoard(myCMCheckersBoard, numRowsInBoard);




	while (true)
	{
		DisplayBoard(myCMCheckersBoard, numRowsInBoard);
		potentialJumps = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);
		potentialmoves = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove);

		if (potentialJumps == 0 && potentialmoves == 0)
		{
			if (player == WHITEPLAYER)
			{
				cout << "White is unable to move." << endl;
				cout << "GAME OVER, Red has won." << endl;
				PromptAndExit();
			}
			else
			{
				cout << "Red is unable to move" << endl;
				cout << "GAME OVER, White has won" << endl;
				PromptAndExit();
			}
		}
		else
		{
			if (player == WHITEPLAYER)
			{
				cout << "White takes a turn." << endl;
			}
			else
			{
				cout << "Red takes a turn." << endl;
			}
		}

		fromSquareNum = PromptMoveFrom(myCMCheckersBoard, numRowsInBoard, player, potentialJumps);

		keepMoving = true;
		string promptMoveTo = "Enter the square number of the square you want to move your checker to";
		while (keepMoving)
		{
			jumped = false;

			toSquareNum = PromptMoveTo(myCMCheckersBoard, numRowsInBoard, player, fromSquareNum, promptMoveTo);
			legalMove = MakeMove(myCMCheckersBoard, numRowsInBoard, player, fromSquareNum, toSquareNum, jumped);

			if (legalMove)
			{
				if (jumped && IsJump(myCMCheckersBoard, numRowsInBoard, player, toSquareNum % numRowsInBoard, toSquareNum / numRowsInBoard))
				{
					promptMoveTo = "You can jump again, Please enter the next square you wish to move your checker to";
					fromSquareNum = toSquareNum;
					DisplayBoard(myCMCheckersBoard, numRowsInBoard);
				}
				else
				{
					keepMoving = false;
				}
			}
			else
			{
				cout << "ERROR: Moving to that square is not legal, Try again." << endl;
			}
		}

		if (CheckWin(myCMCheckersBoard, numRowsInBoard) == true)
		{
			PromptAndExit();
		}
		if (player == WHITEPLAYER)
		{
			player = REDPLAYER;
		}
		else
		{
			player = WHITEPLAYER;
		}
	}
}

/// <summary>Prompts user then terminates the program.</summary>
void PromptAndExit() {
	string junk;
	cout << "Enter any character to terminate the game then press the enter key" << endl;
	cin >> junk;
	exit(EXIT_FAILURE);
}

/// <summary>Read an integer from cin and verify it is a valid board diamention.</summary>
/// <returns>Integer board diamention.</returns> 
int PromptForBoardDiamention() {
	int numRowsInBoard;
	int attemptsLeft = MAX_BOARD_PROMPTS;

	while (attemptsLeft > 0)
	{
		cout << "Enter the number of squares along each edge of the board" << endl;
		cin >> numRowsInBoard;
		if (cin.fail())
		{
			cout << "ERROR: Board size is not an integer." << endl;
			cin.clear();
			cin.ignore();
		}
		else if (numRowsInBoard % 2 != 0)
		{
			cout << "ERROR: Board size odd." << endl;
		}
		else if (numRowsInBoard > MAX_ARRAY_SIZE)
		{
			cout << "ERROR: Board size too large." << endl;
		}
		else if (numRowsInBoard < MIN_ARRAY_SIZE)
		{
			cout << "ERROR: Board size too small." << endl;
		}
		else
		{
			return numRowsInBoard;
		}
		cout << MIN_ARRAY_SIZE << " <= number of squares <= " << MAX_ARRAY_SIZE << endl;
		attemptsLeft--;
	}

	cout << "ERROR: Too many errors entering the size of the board." << endl;
	PromptAndExit();
}

/// <summary>Prompt user for piece 'From' location.</summary>
/// <param name="CMCheckersBoard">Cheackerboard.</param>  
/// <param name="numRowsInBoard">Number or rows.</param>  
/// <param name="player">Players who is moving.</param>  
/// <param name="potentialJumps">Number of potential jumps.</param>  
/// <returns>Move From location</returns> 
int PromptMoveFrom(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int potentialJumps)
{
	int fromSquareNum;
	int xLoc;
	int yLoc;

	while (true)
	{
		cout << "Enter the square number of the checker you want to move" << endl;
		cin >> fromSquareNum;
		xLoc = fromSquareNum % numRowsInBoard;
		yLoc = fromSquareNum / numRowsInBoard;
		if (cin.fail())
		{
			cout << "ERROR: You did not enter an integer" << endl;
			cout << "Try again" << endl;
			cin.clear();
			cin.ignore();
		}
		else if (xLoc < 0 || xLoc >= numRowsInBoard || yLoc < 0 || yLoc >= numRowsInBoard)
		{
			cout << "ERROR: That square is not on the board." << endl;
			cout << "Try again" << endl;
		}
		else if (CMCheckersBoard[yLoc][xLoc] == EMPTY)
		{
			cout << "ERROR: That square is empty." << endl;
			cout << "Try again" << endl;
		}
		else if (!IsPieceValid(CMCheckersBoard[yLoc][xLoc], player))
		{
			cout << "ERROR: That square contains an opponent's checker." << endl;
			cout << "Try again" << endl;
		}
		else if (potentialJumps > 0 && IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == false)
		{
			cout << "ERROR: You can jump with another checker, you may not move your chosen checker." << endl;
			cout << "You can jump using checkers on the following squares: ";
			int counter = 0;
			for (int j = 0; j < numRowsInBoard; j++)
				for (int k = 0; k < numRowsInBoard; k++)
				{
					{
						if (IsJump(CMCheckersBoard, numRowsInBoard, player, k, j))
						{
							cout << counter << " ";
						}
						counter++;
					}
				}
			cout << endl << "Try again" << endl;
		}
		else if (IsJump(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == false && IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == false)
		{
			cout << "ERROR: There is no legal move for this checker." << endl;
			cout << "Try again" << endl;
		}
		else
		{
			return fromSquareNum;
		}
	}

}

/// <summary>Calculates distance between to locations.</summary>
/// <param name="numRowsInBoard">Number or rows.</param>  
/// <param name="fromSquareNum">From square.</param>  
/// <param name="toSquareNum">To square</param>  
/// <returns>Distance moved.</returns> 
int CalculateDistance(int numRowsInBoard, int fromSquareNum, int toSquareNum) {
	int xFLoc = fromSquareNum % numRowsInBoard;
	int fromSquareY = fromSquareNum / numRowsInBoard;
	int toSquareX = toSquareNum % numRowsInBoard;
	int toSquareY = toSquareNum / numRowsInBoard;
	int xDistance;
	int yDistance;
	//find the xDistance
	xDistance = abs(xFLoc - toSquareX);

	//special cases going around the side of the board
	if (xDistance == numRowsInBoard - 1)
	{
		xDistance = 1;
	}
	else if (xDistance == numRowsInBoard - 2)
	{
		xDistance = 2;
	}

	//find the yDistance
	yDistance = abs(fromSquareY - toSquareY);
	if (!((xDistance == 2 && yDistance == 2) || (xDistance == 1 && yDistance == 1)))
	{
		return -1;
	}

	if (xDistance == 1 && yDistance == 1) return 1;
	if (xDistance == 2 && yDistance == 2) return 2;
	return -1;
}

/// <summary>Prompt user for piece 'To' location.</summary>
/// <param name="CMCheckersBoard">Cheackerboard.</param>  
/// <param name="numRowsInBoard">Number or rows.</param>  
/// <param name="player">Players who is moving.</param>  
/// <param name="fromSquareNum">From square.</param> 
/// <param name="promptMessage">Inital user Prompt.</param> 
/// <returns>Move To location.</returns> 
int PromptMoveTo(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, string promptMessage)
{
	int toSquareNum;
	int toXLoc;
	int toYLoc;
	int fromXLoc = fromSquareNum % numRowsInBoard;
	int fromYLoc = fromSquareNum / numRowsInBoard;
	cout << promptMessage << endl;
	while (true)
	{
		cin >> toSquareNum;
		toXLoc = toSquareNum % numRowsInBoard;
		toYLoc = toSquareNum / numRowsInBoard;
		if (cin.fail())
		{
			cout << "ERROR: You did not enter an integer" << endl;
			cout << "Try again" << endl;
			cin.clear();
			cin.ignore();
		}
		else if (toXLoc < 0 || toXLoc >= numRowsInBoard || toYLoc < 0 || toYLoc >= numRowsInBoard)
		{
			cout << "ERROR: It is not possible to move to a square that is not on the board." << endl;
			cout << "Try again" << endl;
		}

		else if (CMCheckersBoard[toYLoc][toXLoc] != EMPTY)
		{
			cout << "ERROR: It is not possible to move to a square that is already occupied." << endl;
			cout << "Try again" << endl;

		}
		else if (IsJump(CMCheckersBoard, numRowsInBoard, player, fromXLoc, fromYLoc) == true && CalculateDistance(numRowsInBoard, fromSquareNum, toSquareNum) == 1)
		{
			cout << "ERROR: You can jump with this checker, you must jump not move 1 space." << endl;
			cout << "Try again" << endl;
		}
		else
		{
			return toSquareNum;
		}
		cout << "Enter the square number of the square you want to move your checker to" << endl;
	}
}

/// <summary>Check Location to see if it contains a white piece.</summary>
/// <param name="squareToCheck">Location to check.</param>  
/// <returns>True if location contains a white piece.</returns> 
bool IsWhitePiece(int squareToCheck)
{
	return (squareToCheck == WHITESOLDIER || squareToCheck == WHITEMULE || squareToCheck == WHITEKING);
}

/// <summary>Check Location to see if it contains a red piece.</summary>
/// <param name="squareToCheck">Location to check.</param>  
/// <returns>True if location contains a red piece.</returns> 
bool IsRedPiece(int squareToCheck)
{
	return (squareToCheck == REDSOLDIER || squareToCheck == REDMULE || squareToCheck == REDKING);
}

/// <summary>Check Location to see if it contains a players piece.</summary>
/// <param name="squareToCheck">Location to check.</param>  
/// <param name="player">Player to check.</param>  
/// <returns>True if location contains a piece for player.</returns> 
bool IsPieceValid(int squareToCheck, int player)
{
	// If we are checking white player...check to see if square contains a white piece.
	if (player == WHITEPLAYER)
	{
		return IsWhitePiece(squareToCheck);
	}

	// If we are checking red player...check to see if square contains a red piece.
	if (player == REDPLAYER)
	{
		return IsRedPiece(squareToCheck);
	}
	return false;
}

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	// Calculate halfway mark.
	int halfway = (numRowsInBoard / 2);

	for (int y = 0; y < numRowsInBoard; y++)
	{
		for (int x = 0; x < numRowsInBoard; x++)
		{
			bool rowIsEven = (x % 2 == 0);
			bool rowColumnIsEven = ((x + y) % 2 == 0);

			// Set each square to empty.
			//CMCheckersBoard[y][x] = EMPTY;

			// Add WHITEMULE & WHITESOLDIER.
			if (!rowIsEven && y == 0)
			{
				CMCheckersBoard[y][x] = WHITEMULE;
			}

			if (!rowColumnIsEven && (y > 0 && y < halfway - 1))
			{
				CMCheckersBoard[y][x] = WHITESOLDIER;
			}

			// Add REDMULE & REDSOLDIER.
			if (rowIsEven && y == numRowsInBoard - 1)
			{
				CMCheckersBoard[y][x] = REDMULE;
			}

			if (!rowColumnIsEven && (y < (numRowsInBoard - 1) && y >= halfway + 1))
			{
				CMCheckersBoard[y][x] = REDSOLDIER;
			}
		}
	}
}

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int count = 0;

	for (int y = 0; y < numRowsInBoard; y++)
	{
		for (int x = 0; x < numRowsInBoard; x++)
		{
			if (CMCheckersBoard[y][x] == WHITESOLDIER)
			{
				cout << setw(4) << "WS";
			}
			else if (CMCheckersBoard[y][x] == WHITEMULE)
			{
				cout << setw(4) << "WM";
			}
			else if (CMCheckersBoard[y][x] == WHITEKING)
			{
				cout << setw(4) << "WK";
			}
			else if (CMCheckersBoard[y][x] == REDMULE)
			{
				cout << setw(4) << "RM";
			}
			else if (CMCheckersBoard[y][x] == REDSOLDIER)
			{
				cout << setw(4) << "RS";
			}
			else if (CMCheckersBoard[y][x] == REDKING)
			{
				cout << setw(4) << "RK";
			}
			else
			{
				cout << setw(4) << count;
			}
			count = count + 1;
		}
		cout << endl;
	}
	cout << endl << endl;
}

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	// Check that piece is valid and that there is room to move.
	if (IsPieceValid(CMCheckersBoard[yLoc][xLoc], player))
	{
		// Calculate the location of squares to check with wrapping.
		int leftOneSpace = (xLoc - 1) < 0 ? numRowsInBoard - 1 : xLoc - 1;                                                                              // Calc location one space to the left with Wrap.
		int rightOneSpace = (xLoc + 1) % numRowsInBoard;                                                                                                                                        // Calc location one space to the right with Wrap.

		if (player == WHITEPLAYER)
		{
			// White is going down the board home row is yLoc = 0;

			// Check if square one up and the left is empty.
			if (CMCheckersBoard[yLoc + 1][leftOneSpace] == EMPTY)
				return true;

			if (CMCheckersBoard[yLoc + 1][rightOneSpace] == EMPTY)
				return true;

			// Handle King moving backwards.
			if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
			{
				// Check if square one up and the left is empty.
				if (CMCheckersBoard[yLoc - 1][leftOneSpace] == EMPTY)
					return true;

				// Check if square one up and the right is empty.
				if (CMCheckersBoard[yLoc - 1][rightOneSpace] == EMPTY)
					return true;
			}
		}

		if (player == REDPLAYER)
		{
			// Red is going up the board home row is yLoc = numRowsInBoard;

			// Check if square one up and the left is empty.
			if (CMCheckersBoard[yLoc - 1][leftOneSpace] == EMPTY)
				return true;

			if (CMCheckersBoard[yLoc - 1][rightOneSpace] == EMPTY)
				return true;


			// Handle King moving backwards.
			if (CMCheckersBoard[yLoc][xLoc] == REDKING)
			{
				// Check if square one up and the left is empty.
				if (CMCheckersBoard[yLoc + 1][leftOneSpace] == EMPTY)
					return true;

				// Check if square one up and the right is empty.
				if (CMCheckersBoard[yLoc + 1][rightOneSpace] == EMPTY)
					return true;
			}
		}

	}
	return false;
}

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	// Check that piece is valid and that there is room to jump.
	if (IsPieceValid(CMCheckersBoard[yLoc][xLoc], player))
	{
		// Calculate the location of squares to check with wrapping.
		int leftOneSpace = (xLoc - 1) < 0 ? numRowsInBoard - 1 : xLoc - 1;                                                                              // Calc location one space to the left with Wrap.
		int leftTwoSpace = (leftOneSpace - 1) < 0 ? numRowsInBoard - 1 : leftOneSpace - 1;        // Calc location two space to the left with Wrap.
		int rightOneSpace = (xLoc + 1) % numRowsInBoard;                                                                                                                                        // Calc location one space to the right with Wrap.
		int rightTwoSpace = (rightOneSpace + 1) % numRowsInBoard;                                                                                                   // Calc location two space to the right with Wrap.

		if (player == WHITEPLAYER)
		{
			// White is going down the board home row is yLoc = 0;

			// Check if square one up and to the left has an opponent checker.
			if (IsPieceValid(CMCheckersBoard[yLoc + 1][leftOneSpace], REDPLAYER))
			{
				// Check if square two up and the left is empty.
				if (CMCheckersBoard[yLoc + 2][leftTwoSpace] == EMPTY)
					return true;
			}

			// Check if square one up and to the right has an opponent checker.
			if (IsPieceValid(CMCheckersBoard[yLoc + 1][rightOneSpace], REDPLAYER))
			{
				// Check if square two up and the right is empty.
				if (CMCheckersBoard[yLoc + 2][rightTwoSpace] == EMPTY)
					return true;
			}

			// Handle King jumping backwards.
			if (CMCheckersBoard[yLoc][xLoc] == WHITEKING) {

				// Check if square one up and to the left has an opponent checker.
				if (IsPieceValid(CMCheckersBoard[yLoc - 1][leftOneSpace], REDPLAYER))
				{
					// Check if square two up and the left is empty.
					if (CMCheckersBoard[yLoc - 2][leftTwoSpace] == EMPTY)
						return true;
				}

				if (IsPieceValid(CMCheckersBoard[yLoc - 1][rightOneSpace], REDPLAYER))
				{
					// Check if square two up and the left is empty.
					if (CMCheckersBoard[yLoc - 2][rightTwoSpace] == EMPTY)
						return true;
				}
			}
		}

		if (player == REDPLAYER)
		{
			// Red is going up the board home row is yLoc = numRowsInBoard;

			// Check if square one up and to the left has an opponent checker.
			if (IsPieceValid(CMCheckersBoard[yLoc - 1][leftOneSpace], WHITEPLAYER))
			{
				// Check if square two up and the left is empty.
				if (CMCheckersBoard[yLoc - 2][leftTwoSpace] == EMPTY)
					return true;
			}

			// Check if square one up and to the right has an opponent checker.
			if (IsPieceValid(CMCheckersBoard[yLoc - 1][rightOneSpace], WHITEPLAYER))
			{
				// Check if square two up and the right is empty.
				if (CMCheckersBoard[yLoc - 2][rightTwoSpace] == EMPTY)
					return true;
			}

			// Handle King jumping backwards.
			if (CMCheckersBoard[yLoc][xLoc] == REDKING) {

				// Check if square one up and to the left has an opponent checker.
				if (IsPieceValid(CMCheckersBoard[yLoc + 1][leftOneSpace], WHITEPLAYER))
				{
					// Check if square two up and the left is empty.
					if (CMCheckersBoard[yLoc + 2][leftTwoSpace] == EMPTY)
						return true;
				}

				if (IsPieceValid(CMCheckersBoard[yLoc + 1][rightOneSpace], WHITEPLAYER))
				{
					// Check if square two up and the left is empty.
					if (CMCheckersBoard[yLoc + 2][rightTwoSpace] == EMPTY)
						return true;
				}
			}
		}

	}
	return false;
}

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int redcounter = 0;
	int whitecounter = 0;
	int redMule = 0;
	int whiteMule = 0;
	for (int k = 0; k < numRowsInBoard; k++)
	{
		for (int j = 0; j < numRowsInBoard; j++)
		{
			if (IsRedPiece(CMCheckersBoard[k][j]))
			{
				redcounter = redcounter + 1;
			}
			if (IsWhitePiece(CMCheckersBoard[k][j]))
			{
				whitecounter = whitecounter + 1;
			}
			if (CMCheckersBoard[k][j] == WHITEMULE)
			{
				whiteMule = whiteMule + 1;
			}
			if (CMCheckersBoard[k][j] == REDMULE)
			{
				redMule = redMule + 1;
			}
		}
	}
	if (whitecounter == whiteMule)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings" << endl;
		return true;
	}
	if (redcounter == redMule)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings" << endl;
		return true;
	}
	if (whiteMule == 0)
	{
		cout << "The White Player has won the game by losing all of the White Mules" << endl;
		return true;
	}
	if (redMule == 0)
	{
		cout << "The Red Player has won the game by losing all of the Red Mules" << endl;
		return true;
	}
	return false;
}

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int jumps = 0;

	// Initialize arrays.
	for (int i = 0; i < MAX_PIECES; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}

	for (int x = 0; x < numRowsInBoard; x++)
	{
		for (int y = 0; y < numRowsInBoard; y++)
		{
			if (IsPieceValid(CMCheckersBoard[y][x], player))
			{
				if (IsJump(CMCheckersBoard, numRowsInBoard, player, x, y))
				{
					xLocArray[jumps] = x;
					yLocArray[jumps] = y;
					jumps = jumps + 1;
				}
			}
		}
	}
	return jumps;
}

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{

	int moves = 0;
	// Initialize arrays.
	for (int i = 0; i < MAX_PIECES; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}

	for (int x = 0; x < numRowsInBoard; x++)
	{
		for (int y = 0; y < numRowsInBoard; y++)
		{
			if (IsPieceValid(CMCheckersBoard[y][x], player))
			{
				if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, x, y))
				{
					xLocArray[moves] = x;
					yLocArray[moves] = y;
					moves = moves + 1;
				}
			}
		}
	}
	return moves;
}

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
	int fromSquareX = fromSquareNum % numRowsInBoard;
	int fromSquareY = fromSquareNum / numRowsInBoard;
	int toSquareX = toSquareNum % numRowsInBoard;
	int toSquareY = toSquareNum / numRowsInBoard;
	jumped = false;

	int distance = CalculateDistance(numRowsInBoard, fromSquareNum, toSquareNum);
	if (distance == -1)
	{
		cerr << "Error: illegal move" << endl;
		return false;
	}
	//check if the space between the two squares are empty 
	//first check special cases

	//only if the mules or soldiers are moving in the wrong direction 
	if (player == WHITEPLAYER)
	{
		if (CMCheckersBoard[fromSquareY][fromSquareX] == WHITESOLDIER
			|| CMCheckersBoard[fromSquareY][fromSquareX] == WHITEMULE)
		{
			if (fromSquareY - toSquareY > 0)
			{
				cerr << "Error: illegal move" << endl;
				return false;
			}
		}
	}
	else if (player == REDPLAYER)
	{
		if (CMCheckersBoard[fromSquareY][fromSquareNum%numRowsInBoard] == REDSOLDIER
			|| CMCheckersBoard[fromSquareY][fromSquareNum%numRowsInBoard] == REDMULE)
		{
			if (fromSquareY - toSquareY < 0)
			{
				cerr << "Error: illegal move" << endl;
				return false;
			}
		}
	}

	// Handle a 'Move'.
	if (distance == 1) {

		if (IsJump(CMCheckersBoard, numRowsInBoard, player, fromSquareX, fromSquareY))
		{
			cerr << "ERROR: You can jump with this checker, you must jump not move 1 space" << endl << "Try again" << endl;
			return false;
		}

		//if (IsPieceValid(CMCheckersBoard[fromSquareY][fromSquareX], player))
		//{
		// Update board.
		CMCheckersBoard[toSquareY][toSquareX] = CMCheckersBoard[fromSquareY][fromSquareX];
		CMCheckersBoard[fromSquareY][fromSquareX] = EMPTY;
		//}
	}

	// Handle a 'Jump'.
	if (distance == 2)
	{
		// Calculate jumped square coordinates.
		int JumpedYCoord = (fromSquareY + toSquareY) / 2;
		int JumpedXCoord = 0;

		if (fromSquareX > toSquareX)
		{
			if (abs(fromSquareX - toSquareX) == 2)
			{
				JumpedXCoord = (toSquareX + 1) % numRowsInBoard;                                                                                                                                 // Calc location one space to the right with Wrap.
			}
			else
			{
				JumpedXCoord = (toSquareX - 1) < 0 ? numRowsInBoard - 1 : toSquareX - 1;                                        // Calc location one space to the left with Wrap.
			}
		}
		else {
			if (abs(fromSquareX - toSquareX) == 2)
			{
				JumpedXCoord = (fromSquareX + 1) % numRowsInBoard;                                                                                                                                           // Calc location one space to the right with Wrap.
			}
			else
			{
				JumpedXCoord = (fromSquareX - 1) < 0 ? numRowsInBoard - 1 : fromSquareX - 1;                                            // Calc location one space to the left with Wrap.
			}
		}

		if (player == WHITEPLAYER)
		{
			// Check to see that the jumped piece is opposite color and valid.
			if (!IsPieceValid(CMCheckersBoard[JumpedYCoord][JumpedXCoord], REDPLAYER))
			{
				cerr << "Error: illegal move" << endl;
				return false;
			}
		}

		if (player == REDPLAYER)
		{
			// Check to see that the jumped piece is opposite color and valid.
			if (!IsPieceValid(CMCheckersBoard[JumpedYCoord][JumpedXCoord], WHITEPLAYER))
			{
				cerr << "Error: illegal move" << endl;
				return false;
			}
		}

		// Update board.
		CMCheckersBoard[toSquareY][toSquareX] = CMCheckersBoard[fromSquareY][fromSquareX];
		CMCheckersBoard[fromSquareY][fromSquareX] = EMPTY;
		CMCheckersBoard[JumpedYCoord][JumpedXCoord] = EMPTY;
		jumped = true;
	}

	// Check for king promption.
	if (player == REDPLAYER)
	{
		if (toSquareY == 0)
		{
			if (CMCheckersBoard[toSquareY][toSquareX] == REDMULE)
			{
				cout << "Red has created a Mule King,  White wins the game" << endl;
				PromptAndExit();
			}
			CMCheckersBoard[toSquareY][toSquareX] = REDKING;
			jumped = false;
		}
	}

	if (player == WHITEPLAYER)
	{
		if (toSquareY == numRowsInBoard - 1)
		{
			if (CMCheckersBoard[toSquareY][toSquareX] == WHITEMULE)
			{
				cout << "White has created a Mule King, Red wins the game" << endl;
				PromptAndExit();
			}
			CMCheckersBoard[toSquareY][toSquareX] = WHITEKING;
			jumped = false;

		}
	}

	return true;
}