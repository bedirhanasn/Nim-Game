// related libraries added
#include <stdio.h>
#include <stdlib.h>
// 25 is defined as the max number of matchsticks
#define MAX_MATCHSTICKS 25
// Board and Player structures defined here
typedef struct {
    int num_matchsticks;
} Board;
typedef struct {
    char name[20];
} Player;
// board initially created and the maximum number of matchsticks is loaded
void init_board(Board *board) {
    board->num_matchsticks = MAX_MATCHSTICKS;
}
// this function allows the user to enter a name
void init_players(Player *human_player) {
    printf("Enter your name: ");
    scanf("%s", human_player->name);
}
// display_board function returns the number of remaining matchsticks 
void display_board(Board *board) {
    printf("Number of matchsticks left: %d\n", board->num_matchsticks);
    for (int i = 0; i < board->num_matchsticks; i++) {
        printf("|");
    }
    printf("\n");
}
// player makes move and removes the specified number of matchsticks from the board
void player_move(Board *board, Player *player) {
    int num_to_remove;
    printf("%s's turn. Enter the number of matchsticks to remove (1-3): ", player->name);
    scanf("%d", &num_to_remove);
    while (num_to_remove < 1 || num_to_remove > 3 || num_to_remove > board->num_matchsticks) {
        printf("Invalid move. Please enter a number between 1 and 3: ");
        scanf("%d", &num_to_remove);
    }
    board->num_matchsticks -= num_to_remove;
}
// calculate the nim-sum value of the board (helps to computer for winning)
int calculate_nim_sum(Board *board) {
    int nim_sum = 0;
    for (int i = 1; i <= board->num_matchsticks; i *= 2) {
        if ((board->num_matchsticks & i) != 0) {
            nim_sum ^= i;
        }
    }
    return nim_sum;
}
 // calculate the number of matchsticks the computer should remove based on the current number of matchsticks left
int computer_move(Board *board) {
    int nim_sum = calculate_nim_sum(board);
    int num_to_remove;
    if (nim_sum != 0) {
        // if nim_sum is not zero, remove enough matchsticks to make it zero
        for (int i = 1; i <= 3; i++) {
            if ((nim_sum ^ i) < nim_sum) {
                num_to_remove = i;
                break;
            }
        }
    } else {
        // if nim_sum is zero, remove a random number of matchsticks
        num_to_remove = rand() % 3 + 1;
    }
    // print the number of matchsticks the computer removes and update the board
    printf("The computer removes %d matchstick(s).\n", num_to_remove);
    board->num_matchsticks -= num_to_remove;
    return num_to_remove;
}
// main method
int main() {
    Board board;
    Player human_player;
    Player computer_player = {"Computer"};
    int turn = 0;
    // initialize the board and print a welcome message
    init_board(&board);
    printf("Welcome to the Nim game!\n");
    // ask the player for their name
    init_players(&human_player);
    // start the game loop
    while (board.num_matchsticks > 0) { 
        // display the current state of the board
        display_board(&board);
        // if it's the human player's turn, ask them to make a move
        if (turn % 2 == 0) {
            player_move(&board, &human_player);
        // if it's the computer player's turn, make a move for the computer
        } else {
            computer_move(&board);
        }
        // increment the turn counter
        turn++;
    }
    // determine the winner based on the last player who made a move
    if (turn % 2 == 0) {
        printf("%s wins!\n", computer_player.name);
    } else {
        printf("%s wins!\n", human_player.name);
    }
    return 0;
}