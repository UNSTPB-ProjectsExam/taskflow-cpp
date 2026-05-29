# Interactive Task Flow Manager
### Big Homework 1 – Data Structures and Algorithms

---

## What this project does

This is a console application that simulates a task management system for a student team organizing a university event.

Tasks are added one by one and processed in the order they were received (FIFO). If a task was processed by mistake, it can be restored using the undo function.

---

## How to compile

Make sure all four files are in the same folder:

```
Task.h
Queue.h
Stack.h
main.cpp
```
## Data structures used

- **Queue** (custom implementation in `Queue.h`) — stores waiting tasks. Tasks are added at the back and removed from the front, which gives FIFO order.

- **Stack** (custom implementation in `Stack.h`) — stores processed tasks. The most recently processed task sits on top, so undo is straightforward.

No STL containers were used anywhere in the project.

---

## Menu options

| Option | Description |
|--------|-------------|
| 1 | Add a new task (asks for ID, description, priority) |
| 2 | Process the next waiting task |
| 3 | Undo the last processed task (puts it back at the front of the queue) |
| 4 | Display all tasks currently waiting |
| 5 | Display processed task history (most recent first) |
| 6 | Process the next k tasks at once |
| 7 | Search for any task by its ID |
| 8 | Show statistics (waiting count, processed count, undo count) |
| 0 | Exit |

---

## Validation

The program handles the following invalid inputs:

- Duplicate task ID (rejected with an error message)
- Priority outside the range 1–5 (rejected)
- Trying to process when there are no waiting tasks
- Trying to undo when nothing has been processed yet
- Non-numeric input in menus and fields

---

## Notes

- Task IDs must be positive integers and unique across both waiting and processed tasks.
- Descriptions can contain spaces (read as a full line).
- The undo operation restores the task to the front of the waiting queue, not the back, to preserve the original processing order.
- Statistics track undo operations separately from processed tasks.

---

## Files

| File | Role |
|------|------|
| `Task.h` | Defines the Task structure (id, description, priority) |
| `Queue.h` | Custom queue template class using a linked list |
| `Stack.h` | Custom stack template class using a linked list |
| `main.cpp` | Main program logic and menu interface |
