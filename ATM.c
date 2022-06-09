#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000 // Max number of characters scanned at once

typedef struct menu Menu;
struct menu
{
    char *prompt;  // Prompt shown to user
    int opt_count; // Number of options available to user
    char **opts;   // Array of available options
};

// Allocates memory for and defines a menu with a prompt and a set of options
Menu *create_menu(char *prompt, char **opts, int opt_count)
{
    // Allocate memory for menu struct
    Menu *new_menu = malloc(sizeof(Menu));

    // Allocate memory for and set the prompt
    new_menu->prompt = malloc(sizeof(char) * (strlen(prompt) + 1));
    strcpy(new_menu->prompt, prompt);

    // Set the opt_count
    new_menu->opt_count = opt_count;

    // Allocate memory for and set all the provided prompts
    new_menu->opts = calloc(opt_count, sizeof(char *));
    for (int i = 0; i < opt_count; i++)
    {
        new_menu->opts[i] = malloc(sizeof(char) * (strlen(opts[i]) + 1));
        strcpy(new_menu->opts[i], opts[i]);
    }

    return new_menu;
}

// Frees any allocated memory for the provided menu
void free_menu(Menu *menu)
{
    // Frees all opts and the opts array
    for (int i = 0; i < menu->opt_count; i++)
    {
        free(menu->opts[i]);
    }
    free(menu->opts);

    free(menu->prompt);

    free(menu);
}

void print_menu(const Menu menu)
{
    printf("%s\n", menu.prompt);

    for (int i = 0; i < menu.opt_count; i++)
    {
        printf("%3i. %s\n", i + 1, menu.opts[i]);
    }

    printf(">> ");
}

// Checks if a given string is a number
int is_number(char *str)
{
    int result = 1; // 0 for false, 1 for true

    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            result = 0;
            break;
        }

        i++;
    }

    return result;
}

// Presents the menu to the user to pick an option. The picked option is returned.
// This will repeat until the user provides a valid option > 0 and <= menu.opt_count
int ask_user(const Menu menu)
{
    int picked_opt = 0;
    char buffer[MAX_LENGTH] = {};

    while (1)
    {
        print_menu(menu);

        fgets(buffer, MAX_LENGTH, stdin);

        printf(" buffer = %s", buffer);
        if (is_number(buffer))
        {
            int temp = atoi(buffer);

            printf("temp = [%d]\n", temp);

            if (temp <= menu.opt_count && temp > 0)
            {
                picked_opt = temp;
                break;
            }
            else
            {
                printf("\nOut of range. Please try again.\n\n");
            }
        }
        else
        {
            printf("\nNot a number. Please try again.\n\n");
        }
    }

    return picked_opt;
}

int main(void)
{
    char *main_menu_opts[2] = {"First opt", "Second opt"};
    Menu *main_menu = create_menu("Please select an option below:", main_menu_opts, 2);

    int picked = ask_user(*main_menu);
    printf("You picked (%d) %s\n", picked, main_menu_opts[picked - 1]);

    free_menu(main_menu);

    return EXIT_SUCCESS;
}
