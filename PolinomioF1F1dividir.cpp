#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

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

    PolF1(const PolF1& otro) {
        int grado = static_cast<int>(otro.vec[0]);
        capacidad = grado + 2;
        vec = new float[capacidad];
        for (int i = 0; i < capacidad; ++i) {
            vec[i] = otro.vec[i];
        }
    }

    ~PolF1() {
        delete[] vec;
    }

    PolF1& operator=(const PolF1& otro) {
        if (this != &otro) {
            delete[] vec;
            int grado = static_cast<int>(otro.vec[0]);
            capacidad = grado + 2;
            vec = new float[capacidad];
            for (int i = 0; i < capacidad; ++i) {
                vec[i] = otro.vec[i];
            }
        }
        return *this;
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

    
    PolF1 dividir(PolF1 b) {
        PolF1 cociente;
        b.ajustarGrado();

        int gradoB = b.getGrado();
        float coefLiderB = b.vec[1]; 

        
        if (gradoB == 0 && abs(coefLiderB) < 1e-6f) {
            cout << "\nError: Division por cero." << endl;
            return cociente;
        }

        PolF1 resto = *this;
        resto.ajustarGrado();

        
        while (resto.getGrado() >= gradoB && abs(resto.vec[1]) > 1e-6f) {
            int gradoResto = resto.getGrado();
            float coefLiderResto = resto.vec[1];

            float coefCociente = coefLiderResto / coefLiderB;
            int expCociente = gradoResto - gradoB;

            cociente.insertar(expCociente, coefCociente);

            
            for (int expB = 0; expB <= gradoB; ++expB) {
                float coefB = b.vec[1 + (gradoB - expB)];
                float coefResta = coefCociente * coefB;
                int expResta = expCociente + expB;

                resto.insertar(expResta, -coefResta);
            }

            resto.ajustarGrado();
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
    PolF1 p1, p2;

    cout << "=== POLINOMIO 1 - DIVIDENDO (PolF1) ===" << endl;
    p1.leer();

    cout << "\n=== POLINOMIO 2 - DIVISOR (PolF1) ===" << endl;
    p2.leer();

    cout << "\nDividendo (P1): ";
    p1.mostrar();
    cout << "Divisor (P2): ";
    p2.mostrar();

    
    PolF1 cociente = p1.dividir(p2);

    cout << "\n===================================" << endl;
    cout << "Cociente resultante (Objeto PolF1): ";
    cociente.mostrar();
    cout << "===================================" << endl;

    return 0;
}