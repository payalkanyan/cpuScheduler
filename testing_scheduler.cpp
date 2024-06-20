#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <iomanip> // for setw and setprecision

using namespace std;

// ANSI escape sequences for text colors
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_MAGENTA "\033[35m"
#define ANSI_COLOR_CYAN "\033[36m"
#define ANSI_COLOR_BOLD "\033[1m"

// Task struct to hold task details
struct Task {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int remaining_time;
    int priority;

    Task(int _id, int _arrival, int _burst, int _priority)
        : id(_id), arrival_time(_arrival), burst_time(_burst),
          completion_time(0), waiting_time(0), remaining_time(_burst), priority(_priority) {}
};

// Comparator for sorting tasks by arrival time
bool arrival_time_comparator(const Task& a, const Task& b) {
    return a.arrival_time < b.arrival_time;
}

// First Come First Serve (FCFS) Scheduling
void fcfs(vector<Task>& tasks) {
    // Sort tasks by arrival time
    sort(tasks.begin(), tasks.end(), arrival_time_comparator);

    int current_time = 0;
    for (auto& task : tasks) {
        if (current_time < task.arrival_time) {
            current_time = task.arrival_time;
        }
        task.completion_time = current_time + task.burst_time;
        task.waiting_time = current_time - task.arrival_time;
        current_time += task.burst_time;
    }
}

// Shortest Job First (SJF) Scheduling
void sjf(vector<Task>& tasks) {
    // Sort tasks by arrival time (SJF works on arrival time first)
    sort(tasks.begin(), tasks.end(), arrival_time_comparator);

    int current_time = 0;
    int completed = 0;
    vector<bool> is_completed(tasks.size(), false);

    while (completed < tasks.size()) {
        int shortest_job = -1;
        int min_burst_time = INT_MAX;

        for (int i = 0; i < tasks.size(); ++i) {
            if (!is_completed[i] && tasks[i].arrival_time <= current_time) {
                if (tasks[i].burst_time < min_burst_time) {
                    min_burst_time = tasks[i].burst_time;
                    shortest_job = i;
                }
            }
        }

        if (shortest_job == -1) {
            current_time++;
            continue;
        }

        Task& current_task = tasks[shortest_job];
        current_task.completion_time = current_time + current_task.burst_time;
        current_task.waiting_time = current_time - current_task.arrival_time;
        current_time += current_task.burst_time;
        is_completed[shortest_job] = true;
        completed++;
    }
}

// Priority Scheduling
void priority_scheduling(vector<Task>& tasks) {
    // Sort tasks by arrival time (Priority works on arrival time first)
    sort(tasks.begin(), tasks.end(), arrival_time_comparator);

    int current_time = 0;
    int completed = 0;
    vector<bool> is_completed(tasks.size(), false);

    while (completed < tasks.size()) {
        int highest_priority_task = -1;
        int max_priority = INT_MIN;

        for (int i = 0; i < tasks.size(); ++i) {
            if (!is_completed[i] && tasks[i].arrival_time <= current_time) {
                if (tasks[i].priority > max_priority) {
                    max_priority = tasks[i].priority;
                    highest_priority_task = i;
                }
            }
        }

        if (highest_priority_task == -1) {
            current_time++;
            continue;
        }

        Task& current_task = tasks[highest_priority_task];
        current_task.completion_time = current_time + current_task.burst_time;
        current_task.waiting_time = current_time - current_task.arrival_time;
        current_time += current_task.burst_time;
        is_completed[highest_priority_task] = true;
        completed++;
    }
}

// Round Robin (RR) Scheduling
void round_robin(vector<Task>& tasks, int quantum) {
    // Sort tasks by arrival time (RR works on arrival time first)
    sort(tasks.begin(), tasks.end(), arrival_time_comparator);

    queue<Task*> task_queue;
    int current_time = 0;
    int task_index = 0;

    while (task_index < tasks.size() || !task_queue.empty()) {
        // Add tasks arriving at the current time to the queue
        while (task_index < tasks.size() && tasks[task_index].arrival_time <= current_time) {
            task_queue.push(&tasks[task_index]);
            task_index++;
        }

        if (!task_queue.empty()) {
            Task* current_task = task_queue.front();
            task_queue.pop();

            // Process current task
            int execution_time = min(quantum, current_task->remaining_time);
            current_task->completion_time = current_time + execution_time;
            current_task->waiting_time += current_time - current_task->arrival_time;
            current_task->remaining_time -= execution_time;
            current_time += execution_time;

            // If task not completed, push back to queue
            if (current_task->remaining_time > 0) {
                task_queue.push(current_task);
            }
        } else {
            current_time++;
        }
    }
}

// Print function for displaying scheduling results with colors
void print_results(const vector<Task>& tasks, const string& title, const string& color) {
    cout << color << ANSI_COLOR_BOLD << "------ " << title << " ------" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "ID\tArrival\tBurst\tPriority\tCompletion\tWaiting" << ANSI_COLOR_RESET << endl;
    for (const auto& task : tasks) {
        cout << task.id << "\t"
             << task.arrival_time << "\t"
             << task.burst_time << "\t"
             << task.priority << "\t\t"
             << task.completion_time << "\t\t"
             << task.waiting_time << endl;
    }
    cout << endl;
}

int main() {
    vector<Task> tasks = {
        {1, 0, 8, 2},
        {2, 1, 4, 1},
        {3, 2, 9, 4},
        {4, 3, 5, 3}
    };

    int choice;
    int quantum;

    do {
        cout << ANSI_COLOR_BOLD << "Select scheduling algorithm:" << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_YELLOW << "1. First Come First Serve (FCFS)" << endl;
        cout << "2. Shortest Job First (SJF)" << endl;
        cout << "3. Priority Scheduling" << endl;
        cout << "4. Round Robin (RR)" << endl;
        cout << "0. Exit" << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_CYAN << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                fcfs(tasks);
                print_results(tasks, "FCFS Scheduling", ANSI_COLOR_GREEN);
                break;
            case 2:
                sjf(tasks);
                print_results(tasks, "SJF Scheduling", ANSI_COLOR_BLUE);
                break;
            case 3:
                priority_scheduling(tasks);
                print_results(tasks, "Priority Scheduling", ANSI_COLOR_MAGENTA);
                break;
            case 4:
                cout << ANSI_COLOR_CYAN << "Enter time quantum for Round Robin: ";
                cin >> quantum;
                round_robin(tasks, quantum);
                print_results(tasks, "Round Robin Scheduling", ANSI_COLOR_YELLOW);
                break;
            case 0:
                cout << ANSI_COLOR_BOLD << "Exiting program..." << ANSI_COLOR_RESET << endl;
                break;
            default:
                cout << ANSI_COLOR_RED << "Invalid choice. Please enter a valid option." << ANSI_COLOR_RESET << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
