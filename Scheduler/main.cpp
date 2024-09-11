#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <queue>

using namespace std;
  
enum class State {
    READY,
    RUNNING,
    BLOCKED,
    EXIT,
};

class Process {
    public:
        string name;
        long  cpu_burst; //
        long  io_time;
        long  total_cpu_time;
        long  cpu_cicles;
        int   order;
        int   priority; // definido arbitrariamente na criação do processo
        int   credits;
        State state;

    Process(const string& p_name, long p_cpu_cicles, int p_order, int p_priority)
            : name(p_name),
              cpu_cicles(p_cpu_cicles),
              order(p_order),
              priority(p_priority){
        cpu_burst      = 0;
        io_time        = 0;
        total_cpu_time = 0;
        state          = State::READY;
        credits        = priority;
    }
};

priority_queue<Process> blocked;
priority_queue<Process> ready;

void exec(Process process) {

}

int main () {
    Process p1("Process_1", 99, 1, 12);
    Process p2("Process_2", 35, 2, 12);
    Process p3("Process_3", 12, 3, 12);
    Process p4("Process_4", 765, 4, 12);
    Process p5("Process_5", 23, 5, 12);
    Process p6("Process_6", 93, 6, 12);
    Process p7("Process_7", 012, 7, 12);
    Process p8("Process_8", 3, 8, 12);

}
