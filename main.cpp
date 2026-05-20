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
using namespace std;
struct TareaIA 
{
    std::string idTarea;          
    std::string tipoAlgoritmo;      
    double pesoComputacional;     
    double latenciaMaxima;        
    double consumoEnergetico;    
    int urgencia;                 
    TareaIA *prox;
};
TareaIA *crearTreaIA(std::string idtarea,std::string tipoAlgoritmo,double pesoComputacional,double latenciaMaxima,double consumoEnergetico,int urgencia)
{
    TareaIA *nuevo = new TareaIA;
    nuevo->idTarea = idtarea;
    nuevo->tipoAlgoritmo = tipoAlgoritmo;
    nuevo->pesoComputacional = pesoComputacional;
    nuevo->latenciaMaxima = latenciaMaxima;
    nuevo->consumoEnergetico = consumoEnergetico;
    nuevo->urgencia = urgencia;
    nuevo->prox=nullptr;
    return nuevo;
}

bool TareaVacia(TareaIA *Tarea)
{
    return Tarea == NULL;
}

void mostrarTarea(TareaIA *Tarea)
{
   TareaIA *mover;

    if (!TareaVacia(Tarea))
    {
        mover = Tarea;
        while (mover != NULL)
        {
            cout << mover->idTarea << "->";
            cout << mover->tipoAlgoritmo << "->";
            cout << mover->pesoComputacional << "->";
            cout << mover->latenciaMaxima << "->";
            cout << mover->consumoEnergetico << "->";
            cout << mover->urgencia << "->";
            mover = mover->prox;
        }
        cout << "NULL" << endl;
    }
    else
    cout << "Tarea vacia" << endl;
}

void insertarTarea(TareaIA *&Tarea, std::string idtarea,std::string tipoAlgoritmo,double pesoComputacional,double latenciaMaxima,double consumoEnergetico,int urgencia) )
{
   TareaIA *nuevo = crearTreaIA(idtarea, tipoAlgoritmo, pesoComputacional, latenciaMaxima, consumoEnergetico, urgencia);

    if (TareaVacia(Tarea))
    {
        Tarea = nuevo;
    }
    else
    {
      TareaIA *auxiliar = inicio;
    while (auxiliar->prox != NULL)
    {
        auxiliar = auxiliar->prox;
    }
    auxiliar->prox = nuevo;
}
}

void eliminar(Nodo *&inicio, int valor)
{
    Nodo *mover, *anterior = NULL;

    if (listaVacia(inicio))
    cout << "Lista esta vacia" << endl;
    else
    {
        mover = inicio;
        while (mover != NULL && mover->dato != valor)
        {
            anterior = mover;
            mover = mover->prox;
        }
        if (mover == NULL)
            cout << "El elemento no existe en la lista " << endl;
        else
        {
            if (mover == inicio)
                inicio = inicio->prox;
            else
                anterior->prox = mover->prox;
            delete mover;
        }
    }
}

void insertarPrimero(Nodo *&inicio, int valor)
{
    Nodo *nuevo = crearNodo(valor);
    nuevo->prox = inicio;
    inicio = nuevo;
}

void buscarElemento(Nodo *inicio, int valor)
{
    Nodo *aux = inicio;
    bool encontrado = false;
    if (listaVacia(inicio))
        cout << "Lista vacia" << endl;
    else
    {
        while (aux != NULL && encontrado == false)
        {
            if (aux->dato == valor)
            {
                cout << "El dato " << valor << " fue encontrado con exito" << endl;
                encontrado = true;
            }
            else
                aux = aux->prox;
        }
        if (encontrado == false)
        cout << "Valor no encontrado en la lista " << endl;
    }
}
TareaIA *crearTereaia(TareaIA *
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

