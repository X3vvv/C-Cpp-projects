/*
Project:  Tic-tac-toe (2 modes)
Author:   X3vvv
Date:     June 1, 2020

Note:
    O default first, X second;
*/

#include <iostream>
#include <cstring>
#include <windows.h>
#include <algorithm>
#include <ctime>

using namespace std;

//Global Variables
int win_sets[8][3] = {  {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7},\
                        {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7} };
                        // combinations of pieces that lead to win.

int cells[9];           // -1:null  0:O  1:X

int player1;            // record the result in roll-a-dice
                        // 1: Player 1 use X (Player 2 or Computer player first)
                        // 0: Player 1 use O (Player 1 first)

bool ai_active;         // true:  PvE mode
                        // false: PvP mode

bool id_open;           // switch to open/off position IDs

int state;              // 1:  X WIN
                        // 2:  O WIN
                        // 3:  DRAW
                        // 4:  O's turn (default)
                        // 5:  X's turn

bool easy_mode;         // true: easy mode;  false: hard mode


// Function List
void init()
int get_input(int mode)

void welcome_message()
void rule_message()
void goodbye_message()

bool start_game()
void choose_mode()
void roll_a_dice()

bool check_state()
void show_state()
void showboard()
void update_screen()

int evaluate()
bool is_full()
int minimax(int depth, bool isMax)

void ai_move()
void player_move(int piece)
void move()


void init()
{
    /* This function initialize the gameboard. */

    for (int i = 0; i < 9; cells[i++] = -1);  //clear the gameboard
    ai_active = false;                        //default open AI
    state = 4;                                //default O's turn

    id_open = true;                           //default on position IDs
}


int get_input(int mode)
{
    /*
    This function ask the user for an command until a legal command is received.
        mode == 0 : only 1 and 2 is legal commands
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
        if (mode == 0)
        {
            if (c != '1' && c != '2')
            {
                cout << "|-----------------------------------------------------|" << endl;
                cout << "| > Illegal command, please enter again.              |" << endl;
                cout << "|                                                     |" << endl;
                cout << "| > ";
                continue;
            }
        }
        else if (mode == 1)
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


void welcome_message()
{
    /* This function show the welcome message. */

    cout << "+-----------------------------------------------------+" << endl;
    cout << "|  _______         ______              ______         |" << endl;
    cout << "| /_  __(_)____   /_  __/___ ______   /_  __/___  ___ |" << endl;
    cout << "|  / / / / ___/    / / / __ `/ ___/    / / / __ \\/ _ \\|" << endl;
    cout << "| / / / / /__     / / / /_/ / /__     / / / /_/ /  __/|" << endl;
    cout << "|/_/ /_/\\___/    /_/  \\__,_/\\___/    /_/  \\____/\\___/ |" << endl;
    cout << "|                                                     |" << endl;
    cout << "|-----------------------------------------------------|" << endl;
}


void rule_message()
{
    /* This function show how to play the game. */

    system("cls");
    welcome_message();

    if (ai_active)
    {
        cout << "|-----------------------------------------------------|" << endl;
        cout << "| >You choose to against the AI                       |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|  Throw a dice and the bigger one play first         |" << endl;
        cout << "|  (use O as chessman)                                |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|  press any button to throw a dice                   |" << endl;
        cout << "|-----------------------------------------------------|" << endl;
    }
    else
    {
        cout << "|-----------------------------------------------------|" << endl;
        cout << "| >You'll against each other                          |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|  Player 1 and Player 2, you both will throw a dice  |" << endl;
        cout << "|  the bigger one play first (use O as chessman)      |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|  press any button to throw a dice                   |" << endl;
        cout << "|-----------------------------------------------------|" << endl;
    }
    system("pause");
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
    cout << "|      Players VS Computer:     1                     |" << endl;
    cout << "|      Player VS Player:        2                     |" << endl;
    cout << "|                                                     |" << endl;
    cout << "| > ";

    if (get_input(0) == 1) ai_active = true;

    if (ai_active)
    {
        system("cls");
        welcome_message();

        cout << "|-----------------------------------------------------|" << endl;
        cout << "| > Choose AI mode:                                   |" << endl;
        cout << "|      Easy:                1                         |" << endl;
        cout << "|      Utmost:              2                         |" << endl;
        cout << "|                                                     |" << endl;
        cout << "| > ";

        if (get_input(0) == 1) easy_mode = true;
        else easy_mode = false;
    }
}


void roll_a_dice()
{
    /* This function ask the users to roll a dice to decide the game order (PvP only). */

    srand((unsigned)time(NULL)); //offer a seed based on current time

    int i = 0;
    int p1;
    int p2;

    while (i++ < 6 || p1 == p2)
    {
        system("cls");
        p1 = (rand() % 6) + 1;
        p2 = (rand() % 6) + 1;

        cout << "+-----------------------------------------------------+" << endl;

        if (ai_active)
            cout << "|            Player 1             Computer            |" << endl;
        else
            cout << "|            Player 1             Player 2            |" << endl;

            cout << "|                                                     |" << endl;
            cout << "|               " << p1 << "                     " << p2 << "               |" << endl;
            cout << "+-----------------------------------------------------+" << endl;
            Sleep(400);
    }

    player1 = (p1 > p2) ? 0 : 1;

    Sleep(1000);

    if (player1 == 0)
        cout << "|                     Player 1 WIN                    |" << endl;
    else if (ai_active)
        cout << "|                     Computer WIN                    |" << endl;
    else
        cout << "|                     Player 2 WIN                    |" << endl;

    cout << "|_____________________________________________________|" << endl;
    system("pause");
}


bool check_state()
{
    /*
    This function update game state and return false if game has ended, else true.
        State List      1:  X WIN
                        2:  O WIN
                        3:  DRAW
                        4:  O's turn (default)
                        5:  X's turn
    */

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
            state = (winner == 1) ? 1 : 2;
            break;
        }
    }

    //DRAW
    int step = 1;  //ordinal number of the next step
    for (int i = 0; i < 9; i++)
        if (cells[i] != -1) step++;
    if (winner == -1 && step == 10) state = 3;

    //who's turn
    if (winner == -1 && step < 10) state = (step % 2 == 1) ? 4 : 5;

    return (state > 3 ? true : false);
}


void show_state()
{
    /*
    This function show the state information.
        PvP mode:   show "Player x's TURN(O/X)" .
                    show "Player x WIN" or "DRAW" when game end.
        PvE mode:   show "YOUR TURN" only.
                    show "YOU WIN" or "YOU LOSE" or "DRAW" when game end.
        (ASCII(0) = 48)
    */

    char msg[56];
    switch (state)
    {
        //1:  X WIN
    case 1:
        //PvE mode
        if (ai_active)
        {
            //Player 1 use O
            if (player1 == 0)
                strcpy_s(msg, 56, "|                       YOU LOST                      |");
            //Computer use O
            else
                strcpy_s(msg, 56, "|                       YOU WIN                       |");
        }
        //PvP mode
        else if (player1) //Player 1 use X
            strcpy_s(msg, 56, "|                     Player 1 WIN                    |");
        else              //Player 2 use X
            strcpy_s(msg, 56, "|                     Player 2 WIN                    |");
        break;

        //2:  O WIN
    case 2:
        //PvE mode
        if (ai_active)
        {
            //Player 1 use O
            if (player1 == 0)
                strcpy_s(msg, 56, "|                       YOU WIN                       |");
            //Computer use O
            else
                strcpy_s(msg, 56, "|                       YOU LOST                      |");
        }
        //PvP mode
        else if (!player1) //Player 1 use O
            strcpy_s(msg, 56, "|                     Player 1 WIN                    |");
        else               //Player 2 use O
            strcpy_s(msg, 56, "|                     Player 2 WIN                    |");
        break;

        //3:  DRAW
    case 3:
        strcpy_s(msg, 56, "|                        DRAW                         |");
        break;

        //4:  O's turn (default)
    case 4:
        //PvP mode
        if (!ai_active)
        {
            if (player1 == 0) //Player 1 use O
                strcpy_s(msg, 56, "|                   Player 1's TURN                   |");
            else
                strcpy_s(msg, 56, "|                   Player 2's TURN                   |");
        }
        //PvE mode
        else if (ai_active && player1 == 0) //Player 1 use O
            strcpy_s(msg, 56, "|                      YOUR TURN                      |");
        else //AI is fast, so this msg will just flash by
            strcpy_s(msg, 56, "|                      AI's TURN                      |");
        break;

        //5:  X's turn
    case 5:
        //PvP mode
        if (!ai_active)
        {
            if (player1 == 0) //Player 1 use O
                strcpy_s(msg, 56, "|                   Player 2's TURN                   |");
            else
                strcpy_s(msg, 56, "|                   Player 1's TURN                   |");
        }
        //PvE mode
        else if (ai_active && player1 == 1) //Player 1 use X
            strcpy_s(msg, 56, "|                      YOUR TURN                      |");
        else //AI is fast, so this msg will just flash by
            strcpy_s(msg, 56, "|                      AI's TURN                      |");
        break;
    }

    cout << "+-----------------------------------------------------+" << endl;
    cout << msg << endl;
    cout << "|-----------------------------------------------------|" << endl;
}


void showboard()
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
        cout << "|                     ";  //whitespace number: (55 - 11) / 2 = 22
        if (i % 2 == 1)
        {
            cout << "---+---+---" << "                     |" << endl;
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
                if (id_open)
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
        cout << "                     |" << endl;
    }
}


void update_screen()
{
    /* This function update the screen while gaming, show new game state and gameboard. */

    system("cls");

    show_state();
    showboard();
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
            if (cells[s1] == player1) //player win
            {
                return -20;
            }
            else                      //ai win
            {
                return 20;
            }
        }
    }
    return 0;                         //nobody win
}


bool is_full()
{
    /* This function return a bool value indicating whether the gameboard is full. */

    for (int i = 0; i < 9; i++)
    {
        if (cells[i] == -1) return false;
    }
    return true;
}


int minimax(int depth, bool isMax)
{
    /* This function:
        for maxer: return the biggest value
        for miner: return the smallest value. */

    int score = evaluate();

    // In easy mode, ai makes mistake randomly.
    // In each simulated step, ai has less than 
    // 3/4 chance of making mistake.
    srand(unsigned(time(NULL)));
    if (easy_mode && (rand() % 4) < 3) return 0;

    // Another way to implement the easy mode:
    //if (easy_mode && depth >= 2) return score;

    if (score == 20)  return score - depth; //if ai win
    if (score == -20) return score + depth; //if player win
    if (is_full())    return 0;             //if draw

    if (isMax)
    {
        int highest = -1000;
        for (int i = 0; i < 9; i++)
            if (cells[i] == -1)
            {
                cells[i] = !player1;  //simulate ai's move
                highest = max(highest, minimax(depth + 1, !isMax));
                cells[i] = -1;        //withdraw the move
            }
        return highest;
    }
    else
    {
        int lowest = 1000;
        for (int i = 0; i < 9; i++)
            if (cells[i] == -1)
            {
                cells[i] = player1;  //simulate user's move
                lowest = min(lowest, minimax(depth + 1, !isMax));
                cells[i] = -1;       //withdraw the move
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
            cells[i] = !player1;                 //simulate AI's move
            temp_score = minimax(0, false);      //possible player's move
            cells[i] = -1;                       //withdraw the move

            if (temp_score > score)
            {
                best_move = i;
                score = temp_score;
            }
        }
    }
    cells[best_move] = !player1; //make the move
}


void player_move(int piece)
{
    /* This function ask a player to move or turn on/off the id switch. */

    cout << "|-----------------------------------------------------|" << endl;
    cout << "| > Choose a position                                 |" << endl;
    cout << "|         (enter c to open/off position IDs)          |" << endl;
    cout << "| > ";

    int input = get_input(2);

    if (input == 'c' - 48)     //open/off position IDs
        id_open = !id_open;
    else                       //move a step
        cells[input - 1] = piece;
}


void move()
{
    /*
    This function ask players/ai move by turn or open/off positoin IDs.
        O (odd steps)5
        X (even steps)
    */

    int step = 1;
    //e.g. step = 3 for the case below:
    //    |   |   
    // -----------
    //    | O | X 
    // -----------
    //    |   |   

    for (int i = 0; i < 9; i++)
        if (cells[i] != -1) step++;

    //  _____________________________
    // |   step % 2   |   0   |   1  |
    // |--------------+-------+------|
    // | piece's turn |   X   |   O  |
    // |--------------+-------+------|
    // |    player1   |       |      |
    // |that make this|   0   |   1  |
    // |step ai's turn|       |      |
    // |--------------+-------+------|
    if (ai_active && step % 2 == player1)
        ai_move();
    else
        player_move(!(step % 2));
}


int main()
{
    welcome_message();                  //show welcome picture

    while (start_game())                //ask user whether start game
    {
        init();
        choose_mode();                  //ask user to choose a mode
        rule_message();                 //show the rule of the mode

        roll_a_dice();                  //ask user to roll a dice to decide the order

        update_screen();                //show state and gameboard with IDs
        while (true)                    //main game loop
        {
            move();                     //ask user/ai to move a step
            if (!check_state())         //check whether game end
            {
                update_screen();        //show the game result
                break;                  //end this game
            }
            update_screen();            //show state and gameboard
        }
    }

    goodbye_message();                  //show goodbye message

    system("pause");

    return 0;
}