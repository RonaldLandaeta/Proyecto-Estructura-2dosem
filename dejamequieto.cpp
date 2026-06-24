#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <windows.h>
using namespace std;

struct TareaIA
{
    string id_alfanumerico, tipo_algoritmo;
    float peso_computacional, latencia_max, consumo_energetico;
    int urgencia;
    TareaIA *prox;
};

// CORRECCIÓN: Se separa el contador estático en su propia función para poder sincronizarlo desde cargarDesdeArchivo
static int contadorID = 1;

string generarID()
{
    string idResultante = "TASK-" + to_string(contadorID);
    contadorID++;
    return idResultante;
}

string Tipo_algoritmo_aleatorio() {
    string catalogo[] = {
        "Vision_Artificial", 
        "Nlp_Radio", 
        "Analisis_Termico", 
        "Telemetria_Predictiva", 
        "Cifrado_Cuantico"
    };
    static std::random_device rd;  
    static std::mt19937 motor(rd()); 
    std::uniform_int_distribution<int> dist(0, 4);
    return catalogo[dist(motor)];
}

// CORRECCIÓN: Un único motor global para todos los datos aleatorios
static std::mt19937 motorGlobal(std::random_device{}());

int datos_Aleatorios()
{
    std::uniform_int_distribution<int> dist(0, 100); 
    return dist(motorGlobal);
}

int urgencia_aleatoria()
{
    std::uniform_int_distribution<int> dist(1, 10); 
    return dist(motorGlobal);
}

TareaIA *crearNodo_Aleatorio()
{
    TareaIA *nuevo = new TareaIA;
    nuevo->id_alfanumerico = generarID();
    nuevo->tipo_algoritmo = Tipo_algoritmo_aleatorio();
    nuevo->peso_computacional = datos_Aleatorios();
    nuevo->latencia_max = datos_Aleatorios();
    nuevo->consumo_energetico = datos_Aleatorios();
    nuevo->urgencia = urgencia_aleatoria();
    nuevo->prox = nullptr;
    return nuevo;
}

// Permite clonar un nodo para guardarlo en la lista original sin romper los enlaces de memoria
TareaIA *clonarNodo(TareaIA *origen)
{
    if (origen == nullptr) return nullptr;
    TareaIA *nuevo = new TareaIA;
    nuevo->id_alfanumerico = origen->id_alfanumerico;
    nuevo->tipo_algoritmo = origen->tipo_algoritmo;
    nuevo->peso_computacional = origen->peso_computacional;
    nuevo->latencia_max = origen->latencia_max;
    nuevo->consumo_energetico = origen->consumo_energetico;
    nuevo->urgencia = origen->urgencia;
    nuevo->prox = nullptr;
    return nuevo;
}

bool listaVacia(TareaIA *inicio)
{
    return inicio == nullptr;
}

void mostrarLista(TareaIA *inicio)
{
    TareaIA *mover;
    if (!listaVacia(inicio))
    {
        mover = inicio;
        while (mover != nullptr)
        {
            cout << " |" << mover->id_alfanumerico << ", " << mover->tipo_algoritmo << ", " << mover->peso_computacional << ", " << mover->latencia_max << ", " << mover->consumo_energetico << ", " << mover->urgencia << "|->";
            mover = mover->prox;
        }
        cout << "NULL" << endl;
    }
    else
        cout << "Lista esta vacia" << endl;
}

// Inserción al principio usando un nodo ya existente
void insertarPrimero_Nodo(TareaIA *&inicio, TareaIA *nuevo)
{
    nuevo->prox = inicio;
    inicio = nuevo;
}

void insertarUltimo_Nodo(TareaIA *&inicio, TareaIA *nuevo)
{
    if (listaVacia(inicio))
    {
        inicio = nuevo;
    }
    else
    {
        TareaIA *auxiliar = inicio;
        while (auxiliar->prox != nullptr)
        {
            auxiliar = auxiliar->prox;
        }
        auxiliar->prox = nuevo;
    }
}

void insertarUltimo_Aleatorio(TareaIA *&inicio)
{
    TareaIA *nuevo = crearNodo_Aleatorio();
    insertarUltimo_Nodo(inicio, nuevo);
}

void insertarPrimero_Aleatorio(TareaIA *&inicio)
{
    TareaIA *nuevo = crearNodo_Aleatorio();
    insertarPrimero_Nodo(inicio, nuevo);
}

void menorMayor(TareaIA *&inicio)
{
    TareaIA *ordenada = nullptr;
    TareaIA *actual = inicio;
    if (inicio == nullptr)
    { 
        cout << "No hay suficientes tareas en orbita para ordenar." << endl;
        return;
    }
    // CORRECCIÓN: El countdown va ANTES del ordenamiento para que tenga sentido
    int segundos_espera = 4;
    cout << "Iniciando el ordenamiento, faltan " << segundos_espera << " segundos..." << endl;
    for (int i = segundos_espera; i > 0; --i) {
        cout << i << " segundos restantes..." << endl;
        Sleep(1000);
    }
    while (actual != nullptr)
    {
        TareaIA *siguiente = actual->prox;
        if (ordenada == nullptr || actual->consumo_energetico <= ordenada->consumo_energetico) 
        {
            actual->prox = ordenada; 
            ordenada = actual;
        }                          
        else 
        {
            TareaIA *aux = ordenada;
            while (aux->prox != nullptr && aux->prox->consumo_energetico < actual->consumo_energetico) 
            {
                aux = aux->prox;
            }
            actual->prox = aux->prox;
            aux->prox = actual;
        }
        actual = siguiente;
    }
    inicio = ordenada;
    cout << "REALIZADO! las tareas ordenadas ahora son las siguientes: " << endl;
    mostrarLista(inicio);
}

void descarte(TareaIA *&inicio)
{
    TareaIA *actual = inicio; 
    TareaIA *anterior = nullptr;
    float tiempo;
    cout << "Indique el tiempo de espera maximo, se eliminaran los tiempos cuya latencia supere el tiempo de espera: "; 
    cin >> tiempo;
    // CORRECCIÓN: El countdown va ANTES de la eliminación
    int segundos_espera = 4;
    cout << "Iniciando la eliminacion, faltan " << segundos_espera << " segundos..." << endl;
    for (int i = segundos_espera; i > 0; --i) 
    {
        cout << i << " segundos restantes..." << endl;
        Sleep(1000);
    }
    while (actual != nullptr)
    {
        if (tiempo > actual->latencia_max){
            TareaIA *borrar = actual;
            if (anterior == nullptr)
            {
                inicio = actual->prox;     
                actual = inicio;            
            }
            else
            {
                anterior->prox = actual->prox;     
                actual = actual->prox;              
            }
            delete borrar;
        }
        else
        {
            anterior = actual;
            actual = actual->prox;
        }
    }
    cout << "Eliminacion de tareas completado." << endl;
    cout << "La lista actualizada queda como: " << endl;
    mostrarLista(inicio);
}

void paseOrbita(TareaIA *inicio)
{
    TareaIA *aux = inicio; 
    int energia_disponible; 
    int contador = 0;
    cout << "Ingrese porfavor la energia disponible para la mision: "; cin >> energia_disponible;
    while (aux != nullptr)
    {
        if (aux->consumo_energetico <= energia_disponible)
        {
            energia_disponible = energia_disponible - aux->consumo_energetico;
            contador++;
            aux = aux->prox;
        }
        else
        {
            break;
        }
    }
    int segundos_espera = 4;
    cout << "Procesando, espere " << segundos_espera << " segundos..." << endl;
    for (int i = segundos_espera; i > 0; --i)
    {
        cout << i << " segundos restantes..." << endl;
        Sleep(1000);
    }
    cout << "El total de tareas procesables son: " << contador << endl;
    // CORRECCIÓN: Se accede a aux directamente, no a aux->prox, para evitar crash
    if (aux != nullptr)
    {
        cout << "Quedan " << energia_disponible << "W en la nave, por lo que " << aux->id_alfanumerico << " que necesita " << aux->consumo_energetico << "W no se pudo completar.";
    }
    else
    {
        cout << "Se completaron todas las tareas sin problemas.";
    }
}

void balanceodeCarga(TareaIA *&inicio)
{
    TareaIA *actual = inicio;
    float umbral;
    float total = 0;
    TareaIA *ordenada = nullptr;
    TareaIA *listaSecundaria = nullptr;

    cout << "Ingrese el maximo peso computacional que podra realizar el satelite: "; cin >> umbral;
    while (actual != nullptr)
    {
        total = actual->peso_computacional + total;
        actual = actual->prox;
    }
    actual = inicio;
    while (actual != nullptr)
    {
        TareaIA *siguiente = actual->prox;
        if (ordenada == nullptr || actual->urgencia <= ordenada->urgencia)
        {
            actual->prox = ordenada;
            ordenada = actual;
        }                           
        else 
        {
            TareaIA *aux = ordenada;
            while (aux->prox != nullptr && aux->prox->urgencia < actual->urgencia){
                aux = aux->prox;
            }
            actual->prox = aux->prox;
            aux->prox = actual;
        }
        actual = siguiente;
    }
    while (ordenada != nullptr)
    {
        TareaIA *aux = ordenada;
        if (total > umbral)
        {
            ordenada = ordenada->prox; 
            total = total - aux->peso_computacional; 
            aux->prox = listaSecundaria; 
            listaSecundaria = aux; 
        }
        else
        {
            break;
        }
    }
    inicio = ordenada;
    int segundos_espera = 4;
    cout << "Iniciando el ordenamiento, espere " << segundos_espera << " segundos..." << endl;
    for (int i = segundos_espera; i > 0; --i) 
    {
        cout << i << " segundos restantes..." << endl;
        Sleep(1000);
    }
    // CORRECCIÓN: Se usa inicio en vez de ordenada (ya apuntan al mismo lugar, pero es más claro y seguro)
    cout << "Se han eliminado los elementos de la lista y quedaria: " << endl;
    mostrarLista(inicio);
    cout << "Y en la lista secundaria estan: " << endl;
    mostrarLista(listaSecundaria);
    // CORRECCIÓN: Se libera la lista secundaria para evitar memory leak
    while (listaSecundaria != nullptr)
    {
        TareaIA *temp = listaSecundaria;
        listaSecundaria = listaSecundaria->prox;
        delete temp;
    }
}

// El sistema elimina de forma automatica el nodo que presente la peor eficiencia operativa
// definida matematicamente como la menor relacion entre su urgencia y su consumo energetico: Urgencia/consumo
void eliminarpeoreficiencia(TareaIA *&inicio)
{
    if (listaVacia(inicio)) {
        cout << "La lista no cuenta con suficientes elementos" << endl;
        return;
    }
    // CORRECCIÓN: peorAnterior rastrea el nodo ANTERIOR al peor, no el peor mismo
    TareaIA *peor = inicio;
    TareaIA *peorAnterior = nullptr;
    TareaIA *anterior = nullptr;
    TareaIA *aux = inicio;

    // CORRECCIÓN: División en float para no hacer division entera
    double peor_eficiencia = (double)peor->urgencia / (double)peor->consumo_energetico;

    while (aux != nullptr)
    {
        double eficiencia_actual = (double)aux->urgencia / (double)aux->consumo_energetico;
        if (eficiencia_actual < peor_eficiencia)
        {
            peor_eficiencia = eficiencia_actual;
            peor = aux;
            peorAnterior = anterior;
        }
        anterior = aux;
        aux = aux->prox;
    }

    cout << "La tarea con peor eficiencia es: " << peor->id_alfanumerico
         << " (urgencia=" << peor->urgencia
         << ", consumo=" << peor->consumo_energetico
         << ", eficiencia=" << peor_eficiencia << ")" << endl;
    cout << "La tarea con peor eficiencia esta siendo borrada..." << endl;

    // CORRECCIÓN: Se desenlaza correctamente usando peorAnterior
    if (peorAnterior == nullptr)
    {
        // El peor nodo es el primero de la lista
        inicio = peor->prox;
    }
    else
    {
        peorAnterior->prox = peor->prox;
    }
    delete peor;

    cout << "La tarea ha sido eliminada." << endl;
    cout << "La lista nueva es: " << endl;
    mostrarLista(inicio);
}

// Guarda el estado completo de la lista en un archivo TXT
void guardarEnArchivo(TareaIA *inicio, string nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        TareaIA *aux = inicio;
        while (aux != nullptr)
        {
            archivo << aux->id_alfanumerico << " "
                    << aux->tipo_algoritmo << " "
                    << aux->peso_computacional << " "
                    << aux->latencia_max << " "
                    << aux->consumo_energetico << " "
                    << aux->urgencia << "\n";
            aux = aux->prox;
        }
        archivo.close();
        cout << "Informacion guardada en " << nombreArchivo << " exitosamente." << endl;
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo para guardar datos." << endl;
    }
}

// Carga los elementos desde el archivo TXT y reconstruye la lista al iniciar
void cargarDesdeArchivo(TareaIA *&inicio, string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        string id, tipo;
        float peso, latencia, consumo;
        int urgencia;

        while (archivo >> id >> tipo >> peso >> latencia >> consumo >> urgencia)
        {
            TareaIA *nuevo = new TareaIA;
            nuevo->id_alfanumerico = id;
            nuevo->tipo_algoritmo = tipo;
            nuevo->peso_computacional = peso;
            nuevo->latencia_max = latencia;
            nuevo->consumo_energetico = consumo;
            nuevo->urgencia = urgencia;
            nuevo->prox = nullptr;

            insertarUltimo_Nodo(inicio, nuevo);

            // CORRECCIÓN: Se sincroniza el contador global directamente, sin llamadas ficticias a generarID
            try {
                int numId = stoi(id.substr(5));
                if (numId >= contadorID) {
                    contadorID = numId + 1;
                }
            } catch (...) {}
        }
        archivo.close();
        cout << "Datos cargados exitosamente desde " << nombreArchivo << "." << endl;
    }
    else
    {
        cout << "No se encontro un archivo previo (" << nombreArchivo << "). Se iniciara con la lista vacia." << endl;
    }
}

int main()
{
    TareaIA *lista = nullptr;
    TareaIA *listaorg = nullptr;
    int x = -1;
    // CORRECCIÓN: Se eliminó el ofstream que truncaba el archivo al inicio del programa
    // Primero se cargan los datos guardados previamente
    cargarDesdeArchivo(lista, "Lista_actual.txt");
    cargarDesdeArchivo(listaorg, "Lista_original.txt");
    while (x != 10){
        system("cls");
        cout << "------------ BIENVENIDO AL MENU DE LA MISION NEURO-LINK ------------"<< endl;
        cout << "con el siguiente menu podra acceder a distintas secciones del menu" << endl;
        cout << "porfavor presione correctamente los numeros indicados para comenzar" << endl;
        cout << "                                                                               " << endl;
        cout << " 1. Guardar en archivos " << endl;
        cout << " 2. Insertar en lista de forma aleatoria" << endl;
        cout << " 3. Imprimir la lista actual" << endl;
        cout << " 4. Imprimir la lista orignal" << endl;
        cout << " 5. Ordenar la lista en funcion del consumo energetico" << endl;
        cout << " 6. Eliminar nodos que supere un dato determinado de latencia" << endl;
        cout << " 7. Procesar cuantas tareas antes de agotar la bateria" << endl;
        cout << " 8. Mover tareas de menor urgencia a una lista de espera" << endl;
        cout << " 9. Eliminar peor eficiencia" << endl;
        cout << " 10. Salir del menu" << endl;
        cout << "______________________________________________________________________" << endl;
        cout << "Porfavor ingrese que accion desee realizar: "; cin >> x;
        while (x < 0 || x > 10)
        {
            cout << "Numero fuera del rango, porfavor ingrese un numero perteneciente al menu: ";
            cin >> x;
        }
        switch(x)
        {
            case 1:
                guardarEnArchivo(lista, "Lista_actual.txt");
                guardarEnArchivo(listaorg, "Lista_original.txt");
                break;
            case 2:
                cout << "Se empezo el procedimiendo de creacion de Tarea aleatoria" << endl;
                cout << "Desea insertar al principio (1), o al final (2)?: ";
                int z; cin >> z;
                cout << "Cuantas tareas desea agregar: ?";
                int y;cin >>y;
                if (z == 1)
                {
                    for (y>0;y--;)
                    {
                        cout << "Tarea situada de primera, preparando proceso de creacion..." << endl;
                        Sleep(1000);
                        TareaIA *nuevoNodo = crearNodo_Aleatorio();
                        TareaIA *copiaParaOriginal = clonarNodo(nuevoNodo);
                        insertarPrimero_Nodo(lista, nuevoNodo);
                        insertarPrimero_Nodo(listaorg, copiaParaOriginal);
                        cout << "Tarea creada y situada con exito en ambas listas." << endl;
                    }
                }
                else if (z == 2)
                {
                    for (y>0;y--;)
                    {
                        cout << "Tarea situada de ultima, preparando proceso de creacion..." << endl;
                        Sleep(1000);
                        TareaIA *nuevoNodo = crearNodo_Aleatorio();
                        TareaIA *copiaParaOriginal = clonarNodo(nuevoNodo);
                        insertarUltimo_Nodo(lista, nuevoNodo);
                        insertarUltimo_Nodo(listaorg, copiaParaOriginal);
                        cout << "Tarea creada y situada con exito en ambas listas." << endl;
                    }
                }
                else 
                {
                    cout << "Opcion invalida." << endl;
                }
                break;
            case 3:
                if (listaVacia(lista))
                {
                    cout << "la lista esta vacia." << endl;
                }
                else
                {
                    cout << "La lista es: " << endl;
                    mostrarLista(lista);
                }
                break;
            case 4:
                if (listaVacia(listaorg))
                {
                    cout << "la lista esta vacia." << endl;
                }
                else
                {
                    cout << "La lista es: " << endl;
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
                eliminarpeoreficiencia(lista);
                break;
            case 10:
                cout << "Guardando cambios antes de salir..." << endl;
                guardarEnArchivo(lista, "Lista_actual.txt");
                guardarEnArchivo(listaorg, "Lista_original.txt");
                cout << "Muchas gracias por usar el menu. ¡Cambio y fuera!";
                break;
        } 
        if (x != 10) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore(10000, '\n'); 
            cin.get();               
        }
    }
    return 0;
}