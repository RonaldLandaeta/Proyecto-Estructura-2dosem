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
using namespace std;
// Elaborado por Lia Mendoza

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
            cout << "|" << mover->id_alfanumerico << ", " << mover->tipo_algoritmo << ", " << mover->peso_computacional << ", " << mover->latencia_max << ", " << mover->consumo_energetico << ", " << mover->urgencia << "| ->";
            mover = mover->prox;
        }
        cout << "NULL" << endl;
    }
    else
        cout << "Lista esta vacia" << endl;
}

void insertarUltimo(TareaIA *&inicio, string id, string tipo, float peso, float latencia, float energia, int urgencia ){
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

/*Quite insertar elemento, eliminar y buscar porque por ahora no las necesitamos y me molesta tenerlas ahi.
Creo que luego si se van a necesitar pero luego las modifiamos primero hay que hacer la de ordenar de menor a mayor
dependiendo de su consumo energetico*/


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

