#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPT_LENGTH 250 // Max size of menu option including null terminator

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
    new_menu->opts = calloc(opt_count, sizeof(char*));
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
    free (menu->opts);

    free(menu->prompt);

    free(menu);
}

int print_menu(Menu menu) {
    printf("%s\n", menu.prompt);
    
    for (int i = 0; i < menu.opt_count; i++) {
        printf("%3i. %s\n", i, menu.opts[i]);
    }

    printf(">> ");
}

int main(void)
{
    char *main_menu_opts[2] = {"First opt", "Second opt"};
    Menu *main_menu = create_menu("Please select an option below:", main_menu_opts, 2);

    print_menu(*main_menu);

    free_menu(main_menu);

    return EXIT_SUCCESS;
}
