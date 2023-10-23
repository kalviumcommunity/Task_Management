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

    static int totalTasksCompleted;
    static int totalTasks;

public:
    Task(const string& t, const string& desc, const string& dl, int prio)
        : title(t), description(desc), completed(false), priority(prio), deadline(dl) {
        totalTasks++;  // Increment the total task count
    }

    void markAsCompleted() {
        this->completed = true;
        totalTasksCompleted++;
    }

    void markAsIncomplete() {
        this->completed = false;
        totalTasksCompleted--;
    }

    bool isCompleted() const {
        return completed;
    }

    static int getTotalTasksCompleted() {
        return totalTasksCompleted;
    }

    static int getTotalTasks() {
        return totalTasks;
    }

    void display() {
        cout << "Title: " << this->title << endl;
        cout << "Description: " << this->description << endl;
        cout << "Priority: " << this->priority << endl;
        cout << "Deadline: " << this->deadline << endl;
        cout << "Status: " << (this->completed ? "Completed" : "Incomplete") << endl;
    }

    bool setDeadline(const string& newDeadline) {
        regex pattern("^(0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])-[0-9]{4}$");
        if (regex_match(newDeadline, pattern)) {
            this->deadline = newDeadline;
            return true;
        } else {
            return false;
        }
    }
};

int Task::totalTasksCompleted = 0;
int Task::totalTasks = 0;

class TaskCategory {
private:
    string name;
    vector<Task*> tasks;

public:
    TaskCategory(const string& n) : name(n) {}

    void addTask(Task* task) {
        tasks.push_back(task);
    }

    void displayTasks() {
        cout << "Tasks in Category: " << name << endl;
        for (Task* task : tasks) {
            task->display();
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
    vector<TaskCategory*> categories;

public:
    User(const string& uname) : username(uname) {}

    void addCategory(const string& categoryName) {
        categories.push_back(new TaskCategory(categoryName));
    }

    TaskCategory* getCategory(const string& categoryName) {
        for (TaskCategory* category : categories) {
            if (categoryName == category->getName()) {
                return category;
            }
        }
        return nullptr;
    }

    string getUsername() {
        return username;
    }

    ~User() {
        for (TaskCategory* category : categories) {
            delete category;
        }
    }
};

int main() {
    string username;

    cout << "Enter your username: ";
    cin >> username;

    User* user = new User(username);

    user->addCategory("Work");
    user->addCategory("Personal");

    int numTasks; // Number of tasks to add
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

            validDeadline = Task("", "", "", 0).setDeadline(deadline);

            if (!validDeadline) {
                cout << "Invalid deadline format. Please use DD-MM-YYYY format." << endl;
            }
        } while (!validDeadline);

        TaskCategory* workCategory = user->getCategory("Work");
        Task* task1 = new Task(title, description, deadline, priority);

        if (workCategory) {
            workCategory->addTask(task1);
        }

        cout << "Is this task completed? (Y/N): ";
        cin >> option;
        if (option == 'Y' || option == 'y') {
            task1->markAsCompleted();
        }
    }

    TaskCategory* workCategory = user->getCategory("Work");
    if (workCategory) {
        workCategory->displayTasks();
    }

    cout << "Total tasks completed: " << Task::getTotalTasksCompleted() << endl;


    delete user;

    return 0;
}

