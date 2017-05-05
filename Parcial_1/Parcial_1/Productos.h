
struct
{
    int id;
    char nombre[50];
    float precio;
    int idUsuario;
    int stock;
    int cantidadVendida;
    int isPublished;
    int flagRegistro;

}typedef EProducto;


int initArrayProductos(EProducto* arrayProductos, int sizeArrayProductos);

int obtenerPosicionLibreArrayProductos(EProducto* arrayProductos, int sizeArrayProductos);

int buscarProductoPorId(EProducto* arrayProductos, int sizeArrayProductos, int idProducto);

int nuevaPublicacion(EProducto* arrayProductos, int sizeArrayProductos, EUsuario* arrayUsuarios, int sizeArrayUsuarios);

int modificarProductoPorIdUsuario(EProducto* arrayProductos, int sizeArrayProductos, EUsuario* arrayUsuarios, int sizeArrayUsuarios);

void cargaNombreProducto(EProducto* arrayAuxiliarProducto);

int ingresoIdProducto();

float ingresoPrecioProducto();

int ingresoCantidadVendidaProducto(int stock);

int ingresoStockProducto();

int calcularIdProducto(EProducto* arrayProductos, int sizeArrayProductos);

int existenProductosPublicados(EProducto* arrayProductos, int sizeArrayProductos);

int eliminarProductosPorBajaUsuario(EProducto* arrayProductos, int sizeArrayProductos, int idUsuario);

void listarProductosUsuario(EProducto* arrayProductos, int sizeArrayProductos, int idUsuario);


