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
