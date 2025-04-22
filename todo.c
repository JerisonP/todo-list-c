#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

#define MAX_TASKS 100

// Global task list and count
Task task_list[MAX_TASKS];
int task_count = 0;

// Prints the main menu options
void print_menu()
{
  printf("1. Add Task\n");
  printf("2. View Tasks\n");
  printf("3. Mark Task as Done\n");
  printf("4. Delete Task\n");
  printf("5. Save & Exit\n");
}

// Adds a new task to the task list
void add_task()
{
  if (task_count >= MAX_TASKS)
  {
    printf("Task list is full!\n");
    return;
  }

  char desc[100];
  printf("Enter task description: ");

  getchar();                        // Clear leftover newline from previous scanf
  fgets(desc, sizeof(desc), stdin); // Read full line with spaces

  // Remove the newline character from the end
  desc[strcspn(desc, "\n")] = '\0';

  Task new_task;
  new_task.id = task_count + 1;
  strncpy(new_task.description, desc, sizeof(new_task.description));
  new_task.completed = 0;

  task_list[task_count++] = new_task;
  printf("Task added!\n");
}

// Displays all tasks in the list
void view_tasks()
{
  if (task_count == 0)
  {
    printf("No tasks found.\n");
    return;
  }

  printf("\nYour To-Do List:\n");
  for (int i = 0; i < task_count; i++)
  {
    printf("%d. [%c] %s\n",
           task_list[i].id,
           task_list[i].completed ? 'X' : ' ',
           task_list[i].description);
  }
}

// Marks a task as completed by its ID
void mark_task_done()
{
  if (task_count == 0)
  {
    printf("No tasks to mark as done.\n");
    return;
  }

  view_tasks();

  int id;
  printf("Enter the ID of the task to mark as done: ");
  scanf("%d", &id);

  for (int i = 0; i < task_count; i++)
  {
    if (task_list[i].id == id)
    {
      task_list[i].completed = 1;
      printf("Task marked as done!\n");
      return;
    }
  }

  printf("Task with ID %d not found.\n", id);
}

// Deletes a task by its ID
void delete_task()
{
  if (task_count == 0)
  {
    printf("No tasks to delete.\n");
    return;
  }

  view_tasks();

  int id;
  printf("Enter the ID of the task to delete: ");
  scanf("%d", &id);

  for (int i = 0; i < task_count; i++)
  {
    if (task_list[i].id == id)
    {
      // Shift all tasks after this one left by 1
      for (int j = i; j < task_count - 1; j++)
      {
        task_list[j] = task_list[j + 1];
        task_list[j].id = j + 1; // Reset ID to keep order
      }

      task_count--;
      printf("Task deleted!\n");
      return;
    }
  }

  printf("Task with ID %d not found.\n", id);
}

// Saves all tasks to a text file
void save_tasks()
{
  FILE *file = fopen("tasks.txt", "w");
  if (file == NULL)
  {
    printf("Error: Could not open file for writing.\n");
    return;
  }

  for (int i = 0; i < task_count; i++)
  {
    // Write task in the format: id|completed|description
    fprintf(file, "%d|%d|%s\n",
            task_list[i].id,
            task_list[i].completed,
            task_list[i].description);
  }

  fclose(file);
  printf("Tasks saved to file.\n");
}

// Loads tasks from the text file into memory
void load_tasks()
{
  FILE *file = fopen("tasks.txt", "r");
  if (file == NULL)
  {
    // No file yet — not an error
    return;
  }

  char line[200];
  task_count = 0;

  while (fgets(line, sizeof(line), file))
  {
    Task t;
    char desc[100];

    // Parse the line: id|completed|description
    if (sscanf(line, "%d|%d|%[^\n]", &t.id, &t.completed, desc) == 3)
    {
      strncpy(t.description, desc, sizeof(t.description));
      task_list[task_count++] = t;
    }
  }

  fclose(file);
}
