
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cctype>
#include "rlutil.h"
using namespace rlutil;

using namespace std;

#include "Platos.h"





int main()
{
    int opc;
    while (true)
    {

        cout<<"MENU PIRNCIPAL"<<endl<<endl<<"------------------------------"<<endl<<endl;
        cout<< "1 - Platos"<<endl;
        cout<< "2 - Clientes"<<endl;
        cout<< "3 - Pedidos"<<endl;
        cout<< "4 - Reportes"<<endl;
        cout<< "5 - Configuracion"<<endl;
        cout<< "0 - Salir"<<endl<<endl;
        cout<<endl<<"------------------------------"<<endl<<endl;
        cout<< "INGRESE OPCION: "<<endl;
        cin>>opc;

        switch (opc)
        {
        case 1:
            cls();
            Menu_Platos();
            break;

//  case 2:
//  break;

        default:
            cout<<"OPCION INCORRECTA"<<endl;;
            break;
        case 0:
            return 0;
            break;


        }
        cls();
    }
    return 0;
}
