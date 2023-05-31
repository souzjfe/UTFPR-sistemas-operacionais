#include <iostream>
#include <omp.h>
#include <unistd.h> // Para usar a função sleep()

const int MAX_CLIENTS = 5;
const int NUM_CHAIRS = 3;

int numClients = 0;
bool barberSleeping = true;

void barber() {
    while (true) {
        #pragma omp critical
        {
            if (numClients == 0) {
                barberSleeping = true;
                std::cout << "Barbeiro dormindo..." << std::endl;
            }
            else {
                barberSleeping = false;
                numClients--;
                std::cout << "Barbeiro atendendo um cliente. Clientes na sala de espera: " << numClients << std::endl;
            }
        }
        
        if (barberSleeping) {
            // Barbeiro dorme
            sleep(1);
        }
        else {
            // Barbeiro corta o cabelo do cliente
            sleep(2);
        }
    }
}

void customer() {
    #pragma omp critical
    {
        if (numClients < NUM_CHAIRS) {
            numClients++;
            std::cout << "Cliente entrou na sala de espera. Clientes na sala de espera: " << numClients << std::endl;
        }
        else {
            std::cout << "Sala de espera cheia. Cliente foi embora." << std::endl;
        }
    }
    
    // Cliente espera ser chamado pelo barbeiro
    while (!barberSleeping) {
        sleep(1);
    }
}

int main() {
    omp_set_num_threads(MAX_CLIENTS + 1); // +1 para o barbeiro
    
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        
        if (threadID == 0) {
            barber(); // Barbeiro
        }
        else {
            customer(); // Cliente
        }
    }
    
    return 0;
}
