struct
{
    int id;
    char nombre[50];
    char password[50];
    int contadorCalificaciones;
    int acumuladorCalificaciones;
    int flagRegistro;

}typedef Usuario;


Usuario* newUsuario(int id, char nombre[], char password[], int contadorCalificaciones, int acumuladorCalificaciones, int flagRegistro);

void printUsuario(Usuario* pUsuario, int flagRegistro);

void listarUsuarios(ArrayList* listaUsuarios, int flagRegistro);

int cargaInicialUsuarios (ArrayList* listaUsuarios);

int altaUsuario(ArrayList* listaUsuarios);

void cargaNombreUsuario(char* nombre);

void cargaPasswordUsuario(char* password);

int calcularIdUsuario(ArrayList* listaUsuarios);

int tomarYcomprobarExistenciaUsuarioPorId(ArrayList* listaUsuarios, char* leyendaCancelar);

int bajaUsuario(ArrayList* listaUsuarios);

int modificarUsuarioPorId(ArrayList* listaUsuarios);

