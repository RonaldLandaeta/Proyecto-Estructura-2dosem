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
    
    cout << "REALIZADO! las tareas ordenadas ahora son las siguientes: " << endl;
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
    cout << "Quedan " << energia_disponible << "W en la nave, por lo que" << aux->prox->id_alfanumerico << " que necesita " << aux->prox->consumo_energetico << "W no se pudo completar.";
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
            
            case 5:{
                int segundos_espera = 4; // Tiempo del temporizador en segundos

                cout << "Iniciando el ordenamiento, faltan " << segundos_espera << " segundos..." << endl;

                for (int i = segundos_espera; i > 0; --i) {
                    cout << i << " segundos restantes..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }   
                menorMayor(lista);
                break;
            }
            
            
            case 7:
                paseOrbita(lista);
                break;

            case 8:{
                int segundos_espera = 4; // Tiempo del temporizador en segundos

                cout << "Iniciando el ordenamiento, espere " << segundos_espera << " segundos..." << endl;

                for (int i = segundos_espera; i > 0; --i) {
                    cout << i << " segundos restantes..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }   
                balanceodeCarga(lista);
                break;
            }

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

