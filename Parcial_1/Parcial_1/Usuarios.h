
struct
{
    int id;
    char nombre[50];
    char password[50];
    int contadorCalificaciones;
    int acumuladorCalificaciones;
    int flagRegistro;

}typedef EUsuario;

int obtenerPosicionLibreArrayUsuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios);

int buscarUsuarioPorId(EUsuario* arrayUsuarios, int sizeArrayUsuarios, int idUsuario);

int altaUsuario(EUsuario* arrayUsuarios, int sizeArrayUsuarios);

int modificarUsuarioPorId(EUsuario* arrayUsuarios, int sizeArrayUsuarios);

/// int bajaUsuarioPorId(EUsuario* arrayUsuarios, int sizeArrayUsuarios, EProducto* arrayProductos, int sizeArrayProductos);

int ingresoIdUsuario();

int calcularIdUsuario(EUsuario* arrayUsuarios, int sizeArrayUsuarios);

int existenUsuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios);

void cargaNombreYpasswordUsuario(EUsuario* arrayAuxiliarUsuario);

void listarUsuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios);

void cargaAutomaticausuarios(EUsuario* arrayUsuarios, int sizeArrayUsuarios);
