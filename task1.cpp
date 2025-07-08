#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc, bool comp = false) {
        description = desc;
        completed = comp;
    }

    string toString() const {
        return (completed ? "1" : "0") + string("|") + description;
    }
};

class ToDoList {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    ToDoList() {
        loadFromFile();
    }

    void addTask(const string& desc) {
        tasks.push_back(Task(desc));
        cout << "Task added.\n";
        saveToFile();
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << " No tasks available.\n";
            return;
        }
        cout << "\n Your To-Do List:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". [" << (tasks[i].completed ? "" : "") << "] " << tasks[i].description << "\n";
        }
        cout << endl;
    }

    void markCompleted(int index) {
        if (!isValid(index)) return;
        tasks[index].completed = true;
        cout << " Task marked as completed.\n";
        saveToFile();
    }

    void deleteTask(int index) {
        if (!isValid(index)) return;
        tasks.erase(tasks.begin() + index);
        cout << "? Task deleted.\n";
        saveToFile();
    }

    void editTask(int index, const string& newDesc) {
        if (!isValid(index)) return;
        tasks[index].description = newDesc;
        cout << "? Task updated.\n";
        saveToFile();
    }

    void clearAll() {
        tasks.clear();
        cout << " All tasks cleared.\n";
        saveToFile();
    }

private:
    bool isValid(int index) const {
        if (index < 0 || index >= tasks.size()) {
            cout << "Invalid task number.\n";
            return false;
        }
        return true;
    }

    void saveToFile() {
        ofstream out(filename);
        for (const Task& t : tasks) {
            out << t.toString() << "\n";
        }
        out.close();
    }

    void loadFromFile() {
        ifstream in(filename);
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string status, desc;
            getline(ss, status, '|');
            getline(ss, desc);
            tasks.push_back(Task(desc, status == "1"));
        }
        in.close();
    }
};

int main() {
    ToDoList todo;
    int choice;
    string desc;
    int index;

    do {
        cout << "\n --- TO-DO LIST MENU ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Edit Task\n";
        cout << "5. Delete Task\n";
        cout << "6. Clear All Tasks\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, desc);
                todo.addTask(desc);
                break;
            case 2:
                todo.viewTasks();
                break;
            case 3:
                cout << "Enter task number to mark completed: ";
                cin >> index;
                todo.markCompleted(index - 1);
                break;
            case 4:
                cout << "Enter task number to edit: ";
                cin >> index;
                cin.ignore();
                cout << "Enter new description: ";
                getline(cin, desc);
                todo.editTask(index - 1, desc);
                break;
            case 5:
                cout << "Enter task number to delete: ";
                cin >> index;
                todo.deleteTask(index - 1);
                break;
            case 6:
                todo.clearAll();
                break;
            case 7:
                cout << " Exiting. Goodbye!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 7);

    return 0;
}
