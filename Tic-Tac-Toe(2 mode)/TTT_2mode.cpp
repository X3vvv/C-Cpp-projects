/* 
Project:  Tic-tac-toe (2 mode)
Author:   X3vvv
Date:     May 22, 2020

Note:
   O default first, X second;
   player default first, ai second.

Function List:

      void welcome_message()                 void goodbye_message()

      void init()                            int get_input(int mode)      

      bool start_game()                      void choose_mode()

      bool check_state()                     void show_state()

      void showboard(bool id_on = false)     void update_screen(bool id_on = false)      

      int evaluate()                         bool is_full()

      void ai_move()                         void player_move(int piece)

      void move()                            int main()
*/

#include <iostream>
#include <cstring>

using namespace std;

static const int win_sets[8][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7},\
                                    {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};
static int cells[9];    //-1:null  0:O  1:X
static bool ai_active;  //player default first
static bool id_open;    //switch to open/off position IDs

static int state;       //1:  X WIN
                        //2:  O WIN
                        //3:  DRAW
                        //4:  O's turn (default)
                        //5:  X's turn



void welcome_message()
{
   /* This function output the welcome message. */

   cout << "+-----------------------------------------------------+"       << endl;
   cout << "|  _______         ______              ______         |"       << endl;
   cout << "| /_  __(_)____   /_  __/___ ______   /_  __/___  ___ |"       << endl;
   cout << "|  / / / / ___/    / / / __ `/ ___/    / / / __ \\/ _ \\|"     << endl;
   cout << "| / / / / /__     / / / /_/ / /__     / / / /_/ /  __/|"       << endl;
   cout << "|/_/ /_/\\___/    /_/  \\__,_/\\___/    /_/  \\____/\\___/ |"  << endl;
   cout << "|                                                     |"       << endl;
   cout << "|-----------------------------------------------------|"       << endl;
}


void goodbye_message()
{
   /* This function show goodbye message. */

   system("cls");
   cout << "+-----------------------------------------------------+" << endl;
   cout << "|        ______                ____                   |" << endl;
   cout << "|       / ____/___  ____  ____/ / /_  __  _____       |" << endl;
   cout << "|      / / __/ __ \\/ __ \\/ __  / __ \\/ / / / _ \\      |" << endl;
   cout << "|     / /_/ / /_/ / /_/ / /_/ / /_/ / /_/ /  __/      |" << endl;
   cout << "|     \\____/\\____/\\____/\\__,_/_.___/\\__, /\\___/       |" << endl;
   cout << "|                                  /____/             |" << endl;
   cout << "+-----------------------------------------------------+" << endl;
}


void init()
{
   /* This function initialize the gameboard. */

   for (int i = 0; i < 9; cells[i++] = -1);  //clear the gameboard
   ai_active = false;                        //default open AI
   state = 4;                                //default O's turn
   id_open = true;                          //default on position IDs
}


int get_input(int mode)
{
   /* 
   This function ask the user for an legal command.
      mode == 1 : only 0 and 1 is legal commands
      mode == 2 : integer from 1 - 9 or 'c' is legal commands
   */

   char c;
   while (true)
   {

      //get the first char and leave out the rest until the link break
      c = getchar();
      while (getchar() != '\n');

      //illegal command
      if (mode == 1)
      {
         if (c != '0' && c != '1')
         {
            cout << "|-----------------------------------------------------|" << endl;
            cout << "| > Illegal command, please enter again.              |" << endl;
            cout << "|                                                     |" << endl;
            cout << "| > ";
            continue;
         }
      }
      else if (mode == 2)
      {
         //legal ID and empty position on gameboard or 'c'
         if ((c < '1' || c > '9' || cells[c - '1'] != -1) && c != 'c') {
            cout << "|-----------------------------------------------------|" << endl;
            cout << "| > Illegal command, please enter again.              |" << endl;
            cout << "|                                                     |" << endl;
            cout << "| > ";
            continue;
         }
      }
      else throw "get_input() @para mode error";

      //ASCII(0) = 48
      return int(c - 48);
   }
}


bool start_game()
{
   /* This function ask user whether start game and return the bool value. */

   cout << "|-----------------------------------------------------|" << endl;
   cout << "| > Start a new game?                                 |" << endl;
   cout << "|      Quit the system:  0                            |" << endl;
   cout << "|      Start game:       1                            |" << endl;
   cout << "|                                                     |" << endl;
   cout << "| > ";

   //get the user input
   switch (get_input(1))
   {
      case 0: return false;
      case 1: return true;
   }
}


void choose_mode()
{
   /* This function ask the user to choose PvP or PvE */

   system("cls");
   welcome_message();

   cout << "|-----------------------------------------------------|" << endl;
   cout << "| > Choose game mode:                                 |" << endl;
   cout << "|      Two players:      0                            |" << endl;
   cout << "|      One players:      1                            |" << endl;
   cout << "|                                                     |" << endl;
   cout << "| > ";

   if (get_input(1)) ai_active = true;
}


bool check_state()
{
   /* This function update game state and return false if game has ended, else true. */

   //X WIN or O WIN
   int winner = -1;  //-1:  no one win
                     // 0:  O WIN
                     // 1:  X WIN

   for (int i = 0; i < 8; i++)
   {
      int s1 = win_sets[i][0] - 1;
      int s2 = win_sets[i][1] - 1;
      int s3 = win_sets[i][2] - 1;

      if (cells[s1] != -1 && cells[s1] == cells[s2] && cells[s2] == cells[s3])
      {
         winner = cells[s1];
         state = (winner == 1)? 1 : 2;
         break;
      }
   }

   //DRAW
   int step = 1;  //ordinal number of the next step
   for (int i = 0; i < 9; i++)
   {
      if (cells[i] != -1) step++;
   }   
   if (winner == -1 && step == 10) state = 3;
   
   //who's turn
   if (winner == -1 && step < 10) state = (step % 2 == 1)? 4 : 5;

   return (state > 3 ? true : false);
}


void show_state()
{
   /* This function show the state information. */

   char msg[56];
   switch (state)
   {
      case 1:
         if (ai_active)
            strcpy(msg, "|                       YOU LOST                      |");
         else
            strcpy(msg, "|                        O WIN                        |");
         break;
      case 2:
         if (ai_active)
            strcpy(msg, "|                       YOU WIN                       |");
         else
            strcpy(msg, "|                        O WIN                        |");
         break;
      case 3:
         strcpy(msg, "|                        DRAW                         |");
         break;
      case 4:
         strcpy(msg, "|                       O's TURN                      |");
         break;
      case 5:
         strcpy(msg, "|                       X's TURN                      |");
         break;
   }

   cout << "+-----------------------------------------------------+" << endl;
   cout << msg << endl;
   cout << "|-----------------------------------------------------|" << endl;
}


void showboard(bool id_on = false)
{
   /* This function show the game board with or without IDs. */

	// 1 | O | 3
	//---+---+---
	// 4 | X | 6
	//---+---+---
	// 7 | 8 | 9

   int n = 0; //the Nth position of the gameboard
   for (int i = 0; i < 5; i++)
   {
      cout << "|                     ";  //(55 - 11) / 2 = 22
      if (i % 2 == 1) 
      {
         cout << "---+---+---" << endl;
         continue;
      }

      for (int j = 0; j < 5; j++)
      {         
         if (j % 2 == 1)
         {
            cout << "|";
            continue;
         }

         switch (cells[n])
         {
            case -1:
               if (id_on)
                  cout << " " << n + 1 << " ";
               else
                  cout << "   ";
               break;
            case  0:
               cout << " O ";
               break;
            case  1:
               cout << " X ";
               break;
         }
         n++;
      }
      cout << endl;
   }
}


void update_screen(bool id_on = false)
{
   /* This function update the screen while gaming, show new game state and gameboard. */

   system("cls");

   show_state();
   showboard(id_on);
}


int evaluate()
{
   /* This function evaluate the gameboard and return a score. */

   for (int i = 0; i < 8; i++)
   {
      int s1 = win_sets[i][0] - 1;
      int s2 = win_sets[i][1] - 1;
      int s3 = win_sets[i][2] - 1;

      if (cells[s1] != -1 && cells[s1] == cells[s2] && cells[s2] == cells[s3])
      {
         if (cells[s1] == 1)  //ai win
            return 10;
         else                 //player win
            return -10;
      }
   }
   return 0;                  //nobody win
}


bool is_full()
{
   /* This function return a bool value indicating whether the gameboard is full. */

   for (int i = 0; i < 9; i++)
      if (cells[i] == -1) return false;
   return true;
}


int minimax(int depth, bool isMax)
{
   /* This function:
         for maxer: return the biggest value
         for miner: return the smallest value. */

   int score = evaluate();

   if (score == 10)  return score - depth; //if ai win
   if (score == -10) return score + depth; //if player win
   if (is_full())    return 0;             //if draw

   if (isMax)
   {
      int highest = -1000;
      for (int i = 0; i < 9; i++)
         if (cells[i] == -1)
         {
            cells[i] = 1;
            highest = max(highest, minimax(depth + 1, !isMax));
            cells[i] = -1;
         }
      return highest;
   }
   else
   {
      int lowest = 1000;
      for (int i = 0; i < 9; i++)
         if (cells[i] == -1)
         {
            cells[i] = 0;
            lowest = min(lowest, minimax(depth + 1, !isMax));
            cells[i] = -1;
         }
      return lowest;
   }
}


void ai_move()
{
   /* This function play as a ai player to make the optimal move. */

   int best_move; //the index of the best move of cells[9]
   int score = -1000;
   int temp_score;

   for (int i = 0; i < 9; i++)
   {
      if (cells[i] == -1)
      {
         cells[i] = 1;                    //AI's move (X --- 1)
         temp_score = minimax(0, false);  //possible player's move (O --- miner)
         cells[i] = -1;
         if (temp_score > score)
         {
            best_move = i;
            score = temp_score;
         }
      }
   }
   
   cells[best_move] = 1; //make the move
}


void player_move(int piece)
{
   /* This function ask a player to move. */

   cout << "|-----------------------------------------------------|" << endl;
   cout << "| > Choose a position                                 |" << endl;
   cout << "|         (enter c to open/off position IDs)          |" << endl;
   cout << "| > ";

   int input = get_input(2);

   if (input == 'c' - 48)          //open/off position IDs
      id_open = !id_open;
   else                                   //move a step
      cells[input - 1] = !piece;
}


void move()
{
   /*
   This function ask players/ai move by turn or open/off positoin IDs.
      Player1   :   O (odd steps)
      Player2/AI:   X (even steps)
   */
   
   int step = 1;
   for (int i = 0; i < 9; i++)
   {
      if (cells[i] != -1) step++;
   }

   if (ai_active && step % 2 == 0)
      ai_move();
   else
      player_move(step % 2);

}


int main()
{
   welcome_message();      //show welcome picture

   while (start_game())    //ask user whether start game
   {
      init();
      choose_mode();       //ask user to choose a mode
      
      update_screen(true); //show state and gameboard with IDs
      while (true)         //main game loop
      {
         move();                       //ask user/ai to move a step
         if (!check_state())           //check whether game end
         {
            update_screen(id_open);    //show the game result
            break;                     //end this game
         }
         update_screen(id_open);       //show state and gameboard
      }
   }

   goodbye_message();      //show goodbye message

   system("pause");        //freeze the screen
   return 0;
}