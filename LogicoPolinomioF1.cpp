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
public:
    Termino* cabeza;

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
                if (ant == nullptr) cabeza = act->sig;
                else ant->sig = act->sig;
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

    void leer() {
        int numTerminos;
        cout << "¿Cuantos terminos deseas ingresar para PolF2? ";
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


class PolF1 {
private:
    float* vec; 
    int capacidad;

    void redimensionar(int nuevoGrado) {
        int nuevaCapacidad = nuevoGrado + 2;
        float* nuevoVec = new float[nuevaCapacidad]();
        
        nuevoVec[0] = static_cast<float>(nuevoGrado);

        int gradoActual = (vec != nullptr) ? static_cast<int>(vec[0]) : -1;
        if (vec != nullptr) {
            for (int exp = 0; exp <= min(gradoActual, nuevoGrado); ++exp) {
                int posAnt = 1 + (gradoActual - exp);
                int posNue = 1 + (nuevoGrado - exp);
                nuevoVec[posNue] = vec[posAnt];
            }
            delete[] vec;
        }

        vec = nuevoVec;
        capacidad = nuevaCapacidad;
    }

    void ajustarGrado() {
        int gradoActual = getGrado();
        while (gradoActual > 0 && abs(vec[1]) < 1e-6f) {
            float* nuevoVec = new float[gradoActual + 1]();
            nuevoVec[0] = static_cast<float>(gradoActual - 1);
            for (int exp = 0; exp <= gradoActual - 1; ++exp) {
                int posAnt = 1 + (gradoActual - exp);
                int posNue = 1 + ((gradoActual - 1) - exp);
                nuevoVec[posNue] = vec[posAnt];
            }
            delete[] vec;
            vec = nuevoVec;
            gradoActual--;
        }
    }

public:
    PolF1() {
        capacidad = 2;
        vec = new float[capacidad]();
        vec[0] = 0.0f;
    }

    ~PolF1() {
        delete[] vec;
    }

    int getGrado() const {
        return static_cast<int>(vec[0]);
    }

    void insertar(int exp, float coe) {
        if (abs(coe) < 1e-6f) return;

        int gradoActual = getGrado();

        if (exp > gradoActual) {
            redimensionar(exp);
            gradoActual = exp;
        }

        int pos = 1 + (gradoActual - exp);
        vec[pos] += coe;

        ajustarGrado();
    }

    
    bool sonIguales(PolF2 b) const {
        Termino* aux = b.cabeza;
        int gradoA = getGrado();

        int nodosContados = 0;

        
        while (aux != nullptr) {
            int exp = aux->exponente;
            float coef = aux->coeficiente;

            
            if (exp > gradoA) return false;

            int posA = 1 + (gradoA - exp);
            
            
            if (abs(vec[posA] - coef) > 1e-6f) {
                return false;
            }

            nodosContados++;
            aux = aux->sig;
        }

        int terminosEfectivosF1 = 0;
        for (int exp = 0; exp <= gradoA; ++exp) {
            if (abs(vec[1 + (gradoA - exp)]) > 1e-6f) {
                terminosEfectivosF1++;
            }
        }

        return (terminosEfectivosF1 == nodosContados);
    }

    void leer() {
        int numTerminos;
        cout << "¿Cuantos terminos deseas ingresar para PolF1? ";
        cin >> numTerminos;

        for (int i = 0; i < numTerminos; i++) {
            float coef;
            int exp;
            cout << "Ingresa el coeficiente: ";
            cin >> coef;
            cout << "Ingresa el exponente: ";
            cin >> exp;
            insertar(exp, coef);
        }
    }

    void mostrar() const {
        int grado = getGrado();
        bool primero = true;

        for (int exp = grado; exp >= 0; --exp) {
            float coef = vec[1 + (grado - exp)];
            if (abs(coef) > 1e-6f) {
                if (!primero && coef > 0) cout << " + ";
                if (coef < 0) cout << " - ";

                float val = abs(coef);
                if (val != 1 || exp == 0) cout << val;

                if (exp > 0) cout << "x";
                if (exp > 1) cout << "^" << exp;

                primero = false;
            }
        }
        if (primero) cout << "0";
        cout << endl;
    }
};

int main() {
    PolF1 p1;
    PolF2 p2;

    cout << "=== INGRESO DE POLINOMIO 1 (PolF1) ===" << endl;
    p1.leer();

    cout << "\n=== INGRESO DE POLINOMIO 2 (PolF2) ===" << endl;
    p2.leer();

    cout << "\nPolinomio 1 (PolF1): ";
    p1.mostrar();
    cout << "Polinomio 2 (PolF2): ";
    p2.mostrar();

    cout << "\n===================================" << endl;
    if (p1.sonIguales(p2)) {
        cout << "Resultado: Los polinomios SON iguales (true)." << endl;
    } else {
        cout << "Resultado: Los polinomios NO son iguales (false)." << endl;
    }
    cout << "===================================" << endl;

    return 0;
}