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

    Process(const string& p_name, long p_cpu_burst, long p_io_time, long p_total_cpu_time, long p_cpu_cicles
            int p_order, int p_priority, int p_credits, State p_state)
            : name(p_name),
              cpu_burst(p_cpu_burst),
              io_time(p_io_time),
              total_cpu_time(p_total_cpu_time),
              cpu_cicles(p_cpu_cicles),
              order(p_order),
              priority(p_priority),
              credits(p_credits),
              state(p_state) {

    }
};

priority_queue<Process> blocked;
priority_queue<Process> ready;

void exec(Process process) {

}

int main () {
    Process p1("Process_1", )
}
