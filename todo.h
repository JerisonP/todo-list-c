#ifndef TODO_H
#define TODO_H

typedef struct
{
  int id;
  char description[100];
  int completed;
} Task;

void print_menu();
void add_task();
void view_tasks();
void mark_task_done();
void delete_task();
void save_tasks();
void load_tasks();

#endif