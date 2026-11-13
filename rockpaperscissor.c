/*
   Rock Paper Scissors (Console Game in C)
   File handling: 
   scores.txt  -> total wins, losses and draws (saved between runs)
   history.txt -> record of every round played
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SCORE_FILE "scores.txt"
#define HISTORY_FILE "history.txt"

typedef struct {
    int wins;
    int losses;
    int draws;
} Score;

const char *choiceName(int c) {
    if (c == 1) return "Rock";
    if (c == 2) return "Paper";
    return "Scissors";
}

// ---------- File handling ---------- //
void loadScore(Score *s) {
    FILE *f = fopen(SCORE_FILE, "r");
    s->wins = s->losses = s->draws = 0;
    if (f == NULL) return;               // first run: no file yet //
    fscanf(f, "%d %d %d", &s->wins, &s->losses, &s->draws);
    fclose(f);
}

void saveScore(const Score *s) {
    FILE *f = fopen(SCORE_FILE, "w");
    if (f == NULL) {
        printf("Could not save score!\n");
        return;
    }
    fprintf(f, "%d %d %d\n", s->wins, s->losses, s->draws);
    fclose(f);
}

void addHistory(int user, int comp, const char *result) {
    FILE *f = fopen(HISTORY_FILE, "a");  /* append mode */
    if (f == NULL) return;
    char tm[32];
    time_t now = time(NULL);
    strftime(tm, sizeof(tm), "%d-%m-%Y %H:%M", localtime(&now));
    fprintf(f, "%s | You: %s | Computer: %s | %s\n",
            tm, choiceName(user), choiceName(comp), result);
    fclose(f);
}

void showHistory(void) {
    FILE *f = fopen(HISTORY_FILE, "r");
    char line[200];
    if (f == NULL) {
        printf("\nNo history yet. Play a round first!\n");
        return;
    }
    printf("\n------ Match History ------\n");
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    fclose(f);
}

void resetData(Score *s) {
    s->wins = s->losses = s->draws = 0;
    remove(SCORE_FILE);
    remove(HISTORY_FILE);
    printf("\nAll saved data has been deleted.\n");
}

// ---------- Game logic ---------- //
int getComputerChoice(void) {
    return rand() % 3 + 1;               // 1=Rock, 2=Paper, 3=Scissors //
}

// returns 1 if user wins, -1 if computer wins, 0 for draw //
int decideWinner(int user, int comp) {
    if (user == comp) return 0;
    if ((user == 1 && comp == 3) ||
        (user == 2 && comp == 1) ||
        (user == 3 && comp == 2)) return 1;
    return -1;
}

void showScore(const Score *s) {
    printf("\n------ Score ------\n");
    printf("Wins:   %d\n", s->wins);
    printf("Losses: %d\n", s->losses);
    printf("Draws:  %d\n", s->draws);
}

void playRound(Score *s) {
    int user, comp, result;

    printf("\n1. Rock\n2. Paper\n3. Scissors\nEnter your choice: ");
    if (scanf("%d", &user) != 1) {
        while (getchar() != '\n');       // clear bad input //
        printf("Invalid input! Enter a number.\n");
        return;
    }
    if (user < 1 || user > 3) {
        printf("Invalid choice! Pick 1, 2 or 3.\n");
        return;
    }

    comp = getComputerChoice();
    result = decideWinner(user, comp);

    printf("\nYou chose:      %s\n", choiceName(user));
    printf("Computer chose: %s\n", choiceName(comp));

    if (result == 1) {
        printf("Result: You win!\n");
        s->wins++;
        addHistory(user, comp, "Win");
    } else if (result == -1) {
        printf("Result: Computer wins!\n");
        s->losses++;
        addHistory(user, comp, "Loss");
    } else {
        printf("Result: It's a draw!\n");
        s->draws++;
        addHistory(user, comp, "Draw");
    }
    saveScore(s);                        // save after every round //
}

int main(void) {
    Score score;
    int option;

    srand((unsigned)time(NULL));
    loadScore(&score);                   // restore old data //

    printf("=== ROCK PAPER SCISSORS ===\n");
    printf("Saved score loaded -> Wins: %d | Losses: %d | Draws: %d\n",
           score.wins, score.losses, score.draws);

    do {
        printf("\n------ MENU ------\n");
        printf("1. Play a round\n");
        printf("2. View score\n");
        printf("3. View history\n");
        printf("4. Reset all data\n");
        printf("5. Exit\n");
        printf("Enter option: ");

        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            option = 0;
        }

        switch (option) {
            case 1: playRound(&score); break;
            case 2: showScore(&score); break;
            case 3: showHistory(); break;
            case 4: resetData(&score); break;
            case 5: printf("\nThanks for playing. Goodbye!\n"); break;
            default: printf("\nInvalid option. Try again.\n");
        }
    } while (option != 5);

    return 0;
}
