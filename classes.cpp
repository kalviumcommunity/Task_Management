#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class Task {
private:
    string title;
    string description;
    bool completed;
    int priority;
    string deadline;

public:
    Task(const string& t, const string& desc, const string& dl, int prio)
        : title(t), description(desc), completed(false), priority(prio), deadline(dl) {}

    void markAsCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    void display() const {
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Priority: " << priority << endl;
        cout << "Deadline: " << deadline << endl;
        cout << "Status: " << (completed ? "Completed" : "Incomplete") << endl;
    }

    bool setDeadline(const string& newDeadline) {
        regex pattern("^(0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])-[0-9]{4}$");
        if (regex_match(newDeadline, pattern)) {
            deadline = newDeadline;
            return true;
        } else {
            return false;
        }
    }
};

class TaskCategory {
private:
    string name;
    vector<Task> tasks;

public:
    TaskCategory(const string& n) : name(n) {}

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void displayTasks() const {
        cout << "Tasks in Category: " << name << endl;
        for (const Task& task : tasks) {
            task.display();
            cout << "-----------------------" << endl;
        }
    }

    string getName() const {
        return name;
    }
};

class User {
private:
    string username;
    vector<TaskCategory> categories;

public:
    User(const string& uname) : username(uname) {}

    void addCategory(const string& categoryName) {
        categories.push_back(TaskCategory(categoryName));
    }

    TaskCategory* getCategory(const string& categoryName) {
        for (TaskCategory& category : categories) {
            if (categoryName == category.getName()) {
                return &category;
            }
        }
        return nullptr;
    }

    string getUsername() const {
        return username;
    }
};

int main() {
    string username;

    cout << "Enter your username: ";
    cin >> username;

    User user(username);

    user.addCategory("Work");

    int numTasks;
    cout << "Enter the number of tasks you want to add: ";
    cin >> numTasks;

    char option;
    for (int i = 0; i < numTasks; ++i) {
        string title, description, deadline;
        int priority;

        cout << "Enter task details for Work:" << endl;

        cout << "Title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Description: ";
        getline(cin, description);

        cout << "Priority (0-5): ";
        cin >> priority;

        bool validDeadline = false;

        do {
            cout << "Deadline (DD-MM-YYYY): ";
            cin >> deadline;

            Task task(title, description, deadline, priority);
            validDeadline = task.setDeadline(deadline);

            if (!validDeadline) {
                cout << "Invalid deadline format. Please use DD-MM-YYYY format." << endl;
            }

            TaskCategory* workCategory = user.getCategory("Work");
            workCategory->addTask(task);

            cout << "Is this task completed? (Y/N): ";
            cin >> option;
            if (option == 'Y' || option == 'y') {
                task.markAsCompleted();
            }
        } while (!validDeadline);
    }

    TaskCategory* workCategory = user.getCategory("Work");
    if (workCategory) {
        workCategory->displayTasks();
    }

    return 0;
}
