#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <iomanip>
#include <sstream> // For JSON output

using namespace std;

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

bool arrival_time_comparator(const Task& a, const Task& b) {
    return a.arrival_time < b.arrival_time;
}
void fcfs(vector<Task>& tasks) {
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

void sjf(vector<Task>& tasks) {
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

void priority_scheduling(vector<Task>& tasks) {
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

void round_robin(vector<Task>& tasks, int quantum) {
    sort(tasks.begin(), tasks.end(), arrival_time_comparator);
    queue<Task*> task_queue;
    int current_time = 0;
    int task_index = 0;

    while (task_index < tasks.size() || !task_queue.empty()) {
        while (task_index < tasks.size() && tasks[task_index].arrival_time <= current_time) {
            task_queue.push(&tasks[task_index]);
            task_index++;
        }

        if (!task_queue.empty()) {
            Task* current_task = task_queue.front();
            task_queue.pop();
            int execution_time = min(quantum, current_task->remaining_time);
            current_task->completion_time = current_time + execution_time;
            current_task->waiting_time += current_time - current_task->arrival_time;
            current_task->remaining_time -= execution_time;
            current_time += execution_time;

            if (current_task->remaining_time > 0) {
                task_queue.push(current_task);
            }
        } else {
            current_time++;
        }
    }
}

string to_json(const vector<Task>& tasks) {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < tasks.size(); ++i) {
        const auto& task = tasks[i];
        ss << "{"
           << "\"id\":" << task.id << ","
           << "\"arrival_time\":" << task.arrival_time << ","
           << "\"burst_time\":" << task.burst_time << ","
           << "\"priority\":" << task.priority << ","
           << "\"completion_time\":" << task.completion_time << ","
           << "\"waiting_time\":" << task.waiting_time
           << "}";
        if (i < tasks.size() - 1) ss << ",";
    }
    ss << "]";
    return ss.str();
}

int main(int argc, char* argv[]) {
    vector<Task> tasks = {
        {1, 0, 8, 2},
        {2, 1, 4, 1},
        {3, 2, 9, 4},
        {4, 3, 5, 3}
    };

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <algorithm> [quantum]" << endl;
        return 1;
    }

    string algorithm = argv[1];
    if (algorithm == "fcfs") {
        fcfs(tasks);
    } else if (algorithm == "sjf") {
        sjf(tasks);
    } else if (algorithm == "priority") {
        priority_scheduling(tasks);
    } else if (algorithm == "rr") {
        if (argc < 3) {
            cerr << "Round Robin requires a quantum value." << endl;
            return 1;
        }
        int quantum = stoi(argv[2]);
        round_robin(tasks, quantum);
    } else {
        cerr << "Invalid algorithm" << endl;
        return 1;
    }

    cout << to_json(tasks) << endl;
    return 0;
}