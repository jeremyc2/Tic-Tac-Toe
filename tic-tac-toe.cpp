/***********************************************************************
* Program:
*    Lesson 08, Tic-Tac-Toe
* Summary: 
*    This program reads, displays, and writes a Tic-Tac-Toe board
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#define PIECE_X 'X'
#define PIECE_O 'O'
#define SPACE '.'
#define BOARD_SIZE 3
#define BOARD_COUNT 3

bool read(         char board[][BOARD_SIZE], const char* fileName);
bool write(  const char board[][BOARD_SIZE], const char* fileName);
void display(const char board[][BOARD_SIZE]);
bool didWin( const char board[][BOARD_SIZE], char turn);

/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/
int main()
{
   char board[BOARD_SIZE * BOARD_COUNT][BOARD_SIZE];

   // read the board
   char fileName[256];
   cout << "Enter source filename: ";
   cin  >> fileName;
   if (!read(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   // display the board
   display(board);

   // write the board to a file
   cout << "Enter destination filename: ";
   cin  >> fileName;
   if (!write(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[][BOARD_SIZE], const char* fileName)
{
   assert(*fileName);

   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return false;

   int r = 0;
   // read 9 symbols, hopefully they are . X O
   while (!fin.fail())
   {
      for (; !fin.fail(); r++)
         for (int c = 0; c < BOARD_SIZE; c++)
         {
            fin >> board[r][c];

            if (fin.fail())
               break;
               
            assert(!fin.fail());
            assert(board[r][c] == PIECE_X ||
                  board[r][c] == PIECE_O ||
                  board[r][c] == SPACE);
         }
   }

   // close the file
   fin.close();
   return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[][BOARD_SIZE], const char* fileName)
{
   assert(fileName[0] != '\0');

   // open the file
   ofstream fout(fileName);
   if (fout.fail())
      return false;

   int r = 0;
   // write my 9 symbols
   for (;; r++)
   {
      if (!(board[r][0] == PIECE_X ||
               board[r][0] == PIECE_O ||
               board[r][0] == SPACE))
      {
         break;
      }

      for (int c = 0; c < BOARD_SIZE; c++)
         fout << board[r][c] << (c == 2 ? '\n' : ' ');
   }

   // close it!
   fout.close();
   cout << "File written\n";
   return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[][BOARD_SIZE])
{
   // loop through each row
   for (int r = 0; true; r++)
   {
      if (!(board[r][0] == PIECE_X ||
               board[r][0] == PIECE_O ||
               board[r][0] == SPACE))
      {
         break;
      }

      // only the first row is not preceeded with the --+-- magic
      if (r % BOARD_SIZE != 0)
         cout << "---+---+---\n";
      else
         cout << endl;

      // now, on each row, do the column stuff
      for (int c = 0; c < BOARD_SIZE; c++)
      {
         // display a space for the dot
         if (board[r][c] == SPACE)
            cout << "   ";
         else
            cout << " " << board[r][c] << " ";

         // end with a | or a newline
         cout << (c == 2 ? '\n' : '|');
      }
   }

   // display who won
   if (didWin(board, PIECE_X))
      cout << "X won!\n";
   if (didWin(board, PIECE_O))
      cout << "O won!\n";
   
   return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[][BOARD_SIZE], char turn)
{
   bool win = true;
   for (int c = 0; c < BOARD_SIZE; c++)
   {
      if (board[c][c] != turn)
      {
         win = false;
         break;
      }
   }

   if (win)
      return true;

   win = true;
   for (int c = 0; c < BOARD_SIZE; c++)
   {
      if (board[c][BOARD_SIZE - 1 - c] != turn)
      {
         win = false;
         break;
      }
   }

   for (int r = 0; r < BOARD_SIZE; r++)
   {
      win = true;
      for (int c = 0; c < BOARD_SIZE; c++)
      {
         if (board[r][c] != turn)
         {
            win = false;
            break;
         }
      }

      if (win)
         return true;
   }

   for (int c = 0; c < BOARD_SIZE; c++)
   {
      win = true;
      for (int r = 0; r < BOARD_SIZE; r++)
      {
         if (board[r][c] != turn)
         {
            win = false;
            break;
         }
      }

      if (win)
         return true;
   }

   return false;
}
