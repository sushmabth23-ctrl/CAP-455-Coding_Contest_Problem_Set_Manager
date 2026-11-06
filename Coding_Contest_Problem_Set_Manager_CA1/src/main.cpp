#include <iostream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

class Problem {
private:
    int problemId;
    string title;
    string topic;
    string difficulty;
    string statement;

    static int totalProblems;

public:
    Problem() {
        this->problemId = 0;
        this->title = "";
        this->topic = "";
        this->difficulty = "";
        this->statement = "";
    }

    // Inline member function
    inline int getProblemId() const {
        return this->problemId;
    }

    // Create/store problem details in the object
    void setDetails(int id, const string& t, const string& top,
                    const string& diff, const string& desc) {
        this->problemId = id;
        this->title = t;
        this->topic = top;
        this->difficulty = diff;
        this->statement = desc;
        totalProblems++;
    }

    // Static member function
    static int getTotalProblems() {
        return totalProblems;
    }

    // Friend function can access private data members
    friend void displayProblem(const Problem& p);
};

int Problem::totalProblems = 0;

// Friend function definition
void displayProblem(const Problem& p) {
    cout << "\n----------------------------------------\n";
    cout << "Problem ID   : " << p.problemId << '\n';
    cout << "Title        : " << p.title << '\n';
    cout << "Topic        : " << p.topic << '\n';
    cout << "Difficulty   : " << p.difficulty << '\n';
    cout << "Statement    : " << p.statement << '\n';
    cout << "----------------------------------------\n";
}

const int MAX_PROBLEMS = 100;

bool isValidDifficulty(const string& difficulty) {
    return difficulty == "Beginner" ||
           difficulty == "Intermediate" ||
           difficulty == "Advanced";
}

int findProblem(const Problem problems[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (problems[i].getProblemId() == id) {
            return i;
        }
    }
    return -1;
}

void createProblem(Problem problems[], int& count) {
    if (count >= MAX_PROBLEMS) {
        cout << "\nStorage is full. Cannot add more problems.\n";
        return;
    }

    int id;
    string title, topic, difficulty, statement;

    cout << "\nEnter Problem ID (positive number): ";
    if (!(cin >> id) || id <= 0) {
        cout << "Invalid ID. Please enter a positive integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Unique key validation
    if (findProblem(problems, count, id) != -1) {
        cout << "This Problem ID already exists. Duplicate IDs are not allowed.\n";
        return;
    }

    cout << "Enter problem title: ";
    getline(cin, title);
    if (title.empty()) {
        cout << "Title cannot be empty.\n";
        return;
    }

    cout << "Enter topic (e.g., Arrays, Strings, Sorting): ";
    getline(cin, topic);
    if (topic.empty()) {
        cout << "Topic cannot be empty.\n";
        return;
    }

    cout << "Enter difficulty (Beginner/Intermediate/Advanced): ";
    getline(cin, difficulty);
    if (!isValidDifficulty(difficulty)) {
        cout << "Invalid difficulty. Use Beginner, Intermediate or Advanced.\n";
        return;
    }

    cout << "Enter problem statement: ";
    getline(cin, statement);
    if (statement.empty()) {
        cout << "Problem statement cannot be empty.\n";
        return;
    }

    problems[count].setDetails(id, title, topic, difficulty, statement);
    count++;
    cout << "\nProblem created successfully.\n";
}

void readAllProblems(const Problem problems[], int count) {
    if (count == 0) {
        cout << "\nNo problems are available yet.\n";
        return;
    }

    cout << "\n===== ALL CODING PROBLEMS =====\n";
    // Pointer used to access the array of objects
    const Problem* ptr = problems;
    for (int i = 0; i < count; i++) {
        displayProblem(*(ptr + i));
    }
    cout << "Total problems: " << Problem::getTotalProblems() << '\n';
}

void searchProblem(const Problem problems[], int count) {
    int id;
    cout << "\nEnter Problem ID to search: ";
    if (!(cin >> id)) {
        cout << "Invalid ID input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProblem(problems, count, id);
    if (index == -1) {
        cout << "Problem not found.\n";
    } else {
        const Problem* ptr = &problems[index];
        displayProblem(*ptr);
    }
}

int main() {
    Problem problems[MAX_PROBLEMS]; // Array of objects
    int count = 0;
    int choice;

    do {
        cout << "\n====== CODING CONTEST PROBLEM SET MANAGER ======\n";
        cout << "1. Create a problem\n";
        cout << "2. Read all problems\n";
        cout << "3. Search problem by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                createProblem(problems, count);
                break;
            case 2:
                readAllProblems(problems, count);
                break;
            case 3:
                searchProblem(problems, count);
                break;
            case 4:
                cout << "Thank you for using the Problem Set Manager.\n";
                break;
            default:
                cout << "Invalid choice. Select 1 to 4.\n";
        }
    } while (choice != 4);

    return 0;
}
