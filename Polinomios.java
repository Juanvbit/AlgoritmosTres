import java.util.Scanner;

public class Polinomios {
    public static class Polinomio {
        private int grado;
        private int[] coeficientes;

        public Polinomio(int grado) {
            this.grado = grado;
            this.coeficientes = new int[grado + 1];
        }

        public void setCoeficiente(int indice, int valor) {
            if (indice >= 0 && indice <= grado) {
                coeficientes[indice] = valor;
            }
        }

        public int getCoeficiente(int indice) {
            if (indice >= 0 && indice <= grado) {
                return coeficientes[indice];
            }
            return 0;
        }

        public int evaluar(int x) {
            int resultado = 0;
            for (int i = 0; i <= grado; i++) {
                resultado += coeficientes[i] * Math.pow(x, grado - i);
            }
            return resultado;
        }
    }
}
 