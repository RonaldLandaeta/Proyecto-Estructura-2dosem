#include <iostream>
#include <string>
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
string generarID()
{
    static int contador = 1; 
    string idResultante = "TASK-" + to_string(contador);
    contador++; 
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
    std::uniform_int_distribution<int> dist(0, 4); // Elige un índice del 0 al 4
    return catalogo[dist(motor)];
}
int datos_Aleatorios()
{
    unsigned semilla = chrono::high_resolution_clock::now().time_since_epoch().count();
    static mt19937 motor(semilla);
    std::uniform_int_distribution<int> dist(0, 100); 
    return dist(motor);
}
int urgencia_aleatoria()
{
    unsigned semilla = chrono::high_resolution_clock::now().time_since_epoch().count();  
    static mt19937 motor(semilla);
    std::uniform_int_distribution<int> dist(1, 10); 
    return dist(motor);
}
TareaIA *crearNodo(string tipo, float peso, float latencia, float energia, int urgencia )
{
    TareaIA *nuevo = new TareaIA;
    nuevo->id_alfanumerico = generarID();
    nuevo->tipo_algoritmo = tipo;
    nuevo->peso_computacional = peso;
    nuevo->latencia_max = latencia;
    nuevo->consumo_energetico = energia;
    nuevo->urgencia = urgencia;
    nuevo->prox = NULL;
    return nuevo;
}
TareaIA *crearNodo_semi_Aleatorio(float peso, float latencia, float energia, int urgencia )
{
    TareaIA *nuevo = new TareaIA;
    nuevo->id_alfanumerico = generarID();
    nuevo->tipo_algoritmo = Tipo_algoritmo_aleatorio();
    nuevo->peso_computacional = peso;
    nuevo->latencia_max = latencia;
    nuevo->consumo_energetico = energia;
    nuevo->urgencia = urgencia;
    nuevo->prox = NULL;
    return nuevo;
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
    nuevo->prox = NULL;
    return nuevo;
}
bool listaVacia(TareaIA *inicio)
{
    return inicio == NULL;
}
void mostrarLista(TareaIA *inicio)
{
    TareaIA *mover;
    if (!listaVacia(inicio))
    {
        mover = inicio;
        while (mover != NULL)
        {
            cout << " |" << mover->id_alfanumerico << ", " << mover->tipo_algoritmo << ", " << mover->peso_computacional << ", " << mover->latencia_max << ", " << mover->consumo_energetico << ", " << mover->urgencia << "|->";
            mover = mover->prox;
        }
        cout << "NULL" << endl;
    }
    else
        cout << "Lista esta vacia" << endl;
}
void insertarUltimo(TareaIA *&inicio, string tipo, float peso, float latencia, float energia, int urgencia)
{
    TareaIA *nuevo = crearNodo(tipo, peso, latencia, energia, urgencia);
    if (listaVacia(inicio))
    {
    inicio = nuevo;
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
void insertarUltimo_semi_Aleatorio(TareaIA *&inicio,float peso, float latencia, float energia, int urgencia)
{
    TareaIA *nuevo = crearNodo_semi_Aleatorio(peso, latencia, energia, urgencia);
    if (listaVacia(inicio))
    {
    inicio = nuevo;
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
void insertarUltimo_Aleatorio(TareaIA *&inicio)
{
    TareaIA *nuevo = crearNodo_Aleatorio();
    if (listaVacia(inicio))
    {
    inicio = nuevo;
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
void insertarPrimero(TareaIA *&inicio, string tipo, float peso, float latencia, float energia, int urgencia)
{
    TareaIA *nuevo = crearNodo(tipo, peso, latencia, energia, urgencia);
    nuevo->prox = inicio;
    inicio = nuevo;
}
void insertarPrimero_semi_aleatorio(TareaIA *&inicio,float peso, float latencia, float energia, int urgencia)
{
    TareaIA *nuevo = crearNodo_semi_Aleatorio(peso, latencia, energia, urgencia);
    nuevo->prox = inicio;
    inicio = nuevo;
}
void insertarPrimero_Aleatorio(TareaIA *&inicio)
{
    TareaIA *nuevo = crearNodo_Aleatorio();
    nuevo->prox = inicio;
    inicio = nuevo;
}
void menorMayor (TareaIA *&inicio){
    TareaIA *ordenada = NULL;
    TareaIA *actual = inicio;
    if (inicio == NULL)
    { 
        cout << "No hay suficientes tareas en orbita para ordenar." << endl;
        return;
    }
    while (actual != NULL)
    {
        TareaIA *siguiente = actual->prox;
        if (ordenada == NULL || actual->consumo_energetico <= ordenada->consumo_energetico) 
        {
            actual->prox = ordenada; 
            ordenada = actual;
        }                          
        else 
        {
            TareaIA *aux = ordenada;
            while (aux->prox != NULL && aux->prox->consumo_energetico < actual->consumo_energetico) 
            {
                aux = aux->prox;
            }
            actual->prox = aux->prox;
            aux->prox = actual;
        }
        actual = siguiente;
    }
    inicio = ordenada;
    int segundos_espera = 4; 
    cout << "Iniciando el ordenamiento, faltan " << 5 << " segundos..." << endl;
        for (int i = segundos_espera; i > 0; --i) {
            cout << i << " segundos restantes..." << endl;
            Sleep(1000);
        }   
    cout << "REALIZADO! las tareas ordenadas ahora son las siguientes: " << endl;
    mostrarLista(inicio);
}
void descarte(TareaIA *&inicio)
{
    TareaIA *actual = inicio; 
    TareaIA *anterior = NULL;
    float tiempo;
    cout << "Indique el tiempo de espera maximo, se eliminaran los tiempos cuya latencia supere el tiempo de espera: "; 
    cin >> tiempo;
    while (actual != NULL)
    {
        if (tiempo > actual->latencia_max){
            TareaIA *borrar = actual;
            if (anterior == NULL)
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
    int segundos_espera = 4;
    cout << "Iniciando la eliminacion, faltan " << segundos_espera << " segundos..." << endl;
        for (int i = segundos_espera; i > 0; --i) 
        {
            cout << i << " segundos restantes..." << endl;
            Sleep(1000);
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
    while (aux != NULL)
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
    cout << "Iniciando la eliminacion, faltan " << segundos_espera << " segundos..." << endl;
    for (int i = segundos_espera; i > 0; --i)
    {
        cout << i << " segundos restantes..." << endl;
        Sleep(1000);
    }
    cout << "El total de tareas procesables son: " << contador << endl;
    if (aux != NULL)
    {
        cout << "Quedan " << energia_disponible << "W en la nave, por lo que" << aux->prox->id_alfanumerico << " que necesita " << aux->prox->consumo_energetico << "W no se pudo completar.";
    }
    else
    {
        cout << "Se completaron todas las tareas sin problemas.";
    }
    
}
void balanceodeCarga (TareaIA *&inicio)
{
    TareaIA *actual = inicio; float umbral; float total = 0; TareaIA *ordenada = NULL; TareaIA *listaSecundaria = NULL;
    cout << "Ingrese el maximo peso computacional que podra realizar el satelite: "; cin >> umbral;
    while (actual != NULL)
    {
        total = actual->peso_computacional + total;
        actual = actual->prox;
    }
    actual = inicio;
    while (actual != NULL)
    {
        TareaIA *siguiente = actual->prox;
        if (ordenada == NULL || actual->urgencia <= ordenada->urgencia)
        {
            actual->prox = ordenada;
            ordenada = actual;
        }                           
        else 
        {
            TareaIA *aux = ordenada;
            while (aux->prox != NULL && aux->prox->urgencia < actual->urgencia){
                aux = aux->prox;
            }
            actual->prox = aux->prox;
            aux->prox = actual;
        }
        actual = siguiente;
    }
    while (ordenada != NULL)
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
    cout << "Se han eliminado los elementos de la lista y quedaria: " << endl;
    mostrarLista(ordenada);
    cout << "Y en la lista secundaria estan: " << endl;
    mostrarLista(listaSecundaria);
}
// El sistema debe eliminar de forma automarica el nodo que presente la peor eficiencia operativa definida matematicamente como la menor relacion entre su urgencia y su consumo energetico.... Urgencia/consumo
// void eliminarpeoreficiencia(TareaIA *&inicio)
// {
//     if (listaVacia(inicio)) {
//         cout << "La lista no cuenta con suficientes elementos" << endl;
//         return;
//     }
//     TareaIA *peor = inicio;
//     TareaIA *anterior = inicio;
//     TareaIA *aux = inicio->prox;
//     {
//         while(aux!=nullptr){
//             int peor_urgencia=peor->urgencia;
//             int peor_consumo=peor->consumo_energetico;
//             double peor_caso = peor_urgencia/peor_consumo;
//             int urgencia = aux->urgencia;
//             int consumo = aux->consumo_energetico;
//             double caso = urgencia/consumo;
//                 if (peor_caso<caso){
//                 anterior=aux;
//                 aux=aux->prox;
//             }
//                 else{
//                     peor=aux;
//                     anterior=aux;
//                     aux=aux->prox;
//                 }
//         }
//         if (peor == inicio)
//         {
//             inicio = inicio->prox;
//             cout << "la tarea a eliminar es1 " << endl;
//             cout << peor << endl;
//             cout << "La tarea con peor eficiencia esta siendo borrada..." << endl;
//             delete peor;
//             cout << "La tarea ha sido eliminada";
//             cout << "La lista nueva es: " << endl;
//             mostrarLista(inicio);
//         }
//         else
//         {
//             TareaIA *prev = inicio;
//             while (prev->prox != peor && prev->prox != nullptr)
//             {
//                 prev = prev->prox;
//             }
//             if (prev->prox == peor)
//             {  
//                 prev->prox = peor->prox;
//                 cout << "la tarea a eliminar es2 " << endl;
//                 cout << peor << endl;
//                 cout << "La tarea con peor eficiencia esta siendo borrada..." << endl;
//                 delete peor;
//                 cout << "La tarea ha sido eliminada";
//                 cout << "La lista nueva es: " << endl;
//                 mostrarLista(inicio);
//             }
//         }
//         return;
//     }
// }

main()
{
    TareaIA *lista = NULL; TareaIA *listaorg = NULL;
    string id_alfanumerico, tipo_algoritmo;
    float peso_computacional, latencia_max, consumo_energetico;
    int urgencia, x = -1;
    while (x != 10){
        system ("cls");
        cout << "------------ BIENVENIDO AL MENU DE LA MISION NEURO-LINK ------------"<< endl;
        cout << "con el siguiente menu podra acceder a distintas secciones del menu" << endl;
        cout << "porfavor presione correctamente los numeros indicados para comenzar" << endl;
        cout << "                                                                               " << endl;
        cout << " 0. Modo desarrollador" << endl;
        cout << " 1. Insertar en lista de forma manual (Principio/Final)" << endl;
        cout << " 2. Insertar en lista de forma aleatoria" << endl;
        cout << " 3. Imprimir la lista actual" << endl;
        cout << " 4. Imprimir la lista orignal" << endl;
        cout << " 5. Ordenar la lista en funcion del consumo energetico" << endl;
        cout << " 6. Eliminar nodos que supere un dato determinado de latencia" << endl;
        cout << " 7. Procesar cuantas tareas antes de agotar la bateria" << endl;
        cout << " 8. Mover tareas de menor urgencia a una lista de espera" << endl;
        cout << " 9. eliminar peor eficiencia" << endl;
        cout << " 10. Salir del menu" << endl;
        cout << "______________________________________________________________________" << endl;
        cout << "Porfavor ingrese que accion desee realizar: "; cin >> x;
        while (x < 0 || x > 10)
        {
            cout << "Numero fuera del rango, porfavor ingrese un numero perteneciente al menu";
            cin >> x;
        }
        switch(x)
        {
            case 0:
                break;
            case 1:
                cout<<"Desea insertar al principio (1), o al final (2)?: "<<endl;
                int y; cin>>y;
                if(y==1)
                {
                    cout<<"La tarea sera insertada al inicio"<<endl;
                    Sleep(1000);
                    cout << "1. Se te ha generado un id predeterminado..."<<endl;
                    Sleep(1000);
                    cout << "2. Ingrese Tipo de Algoritmo, escogiendo alguno de los siguientes casos: (sin espacios): ";
                    cin >> tipo_algoritmo;
                    cout << "3. Ingrese Peso Computacional (TFLOPS): ";
                    cin >> peso_computacional;
                    cout << "4. Ingrese Latencia Maxima (tiempo en ms): ";
                    cin >> latencia_max;
                    cout << "5. Ingrese Consumo Energetico (Watts): ";
                    cin >> consumo_energetico;
                    cout << "6. Ingrese Nivel de Urgencia (1 al 10): ";
                    cin >> urgencia;
                    cout << "La lista actual es: ";
                    insertarPrimero(lista,tipo_algoritmo,peso_computacional,latencia_max,consumo_energetico,urgencia);
                    mostrarLista(lista);
                    break;
                }
                if (y==2)
                {
                    cout<<"La tarea sera insertada al final"<<endl;
                    Sleep(1000);
                    cout << "1. Se ha definido un id predeterminado..."<<endl;
                    Sleep(1000);
                    cout << "2. Ingrese Tipo de Algoritmo, escogiendo alguno de los siguientes casos: (sin espacios): ";
                    cout<<"Vision_Artificial"<<endl;
                    cout<<"Nlp_Radio"<<endl;
                    cout<<"Analisis_Termico"<<endl;
                    cout<<"Telemetria_Predictiva"<<endl;
                    cout<<"Cifrado_Cuantico"<<endl;
                    cin >> tipo_algoritmo;
                    cout << "3. Ingrese Peso Computacional (TFLOPS): ";
                    cin >> peso_computacional;
                    cout << "4. Ingrese Latencia Maxima (tiempo en ms): ";
                    cin >> latencia_max;
                    cout << "5. Ingrese Consumo Energetico (Watts): ";
                    cin >> consumo_energetico;
                    cout << "6. Ingrese Nivel de Urgencia (1 al 10): ";
                    cin >> urgencia;
                    cout << "La lista actual es: ";
                    insertarUltimo(lista,tipo_algoritmo,peso_computacional,latencia_max,consumo_energetico,urgencia);
                    mostrarLista(lista);
                    break;
                }
                else
                {
                    cout<<"opcion no valida hjpt"<<endl;
                    break;
                }
                break;
            case 2:
                cout<<"Se empezo el procedimiendo de creacion de Tarea aleatoria"<<endl;
                cout<<"Desea insertar al principio (1), o al final (2)?: "<<endl;
                int z; cin>>z;
                if (z==1)
                {
                    cout<<"Tarea situada de primera, prepadando proceso de creacion..."<<endl;
                    Sleep(1000);
                    insertarPrimero_Aleatorio(lista);
                    cout<<"Tarea creada y situada con extio"<<endl;
                    cout << "La lista actual es: ";
                    mostrarLista(lista);
                    break;
                }
                if (z==2)
                {
                    cout<<"Tarea situada de ultima, prepadando proceso de creacion..."<<endl;
                    Sleep(1000);
                    insertarUltimo_Aleatorio(lista);
                    cout<<"Tarea creada y situada con extio"<<endl;
                    cout << "La lista actual es: ";
                    mostrarLista(lista);
                    break;
                }
                else 
                {
                    cout<<"Eliga bien perro"<<endl;
                }
                break;
            case 3:
                if (listaVacia(lista))
                {
                    cout << "la lista esta vacia.";
                }
                else
                {
                    cout << "La lista es: ";
                    mostrarLista(lista);
                }
                break;
            case 4:
                if (listaVacia(lista))
                {
                    cout << "la lista esta vacia.";
                }
                else
                {
                    cout << "La lista es: ";
                    mostrarLista(listaorg);
                }
                break;
            case 5:
                menorMayor(lista);
                break;
            case 6:
                cout << "Iniciando la eliminacion, faltan 5 segundos..." << endl;
                descarte(lista);
                break;
            case 7:
                paseOrbita(lista);
                break;
            case 8:
                cout << "Iniciando la eliminacion, faltan 5 segundos..."  << endl;
                balanceodeCarga(lista);
                break;
            // case 9:
            //     cout << "Procediendo con la eliminacion de eficiencia"<<endl;
            //     eliminarpeoreficiencia(lista);
            //     break;
            case 10:
            cout << "Muchas gracias por usar el menu";
                break;
    }
        if (x != 10) {
            cout << "Presione ENTER para continuar...";
            cin.ignore(10000, '\n'); 
            cin.get();               
        }
    }
    return 0;
}
