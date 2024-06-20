## CPU SCHEDULER
 This project is a CPU scheduler implemented in C++ and served using a FastAPI backend. It supports multiple scheduling algorithms including Round Robin (RR), Shortest Job First (SJF), First-Come, First-Served (FCFS), and Priority Scheduling.

# How to run
Follow these steps to set up and run the CPU scheduler locally:

1. Compile the C++ code:
`g++ -o cpu_scheduler cpu_scheduler.cpp`
2. Install the necessary Python packages:
`pip install fastapi uvicorn`
3. Start the FastAPI server:
 `uvicorn main:app --reload`
4. Open your HTML file in the browser:
Click on Go Live in your code editor (such as VS Code) to open the HTML file in the localhost.

## Scheduling Algorithms
### Round Robin
Round Robin scheduling algorithm is designed for time-sharing systems. It assigns a fixed time unit per process and cycles through them. This approach ensures that all processes get an equal share of CPU time, making it fair and efficient for interactive systems. However, it can result in high context switching overhead.

### Shortest Job First
Shortest Job First scheduling algorithm selects the process with the smallest execution time to run next. This minimizes the average waiting time for processes, making it efficient for batch processing. There are two variants of SJF: non-preemptive, where the CPU is not taken away from a running process, and preemptive (also known as Shortest Remaining Time First, SRTF), where the CPU can be taken away if a new process arrives with a shorter burst time.

### First Come, First Served
First-Come, First-Served scheduling algorithm processes requests in the order they arrive in the ready queue. It is simple and easy to implement. However, it can lead to the "convoy effect," where shorter processes wait for a longer process to finish, resulting in increased average waiting time and lower CPU efficiency.

### Priority Scheduling
Priority Scheduling algorithm assigns a priority to each process, and the CPU is allocated to the process with the highest priority. Processes with the same priority are scheduled using FCFS. This method can be preemptive or non-preemptive. While it is efficient in handling tasks with different urgency levels, it can lead to starvation, where lower priority processes may never get executed if high priority processes continue to arrive.

### Internal working of the project 
The CPU Scheduling project is a comprehensive tool that demonstrates various CPU scheduling algorithms through a command-line interface. The key components of the project are implemented in C++, Python, and HTML. Here's a brief overview of the internal workings of the project, focusing on the core algorithm implementation in the cpu_scheduler.cpp file.

#### Core Algorithm Implementation (cpu_scheduler.cpp)
The cpu_scheduler.cpp file is responsible for implementing the four main CPU scheduling algorithms: First-Come, First-Served (FCFS), Shortest Job First (SJF), Priority Scheduling, and Round Robin (RR). The main components of this file include:

#### Task Structure:
Defines a Task structure to represent each process with attributes like id, arrival_time, burst_time, completion_time, waiting_time, remaining_time, and priority.
Initializes the task attributes through a constructor.

#### Utility Functions:
arrival_time_comparator: A comparator function to sort tasks based on their arrival time.
to_json: Converts the task list to a JSON string for easy readability and output.

#### Scheduling Algorithms:
1. FCFS: Implements the First-Come, First-Served scheduling by sorting tasks by arrival time and processing them in order.
2. SJF: Implements the Shortest Job First scheduling by selecting the task with the shortest burst time from the tasks that have arrived.
3. Priority Scheduling: Selects the task with the highest priority from the tasks that have arrived.
4. Round Robin: Implements time-sharing by processing tasks in a cyclic manner, using a time quantum to determine how long each task should be executed before moving to the next.
   
#### Main Function:
1. Initializes a list of tasks.
2. Reads the scheduling algorithm name and parameters (like quantum for Round Robin) from the command-line arguments.
3. Executes the corresponding scheduling algorithm based on the input.
4. Outputs the task details in JSON format.

### Key Takeaways
While workkign on this project, I learnt a lot new CPU scheduling algorithms and implemented four of them. I got a chance to get a strong grip on API calls more after using python for this project to make the API calls and used C++ for core algorithm coding. Through this project, I got to learn about the internal working of a proceses in action.

### References
[CPU Schedluing](https://www.youtube.com/playlist?list=PLBlnK6fEyqRitWSE_AyyySWfhRgyA-rHk)

