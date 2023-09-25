#include <iostream>
#include <vector>
#include <string>

using namespace std; // Adding the namespace std

// Class for Task
class Task {
private:
    string title;
    string description;
    bool completed;
    
   

public:
    Task(const string& t, const string& desc)
        : title(t), description(desc), completed(false) {}

    void markAsCompleted() {
        completed = true;
    }
    void display() {
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << (completed ? "Completed" : "Incomplete") << endl;
    }
};

// Class for Task Category
class TaskCategory {
private:
    string name;
    vector<Task> tasks;

public:
    TaskCategory(const string& n) : name(n) {}

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void displayTasks() {
        cout << "Tasks in Category: " << name << endl;
        for ( Task& task : tasks) {
            task.display();
            cout << "-----------------------" << endl;
        }
    }

    string getName() const { 
        return name;
    }
};

// Class for User
class User {
private:
    string username;
    vector<TaskCategory> categories;

public:
    User(const string& uname) : username(uname) {}

    void addCategory(const string& categoryName) {
        categories.emplace_back(categoryName);
    }

    TaskCategory* getCategory(const string& categoryName) {
        for (TaskCategory& category : categories) {
            if (categoryName == category.getName()) {
                return &category;
            }
        }
        return nullptr; // Category not found
    }

    string getUsername() {
        return username;
    }
};

int main() {
    string username;
    
    // Prompt the user to enter their username
    cout << "Enter your username: ";
    cin >> username;
    
    // Create a User
    User user(username);

    // Add task categories
    user.addCategory("Work");
    user.addCategory("Personal");

    // Create tasks and add them to categories
    Task task1("Finish Report", "Complete the quarterly report");
    Task task2("Grocery Shopping", "Buy groceries for the week");

    TaskCategory* workCategory = user.getCategory("Work");
    TaskCategory* personalCategory = user.getCategory("Personal");

    if (workCategory) {
        workCategory->addTask(task1);
    }

    if (personalCategory) {
        personalCategory->addTask(task2);
    }

    // Display tasks in categories
    if (workCategory) {
        workCategory->displayTasks();
    }

    if (personalCategory) {
        personalCategory->displayTasks();
    }

    return 0;
}