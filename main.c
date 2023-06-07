#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct Parte{
    char *nombre;
    int costo;
    int idParte;
    int numeroDeChasisAsociado;
};

struct Accesorio{
    char *nombre;
    int costo;
    int idAccesorio;
    int numeroDeChasisAsociado;
};

struct NodoAccesorio{
    struct Accesorio *accesorio;
    struct NodoAccesorio *sig;
};

struct Producto /*(automovil)*/{
    int numeroDeChasis;
    int yearFabricado;
    char *marca, *modelo;
    int totalPartes;
    struct Parte **partes;
    int totalAccesorios;
    struct NodoAccesorio *headAccesorios; //Todos los accesorios disponibles del automovil.
    int costeTotal; //Precio base + Precio de cada parte sin considerar accesorios.
};

struct NodoProducto{
    struct Producto *automovil; //Arbol Binario de Busqueda se ordena con el numero de Chasis de cada automovil.
    struct NodoProducto *izq, *der;
};

struct NodoParte{
    struct Parte *repuesto;
    struct NodoParte *sig;
};

struct Compra{
    int RutComprador;
    int numeroComprobante;
    struct Producto *detalles; //NodoAccesorio se deja NULL, este almacenara los accesorios que compres
    struct NodoParte *headRepuestos;
};

struct NodoCompra{
    struct Compra *datos; //darle memoria, necesita nueva memoria para que no se cambie lo pagado
    struct NodoCompra *sig;
};

struct Cliente{
    int RUT, numRegion; //numRegion se implementara despues
    char *nombre, *direccion, *comuna, *email;
    struct NodoCompra *headCompras;
    int totalGastado;
};

struct NodoCliente{
    struct Cliente *cliente;
    struct NodoCliente *sig;
};

struct Stock{
    int maxProductos; //Se cambia dependiendo de la cantidad real de espacios ocupados en el arreglo
    int totalProductos; //No se cambia
    struct Producto **autosEnVenta;

    int maxRepuestos;
    int totalRepuestos;
    struct Parte **repuestosEnVenta;

    int maxAccesorios; //Unidades totales que puedo almacenar
    int totalAccesorios; //Unidades almacenadas actualmente
    struct Accesorio **accesoriosDisponibles; //Accesorios en general que tiene la sucursal.
};

struct Sucursal{
    char *director, *comuna, *direccion;
    struct Stock *almacenamiento;
    struct NodoCompra *headRecalls;
};

struct NodoSucursal{
    struct Sucursal *sucursal;
    struct NodoSucursal *ant, *sig;
};

struct Region{
    int numRegion;
    int cantClientes;
    int cantSucursales;
    struct NodoCliente *headClientes;
    struct NodoSucursal *headSucursales; //Doblemente Circular
};

struct Derco{
    char *jefe;
    int ganancias;

    int maxRegionesOperacion; //Max de regiones para operar
    int regionesOperandoActualmente; //Numero de regiones donde Derco opera actualmente
    struct Region **region;
    int totalProductos;
    struct NodoProducto *raizProductos;

};

struct Parte *crearParte(){
    char buffer[100];
    struct Parte *temp;
    temp = (struct Parte *)malloc(sizeof(struct Parte));
    printf("Ingrese el nombre de la parte:");
    scanf("%100s[^\n]", buffer);
    temp ->nombre = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> nombre, buffer);
    printf("Ingrese el id de la parte:");
    scanf("%d", &(temp -> idParte));
    printf("Ingrese el coste de esta parte:");
    scanf("%d", &(temp -> costo));
    return temp;
}

struct Accesorio *crearAccesorio(int numChasisAsociado){
    char buffer[100];
    struct Accesorio *temp;
    temp = (struct Accesorio *)malloc(sizeof(struct Accesorio));
    printf("Ingrese el nombre del accesorio:");
    scanf("%100s[^\n]", buffer);
    temp -> nombre = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> nombre, buffer);
    printf("Ingrese el costo del accesorio:");
    scanf("%d", &(temp -> costo));
    printf("Ingrese el id con el que se identificara al accesorio:");
    scanf("%d", &(temp -> idAccesorio));
    temp -> numeroDeChasisAsociado = numChasisAsociado;

    return temp;
}

struct NodoAccesorio *crearNodoAccesorio(struct Accesorio *nuevo){
    struct NodoAccesorio *temp = NULL;

    temp = (struct NodoAccesorio *)malloc(sizeof(struct NodoAccesorio));
    temp -> accesorio = nuevo;
    temp -> sig = NULL;

    return temp;
}

int agregarAccesorioLista(struct NodoAccesorio **head, struct NodoAccesorio *nuevo){

    struct NodoAccesorio *rec = *head;

    if (*head == NULL){
        *head = nuevo;
    }
    else {
        while (rec) {
            if (rec->sig == NULL) {
                rec->sig = nuevo;
                return 1;
            }
            rec = rec->sig;
        }
    }
    return 1;
}




//ARRAYS
void verPartesArray(struct Parte **vectorPartes, int maxPartes){
    int i;
    int seMostroChasis = 0;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i]){
            if (seMostroChasis == 0){
                printf("Numero de chasis al que pertenecen las partes: %d\n", vectorPartes[i] -> numeroDeChasisAsociado);
                seMostroChasis++;
            }
            printf("%s\n", vectorPartes[i] -> nombre);
            printf("Id asociada a la parte: %d\n", vectorPartes[i] -> idParte);
            printf("Costo individual de la parte: $%d\n", vectorPartes[i] -> costo);
        }
    }
}


int agregarParteArray(struct Parte **vectorPartes, int maxPartes, struct Parte *nuevo){
    int i;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i] == NULL){
            vectorPartes[i] = nuevo;
            return 1;
        }

    }
    return 0;
}

struct Parte *buscarParteArray(struct Parte **vectorPartes, int maxPartes, int idBuscado){
    int i;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i] && vectorPartes[i] -> idParte == idBuscado) return vectorPartes[i];
    }
    return NULL;
}

int eliminarParteArray(struct Parte **vectorPartes, int maxPartes, int idBuscado){
    int i;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i] && vectorPartes[i] -> idParte == idBuscado){
            vectorPartes[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void verAccesoriosArray(struct Accesorio **vectorAccesorios, int maxAccesorios){
    int i;
    int seMostroChasis = 0;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i]){
            if (seMostroChasis == 0){
                printf("Numero de chasis con el cual estan asociados los accesorios: %d\n", vectorAccesorios[i] -> numeroDeChasisAsociado);
                seMostroChasis++;
            }
            printf("%s\n", vectorAccesorios[i]->nombre);
            printf("Id asociado al accesorio: %d\n", vectorAccesorios[i]->idAccesorio);
            printf("Coste del accesorio: $%d\n\n", vectorAccesorios[i]->costo);
        }
    }
}

struct Accesorio *buscarAccesorioArray(struct Accesorio **vectorAccesorios, int maxAccesorios, int idBuscado){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i] && vectorAccesorios[i] -> idAccesorio == idBuscado){
            return vectorAccesorios[i];
        }
    }
    return NULL;
}

int agregarAccesorioArray(struct Accesorio **vectorAccesorios, int maxAccesorios, struct Accesorio *nuevo){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i] == NULL){
            vectorAccesorios[i] = nuevo;
            return 1;
        }
    }
    return 0;
}

int eliminarAccesorioArray(struct Accesorio **vectorAccesorios, int maxAccesorios, int idBuscado){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i] && vectorAccesorios[i] -> idAccesorio == idBuscado){
            vectorAccesorios[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void mostrarProductosArray(struct Producto **productos, int maxProductos){
    int i;
    for (i = 0; i < maxProductos; i++){
        if (productos[i]){
            printf("%s %s\n", productos[i] -> marca, productos[i] -> modelo);
            printf("Año de fabricacion: %d\n", productos[i] -> yearFabricado);
            printf("Numero de Chasis: %d\n", productos[i] -> numeroDeChasis);
            printf("Total de partes que componen el producto: %d", productos[i] -> totalPartes);
            printf("Total de accesorios disponibles: %d", productos[i] -> totalAccesorios);
            printf("Valor del producto: $%d", productos[i] -> costeTotal);
        }
    }
}

struct Producto *buscarProductoArray(struct Producto **productos, int maxProductos, int chasisBuscado) {
    int i;
    for (i = 0; i < maxProductos; i++) {
        if (productos[i] && productos[i] -> numeroDeChasis == chasisBuscado) return productos[i];
    }
    return NULL;
}

struct Producto *rellenarDatosProducto(){
    char buffer[100];
    struct Producto *temp = NULL;
    int i;
    temp = (struct Producto *)malloc (sizeof(struct Producto));
    printf("Ingrese numero de chasis del automovil:");
    scanf("%d", &temp -> numeroDeChasis);
    printf("Ingrese el año de fabricacion:");
    scanf("%d", &temp -> yearFabricado);
    printf("Ingrese la marca del automovil:");
    scanf("%100s[^\n]", buffer);
    temp -> marca = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> marca, buffer);

    printf("Ingrese el modelo del automovil:");
    scanf("%100s[^\n]", buffer);
    temp -> modelo = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> modelo, buffer);

    printf("Ingrese el total de partes que componen el automovil:");
    scanf("%d", &temp -> totalPartes);
    temp ->partes = (struct Parte **)malloc(sizeof(struct Parte *) * temp -> totalPartes);
    temp ->headAccesorios = NULL;
    for (i = 0; i < temp -> totalPartes; i++){
        agregarParteArray(temp -> partes, temp ->totalPartes, crearParte());
    }


    printf("Ingrese la cantidad maxima de accesorios disponibles para el producto:");
    scanf("%d", &temp -> totalAccesorios);
    for (i = 0; i < temp -> totalAccesorios; i++){
        agregarAccesorioLista(&temp -> headAccesorios, crearNodoAccesorio(crearAccesorio((temp) -> numeroDeChasis)));
    }

    return temp;
}

int agregarProductoArray(struct Producto **productos, int maxProductos, struct Producto *nuevo){
    int i;
    for (i = 0; i < maxProductos; i++){
        if (productos[i] == NULL){
            productos[i] = nuevo;
            return 1;
        }
    }
    return 0;
}

int eliminarProductoArray(struct Producto **productos, int maxProductos, int chasisBuscado){
    int i;
    for (i = 0; i < maxProductos; i++){
        if (productos[i] && productos[i] -> numeroDeChasis == chasisBuscado){
            productos[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void modificarParte(struct Parte **parteAModificar){
    int opcion;
    int temp;
    printf("Seleccione que desea modificar de esta parte\n");
    printf("Opcion 1: Modificar id\n");
    printf("Opcion 2: Modificar precio.\n");
    printf("Ingresar un 0: Salir.");
    while (1){
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;

            case 1:
                printf("Ingrese el nuevo id que desea asociar con la parte:");
                scanf("%d", &temp);
                (*parteAModificar) -> idParte = temp;
                break;

            case 2:
                printf("Seleccione el nuevo precio que tendra la parte:");
                scanf("%d", &temp);
                (*parteAModificar) -> costo = temp;
                break;

            default:
                printf("La opcion que ingreso no coincide con ninguna presentada, por favor, intentelo nuevamente\n");
                break;
        }
    }
}

int modificarParteArray(struct Parte **partes, int maxPartes, int idParte, int numChasis){
    int i;
    int opcion;
    for (i = 0; i < maxPartes; i++) {
        if (partes[i] && partes[i]->idParte == idParte && partes[i]->numeroDeChasisAsociado == numChasis){
            modificarParte(&partes[i]);
            return 1;
        }
    }
    return 0;
}

void mostrarStock(struct Stock *almacenamiento){
    printf("Automoviles a la venta:\n");
    mostrarProductosArray(almacenamiento -> autosEnVenta, almacenamiento -> maxProductos);
    printf("\nRepuestos disponibles:\n");
    verPartesArray(almacenamiento ->repuestosEnVenta, almacenamiento -> maxRepuestos);
    printf("\nAccesorios en venta:\n");
    verAccesoriosArray(almacenamiento -> accesoriosDisponibles, almacenamiento -> maxAccesorios);
}

//LISTAS
void verAccesoriosLista(struct NodoAccesorio *head){
    struct NodoAccesorio *rec = head;
    printf("Numero de chasis con el cual estan asociados los accesorios: %d\n", rec -> accesorio ->numeroDeChasisAsociado);
    if (head == NULL){
        printf("Producto no tiene accesorios!\n");
    }
    else{
        while (rec) {
            printf("%s\n", rec->accesorio->nombre);
            printf("Id asociado al accesorio: %d\n", rec->accesorio->idAccesorio);
            printf("Coste del accesorio: $%d\n\n", rec->accesorio->idAccesorio);
            rec = rec->sig;
        }
    }
}




struct Accesorio *buscarAccesorioLista(struct NodoAccesorio *headAccesorios, int idBuscado){
    struct NodoAccesorio *rec = headAccesorios;
    while (rec){
        if (rec -> accesorio ->idAccesorio == idBuscado) return rec -> accesorio;
        rec = rec -> sig;
    }
    return NULL;
}

int eliminarAccesorioLista(struct NodoAccesorio **headAccesorios, int idAccesorioAEliminar){
    struct NodoAccesorio *rec = *headAccesorios;
    struct NodoAccesorio *ant = NULL;
    printf("Ingrese id del accesorio que desea eliminar:");

    while (rec) {
        if (rec->accesorio->idAccesorio == idAccesorioAEliminar) {
            if (ant != NULL) { //no es el head
                ant->sig = rec->sig;
                rec = ant;
            } else { //es el head
                (*headAccesorios) = rec->sig;
            }
            printf("Accesorio se elimino Satisfactoriamente");
            return 1;
        }
        ant = rec;
        rec = rec->sig;
    }
    printf("Accesorio no se encontraba dentro de la lista");
    return 0;
}

void modificarAccesorio(struct Accesorio **accesorioAModificar){
    int opcion;
    int temp;
    printf("Seleccione que desea modificar de este accesorio\n");
    printf("Opcion 1: Modificar id\n");
    printf("Opcion 2: Modificar precio.\n");
    printf("Ingresar un 0: Salir.");
    while (1){
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;

            case 1:
                printf("Ingrese el nuevo id que desea asociar con la parte:");
                scanf("%d", &temp);
                (*accesorioAModificar) -> idAccesorio = temp;
                break;

            case 2:
                printf("Seleccione el nuevo precio que tendra la parte:");
                scanf("%d", &temp);
                (*accesorioAModificar) -> costo = temp;
                break;

            default:
                printf("La opcion que ingreso no coincide con ninguna presentada, por favor, intentelo nuevamente\n");
                break;
        }
    }
}

int modificarAccesorioArray(struct Accesorio **accesorios, int maxAccesorios, int idAccesorio, int numChasis){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (accesorios[i] && accesorios[i] ->idAccesorio == idAccesorio && accesorios[i] ->numeroDeChasisAsociado == numChasis){
            modificarAccesorio(&accesorios[i]);
            return 1;
        }
    }
    return 0;
}

int modificarAccesorioLista(struct NodoAccesorio **headAccesorios, int idAccesorio){
    struct NodoAccesorio *rec = *headAccesorios;
    while (rec){
        if (rec ->accesorio ->idAccesorio == idAccesorio){
            modificarAccesorio(&(rec ->accesorio));
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}

void mostrarAutomovil(struct Producto *producto){
    char desicion[2];
    printf("Automovil Marca: %s\n", producto -> marca);
    printf("Modelo: %s\n", producto -> modelo);
    printf("Fabricado en el año: %d\n", producto -> yearFabricado);
    printf("Su valor total es de $%d dolares\n", producto -> costeTotal);

    while (true){
        printf("Desea ver las partes del automovil? SI/NO\n\n");
        scanf("%2s[^\n]", desicion);
        if (strcmp(desicion, "SI") == 0) {
            verPartesArray(producto -> partes, producto -> totalPartes);
            break;
        }
        else if(strcmp(desicion, "NO") == 0) break;
        printf("POR FAVOR INTRODUZCA UNA OPCION VALIDA\n");
    }

    while(true){
        printf("Desea ver los accesorios del automovil? SI/NO\n\n");
        scanf("%2s[^\n]", desicion);
        if (strcmp(desicion, "SI") == 0) {
            verAccesoriosLista(producto -> headAccesorios);
            break;
        }
        else if(strcmp(desicion, "NO") == 0) break;
        printf("POR FAVOR INTRODUZCA UNA OPCION VALIDA\n");
    }
    /*Mostrar partes y accesorios disponibles*/

}

void verPartesLista(struct NodoParte *head){
    struct NodoParte *rec = head;
    while (rec){
        printf("%s\n", rec -> repuesto -> nombre);
        printf("Id asociada a la parte: $%d\n", rec -> repuesto -> idParte);
        printf("Costo individual de la parte: %d\n", rec -> repuesto -> costo);
        rec = rec -> sig;
    }
}

struct Parte *buscarParteLista(struct NodoParte *head, int idParte){
    struct NodoParte *rec = head;
    while (rec){
        if (rec ->repuesto ->idParte == idParte) return rec -> repuesto;
        rec = rec -> sig;
    }
    return NULL;
}

int eliminarParteLista(struct NodoParte **head, int idParte){
    struct NodoParte *ant = NULL, *rec = *head;
    while (rec){
        if (rec -> repuesto ->idParte == idParte){
            if (ant){
                //No es el head
                ant -> sig = rec -> sig;
                rec = ant;
            }
            else{
                //Es el head;
                ant = *head;
                (*head) = (*head) -> sig;
                free(ant);
            }
            return 1;
        }
        ant = rec;
        rec = rec -> sig;
    }
    return 0;
}

int agregarParteLista(struct NodoParte **headRepuestos, struct Parte *dato){
    struct NodoParte *rec = *headRepuestos;
    struct NodoParte *temp;
    while (rec){
        if (rec -> sig == NULL){
            temp = (struct NodoParte *)malloc(sizeof(struct NodoParte));
            temp -> repuesto = dato;
            temp -> sig = NULL;
            rec -> sig = temp;
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}

void mostrarRecalls(struct NodoCompra *headRecalls){
    struct NodoCompra *rec = headRecalls;
    while (rec){
        printf("RUT del comprador: %d\n", rec -> datos ->RutComprador);
        mostrarAutomovil(rec -> datos -> detalles);
        verPartesLista(rec -> datos ->headRepuestos);
        rec = rec -> sig;
    }
}

struct Compra *buscarCompra(struct NodoCompra *head, int idComprobante){
    struct NodoCompra *rec = head;
    while(rec)
    {
        if(rec -> datos -> numeroComprobante == idComprobante) return rec -> datos;

    }
    return NULL;
}

struct Compra *crearCompra(struct Cliente **cliente, struct Producto *compra){
    struct Compra *temp = NULL;
    temp =(struct Compra *) malloc(sizeof (struct Compra));
    temp -> RutComprador = (*cliente) -> RUT;
    temp -> headRepuestos = NULL;
    printf("Ingrese el numero de comprobante:");
    scanf("%d",&(temp -> numeroComprobante));
    temp -> detalles = (struct Producto *)malloc(sizeof(struct Producto));
    temp -> detalles = compra;
    (*cliente) -> totalGastado += temp -> detalles -> costeTotal;
    return temp;
}

struct NodoCompra *crearNodoCompra(struct Compra *nuevo){
    struct NodoCompra *temp = NULL;
    temp = (struct NodoCompra *)malloc(sizeof(struct NodoCompra));
    temp ->datos = nuevo;
    temp -> sig = NULL;
    return temp;
}

int agregarCompra(struct NodoCompra **head, struct NodoCompra *nuevo)
{
    struct NodoCompra *rec = *head;
    if(!(*head))
    {
        (*head) = nuevo;

    }
    else{
        while (rec -> sig) {
            rec = rec->sig;
        }
        rec -> sig = nuevo;
        rec -> sig -> sig = NULL;
    }
    return 1;
}

int eliminarCompra(struct NodoCompra **head, int idComprobanteElim){
    struct NodoCompra *rec, *temp = NULL;
    rec = *head;
    while(rec)
    {
        if(rec->datos->numeroComprobante == idComprobanteElim)
        {
            if(rec == *head)
            {
                (*head) = rec -> sig;
                rec = NULL;

            }
            else{
                temp -> sig = rec -> sig;
                rec = NULL;
            }
            return 1;
        }
        temp = rec;
        rec = rec->sig;
    }
    return 0;
}

void mostrarCompras(struct NodoCompra *head){
    struct NodoCompra *rec = head;
    while (rec){
        mostrarAutomovil(rec -> datos -> detalles);
        verPartesLista(rec -> datos -> headRepuestos);
        rec = rec -> sig;
    }
}

int agregarRecall(struct NodoCompra **head, struct Compra *nuevo){
    struct NodoCompra *rec = *head;
    if (*head == NULL){
        (*head) = crearNodoCompra(nuevo);
        return 1;
    }
    while (rec){
        if (rec -> sig == NULL){
            rec -> sig = crearNodoCompra(nuevo);
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}

int eliminarRecall(struct NodoCompra **head, int numComprobante, int RUT){
    struct NodoCompra *rec = *head, *ant = NULL;
    while (rec){
        if (rec -> datos -> RutComprador == RUT && rec -> datos -> numeroComprobante == numComprobante){
            if (ant == NULL){
                (*head) = rec -> sig;
            }
            else{
                ant -> sig = rec -> sig;
            }
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}

void mostrarSucursales(struct NodoSucursal *head){
    struct NodoSucursal *rec = head;
    do {
        printf("Jefe de la sucursal: %s\n", rec ->sucursal -> director);
        printf("Direccion: %s\n", rec -> sucursal -> direccion);
        printf("Comuna:%s\n", rec -> sucursal -> comuna);
        mostrarStock(rec -> sucursal -> almacenamiento);
        mostrarRecalls(rec -> sucursal -> headRecalls);
        rec = rec -> sig;
    }while (rec != head);
}

struct Sucursal *buscarSucursal(struct NodoSucursal *head, char *comuna, char *direccion){
    struct NodoSucursal *rec = head;
    do{
        if (strcmp(rec ->sucursal ->comuna, comuna) == 0 &&
            strcmp(rec ->sucursal ->direccion, direccion) == 0) return rec -> sucursal;
        rec = rec -> sig;
    }while (rec != head);
    return NULL;
}

struct Cliente *buscarCliente(struct NodoCliente *head, int RUTBuscado){
    struct NodoCliente *rec = head;
    while (rec){
        if (rec -> cliente ->RUT == RUTBuscado) return rec -> cliente;
        rec = rec -> sig;
    }
    return NULL;
}

void modificarDatosSucursal(struct NodoSucursal **headSucursales) {
    char comunaBusc[100], direccionBusc[100], nuevoDirector[100];
    struct Sucursal *sucursalBuscada = NULL;
    char desicion[2];

    printf("Ingrese la comuna y direccion de la sucursal que desea cambiar");
    while (sucursalBuscada == NULL || strlen(comunaBusc) == 0) {
        printf("Escriba la comuna de la sucursal:");
        scanf("%100s[^\n]", comunaBusc); // CHEQUEAR ESTE SCAN DE STRING
        printf("Escriba la direccion de la sucursal:");
        scanf("%2s[^\n]", direccionBusc);
        sucursalBuscada = buscarSucursal((*headSucursales), comunaBusc, direccionBusc);
    }
    printf("El unico dato que puede ser cambiado es el director debido a falta de permisos\n");
    while (1){
        printf("Ingrese el nombre del nuevo director:");
        scanf("%100s[^\n] ", nuevoDirector);
        printf("Esta seguro de colocar a este nuevo director? SI/NO");
        scanf("%2s[^\n]", desicion);
        if (strcmp(sucursalBuscada -> director, nuevoDirector) == 0){
            printf("Usted no puede colocar como nuevo director al actual\n");
        }
        else{
            if (strcmp(desicion, "SI") == 0) {
                strcpy(sucursalBuscada->director, nuevoDirector);
                return;
            }
            if (strcmp(desicion, "NO") == 0){
                printf("Desea ingresar otro nombre? SI/NO");
                scanf("%2s[\n]", desicion);
                if (strcmp(desicion, "NO") == 0){
                    return;
                }
                if (strcmp(desicion, "SI") != 0){
                    printf("Por favor, ingrese una opcion valida\n");
                }
            }
        }
    }
}

int modificarDatosCliente(struct Cliente **cliente) {
    char desicion[2];
    char nuevoMail[100];

    printf("Debido a lmitaciones tecnicas, solo es posible modificar el e-mail del cliente.\n");
    printf("Desea seguir con la operacion? SI/NO:\n");
    while (1){
        scanf("%2s[^\n]", desicion);
        if (strcmp(desicion, "SI") == 0){
            printf("Por favor, ingrese el nuevo email: ");
            scanf("%100s[^\n]", nuevoMail);
            strcpy((*cliente) -> email, nuevoMail);
            return 1;
        }
        else if (strcmp(desicion, "NO") == 0) return 0;
        printf("La desicion que usted ingreso no coincide con ninguna opcion presentada.\n");
    }
}



//ARBOL
struct Producto *buscarProducto(struct NodoProducto *raiz, int numeroDeChasis){
    if (raiz){
        if (numeroDeChasis < raiz -> automovil -> numeroDeChasis)
            return buscarProducto(raiz -> izq, numeroDeChasis); //Moverse a la izquierda
        if (numeroDeChasis > raiz -> automovil -> numeroDeChasis)
            return buscarProducto(raiz -> der, numeroDeChasis); //Moverse a la derecha
        return raiz -> automovil; //Retorna el nodo
    }
    return NULL; //Retorna NULL
}

int insertarProducto(struct NodoProducto **raiz, struct Producto *producto){
    if ((*raiz)){
        if (producto -> numeroDeChasis < (*raiz) -> automovil ->numeroDeChasis)
            return insertarProducto(&((*raiz) -> izq), producto); //Moverse a la izquierda
        if (producto -> numeroDeChasis > (*raiz) -> automovil ->numeroDeChasis)
            return insertarProducto(&((*raiz) -> der), producto); //Moverse a la derecha
        printf("Lo sentimos, producto no puede agregarse a nuestro catalogo debido a que ya esta\n");
        return 0;
    }
    (*raiz) = (struct NodoProducto *) malloc (sizeof(struct NodoProducto));
    if ((*raiz)){ //Validacion de memoria
        (*raiz) -> automovil = producto;
        (*raiz) -> izq = (*raiz) -> der = NULL;
        printf("Producto fue agregado de manera satisfactoria a nuestro catalogo");
        return 1;
    }
    else{
        printf("Ocurrio un error al agregar el producto a nuestro catalogo");
        return 0;
    }
}

void mostrarProductos(struct NodoProducto *raiz){
    if (raiz){
        mostrarProductos(raiz -> izq);
        mostrarProductos(raiz -> der);
        mostrarAutomovil(raiz -> automovil);
        printf("\n");
    }
}

void reemplazar(struct NodoProducto **raiz, struct NodoProducto **aux){
    if (!((*raiz) -> der)){
        (*aux) -> automovil = (*raiz) -> automovil;
        *aux = *raiz;
        *raiz = (*raiz) -> izq;
    }
    else{
        reemplazar(&((*raiz) -> der), &(*aux));
    }
}

int eliminarProductoArbol(struct NodoProducto **raiz, int numeroChasis){
    struct NodoProducto *aux;
    if (!(*raiz)){
        return 0;
    }
    if ((*raiz) -> automovil -> numeroDeChasis < numeroChasis){
        return eliminarProductoArbol(&((*raiz) -> der), numeroChasis);
    }
    else{
        if (numeroChasis < (*raiz) -> automovil -> numeroDeChasis){
            return eliminarProductoArbol(&((*raiz) -> izq), numeroChasis);
        }
        else{
            if ((*raiz) -> automovil -> numeroDeChasis == numeroChasis){
                aux = *raiz;
                if (!((*raiz) -> izq)){
                    *raiz = (*raiz) -> der;
                }
                else{
                    if (!((*raiz) -> der)){
                        *raiz = (*raiz) -> izq;
                    }
                    else{
                        reemplazar(&((*raiz) -> izq), &aux);
                    }
                    free(aux);
                }
                return 1;
            }
        }
    }
    return 0;
}

int modificarCosteTotalProducto(struct Producto **producto, int nuevoCostoBase){
    int i;
    (*producto) -> costeTotal = nuevoCostoBase;
    for (i = 0; i < (*producto) -> totalPartes; i++){
        if ((*producto) ->partes[i]){
            (*producto) -> costeTotal += (*producto) -> partes[i] -> costo;
        }
        else return 0;
    }
    return 1;
}



int realizarCambiosProducto(struct NodoProducto **hoja){
    int opcion, cambios = 0;
    int idAEliminar;
    int nuevoCostoBase;


    while (true){
        printf("Por favor, ingrese lo que desea modificar del producto\n");
        printf("Opcion 1: Agregar un Accesorio\n");
        printf("Opcion 2: Eliminar un accesorio\n");
        printf("Opcion 3: Cambiar el coste del producto\n");
        printf("Ingresar un 0: Finalizar modificacion\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return cambios;
            case 1:
                (*hoja) -> automovil -> totalAccesorios += agregarAccesorioLista(&((*hoja) ->automovil -> headAccesorios), crearNodoAccesorio(crearAccesorio((*hoja) -> automovil -> numeroDeChasis)));
                cambios++;
                break;
            case 2:
                printf("Ingrese el numero del chasis del automovil que desea eliminar:");
                do{
                    scanf("%d", &idAEliminar);
                } while (buscarAccesorioLista((*hoja) ->automovil ->headAccesorios, idAEliminar) == 0);
                (*hoja) -> automovil -> totalAccesorios -= eliminarAccesorioLista(&((*hoja) -> automovil -> headAccesorios), idAEliminar);
                cambios++;
                break;
            case 3:
                printf("Ingrese el nuevo coste base del producto:");
                scanf("%d", &nuevoCostoBase);
                modificarCosteTotalProducto(&(*hoja) -> automovil, nuevoCostoBase);
                cambios++;
            default:
                printf("La opcion que usted ha ingresado no se encuentra disponible\n");
        }
    }
}

int modificarProducto(struct NodoProducto **raiz, int numeroDeChasis){
    if (*raiz){
        if (numeroDeChasis < ((*raiz) -> automovil -> numeroDeChasis))
            return modificarProducto(&((*raiz) -> izq), numeroDeChasis); //Moverse a la izquierda
        if (numeroDeChasis > ((*raiz) -> automovil -> numeroDeChasis))
            return modificarProducto(&((*raiz) -> der), numeroDeChasis); //Moverse a la derecha
        return realizarCambiosProducto(raiz);
    }
    printf("Lo sentimos, este producto no existe en nuestro catalogo");
    return 0;
}

struct Stock *rellenarAlmacenes(struct NodoProducto *arbol) {
    struct Stock *temp = NULL;
    int opcion;
    int numeroDeChasis, id;
    struct Producto *automovil = NULL;
    struct Parte *repuesto = NULL;
    struct Accesorio *accesorio = NULL;

    temp = (struct Stock *) malloc(sizeof(struct Stock));
    printf("Ingrese la cantidad maxima de productos que se pueden almacenenar:");
    scanf("%d", &temp->maxProductos);
    temp->autosEnVenta = (struct Producto **) malloc(sizeof(struct Producto *) * temp->maxProductos);
    temp->totalProductos = 0;

    printf("Ingrese la cantidad maxima de repuestos que se pueden almacenenar:");
    scanf("%d", &temp->maxRepuestos);
    temp->repuestosEnVenta = (struct Parte **) malloc(sizeof(struct Parte *) * temp->maxRepuestos);
    temp->totalRepuestos = 0;

    printf("Ingrese la cantidad maxima de accesorios que se pueden almacenenar:");
    scanf("%d", &temp->maxAccesorios);
    temp->accesoriosDisponibles = (struct Accesorio **) malloc(sizeof(struct Accesorio *) * temp->maxAccesorios);
    temp->totalAccesorios = 0;

    while (true) {
        printf("Por favor, seleccione una opcion:\n");
        printf("Opcion 1: Agregar Producto:\n");
        printf("Opcion 2: Agregar Repuesto:\n");
        printf("Opcion 3: Agregar Accesorio:\n");
        printf("Ingresar un 0: Salir");
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return temp;

            case 1:
                if (temp->totalProductos < temp->maxProductos) {
                    printf("Ingrese el numero de chasis del producto que desea agregar:");
                    do {
                        scanf("%d", &numeroDeChasis);
                        automovil = buscarProducto(arbol, numeroDeChasis);
                    } while (automovil == NULL);
                    temp->totalProductos += agregarProductoArray(temp->autosEnVenta, temp->maxProductos, automovil);
                } else {
                    printf("Lo sentimos, no queda espacio dentro del almacen para guardar mas automoviles");
                }
                break;

            case 2:
                if (temp->totalRepuestos < temp->maxRepuestos) {
                    printf("Ingrese el id del repuesto que desea agregar junto al numero de chasis asociado");
                    do {
                        scanf("%d %d", &id, &numeroDeChasis);
                        automovil = buscarProducto(arbol, numeroDeChasis);
                        if (automovil != NULL) {
                            repuesto = buscarParteArray(automovil->partes, automovil->totalPartes, id);
                        } else {
                            printf("El numero de chasis ingresado no coincide con ningun producto de nuestro catalogo\n");
                        }
                    } while (repuesto == NULL);
                    temp->totalRepuestos = agregarParteArray(temp->repuestosEnVenta, temp->maxRepuestos, repuesto);
                } else {
                    printf("Lo sentimos, no queda espacio dentro del almacen para guardar mas repuestos");
                }
                break;
            case 3:
                if (temp->totalAccesorios < temp->maxAccesorios) {
                    printf("Ingrese el id del accesorio que desea agregar junto al numero de chasis asociado");
                    do {
                        scanf("%d %d", &id, &numeroDeChasis);
                        automovil = buscarProducto(arbol, numeroDeChasis);
                        if (automovil != NULL) {
                            accesorio = buscarAccesorioLista(automovil->headAccesorios, id);
                        } else {
                            printf("El numero de chasis ingresado no coincide con ningun producto de nuestro catalogo\n");
                        }
                    } while (accesorio == NULL);
                    temp->totalAccesorios += agregarAccesorioArray(temp->accesoriosDisponibles, temp->maxAccesorios,
                                                                   accesorio);
                }
                break;
            default:
                printf("Lo sentimos, esa opcion no se encuentra disponible\n");
                break;
        }
    }
}


struct Sucursal *rellenarDatosSucursal(struct NodoProducto *arbol){
    struct Sucursal *temp;
    char buffer[100];

    temp = (struct Sucursal *)malloc(sizeof(struct Sucursal));
    printf("Ingrese el nombre del director de esta sucursal:");
    scanf("%100s[^\n]", buffer);
    temp -> director = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> director, buffer);

    printf("Ingrese el nombre de la comuna donde esta la sucursal:");
    scanf("%100s[^\n]", buffer);
    temp -> comuna = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> comuna, buffer);

    printf("Ingrese la direccion de esta sucursal:");
    scanf("%100s[^\n]", buffer);
    temp -> direccion = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> direccion, buffer);

    temp -> almacenamiento = NULL;
    if (arbol == NULL){
        printf("Lo sentimos, no se pueden rellenar los almacenes debido a que no existe catalogo\n");
    }
    else {
        temp -> almacenamiento = rellenarAlmacenes(arbol);
    }
    temp -> headRecalls = NULL;
    return temp;
}

struct NodoSucursal *crearNodoSucursal(struct Sucursal *nuevo){
    struct NodoSucursal *temp = NULL;
    temp = (struct NodoSucursal *)malloc(sizeof(struct Sucursal));
    temp -> sucursal = nuevo;
    temp -> ant = temp -> sig = NULL;
    return temp;
}

int agregarSucursal(struct NodoSucursal **head, struct NodoSucursal *nuevo){
    if (nuevo){
        if ((*head) == NULL) {
            (*head) = nuevo;
            (*head)->ant = (*head)->sig = (*head);
            return 1;
        } else {
            nuevo->ant = (*head)->ant;
            (*head)->ant->sig = nuevo;
            nuevo->sig = (*head);
            (*head)->ant = nuevo;
            return 1;
        }
    }
    return 0;
}

int eliminarSucursal(struct NodoSucursal **head, char *comuna, char *direccion){
    struct NodoSucursal *rec = *head;
    do{
        if (strcmp(rec ->sucursal ->comuna, comuna) == 0 &&
            strcmp(rec ->sucursal ->direccion, direccion) == 0){

            if (rec == (*head)){
                (*head) = (*head) -> sig;
            }

            rec -> ant -> sig = rec -> sig;
            rec -> sig -> ant = rec -> ant;
            return 1;
        }
        rec = rec -> sig;
    }while (rec != *head);
    return 0;
}

struct Cliente *crearCliente(){
    struct Cliente *temp = NULL;
    char buffer[100];
    temp = (struct Cliente *)malloc(sizeof(struct Cliente));
    printf("Ingrese el nombre del cliente:");
    scanf("%100s[^\n]", buffer);
    temp -> nombre = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> nombre, buffer);

    printf("Ingrese el RUT del cliente:");
    scanf("%d", &(temp -> RUT));

    printf("Ingrese e-mail de contacto del cliente:");
    scanf("%100s[^\n]", buffer);
    temp -> email = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> email, buffer);

    printf("Ingrese la region de residencia del cliente:");
    scanf("%d", &(temp -> numRegion));

    printf("Ingrese la comuna donde vive el cliente:");
    scanf("%100s[^\n]", buffer);
    temp -> comuna = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> comuna, buffer);

    printf("Ingrese la direccion del domicilio del cliente:");
    scanf("%100s[^\n]", buffer);
    temp -> direccion = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> direccion, buffer);

    temp -> totalGastado = 0;
    temp -> headCompras = NULL;

    return temp;
}

struct NodoCliente *crearNodoCliente(struct Cliente *nuevo){
    struct NodoCliente *temp;
    temp = (struct NodoCliente *)malloc (sizeof(struct NodoCliente));
    temp -> cliente = nuevo;
    temp -> sig = NULL;
    return temp;
}

int agregarCliente(struct NodoCliente **head, struct NodoCliente *nuevo){
    struct NodoCliente *rec = *head;
    if (!(*head)){
        (*head) = nuevo;
    }
    else{
        while (rec) {
            if (rec->sig == NULL) {
                rec -> sig = nuevo;
                rec = rec -> sig;
            }
            rec = rec -> sig;
        }
    }
    return 1;

}

int eliminarCliente(struct NodoCliente **head, int RUT){
    struct NodoCliente *rec = *head, *ant = NULL;
    while (rec){
        if (rec -> cliente ->RUT == RUT){
            if (ant){
                ant -> sig = rec -> sig;
            }
            else{
                (*head) = (*head) -> sig;
            }
            return 1;
        }
        ant = rec;
        rec = rec -> sig;
    }
    return 0;
}

void mostrarClientes(struct NodoCliente *head){
    struct NodoCliente *rec = head;
    char desicion[2];
    while (rec){
        printf("Nombre Cliente: %s\n", rec -> cliente -> nombre);
        printf("Rut: %d\n", rec -> cliente -> RUT);
        printf("E-mail: %s\n", rec -> cliente -> email);
        printf("Direccion: %s\n", rec -> cliente -> direccion);
        printf("Comuna: %s\n", rec -> cliente -> comuna);
        printf("Desea ver las compras que ha realizado el cliente? Introduzca SI o NO\n");
        while (true){
            scanf("%2s[^\n]", desicion);
            if (strcmp(desicion, "SI") == 0){
                mostrarCompras(rec -> cliente -> headCompras);
                printf("Total gastado por el cliente: %d\n", rec -> cliente -> totalGastado);
                break;
            }
            else if (strcmp(desicion, "NO") == 0) break;
            printf("Por favor, introduzca una opcion valida");
        }
        printf("\n");
        rec = rec -> sig;
    }
}

void mostrarRegiones(struct Region **regiones, int maxRegiones){
    int i;
    char desicion[2];
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i]){
            printf("Numero de region: %d\n", regiones[i] -> numRegion);
            printf("Cantidad de clientes en la region: %d\n", regiones[i] -> cantClientes);
            printf("Desea ver los datos de cada cliente? Introduzca SI o NO\n");
            while (true){
                scanf("%2s[^\n]", desicion);
                if (strcmp(desicion, "SI") == 0){
                    if (regiones[i] -> headClientes == NULL){
                        printf("Lo sentimos, no existen Clientes en nuestra base de datos respecto a esta region\n");
                    }
                    else{
                        mostrarClientes(regiones[i]->headClientes);
                    }
                    break;
                }
                else if (strcmp(desicion, "NO") != 0){
                    printf("Por favor, introduzca una opcion valida");
                }
                else break;
            }
            printf("Cantidad de sucursales operando en la region: %d\n", regiones[i] -> cantSucursales);
            printf("Desea ver los datos de cada sucursales? Introduzca SI o NO\n");
            while (true){
                scanf("%2s[^\n]", desicion);
                if (strcmp(desicion, "SI") == 0){
                    if (regiones[i] -> headSucursales == NULL){
                        printf("Lo sentimos, no existen sucursales en nuestras bases de datos operando en la region\n");
                    }
                    else{
                        mostrarSucursales(regiones[i]->headSucursales);
                    }
                    break;
                }
                else if (strcmp(desicion, "NO") != 0){
                    printf("Por favor, introduzca una opcion valida");
                }
                else break;
            }

        }
    }
}

int modificarCompra(struct Compra **detalles){
    char desicion[2];

    printf("Usted solo puede modificar el numero del comprobante de la compra. ");
    printf("Desea realizar la operacion? SI/NO");
    while (true){
        scanf("%2s[^\n]", desicion);
        if (strcmp(desicion, "SI") == 0){
            printf("Ingrese el nuevo numero de comprobante");
            scanf("%d", &((*detalles) -> numeroComprobante));
            return 1;
        }
        if (strcmp(desicion, "NO") == 0) return 0;
        printf("Lo sentimos, la desicion que ingreso no esta disponible.");
    }
}

struct Region *buscarRegion(struct Region **regiones, int maxRegiones, int numRegionBuscada){
    int i;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] && regiones[i] -> numRegion == numRegionBuscada) return regiones[i];
    }
    return NULL;
}

int agregarRegion(struct Region ***regiones, int maxRegiones, struct Region **nueva){
    int i;
    for (i = 0; i < maxRegiones; i++){
        if (*regiones[i] == NULL){
            (regiones[i]) = nueva;
            return 1;
        }
    }
    return 0;
}

int eliminarRegion(struct Region **regiones, int maxRegiones, int numRegion){
    int i;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] && regiones[i] ->numRegion == numRegion){
            regiones[i] = NULL;
            return 1;
        }
    }
    return 0;
}

int buscarNodoCliente(struct NodoCliente *head, int rutBuscado)
{
    struct NodoCliente *rec = head;
    while(rec){
        if(rec -> cliente -> RUT == rutBuscado)
        {
            return 1;
        }
        rec = rec->sig;
    }

    return 0;
}


void modificarRegion(struct Region *region){
    int opcion;
    int RUTBuscado;
    struct Cliente *buscado;
    printf("Que datos desea modificar?\n");
    printf("Opcion 1: Modificar la sucursal.\n");
    printf("Opcion 2: Modificar los clientes.\n");
    printf("Ingresar un 0: Salir.\n");
    while (1){
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;
            case 1:
                modificarDatosSucursal(&(region -> headSucursales));
                break;
            case 2:
                printf("Introduzca el RUT del cliente que desea modificar:");
                scanf("%d", &RUTBuscado);
                buscado = buscarCliente(region ->headClientes, RUTBuscado);
                if (buscado) {
                    printf("Cliente se encuentra en la region! \n");
                    modificarDatosCliente(&buscado);
                }
                else{
                    printf("Cliente no se encuentra en la region\n");
                }
            default:
                printf("Lo sentimos, la opcion que usted ingreso no esta disponible, intentelo de nuevo\n");
                break;
        }
    }
}


int contarGastosRepuestos(struct NodoParte *head){
    int contador = 0;
    struct NodoParte *rec = head;
    while (rec){
        contador += rec -> repuesto -> costo;
        rec = rec -> sig;
    }
    return contador;
}

int contarGastosCliente(struct NodoCompra *head){
    int contador = 0;
    struct NodoCompra *rec = head;
    while (rec){
        contador += rec -> datos -> detalles -> costeTotal;
        contador += contarGastosRepuestos(rec -> datos ->headRepuestos);
        rec = rec -> sig;
    }
    return contador;
}

int calcularGanancia(struct Region *datosRegion){
    int contador = 0;
    struct NodoCliente *rec = datosRegion -> headClientes;
    while (rec){
        contador += contarGastosCliente(rec -> cliente -> headCompras);
        rec = rec -> sig;
    }
    return contador;
}

struct Region *calcularRegionMenorGanancia(struct Region **regiones, int maxRegiones){
    int i;
    int menorGanancia;
    int numRegionMenorGanancia;
    struct Region *regionMasIneficiente;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] != NULL){
            if (!regionMasIneficiente || (regiones[i] && menorGanancia > calcularGanancia(regiones[i])))
                menorGanancia = calcularGanancia(regiones[i]);
            regionMasIneficiente = regiones[i];
            numRegionMenorGanancia = regiones[i]->numRegion;
        }
    }
    return regionMasIneficiente;
}

struct Region *calcularRegionMayorGanancia(struct Region **regiones, int maxRegiones){
    int i;
    int mayorGanancia;
    int numRegionMasEficiente;
    struct Region *regionMasEficiente;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] != NULL){
            if (!regionMasEficiente || (regiones[i] && mayorGanancia < calcularGanancia(regiones[i])))
                mayorGanancia = calcularGanancia(regiones[i]);
            regionMasEficiente = regiones[i];
            numRegionMasEficiente = regiones[i]->numRegion;
        }
    }
    return regionMasEficiente;
}

struct Derco *crearEmpresa(){
    struct Derco *temp;
    char jefe[100];
    temp = (struct Derco *)malloc(sizeof(struct Derco));
    printf("Ingrese el nombre del Jefe a cargo de la empresa:");
    scanf("%100s[^\n]", jefe);
    temp -> jefe = (char *)malloc(sizeof(char) * strlen(jefe));
    strcpy(temp -> jefe, jefe);
    temp ->raizProductos = NULL;
    temp -> totalProductos = 0;
    temp -> region = NULL;
    temp -> region = NULL;
    temp ->ganancias = 0;

    return temp;
}

void verCatalogo(struct NodoProducto **raiz, int *totalProductos) {
    char desicion[2];
    int numeroBuscado;
    int opcionElegida;
    struct Producto *nuevoProd;
    if ((*raiz) == NULL) {
        printf("Al parecer, el catalogo de productos esta vacio, desea aÃ±adir un producto? SI/NO\n");
        scanf("%2s[\n]", desicion);
        while (true) {
            if (strcmp(desicion, "SI") == 0) {
                (*totalProductos) += insertarProducto((raiz), rellenarDatosProducto());
                break;
            }
            if (strcmp(desicion, "NO") == 0) break;
            printf("La opcion que ingreso no es valida, por favor intentelo nuevamente.\n");
        }
    } else {
        printf("Usted ha seleccionado trabajar con los productos de nuestro catalogo.\n");


        while (true) {
            printf("Por favor, seleccione la operacion que desea realizar sobre nuestro catalogo:\n");
            printf("Opcion 1: Mostrar los productos\n");
            printf("Opcion 2: Buscar un producto\n");
            printf("Opcion 3: Agregar un producto\n");
            printf("Opcion 4: Eliminar un producto\n");
            printf("Opcion 5: Modificar un producto\n");
            printf("Ingrese un 0 si quiere salir\n");
            scanf("%d", &opcionElegida);
            switch (opcionElegida) {
                case 0:
                    return;
                case 1:
                    mostrarProductos(*raiz);
                    break;
                case 2:

                    printf("Ingrese el numero de chasis\n");
                    scanf("%d", &numeroBuscado);
                    if (buscarProducto(*raiz, numeroBuscado) != NULL) {
                        printf("Este producto si se encuentra en nuestro catalogo!\n");
                    } else {
                        printf("Este producto no se encuentra en nuestro catalogo\n");

                    }
                    break;
                case 3:
                    nuevoProd = rellenarDatosProducto();
                    if (nuevoProd) {

                        (*totalProductos) += insertarProducto(raiz, nuevoProd);
                    } else {
                        printf("No se pudo agregar el producto ya que no fue creado propiamente\n");
                    }
                    break;
                case 4:
                    printf("Escriba el numero de chasis del producto que quiere eliminar\n");
                    scanf("%d", &numeroBuscado);
                    if (buscarProducto(*raiz, numeroBuscado) != NULL) {
                        if (eliminarProductoArbol(raiz, numeroBuscado) == 1) {
                            printf("El producto fue eliminado!\n");
                            (*totalProductos)--;
                        } else {
                            printf("No se pudo eliminar el producto\n");
                        }
                    } else {
                        printf("El producto no existe, entonces no se elimino");
                    }
                    break;
                case 5:
                    printf("Escriba el numero de chasis del producto\n");
                    scanf("%d", &numeroBuscado);
                    modificarProducto((raiz), numeroBuscado);
                    break;
                default:
                    printf("La opcion que usted ingreso no se encuentra disponible, intentelo de nuevo.\n");
            }
        }
    }
}

struct Region *crearRegion(struct NodoProducto *raiz){
    struct Region *temp;
    temp = (struct Region *)malloc(sizeof(struct Region));
    printf("Ingrese el numero de la region:");
    scanf("%d", &(temp -> numRegion));
    printf("Ingrese la cantidad de clientes en la region:");
    scanf("%d", &(temp ->cantClientes));
    printf("Ingrese la cantidad de Sucursales operando en la region:");
    scanf("%d", &(temp -> cantSucursales));
    temp -> headClientes = NULL;
    temp -> headSucursales = NULL;
    return temp;
}

struct Region **crearArrayRegiones(int maxRegiones){
    struct Region **temp;
    int i;
    temp = (struct Region **)malloc(sizeof(struct Region *) * maxRegiones);
    return temp;
}

void revisarCompras(struct Cliente** clienteRev) {
    int opcion;
    int comprobante;
    struct Compra *buscado;
    struct NodoCompra *rec = (*clienteRev)->headCompras;
    if (rec == NULL) {
        printf("Cliente no tiene compras\n");
        return;
    }
    printf("Escriba la opcion a revisar.\n");
    printf("Opcion 1: Mostrar compras.\n");
    printf("Opcion 2: Buscar una compra.\n");
    printf("Opcion 3: Eliminar una compra.\n");
    printf("Opcion 4: Modificar una compra.\n");
    while (true) {
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;

            case 1:
                mostrarCompras(rec);
                break;
            case 2:
                printf("Escriba el numero comprobante de la compra\n");
                scanf("%d", &comprobante);
                buscado = buscarCompra(rec, comprobante);
                if (buscado) {
                    printf("Se encontro la compra!\n");
                } else {
                    printf("La compra no se encuentra en la lista\n");
                }
                break;
            case 3:
                printf("Escriba el numero comprobante de la compra\n");
                scanf("%d", &comprobante);
                buscado = buscarCompra(rec, comprobante);
                if (buscado) {
                    eliminarCompra(&(*clienteRev)->headCompras, comprobante);
                    printf("Se elimino la compra\n");
                }

                else {
                    printf("No se pudo eliminar la compra ya que no existe\n");
                }
                break;
            case 4:
                printf("Escriba el numero comprobante de la compra\n");
                scanf("%d", &comprobante);
                buscado = buscarCompra(rec, comprobante);
                if (buscado) {
                    modificarCompra(&buscado);
                } else {
                    printf("La compra no se encuentra en la lista\n");
                }
            default:
                printf("Opcion no esta disponible, intentelo de nuevo\n");
                break;
        }

    }
}

void verOpcionesClientes(struct NodoCliente **head, int *totalClientes){
    int i;
    int opcion;
    int rutBusc;
    struct Cliente *buscado;
    if (*head == NULL){
        for (i = 0; i < (*totalClientes); i++){
            agregarCliente(head, crearNodoCliente(crearCliente()));
        }
    }
    else {

        printf("Escriba el numero de la opcion que desea usar.\n");
        printf("Opcion 1: Mostrar Clientes\n");
        printf("Opcion 2: Buscar un Cliente\n");
        printf("Opcion 3: Agregar un Cliente\n");
        printf("Opcion 4: Eliminar un Cliente\n");
        printf("Opcion 5: Modificar un Cliente\n");
        printf("Opcion 6: Revisar las compras de un cliente\n");
        printf("Ingrese un 0 para terminar la ejecucion\n");
        while (true) {
            scanf("%d", &opcion);
            switch (opcion) {
                case 0:
                    return;

                case 1:
                    mostrarClientes(*head);
                    break;
                case 2:

                    printf("Ingrese el rut del cliente que quiere buscar\n");
                    scanf("%d", &rutBusc);
                    buscado = buscarCliente(*head, rutBusc);
                    if (buscado) {
                        printf("Se encontro el cliente!\n");
                    } else {
                        printf("No se encontro el cliente\n");
                    }
                    break;
                case 3:
                    (*totalClientes) += agregarCliente(head, crearNodoCliente(crearCliente()));
                    break;
                case 4:
                    printf("Escriba el rut del cliente que desea eliminar\n");
                    scanf("%d", &rutBusc);
                    (*totalClientes) -= eliminarCliente(head, rutBusc);
                    break;
                case 5:
                    printf("Escriba el rut del cliente que quiere modificar\n");
                    scanf("%d", &rutBusc);
                    buscado = buscarCliente(*head, rutBusc);
                    modificarDatosCliente(&buscado);
                    break;
                case 6:
                    printf("Ingrese el rut del cliente con las compras que desea ver\n");
                    scanf("%d", &rutBusc);
                    buscado = buscarCliente(*head, rutBusc);
                    revisarCompras(&buscado);
                    break;
                default:
                    printf("Opcion no esta disponible, intentelo de nuevo\n");
                    break;
            }
        }
    }
}



void verRegiones(struct Region ***regiones, int *maxRegiones, int *totalActualRegiones, struct NodoProducto *raiz) {
    char desicion[2];
    int opcion;
    struct Region* buscado;
    int numRegion;
    if (*regiones == NULL) {
        printf("Actualmente no hay regiones, desea agregar? SI/NO");
        while (true) {
            scanf("%2s[\n]", desicion);
            if (strcmp(desicion, "SI") == 0) {
                printf("Ingrese el maximo de regiones:");
                scanf("%d", maxRegiones);
                (*totalActualRegiones) = 0;
                *regiones = crearArrayRegiones((*maxRegiones));
                buscado = crearRegion(raiz);
                totalActualRegiones += agregarRegion(regiones, *maxRegiones, &buscado);
                break;
            }
        }
    }
    else {
        printf("Usted ha deseado trabajar con las regiones, ahora seleccione una opcion:\n");
        printf("Opcion 1: Mostrar Regiones\n");
        printf("Opcion 2: Buscar Region\n");
        printf("Opcion 3: Agregar Region\n");
        printf("Opcion 4: Eliminar una Region\n");
        printf("Opcion 5: Mostrar la region con menos ganancias\n");
        printf("Opcion 6: Mostrar la region con mas ganancias\n");

        printf("Ingrese un 0 para salir.\n");
        while (true) {
            scanf("%d", &opcion);
            switch (opcion) {
                case 0: return;
                case 1:
                    mostrarRegiones(*regiones, *maxRegiones);
                    break;
                case 2:
                    printf("Ingrese el numero de la region que busca:");
                    scanf("%d", &numRegion);
                    buscado = buscarRegion(*regiones, *maxRegiones, numRegion);
                    if (buscado) {
                        printf("Se encontro region, desea modificarla? SI/NO");
                        scanf("%2s", desicion);
                        while (true) {
                            if (strcmp(desicion, "SI") == 0) {
                                modificarRegion(buscado);
                            }
                            if (strcmp(desicion, "NO") == 0) {
                                break;
                            }
                            printf("Opcion que ingreso no esta disponible, intentelo nuevamente\n");
                        }
                    }
                    else {
                        printf("La region que pedia no se encontro en el arreglo\n");
                    }
                    break;
                case 3:
                    if (*totalActualRegiones < *maxRegiones) {
                        buscado = crearRegion(raiz);
                        totalActualRegiones += agregarRegion(regiones, *maxRegiones, &buscado);
                    }
                    else {
                        printf("Lo sentimos, no tenemos espacio para agregar la region que desea\n");
                    }
                    break;
                case 4:
                    printf("Por favor, escriba el numero de la region que desea eliminar:");
                    scanf("%d", &numRegion);
                    (*totalActualRegiones) -= eliminarRegion(*regiones, *maxRegiones, numRegion);
                case 5:
                    buscado = calcularRegionMenorGanancia(*regiones, *maxRegiones);
                    printf("La region con menor ganancias es la numero %d\n", (buscado) -> numRegion);
                case 6:
                    buscado = calcularRegionMayorGanancia(*regiones, *maxRegiones);
                    printf("La region que presento la mayor ganancia es la numero %d\n", buscado -> numRegion);
                    break;
                default:
                    printf("Opcion no disponible, intentelo nuevamente\n");
            }
        }
    }
}

void elegirOpcionSucursal(struct Region **region, struct NodoProducto *raiz){
    int opcion;
    char comuna[100], direccion[100];
    struct Sucursal *buscado;
    int id;
    int RUTBuscado;
    int comprobante;
    struct Producto *elegido;
    struct NodoSucursal *recSucursal;
    struct NodoCliente *recClientes;
    struct Cliente *comprador;
    struct Parte *repuesto;
    struct Compra *comprado;
    struct Accesorio *accesorioComprado;
    struct Compra *compraARecall;

    printf("Elija una opcion\n");
    printf("Opcion 1: Buscar una sucursal\n");
    printf("Opcion 2: Agregar una sucursal\n");
    printf("Opcion 3: Eliminar una sucursal\n");
    printf("Opcion 4: Mostrar Recalls\n");
    printf("Opcion 5: Comprar un automovil\n");
    printf("Opcion 6: Comprar un repuesto.\n");
    printf("Opcion 7: Comprar un accesorio.\n");
    printf("Opcion 8: Agregar un Recall.\n");
    printf("Ingrese un 0 para salir\n");
    while (true){
        scanf("%d", &opcion);
        switch (opcion) {
            case 0: return;
            case 1:
                printf("Ingrese la comuna y direccion de la sucursal que esta buscando:");
                scanf("%100[^\n] %100s[^\n]", comuna, direccion);
                buscado = buscarSucursal(((*region) -> headSucursales), comuna, direccion);
                if (buscado != NULL){
                    printf("Sucursal si se encuentra en nuestra base de datos\n");
                }
                else{
                    printf("Sucursal no se encuentra en nuestra base de datos\n");
                }
                break;
            case 2:
                (*region) -> cantSucursales += agregarSucursal(&(*region) -> headSucursales, crearNodoSucursal(rellenarDatosSucursal(raiz)));
                break;
            case 3:
                printf("Ingrese la comuna y direccion de la sucursal que desea eliminar:");
                scanf("%100[^\n] %100s[^\n]", comuna, direccion);
                (*region) -> cantSucursales -= eliminarSucursal(&(*region) ->headSucursales, comuna, direccion);
                break;
            case 4:
                printf("\"Ingrese la comuna y direccion de la sucursal que desea ver los recalls:\"");
                scanf("%100[^\n] %100s[^\n]", comuna, direccion);
                buscado = buscarSucursal((*region) -> headSucursales, comuna, direccion);
                if (buscado) {
                    if (buscado -> headRecalls)
                        mostrarRecalls((*region)->headSucursales ->sucursal ->headRecalls);
                    else{
                        printf("Lo sentimos, esta sucursal no tiene recalls.\n");
                    }
                }
                else{
                    printf("No se encontro la sucursal que usted deseaba");
                }
                break;
            case 5:
                printf("Ingrese el numero de chasis del producto a comprar:");
                scanf("%d", &id);
                recSucursal = (*region) ->headSucursales;
                if (recSucursal == NULL){
                    printf("Lo sentimos, no existen sucursales en esta region.\n");
                }
                else{
                    do {
                        elegido = buscarProductoArray(recSucursal ->sucursal->almacenamiento->autosEnVenta, recSucursal ->sucursal->almacenamiento->maxProductos, id);
                        recSucursal = recSucursal -> sig;
                    }while (recSucursal != (*region) -> headSucursales && elegido == NULL);
                    if (elegido == NULL){
                        printf("Producto no esta disponible en ninguna sucursal.\n");
                    }
                    else{
                        printf("Ingrese el RUT del Cliente:");
                        scanf("%d", &RUTBuscado);
                        if ((*region) -> headClientes) {
                            recClientes = (*region) -> headClientes;
                            while (recClientes && comprador == NULL) {
                                comprador = buscarCliente(recClientes, RUTBuscado);
                                recClientes = recClientes -> sig;
                            }
                            if (comprador != NULL) {
                                agregarCompra(&comprador -> headCompras, crearNodoCompra(crearCompra(&comprador, elegido)));
                                recSucursal ->sucursal ->almacenamiento ->totalProductos -= eliminarProductoArray(recSucursal ->sucursal ->almacenamiento -> autosEnVenta, recSucursal ->sucursal ->almacenamiento -> maxProductos, id);
                            }
                        }
                        else{
                            printf("Lo sentimos, la region no tiene clientes disponibles.\n");
                        }
                    }
                }
                break;

            case 6:
                printf("Ingrese el id del repuesto a comprar:");
                scanf("%d", &id);
                recSucursal = (*region) ->headSucursales;
                if (recSucursal == NULL){
                    printf("Lo sentimos, no existen sucursales en esta region.\n");
                }
                else{
                    do {
                        repuesto = buscarParteArray(recSucursal ->sucursal->almacenamiento->repuestosEnVenta, recSucursal ->sucursal->almacenamiento->maxRepuestos, id);
                        recSucursal = recSucursal -> sig;
                    }while (recSucursal != (*region) -> headSucursales && elegido == NULL);
                    if (repuesto == NULL){
                        printf("Repuesto no esta disponible en ninguna sucursal.\n");
                    }
                    else{
                        printf("Ingrese el RUT del Cliente:");
                        scanf("%d", &RUTBuscado);
                        if ((*region) -> headClientes) {
                            recClientes = (*region) -> headClientes;
                            while (recClientes && comprador == NULL) {
                                comprador = buscarCliente(recClientes, RUTBuscado);
                                recClientes = recClientes -> sig;
                            }
                            if (comprador != NULL) {
                                agregarParteLista(&comprador -> headCompras ->datos->headRepuestos, repuesto);
                                comprador -> totalGastado += repuesto -> costo;
                                eliminarParteArray(recSucursal ->sucursal ->almacenamiento ->repuestosEnVenta, recSucursal ->sucursal ->almacenamiento ->maxRepuestos, id);
                            }
                        }
                        else{
                            printf("Lo sentimos, la region no tiene clientes disponibles.\n");
                        }
                    }
                }
                break;
            case 7:
                printf("Ingrese el id del accesorio a comprar:");
                scanf("%d", &id);
                recSucursal = (*region) ->headSucursales;
                if (recSucursal == NULL){
                    printf("Lo sentimos, no existen sucursales en esta region.\n");
                }
                else{
                    do {
                        accesorioComprado = buscarAccesorioArray(recSucursal ->sucursal->almacenamiento->accesoriosDisponibles, recSucursal ->sucursal->almacenamiento->maxAccesorios, id);
                        recSucursal = recSucursal -> sig;
                    }while (recSucursal != (*region) -> headSucursales && accesorioComprado == NULL);
                    if (accesorioComprado == NULL){
                        printf("Accesorio no esta disponible en ninguna sucursal.\n");
                    }
                    else{
                        printf("Ingrese el RUT del Cliente:");
                        scanf("%d", &RUTBuscado);
                        if ((*region) -> headClientes) {
                            recClientes = (*region) -> headClientes;
                            while (recClientes && comprador == NULL) {
                                comprador = buscarCliente(recClientes, RUTBuscado);
                                recClientes = recClientes -> sig;
                            }
                            if (comprador != NULL) {
                                comprador -> headCompras ->datos-> detalles ->totalAccesorios+= agregarAccesorioLista(&comprador -> headCompras ->datos-> detalles ->headAccesorios, crearNodoAccesorio(accesorioComprado));
                                comprador -> totalGastado += repuesto -> costo;
                                recSucursal ->sucursal ->almacenamiento ->totalAccesorios-= eliminarAccesorioArray(recSucursal ->sucursal ->almacenamiento ->accesoriosDisponibles, recSucursal ->sucursal ->almacenamiento ->maxAccesorios, id);
                            }
                        }
                        else{
                            printf("Lo sentimos, la region no tiene clientes disponibles.\n");
                        }
                    }
                }
                break;

            case 8:
                printf("Ingrese la comuna y la direccion de la sucursal que pidio el Recall:");
                scanf("%100s[^\n] %100s[^\n]", comuna, direccion);
                buscado = buscarSucursal((*region) -> headSucursales, comuna, direccion);
                if (buscado){
                    printf("Ingrese el RUT del dueño del Recall");
                    scanf("%d", &RUTBuscado);
                    if ((*region) -> headClientes) {
                        recClientes = (*region) -> headClientes;
                        while (recClientes && comprador == NULL) {
                            comprador = buscarCliente(recClientes, RUTBuscado);
                            recClientes = recClientes -> sig;
                        }
                        if (comprador != NULL) {
                            printf("Ingrese el numero de comprobante del auto a Recall:");
                            scanf("%d", &comprobante);
                            compraARecall = buscarCompra(comprador ->headCompras, comprobante);
                            if (compraARecall){
                                agregarRecall(&(buscado) -> headRecalls, compraARecall);
                            }
                        }
                        else{
                            printf("Lo sentimos, el cliente del recall no existe");
                        }
                    }
                    else{
                        printf("Lo sentimos, la region no tiene clientes disponibles.\n");
                    }
                }
                else{
                    printf("Lo sentimos, no existe la sucursal que pidio el Recall");
                }
                break;
            default:
                printf("Opcion que eligio no esta disponible, intentelo de nuevo\n");
                break;
        }
    }

}

void menuPrincipal(struct Derco **empresa){
    char desicion[2];
    int opcion;
    int i;
    int numRegion;
    struct Region *buscado;
    while (true){
        if ((*empresa) == NULL){
            printf("Parece que la empresa no existe, desea crearla? SI/NO\n");
            while (true){
                scanf("%2s[^\n]", desicion);
                if (strcmp(desicion, "SI") == 0){
                    (*empresa) = crearEmpresa();
                    break;
                }
                if (strcmp(desicion, "NO") == 0) return;
                printf("La opcion que entrego no esta disponible, intentelo nuevamente\n");
            }
        }
        else{

            while (true){
                printf("\nPor favor seleccione una de las siguientes opciones:\n");
                printf("Opcion 1: Trabajar con el catalogo de productos.\n");
                printf("Opcion 2: Trabajar con las regiones.\n");
                printf("Opcion 3: Ver Sucursales en cada region\n");
                printf("Ingrese un 0 si desea salir y finalizar.\n");
                scanf("%d", &opcion);
                switch (opcion){
                    case 0: return;

                    case 1:
                        verCatalogo(&((*empresa) -> raizProductos), &(*empresa) -> totalProductos);
                        break;

                    case 2:
                        if ((*empresa) -> raizProductos == NULL){
                            printf("No existe un catalogo de productos, por favor seleccione la opcion 1 antes de continua.\n\n");
                        }
                        else{
                            verRegiones(&(*empresa) -> region, &(*empresa) -> maxRegionesOperacion, &(*empresa) -> regionesOperandoActualmente, (*empresa) ->raizProductos);
                        }
                        break;
                    case 3:
                        if ((*empresa) -> raizProductos == NULL){
                            printf("No hay catalago disponible para rellenar las sucursales, por favor seleccione la opcion 1 antes de volver a intentarlo.\n");
                        }
                        else {
                            if ((*empresa) -> region == NULL){
                                printf("No hay regiones disponibles donde revisar las sucursales, por favor seleccione la opcion 2 antes de volver a intentarlo.\n");
                            }
                            else {
                                printf("Ingrese el numero de la region con la que desea trabajar\n");
                                scanf("%d", &numRegion);
                                buscado = buscarRegion((*empresa) -> region, (*empresa) -> maxRegionesOperacion, numRegion);
                                if (buscado) {
                                    elegirOpcionSucursal(&buscado, (*empresa)->raizProductos);
                                }
                                else{
                                    printf("La region con la que desea trabajar no se encuentra en nuestra base de datos.\n");
                                }
                            }
                        }
                        break;
                    default:
                        printf("Opcion no esta disponible, intentelo de nuevo.\n");
                }
            }

        }
    }
}

int main(){
    struct Derco *empresa = NULL;
    menuPrincipal(&empresa);
    return 0;
}