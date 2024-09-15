#include <string>
#include <queue>
#include <iostream>

using namespace std;

template <typename T>
void safeDelete(T*& pointer){
    if (pointer != nullptr){
        delete pointer;
        pointer = nullptr;
    }
}

enum class State {
    READY,
    RUNNING,
    BLOCKED,
    EXIT,
};

class Process {
private:
    string name;
    long  cpu_burst; //
    long  io_time;
    long  total_cpu_time;
    int   order;
    int   priority; // definido arbitrariamente na criação do processo
    int   credits;
    State state;
public:
    // Construtor
    Process(const string& p_name, long p_total_cpu_time, int p_order, int p_priority)
            : name(p_name),
              cpu_burst(0),            // Inicializa como 0
              io_time(0),              // Inicializa como 0
              total_cpu_time(p_total_cpu_time),
              order(p_order),
              priority(p_priority),
              credits(p_priority),     // Créditos inicializados com a prioridade
              state(State::READY) {}   // Estado inicial: READY
    void ToString() {
        cout << name << endl;
    }

    [[nodiscard]] int Priority() const {
        return priority;
    }

};

auto Compare = [](Process* p1, Process* p2) {
    return p1->Priority() > p2->Priority();
};

int main () {
    auto* blocked = new priority_queue<Process*, vector<Process*>, decltype(Compare)>(Compare);
    auto* p1 = new Process("Process_1", 99, 1, 12);
    auto* p2 = new Process("Process_2", 56, 3, 20);
    //p1->ToString();
    blocked->push(p2);
    blocked->push(p1);

    safeDelete(p1);
    safeDelete(p2);
    safeDelete(blocked);
    return 0;
}