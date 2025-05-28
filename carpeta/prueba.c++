#include <iostream>
#include <pthread.h>
#include <semaphore.h> //se importan las librerias correspondientes para trabajar, "pthread" para el maejo de hilos y "sempahore" para los semaforos.


int contador = 0; //contador iniciado en 0 que todos los hilos van a utilizar
sem_t semaforo; //inicializacion del semafoto, controla el acceso de los hijos

const int NUM_HILOS = 5; //cantidad de hilos

void* incrementarContador(void* arg) { //Funcion del hilo. funciones como "wait" bloquea si otro hilo esta dentro, haciendo que espere su turno. Espera a que termine el hilo, se agrega, y termina el uso del semaforo con "sem_post"
    for (int i = 0; i < 1000; i++) {
        sem_wait(&semaforo);
        contador++;
        sem_post(&semaforo);
    }
    return nullptr;
}

int main() {
    pthread_t hilos[NUM_HILOS];

    // Declara que inicia el semaforo donde solo entra un hilo a la vez
    sem_init(&semaforo, 0, 1);

    // crea los 5 hilos que ejecutaran la funcion de incrementar el contador
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&hilos[i], nullptr, incrementarContador, nullptr);
    }

    // aca espera a que todos los hilos sean agregador y terminados para poder continuar hasta terminar eon el numero de hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], nullptr);
    }

    // termina con el uso del semaforo
    sem_destroy(&semaforo);
    std::cout << "Valor final del contador: " << contador << std::endl;

    return 0;
}

