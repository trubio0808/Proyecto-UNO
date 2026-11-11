#include<iostream>
#include<cctype>
#include<string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Se documentan las reglas del juego.
void mostrar_reglas(){
    cout<<R"reglas(Reglas del juego UNO.
Objetivo:

Quedarte sin cartas en la mano antes que los demas. 
Quien lo logra gana la ronda. 
Se pueden jugar varias rondas, y el ganador definitivo es el jugador que gane mas rondas.

Jugadores: De 2 a 4 jugadores.

Las cartas: 108 en total
Cartas de numero: cuatro colores (azul, verde, rojo y amarillo). Cada color tiene un 0 y dos cartas de cada numero del 1 al 9.
Cartas de accion: cada color tiene 2 Salta, 2 Reversa y 2 Roba +2.
Cartas comodin: 4 Comodin y 4 Roba +4.

Inicio de la ronda:
Se barajan las cartas y se reparten 7 a cada jugador.
Las cartas que sobran forman el mazo para robar, boca abajo.
Se pone una carta boca arriba para iniciar la pila de descarte. Esa es la carta activa.

Como se juega:
Los jugadores juegan por turnos, uno despues del otro.
En tu turno debes jugar una carta que coincida con la carta activa en color, numero o simbolo. 
Tambien puedes jugar un comodin en cualquier momento.
Si no tienes ninguna carta que puedas jugar, robas una carta del mazo.
Si la carta que robaste se puede jugar, puedes jugarla de inmediato. Si no, la guardas y el turno pasa al siguiente jugador.
Si el mazo para robar se acaba, se vuelven a usar las cartas de la pila de descarte, menos la carta activa.

Cartas de accion:
Salta: el siguiente jugador pierde su turno.
Reversa: cambia el sentido del juego.
Roba +2: el siguiente jugador roba 2 cartas y pierde su turno.
Comodin: eliges el color con el que se va a seguir jugando.
Roba +4: eliges el color, y el siguiente jugador roba 4 cartas y pierde su turno.

Ganar:
Quien se queda sin cartas primero gana la ronda y suma una victoria.
Se pueden jugar tantas rondas como quieran.
Cuando termina el juego, gana quien tenga mas rondas ganadas.)reglas"<<endl<<endl;
}

// Funcion menu principal devuelve la opcion elegida por el usuario.
int menu (){
    int respuesta;
    cout<<"Bienvenido al juego UNO"<< endl;
    cout<<"oprime 1 para jugar"<<endl;
    cout<<"oprime 2 para salir"<<endl;
    cout<<"oprime 3 para conocer las reglas del juego"<<endl;

    cin>> respuesta;

    return respuesta;

}

// Definicion de la estructura con la informacion de cada carta
struct carta{
    int numero;
    string color;
    string tipo;
    bool estatus;
};

// Matriz con todas las cartas que conforman el juego, cada carta inicia disponible para jugar.

carta mazo[5][25]={
 {{0, "azul","normal", true}, {1, "azul","normal",true},{2, "azul","normal",true}, {3, "azul","normal",true},{4, "azul","normal",true}, {5, "azul","normal",true}, {6, "azul","normal",true}, {7, "azul","normal",true}, {8, "azul","normal",true},
 {9, "azul","normal",true}, {1, "azul","normal",true},{2, "azul","normal",true}, {3, "azul","normal",true},{4, "azul","normal",true}, {5, "azul","normal",true}, {6, "azul","normal",true}, {7, "azul","normal",true}, {8, "azul","normal",true},{9, "azul","normal",true},
  {10, "azul","+2",true}, {10, "azul","+2",true},{10, "azul","salta",true}, {10, "azul","reversa",true},{10, "azul","salta",true}, {10, "azul","reversa",true}},

 {{0, "rojo","normal",true}, {1, "rojo","normal",true},{2, "rojo","normal",true}, {3, "rojo","normal",true},{4, "rojo","normal",true}, {5, "rojo","normal",true}, {6, "rojo","normal",true}, {7, "rojo","normal",true}, {8, "rojo","normal",true},
 {9, "rojo","normal",true}, {1, "rojo","normal",true},{2, "rojo","normal",true}, {3, "rojo","normal",true},{4, "rojo","normal",true}, {5, "rojo","normal",true}, {6, "rojo","normal",true}, {7, "rojo","normal",true}, {8, "rojo","normal",true},{9, "rojo","normal",true},
  {10, "rojo","+2",true}, {10, "rojo","+2",true},{10, "rojo","salta",true}, {10, "rojo","reversa",true},{10, "rojo","salta",true}, {10, "rojo","reversa",true}},

 {{0, "verde","normal",true}, {1, "verde","normal",true},{2, "verde","normal",true}, {3, "verde","normal",true},{4, "verde","normal",true}, {5, "verde","normal",true}, {6, "verde","normal",true}, {7, "verde","normal",true}, {8, "verde","normal",true},
 {9, "verde","normal",true}, {1, "verde","normal",true},{2, "verde","normal",true}, {3, "verde","normal",true},{4, "verde","normal",true}, {5, "verde","normal",true}, {6, "verde","normal",true}, {7, "verde","normal",true}, {8, "verde","normal",true},{9, "verde","normal",true},
  {10, "verde","+2",true}, {10, "verde","+2",true},{10, "verde","salta",true}, {10, "verde","reversa",true},{10, "verde","salta",true}, {10, "verde","reversa",true}},

 {{0, "amarillo","normal",true}, {1, "amarillo","normal",true},{2, "amarillo","normal",true}, {3, "amarillo","normal",true},{4, "amarillo","normal",true}, {5, "amarillo","normal",true}, {6, "amarillo","normal",true}, {7, "amarillo","normal",true}, {8, "amarillo","normal",true},
 {9, "amarillo","normal",true}, {1, "amarillo","normal",true},{2, "amarillo","normal",true}, {3, "amarillo","normal",true},{4, "amarillo","normal",true}, {5, "amarillo","normal",true}, {6, "amarillo","normal",true}, {7, "amarillo","normal",true}, {8, "amarillo","normal",true},{9, "amarillo","normal",true},
  {10, "amarillo","+2",true}, {10, "amarillo","+2",true},{10, "amarillo","salta",true}, {10, "amarillo","reversa",true},{10, "amarillo","salta",true}, {10, "amarillo","reversa",true}},

 {{11, "+ 4", "+4",true},{11, "+4", "+4",true},{11, "+4", "+4",true},{11, "+4", "+4",true}, {11, "cambio color", "cambio color",true},{11, "cambio color", "cambio color",true},{11, "cambio color", "cambio color",true},{11, "cambio color", "cambio color",true}}
};

struct registro{
    string nombre;
    int victorias = 0;
};

struct cartajugadores{
    int filamazo = 0;
    int colmazo = 0;
};

cartajugadores jugadores[5][100]={};

void repartir_cartas(carta mazo[5][25], int i, int cartasarepartir, cartajugadores jugadores[4][100]){
    int fila = 0;
    int col = 0;
    
    // Asigna n cartas(cartas a repartir) al jugador correspondiente (i)
    for(int x=0; x < cartasarepartir; x++){

        // Busca dos numeros aleatoreos para fila y columna de la matriz mazo hasta encontrar uno disponible
        do{
            fila = rand() % 5;
            if(fila == 4){
                col = rand() % 8;   
            }else{
                col = rand() % 25;
            } 
        } while(mazo[fila][col].estatus == false);

        // Busca dentro de la matriz de jugadores donde ubicar la carta seleccionada  
        if (i == 5){  //identifica la carta superior en juego
            jugadores[i][0].filamazo = fila;
            jugadores[i][0].colmazo = col;
            mazo[fila][col].estatus=false;
        }else{ //carta para los jugadores
            for(int J =0; J<100;J++){
                if(jugadores[i][J].filamazo == -1){
                    jugadores[i][J].filamazo = fila;
                    jugadores[i][J].colmazo = col;
                    mazo[fila][col].estatus=false;
                    break;
                }     
            }
        }        
    }
}

int siguienteturno(int jugadoractual, int njugadores, int &sentidoavance){
    jugadoractual += sentidoavance;
    if (jugadoractual < 0){
        jugadoractual = njugadores-1;
    }else if(jugadoractual >= njugadores){
        jugadoractual -= njugadores;
    }
    
    //falta sentido avance
    return jugadoractual;

}

char menujugador(cartajugadores jugadores[5][100], carta mazo[5][25], int jugadoract){
    int x = 0;
    int y = 0;

    //muestra carta superior
    x = jugadores[5][0].filamazo;
    y = jugadores[5][0].colmazo;
    
    cout<<"Carta superior: "<<mazo[x][y].numero<<" "<<mazo[x][y].color <<" "<< mazo[x][y].tipo<<endl;

    //Recorre la matriz de jugadores e imprime las cartas del jugador actual
    cout<< "Cartas del jugador: "<<jugadoract<<endl;
    for(int J = 0; J < 100; J++){

        if(jugadores[jugadoract][J].filamazo != -1){
            x = jugadores[jugadoract][J].filamazo;
            y = jugadores[jugadoract][J].colmazo;

            cout<< "carta: "<< J <<" "<< mazo[x][y].numero<<" "<<mazo[x][y].color <<" "<< mazo[x][y].tipo<<endl;
        }
    }

    // muestra menu para que el jugador elija la opcion a seguir
    char opj;
    do{
        cout<<"R. robar   U.gritar uno    J.jugar"<< endl;
        cout<<"Indique cual sera su accion a seguir (R, U, J): "<<endl;
        cin>> opj;

        return opj;

    } while (opj != 'R' && opj != 'U' && opj != 'J');
    
    
}

int main(){
    std::srand(std::time(nullptr));
    int njugadores;
    int opcion;
    char opj;
    int sentidoavance = 1;
    bool ganador = false;

    //Se inicializa la matriz jugadores
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 100; j++){
            jugadores[i][j].filamazo = -1;
            jugadores[i][j].colmazo = -1;
        }
        
    }
    
    
    do{

        // Se llama la funcion menu 
        opcion = menu();

        // Se elige la opcion jugar
        if (opcion == 1){
  
            //solicita numero de jugadores y verifica el rango permitido entre 2 y 4
            do{
                
                cout<<"¿cuantos jugadores quieren jugar (min 2, max 4)? "<<endl;
                cin>> njugadores;

            }while(njugadores<2 || njugadores>4 );

            //Define un arreglo tipo struct, y con una longitud del numero jugadores 
            registro usuarios [njugadores];

            //Solicita el nombre de los jugadores y los guarda en el arreglo 
            for(int i=0; i<njugadores; i++){
                cout<<"ingrese nombre del jugador   "<< i+1 <<endl;
                cin>> usuarios[i].nombre;
            }

            //Se reparten de manera aleatoria las 7 cartas para cada jugador
            for(int i=0; i < njugadores; i++){
                repartir_cartas(mazo, i, 7, jugadores);
            }

            //Se selecciona la carta inicial de juego
            repartir_cartas(mazo, 5, 1, jugadores);

            int jugadoract = 0;
            // Se inicia el juego
            do{

                //Recibe opcion jugador
                opj=menujugador(jugadores, mazo, jugadoract);

                if(opj == 'J'){
                    cout<<"elijio j"<<endl;
                    ganador = true;
                }else if(opj == 'R'){
                    cout<<"elijio r"<<endl;
                     ganador = true;
                    //repartir_cartas(mazo, int posiciondeljugador, 1);

                }else if(opj == 'U'){
                    cout<<"elijio u"<<endl;
                     ganador = true;

                }

            }while(ganador=false);
           
            
        }
        
        // Se elige la opcion salir
        if(opcion == 2){
            break;
        }

        // Se elige la opcion reglas del juego
        if(opcion==3){
            mostrar_reglas();
        }


    }while(opcion != 2);

return 0;

}
