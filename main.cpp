#include <iostream>
#include <map>
#include "router.h"
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
map<char,router> R;
int *ru;
vector<char> eliminados;
map<char,router> leer_y_agregar();
map<char,router> full_ramas(map<char,router>);
void crear_red();
char ya_existe(map<char,router>,int *);
bool esta_vector(char,vector<char>);
map<char,router> nueva_red(void);
bool esta_visitado(char a,map<char,int> b);
map<char,router> dar_posibles_rutas(map<char,router>);
void mostrar(void);
int continuar();
int peso_ruta(string);
int main()
{
    bool seguir=1;
    srand(time(NULL));
    R=nueva_red();
    mostrar();

    int opt;
    cout<< "escriba 1(agregar router), 2(eliminar router), 3(agregar topologia por archivo),4(todas las rutas disponibles)" << endl;
    cin >> opt;
    while(seguir){

        switch(opt){

        case 1:{
            //agregar router
            char l;
            char g='A';
            int con=0;

            map<char,router>::iterator it;
            for (it=R.begin(); it!=R.end(); it++) {
                if(esta_vector(it->first,eliminados)==1){
                g=g+1;
                }
                else{g=it->first;con++;}
            }
            l=g+1;
            cout<< con << endl;
            router aux(l);
            char ko;
            int jum;
            for(int i=0;i<con;i++){
                ko='A'+i;
                cout << "escriba el valor de la ruta entre " << l << " y " << ko << endl;
                cin>>jum;
                aux.agregar_rutas_manuales(ko,jum);
                aux.agregar_rutas_manuales(l,0);
                R[ko].agregar_rutas_manuales(l,jum);
            }

            R.insert(pair<char,router>(l,aux));
            mostrar();
            cout<<"quiere seguir con el programa?ingrese 1 para continuar"<<endl;
            cout<<"y 0 cara salir"<<endl;
            cin>>seguir;
            if(seguir){
                opt=continuar();
            }
            break;}

        case 2:{
            //eliminar router
            char err;
            cout << "escriba el nombre del router a borrar" << endl;
            cin >> err;
            R.erase(err);
            router sen;
            map<char,router>::iterator it;
            for(it=R.begin();it!=R.end();it++){
                sen = it->second;
                sen.eliminar_rutas(err);
                R[it->first]=sen;
            }
            eliminados.push_back(err);
            mostrar();
            cout<<"quiere seguir con el programa?ingrese 1 para continuar"<<endl;
            cout<<"y 0 cara salir"<<endl;
            cin>>seguir;
            if(seguir){
                opt=continuar();
            }
            break;}

        case 3:{
            //agregar mapeo archivo
            R=leer_y_agregar();
            mostrar();
            cout<<"quiere seguir con el programa?ingrese 1 para continuar"<<endl;
            cout<<"y 0 cara salir"<<endl;
            cin>>seguir;
            if(seguir){
                opt=continuar();
            }
            break;}

        case 4:{
            //ruta optimizada entre 2 routers
            R=dar_posibles_rutas(R);
            mostrar();
            cout<<"quiere seguir con el programa?ingrese 1 para continuar"<<endl;
            cout<<"y 0 cara salir"<<endl;
            cin>>seguir;
            if(seguir){
                opt=continuar();
            }
            break;}

        default:
            cout<<"opción invalida"<<endl;
            cout<<"vuelva a ingresar una opción"<<endl;
            cin>>opt;
            break;

        }
    }
        return 0;
}

map<char,router> nueva_red(void)
{
    map <char,router> red;
    int n_routers=4;//rand()%10;
    srand(time(NULL));
    for(int i=0;i<n_routers;i++){
        router aux('A'+i);
        aux.agregar_rutas(n_routers);
        red.insert(pair<char,router>('A'+i,aux));
        red=aux.agregar_rutas('A'+i,red);
    }
    return red;
}

void mostrar(void)
{
    router temp;
    map<char,router>::iterator it;
    for(it=R.begin();it!=R.end();it++)
    {
        cout<<it->first;
        temp=it->second;
        temp.mostrar_topo();
    }
}

bool esta_visitado(char a,map<char,int> b){
    bool esta = 0;
    map<char,int>::iterator it;
    for (it=b.begin(); it!=b.end(); it++) {
        if(a == it->first){
            esta = 1;
            break;
        }
    }
return esta;
}


char ya_existe(map<char,router> k,int *a){
    char g='A';
    int con=0;
    map<char,router>::iterator it;
    for (it=k.begin(); it!=k.end(); it++) {
        if(esta_vector(it->first,eliminados)==1){
        g=g+1;
        }
        else{g=it->first;con++;}
    }
*a=con;
return g+1;
}


bool esta_vector(char a,vector<char> el){

    for (auto i= el.begin(); i!= el.end(); ++i){
        if(a==*i){
            return 1;
        }
    }
return 0;
}


map<char,router> leer_y_agregar(){
    string h;
    string po;
    int a;
    ifstream fe("D:/prueba.txt");
    map<char,router> red;
    vector<char> creado;
    while (!fe.eof()) {
        getline(fe,h);
        if(esta_vector(h[0],creado)==0){
            creado.push_back(h[0]);
            router aux(h[0]);
            //po= h.substr(3,h.size()-3);
            //if(istringstream(po)>>a){}
            aux.agregar_rutas_manuales(h[0],0);
            red.insert(pair<char,router>(h[0],aux));
        }
        if(esta_vector(h[1],creado)==0){
            creado.push_back(h[1]);
            router aux(h[1]);
            //po= h.substr(3,h.size()-3);
            //if(istringstream(po)>>a){}
            aux.agregar_rutas_manuales(h[1],0);
            red.insert(pair<char,router>(h[1],aux));
        }
        po= h.substr(3,h.size()-3);
        if(istringstream(po)>>a){}
        red[h[0]].agregar_rutas_manuales(h[1],a);
        red[h[1]].agregar_rutas_manuales(h[0],a);
    }

    fe.close();
return red;
}


map<char,router> full_ramas(map<char,router> p){
    map<char,router>::iterator it;
    for(it=p.begin();it!=p.end();it++){
        it->second.sacar_ramas();
    }
return p;
}

bool esta_en_save(char a,string b){
    int y=b.size();
    for(int i=0;i<y;i++){
        if(b[i]==a){return 1;}
    }
return 0;
}

map<char,router> dar_posibles_rutas(map<char,router> R){
    vector <char> ramain;
    map <string,int> saru;
    router tem;
    char x, in = 'A', destino = 'D', actual = 'A', aux;
    int y, rama = 0, menor = 0;
    cout<<"ingrese el router de origen"<<endl;
    cin>>in;
    cout<<"ingrese el router destino"<<endl;
    cin>>destino;
    map<char,router>::iterator ita;
    while(R.find(in)==R.end()||R.find(destino)==R.end()){
        cout<<"uno de los routers ingresados no existe"<<endl;
        cout<<"ingrese el router de origen"<<endl;
        cin>>in;
        cout<<"ingrese el router destino"<<endl;
        cin>>destino;
    }
    map <char,int> visitados, sacar2;
    string mascorta="";
    R=full_ramas(R);
    R[destino].cerrar_destino();
    int ramainicial = R[in].sacar_ramas();
    visitados.insert(pair<char,int>(in,ramainicial));
    map<char,int> sacar = R[in].dar_mapa();
        string save;
        save.push_back(in);

        while(sacar[actual]==-1 || sacar[actual]==0){
            if(R.find(actual)!=R.end()){
                actual++;
            }
        }

        if (destino==actual){
            visitados[in]= visitados[in]-1;
            ramain.push_back(actual);
            //menor = R[in].costo_camino(actual);
            actual++;
        }

        while(sacar[actual]==-1 || sacar[actual]==0){
            if(R.find(actual)!=R.end()){
                actual++;
            }
        }
        save.push_back(actual);
        R[in].cerrar_ruta(actual);
        while (actual!=destino && R.find(actual)!=R.end()){
            tem = R[actual];
            rama = tem.sacar_ramas();
            visitados.insert(pair<char,int>(actual,rama));
            sacar2 = tem.dar_mapa();
            map<char,int>::iterator it;
            for (it=sacar2.begin(); it!=sacar2.end(); it++) {
                x = it->first;
                y = it->second;

                if(y!=-1 && y!=0 && esta_visitado(x,visitados)!=1){
                    R[actual].cerrar_ruta(x);
                    actual = x;
                    save.push_back(actual);
                    break;
                }
            }
        }
        while(R.find(actual)==R.end()){
            actual++;
        }

        map<char,int>::iterator it;
        for (it=visitados.begin(); it!=visitados.end(); it++) { //imprime la primera ruta
            R[it->first].ver_caminos();
        }
        R[destino].ver_caminos();
        saru.insert(pair<string,int>(save,peso_ruta(save)));

        save.erase(save.size()-1,1);
        //menor=peso_ruta(save);
        R[save[save.size()-1]].cerrar_ruta(destino);//save.size()-1//

        while(ramainicial!=0) {
            while(in!=save[save.size()-1]){
                map<char,bool>duplica= R[save[save.size()-1]].sacar_pass();
                map<char,bool>::iterator it;
                int revisados=0;
                for (it=duplica.begin(); it!=duplica.end(); it++){

                    if(esta_en_save(it->first,save)==1 && it->second==0){
                        R[save[save.size()-1]].cerrar_ruta(it->first);
                        aux=save[save.size()-1];
                        break;
                    }

                    if(it->first==destino && it->second==0){
                        aux=save[save.size()-1];
                        save.push_back(destino);
                        saru.insert(pair<string,int>(save,peso_ruta(save)));
                        save.erase(save.size()-1,1);
                        R[save[save.size()-1]].cerrar_ruta(destino);
                        break;
                    }

                    if(it->second==0){
                        R[save[save.size()-1]].cerrar_ruta(it->first);
                        aux=save[save.size()-1];
                        save.push_back(it->first);//entra a routers anteriores//
                        break;
                    }
                    revisados++;
                    aux=save[save.size()-1];
                }
                if(revisados==R[aux].sacar_ramas('a')){
                    save.erase(save.size()-1,1);
                }
            }
        for(map<char,router>::iterator it2=R.begin();it2!=R.end();it2++){
            if(it2->first!=in && it2->first!=destino){
                R[it2->first].limpiar();
            }
        }
        ramainicial=ramainicial-1;
        //sacar una de las ramas de A que no tenga 1 para continuar el codigo
        map<char,bool>doppel= R[in].sacar_pass();
        map<char,bool>::iterator it;
        for (it=doppel.begin(); it!=doppel.end(); it++){
            if(it->second==0){
                R[in].cerrar_ruta(it->first);
                save.push_back(it->first);
                if(it->first==destino){
                    saru.insert(pair<string,int>(save,peso_ruta(save)));
                    save.erase(save.size()-1,1);
                }
                break;
            }

        }
       }
  map<string,int>::iterator ho=saru.begin();
  map<string,int>::iterator ho2;
  ho2=ho++;
  int a=0;
  for (ho=saru.begin(); ho!=saru.end(); ho++){
      if(ho2!=saru.end()){
          if(ho->second<=ho2->second && a==0){
              a++;
              menor=ho->second;mascorta=ho->first;
          }
          else if(ho->second>=ho2->second && a==0){
              a++;
              menor=ho->second;mascorta=ho->first;
          }
          if(ho->second<=ho2->second && a!=0){
              if(menor>=ho->second){
                  menor=ho->second;mascorta=ho->first;
              }
          }
          else if(ho->second>=ho2->second && a!=0){
              if(menor>=ho2->second){
                  menor=ho2->second;mascorta=ho2->first;
              }
          }
      }
      else{
          cout<< ho2->first <<" con costo "<<ho2->second<<endl;
          break;
      }
      cout<< ho->first <<" con costo "<<ho->second<<endl;
      ho2++;
  }
  cout<<"la ruta mas corta es "<<mascorta<<" con un peso de "<<menor<<endl;
  R[in].actualizar_links(destino,menor);
  R[destino].actualizar_links(in,menor);
  return R;
}

int peso_ruta(string ruta){
    int peso=0;
    for(unsigned long long pos=0;pos<ruta.size()-1;pos++){
        if(pos+1<ruta.size()){
            peso=R[ruta[pos]].costo_camino(ruta[pos+1])+peso;
        }
        else{break;}
    }
    return peso;
}

int continuar(){
    int opt;
    cout<< "escriba 1(agregar router), 2(eliminar router), 3(agregar topologia por archivo),4(todas las rutas disponibles)" << endl;
    cin>>opt;

    return opt;
}





