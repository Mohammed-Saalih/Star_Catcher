#include<iostream>
#include<vector>
#include<conio.h>
#include<windows.h>
#include<random>

using namespace std;

int main()
{
    // creating an Arena to play
    string Arena[18][18];

    // starting position of the pawn
    int XPos = 5, YPos = 5;

    // initializing the score to 0
    int Score = 0;

    // vectors that can be used to generate stars
    vector<int> StarX;
    vector<int> StarY;

    //vectors that can be used to generate bombs
    vector<int> BombX;
    vector<int> BombY;

    // co ordinates of the fruit that is going to spawn
    int SXPos, SYPos,BXPos,BYPos;

    // initially setting the input to null
    char input;

    // initializing the Arena with spaces
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 18; j++)
            {
                Arena[i][j] = " ";
            }
        if (i >= 1 && i <= 16)
        {
            StarX.push_back(i);
            StarY.push_back(i);
            BombX.push_back(i);
            BombY.push_back(i);
        }
    }

    // initialize random number generator
    random_device rd;
    mt19937 gen(rd());

    // define the range for indices
    uniform_int_distribution<> distr1(0, StarX.size() - 1);
    uniform_int_distribution<> distr2(0, StarY.size() - 1);

    uniform_int_distribution<> distr3(0, BombX.size() - 1);
    uniform_int_distribution<> distr4(0, BombY.size() - 1);

    // setting boundary for the Arena
    for (int i = 0; i < 18; i++)
    {
        Arena[i][0] = "#";
        Arena[0][i] = "#";
        Arena[17][i] = "#";
        Arena[i][17] = "#";
    }

    // Spawn the first fruit at a random position
    do
    {
        SXPos = StarX[distr1(gen)];
        SYPos = StarY[distr2(gen)];
    } while (SXPos == XPos && SYPos == YPos);  // Ensure fruit doesn't spawn at player's position

    do
    {
        BXPos = BombX[distr3(gen)];
        BYPos = BombY[distr4(gen)];
    } while(BXPos == SXPos && BYPos == SYPos && BXPos == XPos && BYPos == YPos);

    Arena[XPos][YPos] = "\033[32mO\033[0m";
    Arena[SXPos][SYPos] = "\033[33m*\033[0m";
    Arena[BXPos][BYPos] = "\033[31m@\033[0m";

    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            cout << Arena[i][j] << " ";
        }
            cout << "\n";
    }
    cout << "Score: " << Score << endl;
    while (true)
    {

        // Wait for a key press before updating the game
        if (_kbhit())
        {
            input = _getch(); // getting the character pressed without
            // clear the screen so that the previously printed Arena is discarded
            system("cls");
            if (input == 'q')
            {
                break; // exit the game if 'q' is pressed
            }

            // erase the current position of the pawn
            Arena[XPos][YPos] = " ";

            // move pawn based on input
            if (input == 'w' && Arena[XPos - 1][YPos] != "#")
            {
                XPos--; // move up
            }
            else if (input == 's' && Arena[XPos + 1][YPos] != "#")
            {
                XPos++; // move down
            }
            else if (input == 'a' && Arena[XPos][YPos - 1] != "#")
            {
                YPos--; // move left
            }
            else if (input == 'd' && Arena[XPos][YPos + 1] != "#")
            {
                YPos++; // move right
            }
            if(XPos == BXPos && BYPos == YPos)
            {
                system("cls");
                cout<<"Game Over!!"<<endl;
                cout<<"Score:"<<Score;
                break;
            }
            // checking if player collects the fruit
            if (XPos == SXPos && YPos == SYPos)
            {
                cout << "\a";
                Score++;
                Arena[BXPos][BYPos] = " ";
                // regenerate the fruit at a new poistion
                do
                {
                    SXPos = StarX[distr1(gen)];
                    SYPos = StarY[distr2(gen)];
                } while (SXPos == XPos && SYPos == YPos); // ensures fruit doesn't spawn at player's position

                do
                {
                    BXPos = BombX[distr3(gen)];
                    BYPos = BombY[distr4(gen)];
                } while(BXPos == SXPos && BYPos == SYPos && BXPos == XPos && BYPos == YPos); //ensures bomb doesn't spawn on both fruti and pawn

                Arena[SXPos][SYPos] = "\033[33m*\033[0m"; // place the new fruit
                Arena[BXPos][BYPos] = "\033[31m@\033[0m"; // place the new bomb
            }

            // update the position of pawn
            Arena[XPos][YPos] = "\033[32mO\033[0m";

            // print the Arena
            for (int i = 0; i < 18; i++)
            {
                for (int j = 0; j < 18; j++)
                {
                    cout << Arena[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "Score: " << Score << endl;
        }
    }
}
