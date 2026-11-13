# Rock Paper Scissors (C Console Game)

A menu-driven Rock Paper Scissors game written in C. Scores and match
history are saved to files, so your old data is still there when you
run the game again.

## Features
- Play against the computer (random choice)
- Tracks wins, losses and draws
- Score is saved after every round
- Full match history with date and time
- Reset option to delete all saved data
- Input validation for wrong choices

## File Handling
- `scores.txt`: total wins, losses and draws (fopen, fscanf, fprintf)
- `history.txt`: record of every round (append mode, fgets)
- `remove()` is used to delete the data files on reset
- Both files are created automatically when the game is played

## C Concepts Used
Functions, structures, pointers, switch-case, loops, file handling,
string functions, random numbers (rand/srand), input validation

## How to Run
Open a terminal in the project folder:

    gcc main.c -o game
    ./game

On Windows:

    gcc main.c -o game.exe
    game.exe

## Menu
1. Play a round
2. View score
3. View history
4. Reset all data
5. Exit