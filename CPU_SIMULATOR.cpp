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
    wsum += p.waiting;
    tsum += p.turnaround;
    cout << string(70, '-') << "\n";
    cout << "Average Waiting Time: " << wsum / procs.size() << "\n";
    cout << "Average Turnaround Time: " << tsum / procs.size() << "\n";
    
}
// Helper
vector<Process> reset(const vector<Process>& p) {
    vector<Process> r = p;
    for (auto &x : r) {
        x.start = x.finish = -1;
        x.waiting = x.turnaround = 0;
    }
    return r;
}
// ========== FCFS ==========
void fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b){ return a.arrival < b.arrival; });

    int time = 0;
    vector<Gantt> g;

    for (auto &x : p) {
        if (time < x.arrival) {
            g.push_back({0, time, x.arrival});
            time = x.arrival;
        }
        x.start = time;
        time += x.burst;
        x.finish = time;
        x.turnaround = x.finish - x.arrival;
        x.waiting = x.turnaround - x.burst;

        g.push_back({x.pid, x.start, x.finish});
    }
    print_results(p, g);
}

// ========== SJF ==========
void sjf(vector<Process> orig) {
    vector<Process> p = reset(orig);
    int n = p.size();
    vector<bool> done(n, false);

    int time = 0, completed = 0;
    vector<Gantt> g;

    while (completed < n) {
        int idx = -1, mb = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].burst < mb) {
                mb = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) { time++; continue; }

        p[idx].start = time;
        time += p[idx].burst;
        p[idx].finish = time;

        p[idx].turnaround = p[idx].finish - p[idx].arrival;
        p[idx].waiting    = p[idx].turnaround - p[idx].burst;

        g.push_back({p[idx].pid, p[idx].start, p[idx].finish});

        done[idx] = true;
        completed++;
    }

    print_results(p, g);
}

// ========== PRIORITY ==========
void priority_scheduling(vector<Process> orig) {
    vector<Process> p = reset(orig);
    int n = p.size();
    vector<bool> done(n, false);

    int time = 0, completed = 0;
    vector<Gantt> g;

    while (completed < n) {
        int idx = -1, bp = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].priority < bp) {
                bp = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) { time++; continue; }

        p[idx].start = time;
        time += p[idx].burst;
        p[idx].finish = time;

        p[idx].turnaround = p[idx].finish - p[idx].arrival;
        p[idx].waiting    = p[idx].turnaround - p[idx].burst;

g.push_back({p[idx].pid, p[idx].start, p[idx].finish});

        done[idx] = true;
        completed++;
    }

    print_results(p, g);
}

// ========== ROUND ROBIN ==========
void round_robin(vector<Process> orig, int q) {
    vector<Process> p = reset(orig);
    int n = p.size();
    vector<int> rem(n);

    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;

    int time = 0, completed = 0;
    queue<int> Q;
    vector<Gantt> g;
    vector<bool> added(n, false);

    while (completed < n) {

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!added[i] && p[i].arrival <= time) {
                Q.push(i);
                added[i] = true;
            }
        }

        if (Q.empty()) { time++; continue; }

        int idx = Q.front(); Q.pop();

        if (p[idx].start == -1)
            p[idx].start = time;

        int run = min(q, rem[idx]);

        g.push_back({p[idx].pid, time, time + run});

        time += run;
        rem[idx] -= run;

        if (rem[idx] == 0) {
            p[idx].finish = time;
            p[idx].turnaround = p[idx].finish - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        } else {
            Q.push(idx);
        }
    }

    print_results(p, g);
}

// ========== MAIN ==========
int main() {
    cout << "================ CPU Scheduler Input Format ================\n\n";

    int n;
    cout << "Number of Processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "\nProcess Details:\n";
    cout << "PID  Arrival_Time  Burst_Time  Priority\n";

    for (int i = 0; i < n; i++) {
        cout << "Process " << i+1 << ": ";
        cin >> p[i].pid >> p[i].arrival >> p[i].burst >> p[i].priority;
    }

    cout << "\nAlgorithm Choice:\n";
    cout << "1 = FCFS\n2 = SJF\n3 = Round Robin\n4 = Priority\n";
    cout << "Enter choice: ";
    int c;
    cin >> c;

    int quantum = 0;
    if (c == 3) {
        cout << "Enter Time Quantum: ";
        cin >> quantum;
    }

    cout << "\n================ Simulation Output ================\n";

    if      (c == 1) fcfs(p);
    else if (c == 2) sjf(p);
    else if (c == 3) round_robin(p, quantum);
    else if (c == 4) priority_scheduling(p);
    else             cout << "Invalid choice!\n";

    return 0;
}
