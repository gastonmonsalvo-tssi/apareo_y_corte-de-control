/*
Una empresa de transporte cuenta con camiones de diferente tamaño.
Al finalizar el día se cuenta con los datos de cada viaje ordenados por patente en forma ascendente:

struct
{
- Patente
- Hora de inicio
- Hora de fin
- Kilómetros recorridos
- Importe
}
Y en forma separada, los datos de cada vehículo:

struct
{
- Patente
- Modelo
- Consumo por kilómetro
}

Para escribir el código, se asume que los datos ya están cargados en vectores estáticos
y que cada vector tiene una variable asociada que indica la cantidad de elementos cargados.
Se asume que cada vehículo realiza al menos un viaje en el día.


1) Escribir una función que ordene el vector de vehículos por modelo (ordenamiento burbuja). --> burbujeo en Camion
2) Escribir una función que busque en el vector de vehículos por patente y devuelva la posición
en el vector (búsqueda binaria).
3) Escribir una función que calcule el costo total del combustible utilizado por todos los camiones en el día.
4) Escribir una función que indique la patente del vehículo con mejor y peor rendimiento, de acuerdo al consumo
total de combustible en relación con el total de los importes cobrados por los viajes. 
(cuanto estas cobrando por km recorrido)

*/

#include <iostream>
#include <string>
using namespace std;

struct Viaje
{
    // por fines practicos
    long patente;
    int hora_de_inicio;
    int hora_de_fin;
    int kilmetros_recorridos;
    float importe;
};

struct Camion
{ // modelo --> año vehiculo
    long patente;
    int modelo;
    int consumo_por_kilometro;
};

//vector para res ej 3-4
struct Consumo
{
    long patente;   //fines comunicativos
    int consumo;
    float importe;
    float rendimiento;
};

/*
    1) 
 Escribir una función que ordene el vector de vehículos por modelo (ordenamiento burbuja). 
 --> burbujeo en Camion
*/
void burbujeo_modelo(Camion arr[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].modelo > arr[j + 1].modelo)
            {
                // Intercambiar
                Camion temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void burbujeo_patente(Camion arr[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].patente > arr[j + 1].patente)
            {
                // Intercambiar
                Camion temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*
 2)
 Escribir una función que busque en el vector de vehículos por patente y devuelva la posición
    en el vector (búsqueda binaria).
*/
int busqueda_binaria(Camion arr[], int n, long valor) {
    int inicio = 0;
    int fin = n - 1;
    int posicion = -1;  //pos, no encontrada
    
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        
        if (arr[medio].patente == valor) {
            posicion=medio;  // Lo encontro
        }
        
        if (arr[medio].patente > valor) {
            fin = medio - 1;     // Buscar en la mitad izquierda
        } else {
            inicio = medio + 1;  // Buscar en la mitad derecha
        }
    }
    
    return posicion;  // No lo encontro
}

void mostrar_vector(Camion a[], int n ){

    for (int i = 0; i < n; i++)
    {
        cout << "Modelo: " << a[i].modelo << ", "; 
    }
    
}

/*
 3)
 Escribir una función que calcule el costo total del combustible 
    utilizado por todos los camiones en el día.
*/
int calcular_costo_total (Camion arr_camiones[], int n , Viaje arr_viajes[], int m, Consumo arr_consumos[] )
{
    int acumulador_consumo = 0;
    //camiones
    for (int i = 0; i < n; i++)
    {
        long key = arr_camiones[i].patente;
        arr_consumos[i].consumo = 0;    //inicializamos consumo en 0
        arr_consumos[i].importe = 0;
        arr_consumos[i].patente = arr_camiones[i].patente;
        //viajes
        for (int j = 0; j < m; j++)
        {
            if (key ==  arr_viajes[j].patente)
            {
                acumulador_consumo += (arr_camiones[i].consumo_por_kilometro) * (arr_viajes[j].kilmetros_recorridos);
                
                arr_consumos[i].consumo = arr_consumos[i].consumo + (arr_camiones[i].consumo_por_kilometro) * (arr_viajes[j].kilmetros_recorridos);
                arr_consumos[i].importe = arr_consumos[i].importe + arr_viajes[j].importe ;
            }
        }
        arr_consumos[i].rendimiento = (arr_consumos[i].importe/arr_consumos[i].consumo);
    }

    return acumulador_consumo;
    
}

/*
 4)
 Escribir una función que indique la patente del vehículo con mejor y peor rendimiento, de acuerdo al consumo
    total de combustible en relación con el total de los importes cobrados por los viajes. 
    (cuanto estas cobrando por km recorrido)
    importe -> km cuanto ganas 
*/

void mostrar_rendimientos(Consumo arr_consumo[], int n)
{
    float mejor_rendimiento = arr_consumo[0].rendimiento;
    float peor_rendimiento = arr_consumo[0].rendimiento;
    int indice_mejor_camion = 0;
    int indice_peor_camion = 0;

    for (int i = 1; i < n; i++)
    {
        
        if (arr_consumo[i].rendimiento > mejor_rendimiento)
        {
            mejor_rendimiento = arr_consumo[i].rendimiento;
            indice_mejor_camion=i;
        }

        if (arr_consumo[i].rendimiento < peor_rendimiento)
        {
            peor_rendimiento = arr_consumo[i].rendimiento;
            indice_peor_camion=i;
        }
    }

    cout << "La patente con mejor rendimiento es " << arr_consumo[indice_mejor_camion].patente << endl;
    cout << "La patente con peor rendimiento es " << arr_consumo[indice_peor_camion].patente << endl;
}


int main()
{

    // Camiones (3)
    Camion camiones[] = {
        {10001, 2018, 34}, // 340 ml/km → 0.34 l/km
        {10002, 2020, 31}, // 310 ml/km → 0.31 l/km
        {10003, 2019, 39}  // 390 ml/km → 0.39 l/km
    };
    int cantidad_camiones = 3;

    // Viajes (4)
    Viaje viajes[] = {
        {10001, 800, 930, 120, 35000.0},
        {10002, 1000, 1130, 200, 47000.0},
        {10003, 900, 1030, 150, 43000.0},
        {10001, 1500, 1630, 100, 31000.0}
    };
    int cantidad_viajes = 4;

    //Consumo (misma cantidad de camiones)
    Consumo consumos[cantidad_camiones];

    burbujeo_modelo(camiones,cantidad_camiones);
    mostrar_vector(camiones, cantidad_camiones);
    burbujeo_patente(camiones,cantidad_camiones);

    long valor_buscado = 10000;
    int indice = busqueda_binaria(camiones,cantidad_camiones,valor_buscado);

    cout << endl;

    cout << "El valor buscado -> " << valor_buscado << " se encuentra en la posicion " << indice;
    
    cout << endl;

    int costo_total = calcular_costo_total(camiones,cantidad_camiones,viajes,cantidad_viajes,consumos);

    cout << "El consumo total es de: " << costo_total;

    cout << endl;

    for (int i = 0; i < cantidad_camiones; i++)
    {
        cout << "Camion n° " << i+1 << endl;
        cout << "Patente: " << consumos[i].patente << endl;
        cout << "Consumo: " << consumos[i].consumo << endl;
        cout << "Importe: " << consumos[i].importe << endl;
        cout << "Rendimiento: " << consumos[i].rendimiento << endl;
        cout << "-----------------------------------"<< endl;
    }

    cout << endl;

    mostrar_rendimientos(consumos,cantidad_camiones);
    

    
    return 0;
}
