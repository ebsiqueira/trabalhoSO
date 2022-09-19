#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include "traits.h"
#include "debug.h"

__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
        public:
            Context() { _stack = 0; }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an){
                //Get no contexto
                getcontext(&_context);

                // Aloca a pilha (importante ser char para trabalhar com bytes)
                _stack = new char[STACK_SIZE];
                if(_stack) {
                    // Define tamanho da pilha
                    _context.uc_stack.ss_size = STACK_SIZE; 
                    // Define ponteiro para o topo da pilha
                    _context.uc_stack.ss_sp = &_stack;
                    // Especifica o estado da pilha
                    _context.uc_stack.ss_flags=0;
                    // Define o contexto que será retomado
                    _context.uc_link = 0;
                } else {
                    exit(-1);
                }

                makecontext(&_context, (void(*)())func, sizeof ...(Tn), an...);
            }

            ~Context();

            void save();
            void load();

        private:            
            char *_stack;
        public:
            ucontext_t _context;
        };

    public:

        static void switch_context(Context *from, Context *to);

};

__END_API

#endif

