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
#include <windows.h>
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
            actual->prox = ordenada; // Esta parte lo que esta haciendo es practicamente un "agregarPrimero", ya que lo 
            ordenada = actual;      // esta haciendo es "si la lista Ordenada esta vacia, o el dato de actual es menor que el primero de ordenada"
        }                           // la inserte
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
    int segundos_espera = 4; // Tiempo del temporizador en segundos
    cout << "Iniciando el ordenamiento, faltan " << segundos_espera << " segundos..." << endl;
        for (int i = segundos_espera; i > 0; --i) {
            cout << i << " segundos restantes..." << endl;
            Sleep(1000);
        }   
    cout << "REALIZADO! las tareas ordenadas ahora son las siguientes: " << endl;
    mostrarLista(inicio);
}

void descarte(TareaIA *&inicio){
    TareaIA *actual = inicio; float tiempo; TareaIA *anterior = NULL;
    cout << "Indique el tiempo de espera maximo, se eliminaran los tiempos cuya latencia supere el tiempo de espera: "; cin >> tiempo;
    while (actual != NULL){
        if (tiempo > actual->latencia_max){
            TareaIA *borrar = actual;
            // CASO 1: El nodo a borrar es el PRIMERO de la lista
            if (anterior == NULL){
                inicio = actual->prox;      // Movemos el cabezal oficial al siguiente nodo
                actual = inicio;            // Reposicionamos nuestro puntero de búsqueda
            }
            else{
                anterior->prox = actual->prox;      // Enganchamos el nodo anterior con el siguiente (puente)
                actual = actual->prox;              // Reposicionamos nuestro puntero de búsqueda
            }
            delete borrar;
        }
        else{
            anterior = actual;
            actual = actual->prox;
        }
    }
    int segundos_espera = 4;
    cout << "Iniciando la eliminacion, faltan " << segundos_espera << " segundos..." << endl;
        for (int i = segundos_espera; i > 0; --i) {
            cout << i << " segundos restantes..." << endl;
            Sleep(1000);
        }
    cout << "Eliminacion de tareas completado." << endl;
    cout << "La lista actualizada queda como: " << endl;
    mostrarLista(inicio);
}

void paseOrbita(TareaIA *inicio){
    TareaIA *aux = inicio; int energia_disponible; int contador = 0;
    cout << "Ingrese porfavor la energia disponible para la mision: "; cin >> energia_disponible;
    while (aux != NULL){
        if (aux->consumo_energetico <= energia_disponible){
            energia_disponible = energia_disponible - aux->consumo_energetico;
            contador++;
            aux = aux->prox;
        }
        else{
            break;
        }
    }
    cout << "El total de tareas procesables son: " << contador << endl;
    if (aux != NULL){
        cout << "Quedan " << energia_disponible << "W en la nave, por lo que" << aux->prox->id_alfanumerico << " que necesita " << aux->prox->consumo_energetico << "W no se pudo completar.";
    }
    else{
        cout << "Se completaron todas las tareas sin problemas.";
    }

    
}

void balanceodeCarga (TareaIA *&inicio){
    TareaIA *actual = inicio; float umbral; float total = 0; TareaIA *ordenada = NULL; TareaIA *listaSecundaria = NULL;
    cout << "Ingrese el maximo peso computacional que podra realizar el satelite: "; cin >> umbral;
    while (actual != NULL){
        total = actual->peso_computacional + total;
        actual = actual->prox;
    }
    actual = inicio;
    while (actual != NULL){
        TareaIA *siguiente = actual->prox;
        if (ordenada == NULL || actual->urgencia <= ordenada->urgencia) {
            actual->prox = ordenada;
            ordenada = actual;
        }                           
        else {
            TareaIA *aux = ordenada;
            while (aux->prox != NULL && aux->prox->urgencia < actual->urgencia){
                aux = aux->prox;
            }
            actual->prox = aux->prox;
            aux->prox = actual;
        }
        actual = siguiente;
    }
    while (ordenada != NULL){
        TareaIA *aux = ordenada;
        if (total > umbral){
            ordenada = ordenada->prox; 
            total = total - aux->peso_computacional; 
            aux->prox = listaSecundaria; 
            listaSecundaria = aux; 
        }
        else{
            break;
        }
    }
    inicio = ordenada;
    int segundos_espera = 4; // Tiempo del temporizador en segundos
        cout << "Iniciando el ordenamiento, espere " << segundos_espera << " segundos..." << endl;
            for (int i = segundos_espera; i > 0; --i) {
            cout << i << " segundos restantes..." << endl;
            Sleep(1000);
            }   
    cout << "Se han eliminado los elementos de la lista y quedaria: " << endl;
    mostrarLista(ordenada);
    cout << "Y en la lista secundaria estan: " << endl;
    mostrarLista(listaSecundaria);
}

main(){
    TareaIA *lista = NULL; TareaIA *listaorg = NULL;
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
        cout << " 3. Imprimir la lista actual" << endl;
        cout << " 4. Imprimir la lista orignal" << endl;
        cout << " 5. Ordenar la lista en funcion del consumo energetico" << endl;
        cout << " 6. Eliminar nodos que supere un dato determinado de latencia" << endl;
        cout << " 7. Procesar cuantas tareas antes de agotar la bateria" << endl;
        cout << " 8. Mover tareas de menor urgencia a una lista de espera" << endl;
        cout << " 9. Salir del menu" << endl;
        cout << "______________________________________________________________________" << endl;
        
        cout << "Porfavor ingrese que accion desee realizar: "; cin >> x;
        while (x < 0 || x > 9){
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
                insertarPrimero(listaorg, id_alfanumerico, tipo_algoritmo, peso_computacional, latencia_max, consumo_energetico, urgencia);
                cout << "La lista actual es: ";
                mostrarLista(lista);
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
                insertarUltimo(lista, id_alfanumerico, tipo_algoritmo, peso_computacional, latencia_max, consumo_energetico, urgencia);
                insertarUltimo(listaorg, id_alfanumerico, tipo_algoritmo, peso_computacional, latencia_max, consumo_energetico, urgencia);
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
                if (listaVacia(lista)){
                    cout << "la lista esta vacia.";
                }
                else{
                    cout << "La lista es: ";
                    mostrarLista(listaorg);
                }
                break;
            case 5:
                menorMayor(lista);
                break;
            case 6:
                descarte(lista);
                break;
            case 7:
                paseOrbita(lista);
                break;
            case 8:
                balanceodeCarga(lista);
                break;
            case 9:
                cout << "Muchas gracias por usar el menu";
                break;
    }
        if (x != 9) {
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

