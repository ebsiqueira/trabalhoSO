#include "cpu.h"
#include "thread.h"
#include <iostream>

__BEGIN_API

// Inicialização do ponteiro para a thread em execução
Thread * Thread::_running = nullptr;
// Contador em 0 (unsigned para evitar contagem negativa)
unsigned int Thread::_thread_counter = 0;

// Tenta trocar o contexto e definir a próxima thread como thread em execução
// Caso capture algum problema, retorna um valor negativo
static int switch_context(Thread * prev, Thread * next){
    db<Thread>(TRC)<<"Thread::switch_context()\n";
    try {
        CPU::switch_context(prev->context(), next->context());
        _running = next;
    } catch (...) {
        return -1;
    }
}

// Encerra a thread deletando seu contexto
void thread_exit (int exit_code) {
    db<Thread>(TRC)<<"Thread::thread_exit()\n";
    if(_context) {
        delete _context;
        _thread_counter--;
    }
}

// Retorna id da thread
int id() {
    db<Thread>(TRC)<<"Thread::id()\n";
    return _id;
}

__END_API