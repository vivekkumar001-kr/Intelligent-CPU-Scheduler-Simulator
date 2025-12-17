#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;
struct Process {
    int pid, arrival, burst, priority;
    int start = -1, finish = -1;
    int waiting = 0, turnaround = 0;
};
struct Gantt {
    int pid, start, finish;
};
void print results(const vector<Process> &procs , const vector<Gantt> &g){
    cout << "\nGantt Chart:\n";
    for (auto &s : g) {
        if (s.pid == 0) cout << "[idle:" << s.start << "->" << s.finish << "] ";
        else cout << "[P" << s.pid << ":" << s.start << "->" << s.finish << "] ";
    }
    cout << "\n\n---------------- CPU Scheduling Result Table ----------------\n";
    cout << left
         << setw(6) << "PID"
         << setw(12) << "Arrival"
         << setw(10) << "Burst"
         << setw(10) << "Start"
         << setw(10) << "Finish"
         << setw(10) << "Waiting"
         << setw(12) << "Turnaround" << "\n";
}