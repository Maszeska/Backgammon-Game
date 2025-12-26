#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define BOARD_DIM 23
#define ROWS BOARD_DIM
#define COLS (BOARD_DIM * 3)
#define SEGMENT (COLS/12)
#define C_HALF (COLS/2)
#define R_HALF (ROWS/2)
#define DOWN_N (ROWS-2)
#define DOWN (ROWS-3)
#define UP_N 1


#define N_DICES 2
#define MIN_DICE 1
#define MAX_DICE 6

#define PLACE 24
#define PLAYERS 2
#define P1 "X"
#define P2 "O"
#define P1c 'X'
#define P2c 'O'



void printNumbers(WINDOW *b_win)
{
    //right down ( 6-1 )
    for (int i = 0; i < 6; ++i)
    {
        mvwprintw(b_win, DOWN_N , C_HALF + 5 + i * SEGMENT, "%d", 6 - i);
    }
    //left down ( 7-12 )
    for (int i = 0; i < 6; ++i)
    {
        mvwprintw(b_win, DOWN_N , C_HALF - 6 - i * SEGMENT, "%d", 7 + i);
    }
    //left up ( 18-13 )
    for (int i = 0; i < 6; ++i)
    {
        mvwprintw(b_win, UP_N , C_HALF - 6 - i * SEGMENT, "%d", 18 - i);
    }
    //right up ( 19-24 )
    for (int i = 0; i < 6; ++i)
    {
        mvwprintw(b_win, UP_N , C_HALF + 5 + i * SEGMENT, "%d", 19 + i);
    }
}

void printBoard(WINDOW *b_win)
{
    //printing the box
    box(b_win, 0, 0);

    //printing the BAR
    mvwvline(b_win, UP_N, C_HALF - 2, ACS_VLINE, DOWN_N);
    mvwvline(b_win, UP_N, C_HALF + 2, ACS_VLINE, DOWN_N);
    mvwprintw(b_win, R_HALF, (COLS - 3)/2, "BAR");

    // printing the numbers
    printNumbers(b_win);

    refresh();
}
void printLogo(int yMax, int xMax)
{
    const int Y = yMax/6, X = xMax/6;
    mvwprintw(stdscr, Y+1, X, " ___                  _                                                       \n");
    mvwprintw(stdscr, Y+2, X, "(  _`\\               ( )                                                      \n");
    mvwprintw(stdscr, Y+3, X, "| (_) )   _ _    ___ | |/')    __     _ _   ___ ___    ___ ___     _     ___  \n");
    mvwprintw(stdscr, Y+4, X, "|  _ <' /'_` ) /'___)| , <   /'_ `\\ /'_` )/' _ ` _ `\\/' _ ` _ `\\ /'_`\\ /' _ `\\\n");
    mvwprintw(stdscr, Y+5, X, "| (_) )( (_| |( (___ | |\\`\\ ( (_) |( (_| || ( ) ( ) || ( ) ( ) |( (_) )| ( ) |\n");
    mvwprintw(stdscr, Y+6, X, "(____/'`\\__,_)`\\____)(_) (_)`\\__  |`\\__,_)(_) (_) (_)(_) (_) (_)`\\___/'(_) (_)\n");
    mvwprintw(stdscr, Y+7, X, "                            ( )_) |                                           \n");
    mvwprintw(stdscr, Y+8, X, "                             \\___/'                                           ");
}

int showMenu(int xMax, int yMax)
{
    const char *menuItems[] = {"Play (P)", "Continue (C)" ,"Quit (Q)"};
    int choice;

    //printing box
    WINDOW *menu_win = newwin(5, 20, (yMax / 2), (xMax / 2) - 10);
    box(menu_win, 0, 0);

    //printing options
    for (int i = 0; i < 3; ++i)
    {
        mvwprintw(menu_win, i + 1, 2, "%s", menuItems[i]);
    }

    //printing author info
    mvwprintw(stdscr, yMax-1, 1, "AUTHOR: Marta Dubowik S198320");

    //printing logo
    printLogo(yMax,xMax);
    wrefresh(menu_win);

    //response to user input
    while (true)
    {
        choice = getch();

        //play
        if(choice == 'p' || choice == 'P')
        {
            return 1;
        }
            //continue
        else if (choice == 'c' || choice == 'C')
        {
            return 2;
        }
            //quit
        else if (choice == 'q' || choice == 'Q')
        {
            return 0;
        }
    }
}

void CurrentState(const int nPawns[], char pType[], WINDOW *b_win)
{
    //go through every number
    for (int num = 0; num < PLACE; ++num)
    {
        int i, n, X = SEGMENT;
        if (num >=0 && num <= 5)
        {
            i = num;
            for ( n = 0; n < nPawns[num]; ++n)
            {
                mvwprintw(b_win, DOWN - n , COLS - 5 - i * X, "%c", pType[num]);
            }
        }
        else if (num >= 6 && num <= 11)
        {
            i = num - 6;
            for ( n = 0; n < nPawns[num]; ++n)
            {
                mvwprintw(b_win, DOWN - n , C_HALF - 6 - i * X, "%c", pType[num]);
            }
        }
        else if (num >= 12 && num <= 17)
        {
            i = num - 12;
            for ( n = 0; n < nPawns[num]; ++n)
            {
                mvwprintw(b_win, 2 + n , 3 + i * X, "%c", pType[num]);
            }
        }
        else
        {
            i = num - 18;
            for ( n = 0; n < nPawns[num]; ++n)
            {
                mvwprintw(b_win, 2 + n , C_HALF + 5 + i * X, "%c", pType[num]);
            }
        }
    }
}

void printDefault(WINDOW *b_win)
{

    int x1n24 = C_HALF + 5 + 5 * SEGMENT;
    int x6n19 = C_HALF + 5;
    int x8n17 = C_HALF - 6 - 1 * SEGMENT;
    int x12n13 = C_HALF - 6 - 5 * SEGMENT;

    //print 2
    for (int i = 0; i < 2; ++i)
    {
        //2 X on 1.
        mvwprintw(b_win, DOWN - i, x1n24, P1);

        //2 O on 24.
        mvwprintw(b_win, 2 + i, x1n24, P2);
    }

    //print 5
    for (int i = 0; i < 5; ++i)
    {
        //5 X on 12.
        mvwprintw(b_win, DOWN - i, x12n13, P1);

        //5 X on 19.
        mvwprintw(b_win, 2 + i, x6n19, P1);

        //5 O on 13.
        mvwprintw(b_win, 2 + i, x12n13, P2);

        //5 O on 6.
        mvwprintw(b_win, DOWN - i, x6n19, P2);
    }

    //print 3

    for (int i = 0; i < 3; ++i)
    {
        //3 X on 17.
        mvwprintw(b_win, 2 + i, x8n17, P1);

        //3 O on 8.
        mvwprintw(b_win, DOWN - i, x8n17, P2);
    }
}

void pawnDefault(char pType[], int nPawns[])
{
    for (int i = 0; i < PLACE; ++i) {
        pType[i] = ' ';
    }

    pType[19-1] = pType[17-1] = pType[12-1] = pType[1-1] = P1c;
    pType[6-1] = pType[8-1] = pType[13-1] = pType[24-1] = P2c;

    nPawns[24-1] = nPawns[1-1] = 2;
    nPawns[6-1] = nPawns[13-1] = nPawns[19-1] = nPawns[12-1] = 5;
    nPawns[8-1] = nPawns[17-1] = 3;

}

void printDefaultStateGame(WINDOW *b_win, int nPawns[], char pType[])
{
    pawnDefault(pType, nPawns);
    printDefault(b_win);

    wrefresh(b_win);
}

void diceRoll(WINDOW *b_win, int dc[], int *mvs)
{
    srand(time(nullptr));

    for (int i = 0; i < N_DICES; ++i)
    {
        dc[i] = rand() % MAX_DICE + MIN_DICE;
    }

    mvwprintw(b_win, R_HALF, C_HALF - 5 - 3 * SEGMENT, "%d", dc[0]);
    mvwprintw(b_win, R_HALF, C_HALF - 7 - 2 * SEGMENT, "%d", dc[1]);

    if (dc[0] == dc[1])
    {
        *mvs = 4;
    }

    wrefresh(b_win);

}

void adding(int yNum, const int xNum, WINDOW *b_win, int nPawns[], int num, bool &active1, char pType[], int direction, bool &cap)
{
    char pawn;
    if (active1)
    {
        pawn = P1c;
    }
    else
    {
        pawn = P2c;
    }

    if (!cap)
    {
        yNum += direction * (nPawns[num-1] + 1);
        mvwprintw(b_win, yNum, xNum, "%c", pawn);

        nPawns[num-1]++;
    }
    else
    {
        yNum += direction * nPawns[num-1];
        mvwprintw(b_win, yNum, xNum, "%c", pawn);
    }

    if (nPawns[num-1] == 1 )
    {
        pType[num-1] = pawn;
    }

    wrefresh(b_win);
}

void erasing(int yNum, const int xNum, WINDOW *b_win, int nPawns[], int num, char pType[], int direction)
{
    yNum += direction * nPawns[num-1];
    mvwprintw(b_win, yNum, xNum, "%c", ' ');
    nPawns[num-1]--;

    if (nPawns[num-1] == 0 )
    {
        pType[num-1] = ' ';
    }

    wrefresh(b_win);
}

void markNumberDown(int num, WINDOW *b_win, int nPawns[], bool &active1, char pType[], int num1, bool &cap)
{
    int xNum, i;
    int yNum = DOWN_N;

    // right down (6-1)
    if (num >= 1 && num <= 6)
    {
        i = 6 - num;
        xNum = C_HALF + 5 + i * SEGMENT;
    }

        // left down ( 12 - 7 )
    else
    {
        i = num - 7;
        xNum = C_HALF - 6 - i * SEGMENT;
    }

    //marking number end erasing
    if (num1 == (-1))
    {
        wattron(b_win, A_REVERSE);
        mvwprintw(b_win, yNum , xNum, "%d", num);
        wattroff(b_win, A_REVERSE);

        erasing(yNum, xNum, b_win, nPawns, num, pType, -1);
    }
    else
    {
        adding(yNum, xNum, b_win, nPawns, num, active1, pType, -1, cap);
    }
}

void markNumberUp(int num, WINDOW *b_win, int nPawns[], bool &active1, char pType[], int num1, bool &cap)
{
    int xNum, i;
    int yNum = 1;

    //left up ( 18 - 13 )
    if (num >= 13 && num <= 18)
    {
        i = 18 - num;
        xNum = C_HALF - 6 - i * SEGMENT;
    }

        //right up ( 19-24 )
    else
    {
        i = num - 19;
        xNum = C_HALF + 5 + i * SEGMENT;
    }

    //marking number end erasing
    if (num1 == (-1))
    {
        wattron(b_win, A_REVERSE);
        mvwprintw(b_win, 1 , xNum, "%d", num);
        wattroff(b_win, A_REVERSE);

        erasing(yNum, xNum, b_win, nPawns, num, pType, 1);
    }
    else
    {
        adding(yNum, xNum, b_win, nPawns, num, active1, pType, 1, cap);
    }
}

int checkingMvs(int x, int dc[], int *mvs)
{
    //checking which dice was used
    if(x == dc[0])
    {
        if (*mvs < 3)
        {
            dc[0] = 0;
        }
        return 1;
    }
    else if (x == dc[1])
    {
        if (*mvs < 3)
        {
            dc[1] = 0;
        }
        return 1;
    }
    else if (x == (dc[0] + dc[1]))
    {
        if (*mvs < 3)
        {
            dc[0] = dc[1] = 0;
        }
        --(*mvs);
        return 1;
    }
    else if (x == (3 * dc[0]) && (*mvs == 4 || *mvs == 3 ))
    {
        *mvs = (*mvs)-2;
        dc[0] = 0;
        return 1;
    }
    else if (x == (4 * dc[0]) && *mvs == 4)
    {
        *mvs = (*mvs)-3;
        dc[0] = dc[1] = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int ifGood(bool &active1, int num, int num1, int dc[], const char pType[], int *mvs, const int nPawns[], bool &cap, int bar[])
{
    int x;
    //distance for X player
    if (active1)
    {
        x = (num - num1);

        if (pType[num-1] == P2c && nPawns[num-1] == 1 )
        {
            // pawn is captured and added to the opponent's bar
            cap = true;
            bar[1] += 1;
        }
        else if (pType[num-1] == P2c && nPawns[num-1] != 1)
        {
            return 0;
        }
    }

        //distance for O player
    else
    {
        x = (num1 - num );

        if (pType[num-1] == P1c && nPawns[num-1] == 1 )
        {
            // pawn is captured and added to the opponent's bar
            cap = true;
            bar[0] += 1;
        }
        else if (pType[num-1] == P1c && nPawns[num-1] != 1)
        {
            return 0;
        }
    }

    //skip
    if ( x == 0)
    {
        return 2;
    }

    //checking if move is legal
    int check = checkingMvs(x, dc, mvs);
    if (check == 1 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//board is divided into two sections
void mark(WINDOW *b_win, int nPawns[], bool &active1, char pType[], int num, int num1, bool &cap)
{
    if (num <= 12)
    {
        markNumberDown(num, b_win, nPawns, active1, pType, num1, cap);
    }
    else
    {
        markNumberUp(num, b_win, nPawns, active1, pType, num1, cap);
    }
}

void firstInput(WINDOW *b_win, int nPawns[], bool &active1, char pType[], int num, int *num1)
{
    bool cap = false;
    //checking if it's player pawn
    if ((pType[num-1] == P1c && active1) || (pType[num-1] == P2c && !active1))
    {
        mark(b_win, nPawns, active1, pType, num, *num1, cap);
        *num1 = num;
    }
    else
    {
        mvprintw(1, 1, "NOT YOUR PAWN\n");
        refresh();
    }
}

void secondInput(WINDOW *b_win, int nPawns[], bool &active1, char pType[], int *mvs, int dc[], int num, int *num1, int bar[])
{
    bool cap = false;

    //checking if move is legal
    int check = ifGood(active1, num, *num1, dc, pType, mvs, nPawns, cap, bar);

    //add number
    if (check == 1)
    {
        mark(b_win, nPawns, active1, pType, num, *num1, cap);
        --(*mvs);
    }
        //skip turn
    else if (check == 2)
    {
        mvprintw(1, 1, "SKIPPING TURN\n");
        printNumbers(b_win);
        refresh();
        mark(b_win, nPawns, active1, pType, *num1, *num1, cap);
        *mvs = 0;
    }
    else
    {
        mvprintw(1, 1, "REVERSING MOVE, INCORRECT VALUE\n");
        printNumbers(b_win);
        refresh();
        mark(b_win, nPawns, active1, pType, *num1, *num1, cap);
    }
    *num1 = (-1);
}


void endGame(int dc[], int *num1, int *mvs, WINDOW *b_win, bool &active1, int nPawns[], char pType[] )
{
    int x;
    //calculating distance from base
    if (active1)
    {
        x = (PLACE + 1 - *num1);
    }
    else
    {
        x = *num1;
    }

    bool cap = false;

    //checking if any of the dices (of the sum) is bigger than distance from base
    if (dc[0] >= x || dc[1] >= x || dc[0] + dc[1] >=x || (*mvs == 3 && (dc[0] * 3) >= x) || (*mvs == 4 && (dc[0] * 4) >= x))
    {
        if (*mvs < 3)
        {
            if (dc[0] >= x && dc[1] >= x)
            {
                if(dc[0] > dc[1])
                {
                    dc[1] = 0;
                }
                else
                {
                    dc[0] = 0;
                }
            }
            else if (dc[0] >= x)
            {
                dc[0] = 0;
            }
            else if (dc[1] >= x)
            {
                dc[1] = 0;
            }
            else
            {
                dc[0] = dc[1] = 0;
            }
            --*mvs;
        }
        else
        {
            --*mvs;
        }
    }
    else
    {
        mvprintw(1, 1, "NOT POSSIBLE TO REMOVE PAWN NOW\n");
        mark(b_win, nPawns, active1, pType, *num1, *num1, cap);

    }
    *num1 = (-1);
    printNumbers(b_win);
    refresh();

}
void endState(bool &active1, const char pType[], bool &end, bool &endOfGame, int *mvs)
{
    int temp = *mvs;
    //checking if first player have pawns on home board
    if (active1)
    {
        for (int i = 0; i < PLACE-6; ++i)
        {
            if(pType[i] != 'X')
            {
                end = true;
            }
            else
            {
                end = false;
                break;
            }
        }

        //checking if player won
        for (int i = 0; i < PLACE; ++i)
        {
            if(pType[i] != 'X')
            {
                endOfGame = true;
                *mvs = 0;
            }
            else
            {
                endOfGame = false;
                *mvs = temp;
                break;
            }
        }
    }

        //checking if second player have pawns on home board
    else
    {
        for (int i = 6; i < PLACE; ++i)
        {
            if(pType[i] != 'O')
            {
                end = true;
            }
            else
            {
                end = false;
                break;
            }
        }

        //checking if player won
        for (int i = 0; i < PLACE; ++i)
        {
            if(pType[i] != 'O')
            {
                endOfGame = true;
                *mvs = 0;
            }
            else
            {
                endOfGame = false;
                *mvs = temp;
                break;
            }
        }
    }
}

void pawnAction(WINDOW *b_win, int nPawns[], bool &active1, char pType[], int mvs, int dc[], int bar[], bool &end, bool &endOfGame)
{
    int num1 = (-1);

    //move until player have no moves
    while (mvs != 0)
    {
        //checking if it's end state of game or if player won
        endState(active1, pType, end, endOfGame, &mvs);

        int num;
        std::cin >> num;

        printNumbers(b_win);
        mvprintw(1, 1, "\n");
        refresh();

        if ((num >= 1 && num <= 24) || num == 100)
        {
            if (num1 == (-1))
            {
                //erasing pawn
                firstInput(b_win, nPawns, active1, pType, num, &num1);
            }
            else
            {
                if (end && num == 100)
                {
                    //adding pawn to base
                    endGame(dc, &num1, &mvs, b_win, active1, nPawns, pType);
                }
                else
                {
                    //adding pawn
                    secondInput(b_win, nPawns, active1, pType, &mvs, dc, num, &num1, bar);
                }
            }
        }
        else
        {
            mvprintw(1, 1, "GIVE NUMBER BETWEEN 1 AND 24\n");
            refresh();
        }
    }
}

void changePlayer(bool &active1, int xMax)
{
    if (active1)
    {
        active1 = false;
        mvprintw(3, xMax-20, "Player " P2 " active\n");
        refresh();
    }
    else
    {
        active1 = true;
        mvprintw(3, xMax-20, "Player " P1 " active\n");
        refresh();
    }
}

void saveGameState(const char *filename, const int nPawns[], const char pType[], bool &active1, int bar[])
{
    FILE *file = fopen(filename, "wb");

    fwrite(nPawns, sizeof(int), PLACE, file);
    fwrite(pType, sizeof(char), PLACE, file);
    fwrite(&active1, sizeof(bool), 1, file);
    fwrite(bar, sizeof(int), PLAYERS, file);

    fclose(file);

}

void loadGameState(const char *filename, int nPawns[], char pType[], bool &active1, int bar[])
{
    FILE *file = fopen(filename, "rb");

    fread(nPawns, sizeof(int), PLACE, file);
    fread(pType, sizeof(char), PLACE, file);
    fread(&active1, sizeof(bool), 1, file);
    fread(bar, sizeof(int), PLAYERS, file);

    fclose(file);

}

void dependencies(bool &active1, int dc[N_DICES])
{
    if (dc[0] > dc[1])
    {
        mvprintw(3, 1, "Player " P1 " starts\n");
        active1 = true;
        refresh();
    }
    else if (dc[0] < dc[1])
    {
        mvprintw(3, 1, "Player " P2 " starts\n");
        active1 = false;
        refresh();
    }
    else
    {
        dc[0] = dc[1] = 0;
        mvprintw(3, 1, "Roll one more time");
        refresh();
    }
}

void firstRoll(bool &active1)
{
    int ch;
    int rollState = 0;

    int dc[N_DICES] = {0};

    mvprintw(1, 1, "Press enter to roll die (Player X first)");
    refresh();

    //rolling until dices are not the same
    while (true) {
        ch = getch();
        if (ch == '\n') {
            srand(time(nullptr));
            if (rollState == 0)
            {
                dc[0] = rand() % MAX_DICE + MIN_DICE;
                mvprintw(1, 1, "Player " P1 " die rolled: %d\n", dc[0]);
                refresh();
                rollState = 1;
            }
            else
            {
                dc[1] = rand() % MAX_DICE + MIN_DICE;
                mvprintw(2, 1, "Player " P2 " die rolled: %d\n", dc[1]);
                refresh();
                rollState = 0;

                //checking dependencies between dices
                dependencies(active1, dc);

                //end if two dices are and are not the same
                if (dc[0] != 0 && dc[1] != 0)
                {
                    mvprintw(4, 1, "Press any key to continue..");
                    refresh();
                    getch();
                    clear();
                    break;
                }

            }
        }
    }
}

void barAction(bool &active1, int *mvs, int dc[], char pType[], int nPawns[], WINDOW *b_win, int bar[])
{
    int num1, num;

    if (active1)
    {
        num1 = 0;
    }
    else
    {
        num1 = (PLACE + 1);
    }

    std::cin >> num;

   if (num != 0)
    {
        bool cap = false;
        int check = ifGood(active1, num, num1, dc, pType, mvs, nPawns, cap, bar);
        if (check == 1)
        {
            mark(b_win, nPawns, active1, pType, num, num1, cap);
            --(*mvs);

            if (active1)
            {
                --bar[0];
            }
            else
            {
                --bar[1];
            }
        }
    }
    else
    {
       *mvs = 0;
    }
}

void startGame(WINDOW *b_win, int nPawns[], char pType[], bool &active1, int xMax, int bar[])
{
    clear();
    refresh();

    //who starts first
    firstRoll(active1);

    //printing all default data
    printBoard(b_win);
    printDefaultStateGame(b_win, nPawns, pType);

    if (active1)
    {
        mvprintw(3, xMax-20, "Player " P1 " active\n");
    }
    else
    {
        mvprintw(3, xMax-20, "Player " P2 " active\n");
    }
    refresh();

    saveGameState("gameState.dat", nPawns, pType, active1, bar);
}

void continueGame(WINDOW *b_win, int nPawns[], char pType[], bool &active1, int xMax, int bar[])
{
    clear();
    refresh();
    loadGameState("gameState.dat", nPawns, pType, active1, bar);

    //printing all loaded data
    if (active1)
    {
        mvprintw(3, xMax-20, "Player " P1 " active\n");
    }
    else
    {
        mvprintw(3, xMax-20, "Player " P2 " active\n");
    }
    printBoard(b_win);
    CurrentState(nPawns, pType, b_win);
}

void displayMenu(int xMax, int yMax, WINDOW *b_win, int nPawns[], char pType[], bool &active1, int bar[])
{
    int menuChoice;

    menuChoice = showMenu(xMax, yMax);
    //start
    if (menuChoice == 1)
    {
        startGame(b_win, nPawns, pType, active1, xMax, bar);
    }
        //continue
    else if (menuChoice == 2)
    {
        continueGame(b_win, nPawns, pType, active1, xMax, bar);
    }
        //quit
    else
    {
        endwin();
        exit(EXIT_SUCCESS);
    }
}

void gamePlay(WINDOW *b_win, int nPawns[], char pType[], bool &active1, int bar[], int xMax, bool &endOfGame)
{
    int dc[N_DICES], mvs = 2;
    bool end = false;

    //dice roll for round
    diceRoll(b_win, dc, &mvs);

    //if there is a pawn on the bar erase it first
    while (((active1 && bar[0] != 0) || (!active1 && bar[1] != 0)) && mvs !=0 )
    {
        mvprintw(1, 1, "REMOVE PAWN FROM THE BAR");
        refresh();
        barAction(active1, &mvs, dc, pType, nPawns, b_win, bar);
        mvprintw(1, 1, "\n");
        refresh();
    }

    //move your pawns on the board or erase them
    pawnAction(b_win, nPawns, active1, pType, mvs, dc, bar, end, endOfGame);

    //next player's round
    if (!endOfGame)
    {
        changePlayer(active1, xMax);
    }
    saveGameState("gameState.dat", nPawns, pType, active1, bar);
}

int main()
{
//    system("open -a Terminal Backgammon_Game");

    initscr();
    refresh();
    curs_set(0);
    noecho();
    cbreak();

    char pType[PLACE];
    static int nPawns[PLACE], bar[PLAYERS];
    bool active1 = true, endOfGame = false;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    //initializing board
    WINDOW *b_win;
    b_win = newwin(ROWS, COLS, (yMax/2)-R_HALF, (xMax/2)-C_HALF);

    //displaying menu and choices
    displayMenu(xMax, yMax, b_win, nPawns, pType, active1, bar);

    //gameplay until someone wins
    while(!endOfGame)
    {
        gamePlay(b_win, nPawns, pType, active1, bar, xMax, endOfGame);
    }

    clear();
    //end of game (end screen)
    mvprintw(yMax/2, xMax/2 - 4, "GAME OVER");
    refresh();

    getch();
    delwin(b_win);
    endwin();
    return 0;
}
