#include <stdio.h>
#include <string.h>

#define NUM_TEAMS 5        // Maximum number of teams
#define SQUAD_SIZE 6       // Maximum players per team
#define CURRENT_YEAR 2024  // Current year for age calculation

// Struct for Date of Birth
typedef struct {
    int day;
    int month;
    int year;
} dob_t;

// Struct for Player
typedef struct {
    char name[26];
    int kit_number;
    char position[20];
    dob_t dob;
} player_t;

// Struct for Team
typedef struct {
    char name[21];
    player_t players[SQUAD_SIZE];
    int active_size;
} team_t;

// Function prototypes
int enroll_club(team_t teams[], int num_teams);
int add_player(team_t teams[], int num_teams);
void search_update(team_t teams[], int num_teams);
void display_clubs(const team_t teams[], int num_teams);
float calculate_average_age(const team_t team);
int is_duplicate_club(const team_t teams[], int num_teams, const char club_name[]);
int is_duplicate_player(const player_t players[], int active_size, const char player_name[]);
int is_duplicate_kit_number(const player_t players[], int active_size, int kit_number);
void clear_input_buffer();

int main() {
    team_t teams[NUM_TEAMS] = {0}; // Teams array
    int num_teams = 0;             // Number of enrolled teams
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enroll a Club\n");
        printf("2. Add a Player\n");
        printf("3. Search/Update Player\n");
        printf("4. Display Clubs\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer(); // Clear input buffer after reading choice

        if (choice == 1) {
            num_teams = enroll_club(teams, num_teams);
        } else if (choice == 2) {
            num_teams = add_player(teams, num_teams);
        } else if (choice == 3) {
            search_update(teams,num_teams);
        } else if (choice == 4) {
            display_clubs(teams, num_teams);
        } else if (choice == 5) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Enroll a new club
int enroll_club(team_t teams[], int num_teams) {
    if (num_teams >= NUM_TEAMS) {
        printf("Cannot add more teams. Maximum limit reached.\n");
        return num_teams;
    }

    printf("Enter club name: ");
    char club_name[21];
    fgets(club_name, sizeof(club_name), stdin);
    club_name[strcspn(club_name, "\n")] = 0; // Remove newline

    if (is_duplicate_club(teams, num_teams, club_name)) {
        printf("Club name already exists. Try again.\n");
        return num_teams;
    }

    strcpy(teams[num_teams].name, club_name);
    teams[num_teams].active_size = 0;
    printf("Club enrolled successfully!\n");
    return num_teams + 1; // Increment number of teams
}

// Add a player to a club
int add_player(team_t teams[], int num_teams) {
    if (num_teams == 0) {
        printf("No clubs enrolled yet. Enroll a club first.\n");
        return num_teams;
    }

    // Display club options
    printf("Select a club to add a player:\n");
    for (int i = 0; i < num_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }

    int club_choice;
    printf("Enter your choice: ");
    scanf("%d", &club_choice);
    clear_input_buffer();

    if (club_choice < 1 || club_choice > num_teams) {
        printf("Invalid club choice. Try again.\n");
        return num_teams;
    }

    int club_index = club_choice - 1;
    if (teams[club_index].active_size >= SQUAD_SIZE) {
        printf("Cannot add more players. Squad is full.\n");
        return num_teams;
    }

    // Add player details
    int current_size = teams[club_index].active_size;

    printf("Enter player name: ");
    char player_name[26];
    fgets(player_name, sizeof(player_name), stdin);
    player_name[strcspn(player_name, "\n")] = 0;

    if (is_duplicate_player(teams[club_index].players, current_size, player_name)) {
        printf("Player name already exists. Try again.\n");
        return num_teams;
    }

    strcpy(teams[club_index].players[current_size].name, player_name);

    printf("Enter kit number: ");
    int kit_number;
    scanf("%d", &kit_number);
    clear_input_buffer();

    // Check for duplicate kit number
    if (is_duplicate_kit_number(teams[club_index].players, current_size, kit_number)) {
        printf("Kit number %d already exists. Try again.\n", kit_number);
        return num_teams;
    }

    teams[club_index].players[current_size].kit_number = kit_number;

    printf("Enter position: ");
    fgets(teams[club_index].players[current_size].position, sizeof(teams[club_index].players[current_size].position), stdin);
    teams[club_index].players[current_size].position[strcspn(teams[club_index].players[current_size].position, "\n")] = 0;

    printf("Enter date of birth (dd mm yyyy): ");
    scanf("%d %d %d", &teams[club_index].players[current_size].dob.day, &teams[club_index].players[current_size].dob.month, &teams[club_index].players[current_size].dob.year);
    clear_input_buffer();

    teams[club_index].active_size++;
    printf("Player added successfully!\n");
    return num_teams;
}

void search_update(team_t teams[], int num_teams) {
    if (num_teams == 0) {
        printf("No clubs enrolled yet.\n");
        return;
    }

    printf("Search by:\n");
    printf("1. Player Name\n");
    printf("2. Kit Number\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();

    int found = 0; // Flag to indicate if a match was found

    if (choice == 1) {
        // Search by player name
        char search_name[26];
        printf("Enter player name to search: ");
        fgets(search_name, sizeof(search_name), stdin);
        search_name[strcspn(search_name, "\n")] = '\0'; // Remove newline

        for (int i = 0; i < num_teams; i++) {
            for (int j = 0; j < teams[i].active_size; j++) {
                if (strcasecmp(search_name, teams[i].players[j].name) == 0) {
                    found = 1;
                    printf("\nMatch found in team '%s':\n", teams[i].name);
                    printf("Name: %s, Kit: %d, Position: %s, DOB: %02d/%02d/%04d\n",
                           teams[i].players[j].name,
                           teams[i].players[j].kit_number,
                           teams[i].players[j].position,
                           teams[i].players[j].dob.day,
                           teams[i].players[j].dob.month,
                           teams[i].players[j].dob.year);

                    // Prompt for updates
                    printf("\nUpdate player details:\n");

                  // Update player details
				printf("Enter new name (or press Enter to keep current): ");
					char new_name[26];
					fgets(new_name, sizeof(new_name), stdin);
						if (strcspn(new_name, "\n") > 0) {
    						new_name[strcspn(new_name, "\n")] = '\0';  // Remove newline character
    						strcpy(teams[i].players[j].name, new_name); // Update player name if new name is entered
}						 else {
   							 printf("Name kept as: %s\n", teams[i].players[j].name); // Keep current name if Enter is pressed
}

// Update player kit number
		printf("Enter new kit number (or press Enter to keep current): ");
			char new_kit_number_str[10]; // Buffer for kit number as string
				fgets(new_kit_number_str, sizeof(new_kit_number_str), stdin);

// Check if user pressed Enter without entering anything
				if (strcspn(new_kit_number_str, "\n") > 0) {
   				 int new_kit_number = atoi(new_kit_number_str); // Convert string to integer
    // Check if the entered kit number is valid (greater than 0)
    if (new_kit_number > 0) {
        teams[i].players[j].kit_number = new_kit_number;
    } else {
        printf("Invalid kit number. Keeping current kit number: %d\n", teams[i].players[j].kit_number);
    }
} else {
    printf("Kit number kept as: %d\n", teams[i].players[j].kit_number); // Keep current kit number if Enter is pressed
}

// Update player position (same as before)
printf("Enter new position (or press Enter to keep current): ");
char new_position[20];
fgets(new_position, sizeof(new_position), stdin);
if (strcspn(new_position, "\n") > 0) {
    new_position[strcspn(new_position, "\n")] = '\0'; // Remove newline character
    strcpy(teams[i].players[j].position, new_position); // Update position if new one is entered
} else {
    printf("Position kept as: %s\n", teams[i].players[j].position); // Keep current position if Enter is pressed
}

// Update player date of birth (DOB)
printf("Enter new DOB (dd mm yyyy or press Enter to keep current): ");
int new_day, new_month, new_year;
int result = scanf("%d %d %d", &new_day, &new_month, &new_year);
clear_input_buffer();

if (result == 3) {
    // If valid input is provided (day, month, and year)
    teams[i].players[j].dob.day = new_day;
    teams[i].players[j].dob.month = new_month;
    teams[i].players[j].dob.year = new_year; // Update DOB if new values are entered
} else {
    // If user presses Enter without entering anything, keep the current DOB
    printf("DOB kept as: %02d/%02d/%04d\n", teams[i].players[j].dob.day, teams[i].players[j].dob.month, teams[i].players[j].dob.year);
}

                    printf("\nPlayer details updated successfully!\n");
                }
            }
        }
    } else if (choice == 2) {
        // Search by kit number
        printf("Enter kit number to search: ");
        int search_kit_number;
        scanf("%d", &search_kit_number);
        clear_input_buffer();

        for (int i = 0; i < num_teams; i++) {
            for (int j = 0; j < teams[i].active_size; j++) {
                if (teams[i].players[j].kit_number == search_kit_number) {
                    found = 1;
                    printf("\nMatch found in team '%s':\n", teams[i].name);
                    printf("Name: %s, Kit: %d, Position: %s, DOB: %02d/%02d/%04d\n",
                           teams[i].players[j].name,
                           teams[i].players[j].kit_number,
                           teams[i].players[j].position,
                           teams[i].players[j].dob.day,
                           teams[i].players[j].dob.month,
                           teams[i].players[j].dob.year);

                    // Similar update prompts as above (reuse code for updates)
                    printf("\nUpdate player details:\n");

                    // Name update
                    printf("Enter new name (or press Enter to keep current): ");
char new_name[26];
fgets(new_name, sizeof(new_name), stdin);
if (strcspn(new_name, "\n") > 0) {
    new_name[strcspn(new_name, "\n")] = '\0';  // Remove newline character
    strcpy(teams[i].players[j].name, new_name); // Update player name if new name is entered
} else {
    printf("Name kept as: %s\n", teams[i].players[j].name); // Keep current name if Enter is pressed
}

// Update player kit number
printf("Enter new kit number (or press Enter to keep current): ");
char new_kit_number_str[10]; // Buffer for kit number as string
fgets(new_kit_number_str, sizeof(new_kit_number_str), stdin);

// Check if user pressed Enter without entering anything
if (strcspn(new_kit_number_str, "\n") > 0) {
    int new_kit_number = atoi(new_kit_number_str); // Convert string to integer
    // Check if the entered kit number is valid (greater than 0)
    if (new_kit_number > 0) {
        teams[i].players[j].kit_number = new_kit_number;
    } else {
        printf("Invalid kit number. Keeping current kit number: %d\n", teams[i].players[j].kit_number);
    }
} else {
    printf("Kit number kept as: %d\n", teams[i].players[j].kit_number); // Keep current kit number if Enter is pressed
}

// Update player position (same as before)
printf("Enter new position (or press Enter to keep current): ");
char new_position[20];
fgets(new_position, sizeof(new_position), stdin);
if (strcspn(new_position, "\n") > 0) {
    new_position[strcspn(new_position, "\n")] = '\0'; // Remove newline character
    strcpy(teams[i].players[j].position, new_position); // Update position if new one is entered
} else {
    printf("Position kept as: %s\n", teams[i].players[j].position); // Keep current position if Enter is pressed
}

// Update player date of birth (DOB)
printf("Enter new DOB (dd mm yyyy or press Enter to keep current): ");
int new_day, new_month, new_year;
int result = scanf("%d %d %d", &new_day, &new_month, &new_year);
clear_input_buffer();

if (result == 3) {
    // If valid input is provided (day, month, and year)
    teams[i].players[j].dob.day = new_day;
    teams[i].players[j].dob.month = new_month;
    teams[i].players[j].dob.year = new_year; // Update DOB if new values are entered
} else {
    // If user presses Enter without entering anything, keep the current DOB
    printf("DOB kept as: %02d/%02d/%04d\n", teams[i].players[j].dob.day, teams[i].players[j].dob.month, teams[i].players[j].dob.year);
}

                    printf("\nPlayer details updated successfully!\n");
                }
            }
        }
    }

    if (!found) {
        printf("No matching players found.\n");
    }
}



// Display clubs and their players
void display_clubs(const team_t teams[], int num_teams) {
    if (num_teams == 0) {
        printf("No clubs enrolled yet.\n");
        return;
    }

    for (int i = 0; i < num_teams; i++) {
        printf("\nTeam: %s\n", teams[i].name);
        printf("Players:\n");
        for (int j = 0; j < teams[i].active_size; j++) {
            player_t p = teams[i].players[j];
            printf("Name: %s, Kit: %d, Position: %s, DOB: %02d/%02d/%04d\n",
                   p.name, p.kit_number, p.position, p.dob.day, p.dob.month, p.dob.year);
        }
        printf("Average Age: %.2f years\n", calculate_average_age(teams[i]));
    }
}

// Calculate average age of players in a team
float calculate_average_age(const team_t team) {
    if (team.active_size == 0) return 0;

    int total_age = 0;
    for (int i = 0; i < team.active_size; i++) {
        total_age += CURRENT_YEAR - team.players[i].dob.year;
    }
    return (float) total_age / team.active_size;
}

// Check for duplicate club name
int is_duplicate_club(const team_t teams[], int num_teams, const char club_name[]) {
    for (int i = 0; i < num_teams; i++) {
        if (strcmp(teams[i].name, club_name) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check for duplicate player name
int is_duplicate_player(const player_t players[], int active_size, const char player_name[]) {
    for (int i = 0; i < active_size; i++) {
        if (strcmp(players[i].name, player_name) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check for duplicate kit number
int is_duplicate_kit_number(const player_t players[], int active_size, int kit_number) {
    for (int i = 0; i < active_size; i++) {
        if (players[i].kit_number == kit_number) {
            return 1;
        }
    }
    return 0;
}

// Clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}