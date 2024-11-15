#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NUM_TEAMS 5       
#define SQUAD_SIZE 20

void display_menu();
void enroll_club(team_t teams[], int *num_teams);
void add_player(team_t teams[], int num_teams);
void search_update(team_t teams[], int num_teams);
void display_club_statistics(const team_t teams[], int num_teams);
void handle_error(const char *message);

