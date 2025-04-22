Project: Command Line To-Do List in C
--------------------------------------

Folder Structure:
```text
todo/
├── main.c      ← The entry point. Shows the menu and loops forever.
├── todo.h      ← Declarations of structs and functions.
├── todo.c      ← Definitions of functions that actually do the work.
└── tasks.txt   ← File used to save/load tasks to disk.
```
Key Concepts:
```text
• structs     — lets us define our own data type (Task) to bundle values together
• file I/O    — read/write data from and to files using fopen/fprintf/sscanf/fgets
• menus       — terminal-based user interface using printf/scanf
• memory      — tasks are stored in RAM as an array of structs during the session
• persistence — tasks are written to and read from disk so they survive restarts
```
Data Structures:

```c
typedef struct {
    int id;                   // unique task ID
    char description[100];   // string for task name
    int completed;           // 1 if done, 0 if not
} Task;
```

Each task is saved to the file like this:

    id|completed|description

Functions (defined in todo.c):

Absolutely! Here's your entire section with **inline C function names and keywords properly formatted using backticks**, so it looks clean and readable on GitHub:

---

### Functions (defined in `todo.c`):

• `void print_menu()`  
  - Displays the menu to the user with numbered options.  
  - Called at the start of every loop in `main`.  
  - Doesn't require input or return a value.  

• `void add_task()`  
  - Checks if task list is full.  
  - Prompts user for task description using `fgets()`.  
  - Removes newline using `strcspn()`.  
  - Creates a `Task` struct with the description and stores it in `task_list[]`.  
  - Increments `task_count` to reflect the new task.  

• `void view_tasks()`  
  - Loops through `task_list[]` and prints each task with:  
    - ID number  
    - `[X]` if completed, `[ ]` if not (using ternary operator)  
    - Description  
  - If no tasks exist, it prints a message and exits early.  

• `void mark_task_done()`  
  - Asks the user for the ID of the task to mark as complete.  
  - Loops through `task_list[]` to find the matching ID.  
  - If found, sets `completed = 1` for that task.  
  - If not found, nothing happens.  

• `void delete_task()`  
  - Asks the user for the ID of the task to delete.  
  - Searches for the task with that ID.  
  - Once found, shifts all later tasks left by 1 to "delete" the gap.  
  - Resets task IDs to maintain order.  
  - Decrements `task_count` to reflect the deletion.  

• `void save_tasks()`  
  - Opens `"tasks.txt"` in write mode.  
  - Loops through `task_list[]` and writes each task in format:  
    `id|completed|description`  
  - Uses `fprintf()` to write to file.  
  - Closes the file at the end.  

• `void load_tasks()`  
  - Opens `"tasks.txt"` in read mode.  
  - Uses `fgets()` to read each line (up to 200 characters).  
  - Parses ID, completed status, and description using `sscanf()`.  
  - Copies values into a new `Task` struct and appends to `task_list[]`.  
  - Rebuilds task list into memory at program startup.  

---

### Important C Functions & Concepts:

• `fgets(desc, size, stdin)`  
  - Reads a full line of user input (including spaces) from the keyboard.  

• `getchar()`  
  - Reads and clears leftover newline character from previous `scanf` calls.  

• `strcspn(string, "\n")`  
  - Returns the index of the newline character `'\n'` so it can be replaced with `'\0'`.  

• `sscanf(line, "%d|%d|%[^\n]", ...)`  
  - Parses values from a string:  
    - `%d` reads integers (for `id` and `completed`)  
    - `%[^\n]` reads everything until newline (for `description`)  

• `strncpy(dst, src, size)`  
  - Copies strings safely up to a limit, preventing overflow.  

• `fprintf(file, "%d|%d|%s", ...)`  
  - Writes formatted data to a file (like `printf` but to disk).  

• `fopen("file", "r"/"w")`  
  - Opens a file:  
    - `"r"` = read  
    - `"w"` = write (overwrites if it exists)  

• `fclose(file)`  
  - Closes a file to flush output and release the file handle.  

---

### Main Program Flow (in `main.c`):

1. Load saved tasks using `load_tasks()`  
2. Show menu with `print_menu()`  
3. Get user input (with `scanf`)  
4. Use `switch`-`case` to run the chosen function:  
    - `add_task()`  
    - `view_tasks()`  
    - `mark_task_done()`  
    - `delete_task()`  
5. On exit (option 5), save tasks using `save_tasks()`
