#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <queue>

using namespace std;
  
enum State {
    Ready,
    Running,
    Blocked,
    Exit,
};

class Process {
    public:
        string name;
        long  cpu_burst;
        long  io_time;
        long  total_cpu_time;
        int   order;
        int   priority;
        int   credits;
        State state;
        
        Process(string name, int priority, int order){
            this->cpu_burst = 0;
            this->io_time = 0;
            this->total_cpu_time = 0;
            this->order = order;
            this->priority = priority;
            this->credits = priority;
            this->state = State::Ready;
        };  
};

priority_queue<Process> blocked;
priority_queue<Process> ready;

void exec(Process process) {

}

int main () {
    
}
