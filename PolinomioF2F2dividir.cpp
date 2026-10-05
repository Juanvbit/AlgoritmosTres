#include <iostream>
#include <cmath>

using namespace std;


struct Termino {
    float coeficiente;
    int exponente;
    Termino* sig;

    Termino(float c, int e) : coeficiente(c), exponente(e), sig(nullptr) {}
};

class PolF2 {
private:
    Termino* cabeza;

public:
    // Constructor por defecto
    PolF2() : cabeza(nullptr) {}

    
    void insertarTermino(float coef, int exp) {
        if (abs(coef) < 1e-6f) return; 

        Termino* act = cabeza;
        Termino* ant = nullptr;

        while (act != nullptr && act->exponente > exp) {
            ant = act;
            act = act->sig;
        }

        
        if (act != nullptr && act->exponente == exp) {
            act->coeficiente += coef;
            
            
            if (abs(act->coeficiente) < 1e-6f) {
                if (ant == nullptr) {
                    cabeza = act->sig;
                } else {
                    ant->sig = act->sig;
                }
                delete act;
            }
            return;
        }

        
        Termino* nuevo = new Termino(coef, exp);
        if (ant == nullptr) {
            nuevo->sig = cabeza;
            cabeza = nuevo;
        } else {
            ant->sig = nuevo;
            nuevo->sig = act;
        }
    }

    
    PolF2 dividir(PolF2 b) {
        PolF2 cociente;

        
        if (b.cabeza == nullptr) {
            cout << "\nError: Division por cero." << endl;
            return cociente;
        }

        
        PolF2 resto;
        for (Termino* aux = this->cabeza; aux != nullptr; aux = aux->sig) {
            resto.insertarTermino(aux->coeficiente, aux->exponente);
        }

        
        while (resto.cabeza != nullptr && resto.cabeza->exponente >= b.cabeza->exponente) {
            float coefCociente = resto.cabeza->coeficiente / b.cabeza->coeficiente;
            int expCociente = resto.cabeza->exponente - b.cabeza->exponente;

            
            cociente.insertarTermino(coefCociente, expCociente);

            
            for (Termino* auxDiv = b.cabeza; auxDiv != nullptr; auxDiv = auxDiv->sig) {
                float coefResta = coefCociente * auxDiv->coeficiente;
                int expResta = expCociente + auxDiv->exponente;

                resto.insertarTermino(-coefResta, expResta);
            }
        }

        return cociente; 
    }

    
    void leer() {
        int numTerminos;
        cout << "¿Cuantos terminos deseas ingresar? ";
        cin >> numTerminos;

        for (int i = 0; i < numTerminos; i++) {
            float coef;
            int exp;
            cout << "Ingresa el coeficiente: ";
            cin >> coef;
            cout << "Ingresa el exponente: ";
            cin >> exp;
            insertarTermino(coef, exp);
        }
    }

    
    void mostrar() const {
        if (cabeza == nullptr) {
            cout << "0" << endl;
            return;
        }

        Termino* aux = cabeza;
        bool primero = true;

        while (aux != nullptr) {
            if (!primero && aux->coeficiente > 0) cout << " + ";
            if (aux->coeficiente < 0) cout << " - ";

            float val = abs(aux->coeficiente);
            if (val != 1 || aux->exponente == 0) cout << val;

            if (aux->exponente > 0) cout << "x";
            if (aux->exponente > 1) cout << "^" << aux->exponente;

            primero = false;
            aux = aux->sig;
        }
        cout << endl;
    }
};

int main() {
    PolF2 p1, p2;

    cout << "=== POLINOMIO 1 (DIVIDENDO) ===" << endl;
    p1.leer();

    cout << "\n=== POLINOMIO 2 (DIVISOR) ===" << endl;
    p2.leer();

    cout << "\nPolinomio 1: ";
    p1.mostrar();
    cout << "Polinomio 2: ";
    p2.mostrar();

    
    PolF2 cociente = p1.dividir(p2);

    cout << "\n===================================" << endl;
    cout << "Cociente resultante (Objeto PolF2): ";
    cociente.mostrar();
    cout << "===================================" << endl;

    return 0;
}