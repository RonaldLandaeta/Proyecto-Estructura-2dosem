// Proyecto Final: Misión Neuro-Link LEO 
// Orquestador de Micro-Servicios de IA en Constelaciones Satelitales 
// 1. El Escenario 
// Estamos en el año 2026. La constelación de satélites Neuro-Link procesa 
// terabytes de información mediante micro-agentes de Inteligencia Artificial 
// antes de enviarlos a la Tierra. El problema es que cada satélite tiene una 
// "ventana de contacto" limitada con la estación terrestre y una batería solar 
// finita.  
// Tu misión es desarrollar el Núcleo de Gestión de Tareas (Kernel) del satélite. 
// Este sistema debe organizar, priorizar y descartar tareas de IA en tiempo real 
// utilizando exclusivamente Listas Simplemente Enlazadas mediante el uso de 
// punteros. 

// 2. Definición del Nodo: TareaIA 
// Cada nodo de la lista representa una petición de procesamiento que llega al 
// satélite. La estructura debe definirse estrictamente de la siguiente manera: 
// • ID de Tarea: Alfanumérico único.  
// • Tipo de Algoritmo: (Ejemplos: Vision_Artificial, Nlp_Radio, 
// Analisis_Térmico).  
// • Peso Computacional: Medido en Teraflops (TFLOPS).  
// • Latencia Máxima: Tiempo en milisegundos que la tarea puede esperar 
// antes de ser considerada "basura espacial".  
// • Consumo Energético: Estimado en Watts (W).  
// • Urgencia: Escala entera del 1 al 10.  
// • Puntero de Enlace: Dirección de memoria al siguiente nodo.  
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

struct TareaIA{
    string id_alfanumerico, tipo_algoritmo;
    float peso_computacional, latencia_max, consumo_energetico;
    int urgencia;
    TareaIA *prox;
};

TareaIA *crearNodo(string id, string tipo, float peso, float latencia, float energia, int urgencia ){
    TareaIA *nuevo = new TareaIA;
    nuevo->id_alfanumerico = id;
    nuevo->tipo_algoritmo = tipo;
    nuevo->peso_computacional = peso;
    nuevo->latencia_max = latencia;
    nuevo->consumo_energetico = energia;
    nuevo->urgencia = urgencia;
    nuevo->prox = NULL;
    return nuevo;
}

bool listaVacia(TareaIA *inicio){
    return inicio == NULL;
}

void mostrarLista(TareaIA *inicio){
    TareaIA *mover;

    if (!listaVacia(inicio)){
        mover = inicio;
        while (mover != NULL){
            cout << " |" << mover->id_alfanumerico << ", " << mover->tipo_algoritmo << ", " << mover->peso_computacional << ", " << mover->latencia_max << ", " << mover->consumo_energetico << ", " << mover->urgencia << "|->";
            mover = mover->prox;
        }
        cout << "NULL" << endl;
    }
    else
        cout << "Lista esta vacia" << endl;
}

void insertarUltimo(TareaIA *&inicio, string id, string tipo, float peso, float latencia, float energia, int urgencia){
    TareaIA *nuevo = crearNodo(id, tipo, peso, latencia, energia, urgencia);

    if (listaVacia(inicio)){
    inicio = nuevo;
    }
    else{
        TareaIA *auxiliar = inicio;
        while (auxiliar->prox != NULL){
            auxiliar = auxiliar->prox;
        }
        auxiliar->prox = nuevo;
    }
}

void insertarPrimero(TareaIA *&inicio, string id, string tipo, float peso, float latencia, float energia, int urgencia){
    TareaIA *nuevo = crearNodo(id, tipo, peso, latencia, energia, urgencia);
    nuevo->prox = inicio;
    inicio = nuevo;
}

void menorMayor (TareaIA *&inicio){
    TareaIA *ordenada = NULL;
    TareaIA *actual = inicio;
    if (inicio == NULL){ // 1. Si la lista está vacía o tiene un solo elemento, ya está ordenada
        cout << "No hay suficientes tareas en orbita para ordenar." << endl;
        return;
    }
    while (actual != NULL){
        // GUARDAMOS el siguiente nodo de la lista original antes de desconectar el 'actual'
        // Si no hacemos esto, perdemos el resto de la lista (Segmentation Fault)
        TareaIA *siguiente = actual->prox;
        if (ordenada == NULL || actual->consumo_energetico <= ordenada->consumo_energetico) {
            actual->prox = ordenada;
            ordenada = actual;
        }
        else {
            TareaIA *aux = ordenada;
            // Avanzamos en la lista ordenada mientras el siguiente nodo exista y su consumo sea menor al del nodo que queremos insertar
            while (aux->prox != NULL && aux->prox->consumo_energetico < actual->consumo_energetico) {
                aux = aux->prox;
            }
            // Conectamos el nodo 'actual' en el hueco encontrado (entre 'aux' y 'aux->prox')
            actual->prox = aux->prox;
            aux->prox = actual;
        }
        // Pasamos a evaluar el siguiente nodo de la lista original
        actual = siguiente;
    }
    // 5. Por último, actualizamos el puntero 'inicio' global para que apunte a la lista ya ordenada
    inicio = ordenada;
    cout << "REALIZADO! las tareas ordenadas ahora son las siguientes: " << endl;
    mostrarLista(inicio);
}

main(){
    TareaIA *lista = NULL;
    string id_alfanumerico, tipo_algoritmo;
    float peso_computacional, latencia_max, consumo_energetico;
    int urgencia, x = -1;

    while (x != 9){
        system ("cls");
        
        cout << "------------ BIENVENIDO AL MENU DE LA MISION NEURO-LINK ------------"<< endl;
        cout << "con el siguiente menu podra acceder a distintas secciones del menu" << endl;
        cout << "porfavor presione correctamente los numeros indicados para comenzar" << endl;
        cout << "                                                                               " << endl;
        cout << " 1. Insertar al inicio de la lista" << endl;
        cout << " 2. Insertar al final de la lista" << endl;
        cout << " 3. Imprimir la lista" << endl;
        cout << " 4. Ordenar la lista en funcion del consumo energetico" << endl;
        cout << " 5. Eliminar nodos que supere un dato determinado de latencia" << endl;
        cout << " 6. Procesar cuantas tareas antes de agotar la bateria" << endl;
        cout << " 7. Mover tareas de menor urgencia a una lista de espera" << endl;
        cout << " 8. Salir del menu" << endl;
        cout << "______________________________________________________________________" << endl;

        cout << "Porfavor ingrese que accion desee realizar: "; cin >> x;
        while (x < 0 || x > 8){
            cout << "Numero fuera del rango, porfavor ingrese un numero perteneciente al menu";
            cin >> x;
        }
        switch(x){
            case 1:
                cout << "1. Ingrese ID Alfanumerico unico: ";
                cin >> id_alfanumerico;
                cout << "2. Ingrese Tipo de Algoritmo (sin espacios): "; 
                cin >> tipo_algoritmo;
                cout << "3. Ingrese Peso Computacional (TFLOPS): ";
                cin >> peso_computacional;
                cout << "4. Ingrese Latencia Maxima (tiempo en ms): ";
                cin >> latencia_max;
                cout << "5. Ingrese Consumo Energetico (Watts): ";
                cin >> consumo_energetico;
                cout << "6. Ingrese Nivel de Urgencia (1 al 10): ";
                cin >> urgencia;
                insertarPrimero(lista, id_alfanumerico, tipo_algoritmo, peso_computacional, latencia_max, consumo_energetico, urgencia);
                break;
            case 2:
                cout << "1. Ingrese ID Alfanumerico unico: ";
                cin >> id_alfanumerico;
                cout << "2. Ingrese Tipo de Algoritmo (sin espacios): "; 
                cin >> tipo_algoritmo;
                cout << "3. Ingrese Peso Computacional (TFLOPS): ";
                cin >> peso_computacional;
                cout << "4. Ingrese Latencia Maxima (tiempo en ms): ";
                cin >> latencia_max;
                cout << "5. Ingrese Consumo Energetico (Watts): ";
                cin >> consumo_energetico;
                cout << "6. Ingrese Nivel de Urgencia (1 al 10): ";
                cin >> urgencia;
                insertarUltimo(lista, id_alfanumerico, tipo_algoritmo, peso_computacional, latencia_max,consumo_energetico, urgencia);
                break;
            
            case 3:
                if (listaVacia(lista)){
                    cout << "la lista esta vacia.";
                }
                else{
                    cout << "La lista es: ";
                    mostrarLista(lista);
                }
                break;
            
            case 4:
                int segundos_espera = 4;
                cout << "Iniciando el ordenamiento, faltan " << segundos_espera << " segundos..." << endl;
                for (int i = segundos_espera; i > 0; --i) {
                    cout << i << " segundos restantes..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }   
                menorMayor(lista);
                break;

            
            
    }
        if (x != 8) {
            cout << "Presione ENTER para continuar...";
            cin.ignore(10000, '\n'); // Limpia la basura del teclado
            cin.get();               // Pausa hasta que presiones Enter
        }
    }
    return 0;
}


// 3. Requerimientos Funcionales  
// A. Algoritmo de "Green Coding"  
// El satélite debe operar bajo una política de ahorro de energía. Deben 
// implementar una función que ordene la lista basándose en el Consumo Energético 
// (de menor a mayor).  
// B. Protocolo de Descarte por Latencia 
// Las tareas en órbita caducan rápido. El sistema debe recorrer la lista y eliminar 
// automáticamente todos los nodos cuyo tiempo de espera supere su Latencia 
// Máxima. Esta función es vital para liberar memoria RAM en el hardware limitado 
// del satélite.  
// C. Simulador de "Pase de Órbita" 
// Antes de entrar en la zona de sombra (donde no hay carga solar), el sistema 
// recibe un parámetro de Energía Disponible (ejemplo 500W). El programa debe 
// calcular cuántas tareas de la lista se pueden procesar antes de agotar la batería, 
// recorriendo la lista y acumulando el campo Consumo Energético.  
// D. Balanceo de Carga LEO 
// Si el Peso Computacional total de la lista principal excede un umbral crítico de 
// procesamiento del procesador satelital, los nodos excedentes de menor urgencia 
// deben ser "movidos" a una Lista de Espera Secundaria. 

