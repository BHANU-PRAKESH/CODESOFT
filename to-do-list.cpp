#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Task {
public:
    string description;
    bool isCompleted;

    Task(const string& desc) : description(desc), isCompleted(false) {}
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& task) {
        tasks.push_back(Task(task));
        cout << "Task added successfully." << endl;
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks to display." << endl;
            return;
        }

        cout << "Tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].description << " [" << (tasks[i].isCompleted ? "Completed" : "Pending") << "]" << endl;
        }
    }

    void markTaskAsCompleted(int taskIndex) {
        if (taskIndex < 1 || taskIndex > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }

        tasks[taskIndex - 1].isCompleted = true;
        cout << "Task marked as completed." << endl;
    }

    void removeTask(int taskIndex) {
        if (taskIndex < 1 || taskIndex > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }

        tasks.erase(tasks.begin() + taskIndex - 1);
        cout << "Task removed successfully." << endl;
    }
};

// Main function
int main() {
    ToDoList todoList;
    int choice;
    string task;
    int taskIndex;

    while (true) {
        cout << "\nTo-Do List Manager" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Completed" << endl;
        cout << "4. Remove Task" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character

        switch (choice) {
            case 1:
                cout << "Enter task: ";
                getline(cin, task);
                todoList.addTask(task);
                break;
            case 2:
                todoList.viewTasks();
                break;
            case 3:
                cout << "Enter task number to mark as completed: ";
                cin >> taskIndex;
                todoList.markTaskAsCompleted(taskIndex);
                break;
            case 4:
                cout << "Enter task number to remove: ";
                cin >> taskIndex;
                todoList.removeTask(taskIndex);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}