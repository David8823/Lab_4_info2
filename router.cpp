#include "router.h"
#include <iostream>
#include <map>
using namespace std;
router::router(){
    cout<<" "<<endl;
}
router::router(char na)
{
    nombre=na;
}

bool router::agregar_rutas(int n_routers)
{
    char letra = 'A';
    int peso;

    if(n_routers<=0){
        return false;
    }

    for (int i=0; i<n_routers; i++) {
        peso = rand()%16 - 1;
        if (letra == nombre){
            links[letra] = 0;
        }else {
            while(peso==0){
                peso = rand()%11 - 1;
            }
            links[letra] = peso;
        }
        letra++;
    }
    return true;
}

void router::mostrar_topo(void){
    map<char,int>::iterator it;
    for (it=links.begin(); it!=links.end(); it++) {
        cout<<"|\t"<<it->first<<":"<<it->second<<"\t";
    }
    cout<<"|" <<endl;
}

map<char,router> router::agregar_rutas(char actual,map<char,router> red)
{
    char comp='A';
    map<char,int> comparar,comparar2;
    if(actual!=comp){
        for(map<char,router>::iterator it=red.begin();it!=red.end();it++)
        {
            router aux=it->second;
            comparar=aux.links;
            if(it->first!=actual)
            {
                router aux2=red[actual];
                comparar2=aux2.links;
                comparar2[it->first]=comparar[actual];
                aux2.links=comparar2;
                red[actual]=aux2;
            }
        }
    }
    return red;
}

map<char,int> router::dar_mapa(){

    map<char,int> a = links;
    return a;
}

int router::sacar_ramas(){
    int ramas=0;
    map<char,int>::iterator it;
    for (it=links.begin(); it!=links.end(); it++) {
        if (it->second!=0 && it->second!=-1){
         ramas++;
         pass.insert(pair<char,bool> (it->first,0));
     }
    }
    return ramas;
}
int router::sacar_ramas(char a){
    int ramas=0;
    map<char,int>::iterator it;
    for (it=links.begin(); it!=links.end(); it++) {
        if (it->second!=0 && it->second!=-1){
         ramas++;
     }
    }
    return ramas;
}

int router::costo_camino(char a){
    int p = links[a];
    return p;
}

bool router::esta_visitado(char a){
    bool esta = 0;
    map<char,int>::iterator it;
    for (it=links.begin(); it!=links.end(); it++) {
        if(a == it->first){
            esta = 1;
            break;
        }
    }
return esta;
}

void router::eliminar_rutas(char sup){
    links.erase(sup);
}

void router::agregar_rutas_manuales(char le,int num){

    links.insert(pair<char,int>(le,num));
}

void router::cerrar_ruta(char y){
    pass[y]=1;
}

void router::ver_caminos(){
    map<char,bool>::iterator it;
    for (it=pass.begin(); it!=pass.end(); it++){
        //cout << it->first << " = " << it->second <<endl;

    }
}

void router::cerrar_destino(){
    map<char,bool>::iterator it;
    for (it=pass.begin(); it!=pass.end(); it++){
        it->second=1;
    }
}

map<char,bool> router::sacar_pass(){
    map<char,bool> tem;
    tem=pass;

return tem;
}

void router::limpiar(){
    map<char,bool>::iterator it;
    for(it=pass.begin(); it!=pass.end();it++){
        pass[it->first]=0;
    }
}

void router::actualizar_links(char destino,int costo){
    links[destino]=costo;
}
