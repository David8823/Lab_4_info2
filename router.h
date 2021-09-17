#ifndef ROUTER_H
#define ROUTER_H
#include<map>
using namespace std;
class router
{
private:
    char nombre;
    map<char, int> links;
    map<char,bool> pass;
public:
    router();
    router(char);
    void limpiar();
    bool agregar_rutas(int);
    map<char,router> agregar_rutas(char,map<char,router>);
    void mostrar_topo(void);
    map<char,int> dar_mapa();
    int sacar_ramas();
    int sacar_ramas(char);
    int costo_camino(char);
    bool esta_visitado(char);
    void eliminar_rutas(char);
    void agregar_rutas_manuales(char le,int num);
    void cerrar_ruta(char);
    void ver_caminos();
    void cerrar_destino();
    void actualizar_links(char,int);
    map<char,bool> sacar_pass();
};

#endif // ROUTER_H
