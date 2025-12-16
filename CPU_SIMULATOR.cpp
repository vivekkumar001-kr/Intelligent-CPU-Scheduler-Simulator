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
    
}