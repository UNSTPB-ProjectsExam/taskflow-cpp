#include <iostream>
#include <string>
#include <limits>
#include "Queue1.h"
#include "Task1.h"
#include "Stack1.h"

using namespace std;


Queue<Task> waitingTasks;
Stack<Task> processedTasks;
int undoCount = 0;

void printTask(const Task& t) {
    cout << "ID: " << t.id
         << ", Description: " << t.description
         << ", Priority: " << t.priority << "\n";
}

//here is checking if id is waiting
bool idExistsInQueue(int id) {
    auto it = waitingTasks.iterator();
    while (it.hasNext()) {
        Task t = it.next();
        if (t.id == id) 
		return true;
    }
    return false;
}

// and here checks if id in processed stack
bool idExistsInStack(int id) {
    auto it = processedTasks.iterator();
    while (it.hasNext()) {
        Task t = it.next();
        if (t.id == id) 
		return true;
    }
    return false;
}

// ...........................

void addTask() {
    int id, priority;
    string desc;

    cout << "Enter task ID: ";
    cin >> id;
    if (cin.fail() || id <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. ID must be a positive integer.\n";
        return;
    }
    cin.ignore();

    if (idExistsInQueue(id) || idExistsInStack(id)) {
        cout << "Error: a task with ID " << id << " already exists.\n";
        return;
    }

    cout << "Enter description: ";
    getline(cin, desc);

    cout << "Enter priority (1-5): ";
    cin >> priority;
    if (cin.fail() || priority < 1 || priority > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid priority. Priority must be between 1 and 5.\n";
        return;
    }
    cin.ignore();

    Task t(id, desc, priority);
    waitingTasks.enqueue(t);
    cout << "Task added successfully:\n";
    printTask(t);
}
//............ 
void Gonext() {
    if (waitingTasks.isEmpty()) {
        cout << "No waiting tasks to process.\n";
        return;
    }
    Task t = waitingTasks.dequeue();
    processedTasks.push(t);
    cout << "Processed task:\n";
    printTask(t);
}
//..........................
void undo() {
    if (processedTasks.isEmpty()) {
        cout << "No processed task available for undo.\n";
        return;
    }
    Task t = processedTasks.pop();
    //our queue is FIFO only
    // so for rebuilding we put t in a temp queue, then re-enqueue all waiting
    Queue<Task> tempQueue;
    tempQueue.enqueue(t);
    while (!waitingTasks.isEmpty()) {
        tempQueue.enqueue(waitingTasks.dequeue());
    }
    while (!tempQueue.isEmpty()) {
        waitingTasks.enqueue(tempQueue.dequeue());
    }

    undoCount++;
    cout << "Undo successful. Restored task:\n";
    printTask(t);
}
//...............................................
void waiting() {
    if (waitingTasks.isEmpty()) {
        cout << "No waiting tasks.\n";
        return;
    }
    cout << "Waiting tasks:\n";
    auto it = waitingTasks.iterator();
    while (it.hasNext()) {
        printTask(it.next());
    }
}
//...........................................
void history() {
    if (processedTasks.isEmpty()) {
        cout << "No processed tasks.\n";
        return;
    }
    cout << "Processed task history:\n";
    auto it = processedTasks.iterator();
    while (it.hasNext()) {
        printTask(it.next());
    }
}
//.............................................
void nextK() {
    int k;
    cout << "Enter number of tasks to process (k): ";
    cin >> k;
    if (cin.fail() || k <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. k must be a positive integer.\n";
        return;
    }
    //allows the user to process multiple tasks (up to k), at once
    cin.ignore();

    if (waitingTasks.isEmpty()) {
        cout << "No waiting tasks to process.\n";
        return;
    }

    cout << "Requested to process " << k << " task(s).\n\n";
    int done = 0;
    while (done < k) {
        if (waitingTasks.isEmpty()) {
            cout << "No more waiting tasks.\n";
            break;
        }
        Task t = waitingTasks.dequeue();
        processedTasks.push(t);
        cout << "Processed task:\n";
        printTask(t);
        cout << "\n";
        done++;
    }
}
//.............................................
void Id() {
	//a search function that looks for a specific id in st and que. 
    int id;
    cout << "Enter task ID to search: ";
    cin >> id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }
    cin.ignore();


    auto qit = waitingTasks.iterator();
    while (qit.hasNext()) {
        Task t = qit.next();
        if (t.id == id) {
            cout << "Task found (status: waiting):\n";
            printTask(t);
            return;
        }
    }

  
    auto sit = processedTasks.iterator();
    while (sit.hasNext()) {
        Task t = sit.next();
        if (t.id == id) {
            cout << "Task found (status: processed):\n";
            printTask(t);
            return;
        }
    }

    cout << "Task not found.\n";
}
//...............................................
void stats() {
    cout << "Statistics:\n";
    cout << "Waiting tasks: " << waitingTasks.size() << "\n";
    cout << "Processed tasks: " << processedTasks.size() << "\n";
    cout << "Successful undo operations: " << undoCount << "\n";
}
//................................................
void printMenu() {
    cout << "\n==============================\n";
    cout << " Interactive Task Flow Manager\n";
    cout << "==============================\n";
    cout << "1. Add new task\n";
    cout << "2. Work on next task\n";
    cout << "3. Undo last processed task\n";
    cout << "4. Show me waiting tasks\n";
    cout << "5. Show me processed task history\n";
    cout << "6. Process next k tasks\n";
    cout << "7. Searching by id\n";
    cout << "8. Show statistics\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

int main() {
    int choice;

    do {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        cout << "\n";

        switch (choice) {
            case 1: addTask();  break;
            case 2: Gonext();   break;
            case 3: undo();     break;
            case 4: waiting();  break;
            case 5: history();  break;
            case 6: nextK();    break;
            case 7: Id();       break;
            case 8: stats();    break;
            case 0: cout << "Program terminated.\n"; break;
            default: cout << "Invalid entering. Please choose from the menu.\n"; break;
        }

    } while (choice != 0);

    return 0;
}