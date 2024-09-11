#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Definição dos estados do processo
enum class State {
    Ready, Running, Blocked, Exit
};

// Estrutura de um processo
struct Process {
    string name;
    int cpu_burst;
    int io_time;
    int total_cpu_time;
    int order;
    int priority;
    int credits;
    State state;

    // Construtor para inicializar o processo
    Process(string n, int cpu, int io, int total, int ord, int prio)
            : name(n), cpu_burst(cpu), io_time(io), total_cpu_time(total),
              order(ord), priority(prio), credits(prio), state(State::Ready) {}

    // Atualiza os créditos quando necessário
    void update_credits() {
        credits = credits / 2 + priority;
    }

    // Reduz os créditos e muda o estado do processo
    void execute() {
        if (credits > 0) {
            credits--;
            total_cpu_time -= cpu_burst;
            if (total_cpu_time <= 0) {
                state = State::Exit; // Processo finalizado
            }
        }
    }
};

// Função para comparação dos processos na fila de execução
bool compare_process(const Process& p1, const Process& p2) {
    if (p1.credits == p2.credits) {
        return p1.order < p2.order;  // Desempate pela ordem
    }
    return p1.credits > p2.credits;  // Prioriza o processo com mais créditos
}

int main() {
    // Criação de processos de exemplo
    vector<Process> processes = {
            Process("A", 2, 5, 6, 1, 3),
            Process("B", 3, 10, 6, 2, 3),
            Process("C", 14, 0, 14, 3, 3),
            Process("D", 10, 0, 10, 4, 3)
    };

    int time = 0; // Relógio do sistema

    while (!processes.empty()) {
        // Ordena os processos pelo número de créditos e ordem
        sort(processes.begin(), processes.end(), compare_process);

        // Seleciona o primeiro processo na fila de prontos
        for (auto& process : processes) {
            if (process.state == State::Ready) {
                cout << "Executando processo: " << process.name << " no tempo " << time << endl;
                process.execute();  // Executa o processo

                // Simula mudança de estado para bloqueio ou término
                if (process.state == State::Exit) {
                    cout << "Processo " << process.name << " finalizado no tempo " << time << endl;
                }

                break;
            }
        }

        // Atualiza os créditos se todos estiverem com 0
        bool all_zero = all_of(processes.begin(), processes.end(), [](Process& p) {
            return p.credits == 0;
        });
        if (all_zero) {
            for (auto& process : processes) {
                process.update_credits();  // Atualiza os créditos de todos os processos
            }
        }

        // Incrementa o tempo do sistema
        time++;

        // Remove os processos finalizados
        processes.erase(remove_if(processes.begin(), processes.end(),
                                  [](Process& p) { return p.state == State::Exit; }), processes.end());
    }

    return 0;
}
