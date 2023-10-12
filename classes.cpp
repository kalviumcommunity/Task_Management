#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std; // Adding the namespace std

// Class for Task
class Task {
private:
    string title;
    string description;
    bool completed;
    int priority;
    string deadline;

   
public:
    Task(){
          cout<<"Constructor of task class runned" << endl;
    }
     Task(const string& t, const string& desc, const string& dl, int priority = 0)
        : title(t), description(desc), completed(false), deadline(dl), priority(priority) {}


        void markAsCompleted() {
        this->completed = true;
    }

    void markAsIncomplete() {
        this->completed = false;
    }


     bool isCompleted() const {
        return completed;
    }
    void display() {
        cout << "Title: " << this->title << endl;
        cout << "Description: " << this->description << endl;
        cout << "Priority: " << this->priority << endl;
        cout << "Deadline: " << this->deadline << endl;
        cout << "Status: " << (this->completed ? "Completed" : "Incomplete") << endl;
    }


 // Validate and set the deadline
    bool setDeadline(const string& newDeadline) {
        // Define a regex pattern for DD-MM-YYYY format
        regex pattern("^(0[1-9]|[1-2][0-9]|3[0-1])-(0[1-9]|1[0-2])-[0-9]{4}$");

        if (regex_match(newDeadline, pattern)) {
            this->deadline = newDeadline;
            return true; // Deadline updated successfully
        } else {
            return false; // Invalid deadline format
        }
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
   
// display all the tasks
    void displayTasks() {
        cout << "Tasks in Category: " << name << endl;
        for ( Task& task : tasks) {
            task.display();
            cout << "-----------------------" << endl;
        }
    }
// returns the name of the category here
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
    User(const string& uname) : username(uname) { }

    void addCategory(const string& categoryName) {
        categories.emplace_back(categoryName);
    }

     ~ User(){
        cout<<"destructor run" << endl;
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

    // Input tasks interactively
    cout << "Enter task details for Work:" << endl;
    string title, description, deadline;
    int priority;

    cout << "Title: ";
    cin.ignore(); // Clear newline character
    getline(cin, title);

    cout << "Description: ";
    getline(cin, description);

    // Input priority with validation
   do {
    cout << "Priority (0-5): ";
    cin >> priority;

    if (cin.fail()) {
        cout << "Invalid input. Please enter a numeric value." << endl;
        cin.clear(); // Clear error flags

        // Discard characters until a newline is encountered
        while (cin.get() != '\n') {
            continue; // Keep discarding characters
        }
    } else if (priority < 0 || priority > 5) {
        cout << "Priority must be between 0 and 5." << endl;
    } else {
        break; // Exit the loop when valid input is provided
    }
} while (true);



    bool validDeadline = false;
    
    // Input deadline with validation
   do {
    cout << "Deadline (DD-MM-YYYY): ";
    cin >> deadline;

    validDeadline = Task().setDeadline(deadline);

    if (!validDeadline) {
        cout << "Invalid deadline format. Please use DD-MM-YYYY format." << endl;
        cin.clear(); // Clear error flags

        // Clear input buffer until a newline character is encountered
        while (cin.get() != '\n') {
            continue; // Keep discarding characters
        }
    }
} while (!validDeadline);



    TaskCategory* workCategory = user.getCategory("Work");
    Task task1(title, description, deadline, priority);

    if (workCategory) {
        workCategory->addTask(task1);
    }

       // Display tasks in the "Work" category after status changes
    if (workCategory) {
        workCategory->displayTasks();
    }


    return 0;
}