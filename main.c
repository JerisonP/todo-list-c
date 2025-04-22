#include <stdio.h>  // For printf, scanf
#include <stdlib.h> // For exit()
#include "todo.h"   // Declarations for our task functions

int main()
{
  int choice;

  // Load tasks from file into memory at startup
  load_tasks();

  // Main menu loop — runs forever until user chooses to exit
  while (1)
  {
    print_menu(); // Show the available options
    printf("Enter your choice: ");
    scanf("%d", &choice); // Get user input

    // Branch to the correct action based on user's choice
    switch (choice)
    {
    case 1:
      add_task(); // Add a new task
      break;
    case 2:
      view_tasks(); // View all tasks
      break;
    case 3:
      mark_task_done(); // Mark a task as completed
      break;
    case 4:
      delete_task(); // Delete a task
      break;
    case 5:
      save_tasks(); // Save all tasks to file
      printf("Saving and exiting...\n");
      exit(0); // End the program cleanly
    default:
      printf("Invalid choice. Try again.\n");
    }

    printf("\n"); // Add a blank line between loops for better UX
  }

  return 0;
}
