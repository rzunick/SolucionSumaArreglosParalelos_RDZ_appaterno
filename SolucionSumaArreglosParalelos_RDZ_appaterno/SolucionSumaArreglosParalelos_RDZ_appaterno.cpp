// SolucionSumaArreglosParalelos_RDZ_appaterno.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <chrono> // Se agrega libreria Chrono para medir tiempo de procesamiento

#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float *d);

int main()
{
    std::cout << "Verificando la ejecucion de las directivas OMP\n";

    #ifdef _OPENMP
        std::cout << "OMP disponible y funcionando" << std::endl;
    #endif   
    
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    // Medición del tiempo de procesamiento
    auto start_time = std::chrono::high_resolution_clock::now(); // Inicia el reloj

    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a,b,c,pedazos) private(i) \
    schedule(static,pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    auto end_time = std::chrono::high_resolution_clock::now(); // Detiene el reloj
    std::chrono::duration<double> elapsed_seconds = end_time - start_time; // Calcula el tiempo transcurrido
    std::cout << "Tiempo de procesamiento: " << elapsed_seconds.count() << " segundos" << std::endl; // Imprime el tiempo transcurrido

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
