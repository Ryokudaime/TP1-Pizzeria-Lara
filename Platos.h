#ifndef PLATOS_H_INCLUDED
#define PLATOS_H_INCLUDED


struct Platos
{
    int    ID;
    char   Nombre[50];
    float  Costo;
    float  Valor;
    int    TemPrep;
    int    IDResto;
    int    comResto;
    int    IDCat;
    bool   Estado;
};




//declaracion de dir

const char *Dir_Platos= "Platos.dat";


//definicion
void Menu_Platos(Platos);
bool cargarPlatos(struct Platos);
int buscarID(int);
bool SavePlatos(struct Platos);
void ShowPlatos();
void Mostrar_Platos(Platos);
void listarxID();
int CantPlatos();
Platos leerID(int);
void Mod_Plato();
bool Mod_file_Platos(Platos, int);
void Supr_Plato();
Platos leerIDResto(int);
int buscarIDResto(int);
void Listar_Platos_Resto();

//FUNCIONES


void Mod_Plato(){
    //MODIFICACION DE PLATO
    /*La opción Modificar Plato deberá solicitar el ID de un plato y
      permitir modificar el costo de venta y el tiempo de preparación.*/

    cls();
    int id, pos,opc;
    bool salir=true;
    cout << "ID a Modificar: ";
    cin >> id;
    pos = buscarID(id);
    if (pos >= 0)
    {
        while (salir)
        {
            Platos vPlatos= leerID(pos);
            Mostrar_Platos(vPlatos);
            cout<<endl<<"-----------------------------";
            cout<<endl<<"DESEA MODIFICAR PLATO? ";
            cout<<endl<<"1 - SI";
            cout<<endl<<"2 - BUSCAR OTRO";
            cout<<endl<<"0 - VOLVER AL MENU ANTERIOR";
            cout<<endl<<"-----------------------------"<<endl;
            cout<<endl<<"INGRESE OPCION: ";
            cin >> opc;
            switch(opc)
            {
            case 1:
            cout<<"COSTO DE PREPARACION: $"<<vPlatos.Costo;
            cout<<endl<<"Ingrese NUEVO costo de Venta (debe ser mayor a Valor de costo): $";
            cin>>vPlatos.Valor;
            cout<<endl<<"Ingrese NUEVO tiempo de elaboracino: " ;
            cin>>vPlatos.TemPrep;

                if((vPlatos.Valor>vPlatos.Costo)&&(vPlatos.TemPrep>0))
                {

                    if( Mod_file_Platos(vPlatos,pos))
                    {
                       cout<<endl<<"----------------------------------------";
                       cout<<endl<<"EXITO EN MODIFICAR EL ARCHIVO PLATOS.DAT";
                       cout<<endl<<"----------------------------------------";

                    }

                    else
                    {
                        cout<<endl<<"------------------------------------";
                        cout<<endl<<"NO SE MODIFICO EL ARCHIVO PLATOS.DAT";
                        cout<<endl<<"------------------------------------";
                    }

                }
                else
                {
                    cout<<endl<<"NO SE CARGO CORRECTAMENTE LA MODIFICACION DEL PLATO"<<endl;
                    getch();
                    cls();
                    salir=false;
                }
                break;

            case 2:
                cls();
                Mod_Plato();
                break;

            case 0:
                cls();
                salir=false;
                break;

            default:
                cout<<"OPCION INCORRECTA"<<endl;getch();
                break;
            }
        }

    }
    else
    {
        cout << "ID INCORRECTO INGRESE NUEVAMENTE.";
        getch();
        cls();
    }


}

Platos leerID(int pos)
{

    Platos vPlatos;
    FILE *p;
    p = fopen(Dir_Platos, "rb");
    if (p == NULL)
    {
        vPlatos.ID = -1;
        return vPlatos;
    }
    fseek(p, pos * sizeof(Platos),SEEK_SET);
    fread(&vPlatos, sizeof(Platos), 1, p);
    fclose(p);
    return vPlatos;
}



int buscarID(int ID){
    //BUSCA ID EN FILE PLATOS.DAT Y COMPARA SI ESTA O NO
    Platos vPlatos;
    int i=0;
    FILE *p;
    p = fopen(Dir_Platos, "rb");
    if (p == NULL)
    {
        return -2;
    }
    while (fread(&vPlatos, sizeof(Platos), 1, p))
    {
        if (vPlatos.ID == ID)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}


void listarxID(){

//LISTAR POR ID LOS PLATOS
    cls();
    int id, pos;
    cout << "ID a buscar: ";
    cin >> id;
    pos = buscarID(id);
    if (pos >= 0)
    {
        Platos vPlatos= leerID(pos);
        Mostrar_Platos(vPlatos);
    }
    else
    {
        cout << "No existe el id buscado.";
        getch();
        cls();
    }
}


void Listar_Platos_Resto(){
// MUESTRA PLATOS POR RESTAURANT
 cls();
  int cant = CantPlatos(), i,IDresto;
    cout<<"ingrese ID del Restaurante: ";
    cin>>IDresto;

  if (cant == 0){
    cout << "No hay Platos";
    return;
  }
  Platos *vPlatos;
  vPlatos = (Platos *) malloc(cant * sizeof(Platos));
  if (vPlatos == NULL){
    cout << "No hay memoria para continuar...";
    return;
  }
  FILE *p;
  p = fopen(Dir_Platos, "rb");
  if (p == NULL){
    free(vPlatos);
    cout << "No existe el archivo...";
    return;
  }
  fread(&vPlatos[0], sizeof(Platos), cant, p);
  fclose(p);

//  ordenar_productos(vPlatos, cant);

  for(i=0; i<cant; i++){
        if(vPlatos[i].IDResto==IDresto && vPlatos[i].Estado==true){

    Mostrar_Platos(vPlatos[i]);
    cout << endl;

    getch();}
  }

  free (vPlatos);
}


bool SavePlatos(Platos vPlatos){
// GUARDA LOS NUEVOS PLATOS EN  "PLATOS.DAT"
    bool b;
    FILE *p;
    p=fopen(Dir_Platos, "ab");

    b = fwrite(&vPlatos,sizeof(Platos),1,p);

    fclose(p);
    return b;

}

void ShowPlatos(){
//BUSCA Y MUESTRA TODOS LOS PLATOS

    cls();
    Platos vPlatos;
    int cant = CantPlatos(), i;
    for(i=0; i<cant; i++)
    {
        vPlatos = leerID(i);
        Mostrar_Platos(vPlatos);

        cout << endl;
    }
 getch();
}

int CantPlatos(){
//
    int bytes, regs;
    FILE *p;
    p = fopen(Dir_Platos, "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    regs = bytes / sizeof(Platos);
    fclose(p);
    return regs;
}

bool Mod_file_Platos(Platos vPlatos, int pos){
//ACTUALIZA EL ARCHIVO AL MODIFICARLO EN FUNCION MOD_PLATOS

    bool modifico;
    FILE *p;
    p = fopen(Dir_Platos, "rb+");
    if (p == NULL)
    {
        return false;
    }
    fseek(p, pos * sizeof(Platos), SEEK_SET);
    modifico = fwrite(&vPlatos, sizeof(Platos), 1, p);
    fclose(p);
    return modifico;

}

void Mostrar_Platos(Platos vPlatos){
//MUESTRA LOS PLATOS CON ESTADO TRUE
    int est;
    if  (vPlatos.Estado==true)
    {
        cout<<"ID: "<<vPlatos.ID<<endl;
        cout<<"Nombre: "<<vPlatos.Nombre<<endl;
        cout<<"Costo Preparacion: "<<vPlatos.Costo<<endl;
        cout<<"Valor de venta: "<<vPlatos.Valor<<endl;
        cout<<"Tiempo de Elaboracion en Minutos: "<<vPlatos.TemPrep<<endl;
        cout<<"ID Restaurante: "<<vPlatos.IDResto<<endl;
        cout<<"Comision: "<<vPlatos.IDCat<<endl;
        //est=vPlatos.Estado;
       // cout<<"Estado: "<<est<<endl;
        cout<<"--------------------------------"<<endl;
    }
//    else{return false;}
  //  getch();
    //cls();
}

void Supr_Plato(){

 int id, pos;

    cout << "Plato a eliminar: ";
    cin >> id;
    pos = buscarID(id);
    if (pos >= 0){
        Platos vPlatos = leerID(pos);
        cout << endl;
        Mostrar_Platos(vPlatos);
        cout << endl << "INGRESE '0' SI ESTA SEGURO: ";
        cin >> vPlatos.Estado;
        if (Mod_file_Platos(vPlatos, pos)){
            cout << "PLATO ELIMINADO.";
        }
        else{
            cout << "NO SE ELIMINO EL PLATO.";
        }}
    else{
        cout << "EL ID DEL PLATO NO FUE ENCONTRADO.";
    }
    }

bool cargarPlatos(Platos *vPlatos)
{
    //CARGA Y COMPROBACION DE PLATOS
    int id;
    cout<<"Cargar ID de Plato: ";
    cin>>vPlatos->ID;
    if(vPlatos->ID<0)
    {
        cout<<"ID incorrecto";
        getch();
        return false;
    }
    else
    {
        id=buscarID(vPlatos->ID);
        if(id>=0)
        {
            cls();
            cout<<"ID ya cargado"<<endl;
            getch();
            return false;
        }
    }

    cout<<"Cargar Nombre de Plato: ";
    cin.ignore();
    cin.getline(vPlatos->Nombre,50);
    if(strlen(vPlatos->Nombre)<=0)
    {
        cout<<"No se ingreso un nombre valido";
        return false;
    }

    cout<<"Cargar Costo de preparacion: ";
    cin>>vPlatos->Costo;
    if(vPlatos->Costo<=0)
    {
        cout<<"Valor de venta menor a valor de costo o igual a 0.";
        return false;
    }

    cout<<"Cargar Valor de venta: ";
    cin>>vPlatos->Valor;
    if((vPlatos->Valor<=0)||(vPlatos->Valor<vPlatos->Costo))
    {
        cout<<"Valor de venta menor a valor de costo o igual a 0.";
        return false;
    }

    cout<<"Cargar Tiempo de preparación: ";
    cin>>vPlatos->TemPrep;
    if(vPlatos->TemPrep<=0)
    {
        cout<<"Tiempo de Preparacion menor a 0.";
        return false;
    }

    cout<<"Cargar ID Restaurant del Plato: ";
    cin>>vPlatos->IDResto;
    if(vPlatos->IDResto<=0)
    {
        cout<<"ID Restaurante menor a 0.";
        return false;
    }
    cout<<"Cargar Comisión restaurante: ";
    cin>>vPlatos->comResto;
    if(vPlatos->comResto<=0||vPlatos->comResto>=100)
    {
        cout<<"Comision incorrecta";
        return false;
    }

    cout<<"Cargar ID Categoría de Plato: ";
    cin>>vPlatos->IDCat;
    if(vPlatos->IDCat<=0)
        return false;

    vPlatos->Estado=true;

    cout<<endl<<"--------------------------"<<endl;



    return true;
}





void Menu_Platos(){

    cls();
    int opc;
    struct Platos vPlatos;
    bool salir=true;


    while (salir)
    {
        cls();
        cout<< "----MENU PLATOS---"<<endl<<endl<<"------------------------------"<<endl<<endl;
        cout<< "1 - NUEVO PLATO."<<endl;
        cout<< "2 - MODIFICAR PLATO."<<endl;
        cout<< "3 - LISTAR PLATO POR ID. "<<endl;
        cout<< "4 - PLATOS POR RESTAURANT."<<endl;
        cout<< "5 - LISTAR TODOS LOS PLATOS."<<endl;
        cout<< "6 - ELIMINAR PLATO."<<endl<<endl;
        cout<< "0 - Salir"<<endl<<endl;
        cout<<"------------------------------"<<endl;
        cout<< "INGRESE OPCION: "<<endl;
        cin>>opc;

        switch (opc)
        {
        case 1:
            cls();
            if(cargarPlatos(&vPlatos)) //carga de platos en vector PLatos (vPlatos) .
            {
                if(SavePlatos(vPlatos)) //graba en el archivo "Platos.dat" los registros generados en cargar
                {
                    cout<<"Carga de Plato, OK. "<<endl;
                    getch();
                    cls();
                }
                else
                {
                    cout << "No se pudo guardar el Plato en el archivo.";
                }
            }
            else
            {
                cls();
                cout << "No se cargo el Plato.";
                getch();
            }
            break;
        case 2:
            cls();
            Mod_Plato();//SE SUPONE QUE MODIFICA LOS PLATOS
             getch();
            break;
        case 3:
            cls();
            listarxID();
            getch();
            //busca por id de plato
            break;
        case 4:
            cls();
            Listar_Platos_Resto();
            break;
        case 5:
            cls();
            ShowPlatos(); //lista todos los platos juntos
            break;
            case 6:
            cls();
            Supr_Plato();
            break;
        default:
            cout<<"OPCION INCORRECTA"<<endl;
            break;
        case 0:
            salir=false;
            break;

        }
    }

};









#endif // PLATOS_H_INCLUDED
