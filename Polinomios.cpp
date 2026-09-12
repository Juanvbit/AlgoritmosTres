struct Termino {
    float coeficiente;
    int   exponente;
    Termino* siguiente;
};
Termino* crearNodo(float coef, int exp) {
    Termino* nodo = new Termino();
    nodo->coeficiente = coef;
    nodo->exponente   = exp;
    nodo->siguiente   = nullptr;
    return nuevo;
}