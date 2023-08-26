/*************************************************************************************************************/
/* Programa: Implementación del método de eliminación gaussiana por el método del pivotaje parcial escalado  */
/*                                                                                                           */
/* Descripcion: Programa que realiza el método del pivotaje parcial escalado para realizar la eliminación    */
/*              Gaussiana de una matriz cuadrática (en este laboratorio se exige de una matriz de 4x4)       */
/*                                                                                                           */
/* Fecha: 16/01/2023                                                                                         */
/*************************************************************************************************************/

// Importación de librerías necesarias
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

// Siempre debe de tratarse de una matriz cuadrática para que el programa funcione, los valores iniciales serán de 4x4 que son los requeridos en este laboratorio
int rows = 4; // Valores filas
int cols = 4; // Valores columnas

double create_matrix(double matrix[rows][cols]) // Función que crea una matriz
{
    // srand(time(NULL)); //Inicializa la semilla para el generador de números aleatorios en caso de usarlos

    for (int i = 0; i < rows; i++) // Recorremos todas las filas
    {
        for (int j = 0; j < cols; j++) // Recorremos todas las columnas
        {
            // matrix[i][j] = rand() % 10; //Descomentar si se desean generar números aleatorios entre 0 y 10

            printf("Ingresa el valor para la fila %d, columna %d: ", i + 1, j + 1); // Mensaje de número que se va a introducir y su posición

            // Control de errores, en el caso de que se introduzca un carácter contrario a un número, volveremos a pedirlo
            char line[256];
            double value;
            while (fgets(line, sizeof(line), stdin))
            {
                if (sscanf(line, "%lf", &value) == 1)
                {                         // Si sscanf devuelve 1, significa que ha leído un número válido
                    matrix[i][j] = value; // Almacena el valor introducido en la matriz
                    break;
                }

                printf("Por favor, introduce una cifra: "); // Mensaje de error, volvemos a pedir el número
            }
        }
        printf("\n");
    }
    return matrix[rows][cols]; // Devolvemos la matriz con las dimensiones deseadas
}

void print_matrix(double matrix[rows][cols]) // Función que imprime una matriz
{
    for (int i = 0; i < rows; i++) // Recorremos todas las filas de la matriz
    {
        for (int j = 0; j < cols; j++) // Recorremos todas las columnas de la matriz
        {
            printf("%f ", matrix[i][j]); // Imprimimos cada posición de la matriz
        }
        printf("\n"); // Salto de línea en cada una de las filas
    }
    printf("\n");
    sleep(5); // Tiempo de delay en la impresión, para que no se solape el texto
}

void swap_rows(double matrix[rows][cols], int row_a, int row_b) // Función que cambia una fila de nuestra matriz por otra ya existente
{
    int temp;
    for (int col = 0; col < cols; col++) // Recorremos la columna de la matriz
    {
        // Intercambiamos cada uno de los valores de la fila A con la fila B
        temp = matrix[row_a][col];
        matrix[row_a][col] = matrix[row_b][col];
        matrix[row_b][col] = temp;
    }
    print_matrix(matrix); // Imprimimos la nueva matriz
}

void check_matrix(double matrix[rows][cols]) // Función que comprueba que se puede realizar el pivotaje parcial escalado correctamente y cambia alguna fila si es necesario
{
    for (int i = 0; i < rows; i++) // Recorremos cada fila de la matriz
    {
        if (matrix[i][i] == 0) // Si el valor de la posición que debe trasformarse a 1 es 0, esto significa que no es posible cambiar este valor, por lo tanto, cambiaremos de fila
        {
            printf("La fila %d debe de ser cambiada de lugar debido a que la cifra que pertenece al lugar [%d][%d] es igual a 0.", i + 1, i + 1, i + 1); // Mensaje que nos indica la fila que será cambiada
            printf("\n");
            bool changes[cols];            // Array booleano que guarda las posiciones en las que el cambio de fila es posible, teniendo en cuenta que fila debemos cambiar
            for (int j = 0; j < rows; j++) // Recorremos toda la fila
            {
                if (matrix[j][i] == 0) // Si la posición por la que queremos cambiar la fila es 0, esta no será válida
                {
                    changes[j] = false;
                }
                else
                {
                    if (matrix[i][j] == 0) // Si la fila que queremos cambiar, hará que en la posición por la que queremos cambiarla tenga valor 0 en su posición de 1, esta no será válida
                    {
                        changes[j] = false;
                    }
                    else
                    {
                        if (j != i) // Si se trata de una fila distinta a la nuestra y no cumple las condiciones anteriores, está será válida
                        {
                            changes[j] = true; // Fila válida para realizar el cambio
                        }
                        else // Si se trata de la misma fila, esta no será válida
                        {
                            changes[j] = false;
                        }
                    }
                }
            }
            bool change = false; // Variable booleana para comprobar cuando se habrá realizado el cambio de fila (para no realizar varios cambios)
            // Como la primera fila es la fila que pivotearemos en la matriz, esta será la última opción a la hora de cambiar la fila
            for (int j = rows - 1; j > 0; j--) // Recorremos las filas en orden inverso
            {
                if (changes[j] && !change) // Si la fila es intercambiable y todavía no se ha realizado el cambio
                {
                    printf("Realizaremos el cambio de la fila %d por la fila %d.", i + 1, j + 1); // Mensaje de cambio
                    printf("\n");
                    swap_rows(matrix, i, j); // Función que cambia una fila por otra de lugar en la matriz
                    change = true;           // Variable que confirma que el cambio ha sido realizado correctamente
                }
            }
        }
    }
}

double search_pivot(double matrix[rows][cols], double pivot[rows]) // Función que busca el pivote de cada fila de la matriz para moverlo a la primera fila
{
    for (int i = 0; i < rows; i++) // Recorremos todas las filas de la matriz
    {
        bool found = false;            // Variable booleana que nos indica cuando encontramos el elemento pivote de la fila
        for (int j = 0; j < cols; j++) // Recorremos todas las columnas de la matriz
        {
            if (matrix[i][j] != 0 && !found) // Para tratarse del pivote de la fila, este debe de tener un valor mayor que 0
            {
                pivot[i] = (double)matrix[i][j]; // Guardamos el elemento pivote de la matriz
                found = true;                    // Pivote encontrado
            }
            else if (matrix[i][j] == 0) // Si el elemento es 0, este no será válido para colocarlo en la primera fila
            {
                found = true; // Pivote no válido para colocarlo en la primera fila
            }
        }
    }
    return pivot[rows]; // Array de los pivotes de cada fila
}

double search_higher(double matrix[rows][cols], double higher[rows]) // Función que busca el elemento más grande en cada una de las filas de la matriz
{

    for (int i = 0; i < rows; i++) // Recorremos todas las filas
    {
        for (int j = 0; j < cols; j++) // Recorremos todas las columnas
        {
            if (j > 0) // Una vez hemos pasado la primera posición (esto significa que ya tendremos un elemento ya guardado)
            {
                if (matrix[i][j] > higher[i]) // Cada uno de los elementos y si estos son más grandes que el que tenemos almacenado
                {
                    higher[i] = (double)matrix[i][j]; // En el caso de que algún número sea más grande lo reemplazaremos por el que teníamos ya guardado
                }
            }
            else
            {
                higher[i] = (double)matrix[i][j]; // Guardamos la primera posición de la matriz
            }
        }
    }
    return higher[rows]; // Devolvemos el array con los números más grandes de cada fila
}

int search_pivot_row(double matrix[rows][cols], double pivot[rows], double higher[rows]) // Función que busca la mejor fila pivote (para colocarlo en la primera posición)
{

    double division[rows];  // Array que almacena las divisiones entre los pivotes y el elemento más grande
    double higher_division; // El cociente más alto de todas las filas
    double higher_pivot;    // El pivote más alto
    int pivot_row = 0;      // La fila que pivotearemos

    printf("pivote/n. alto - cociente");
    printf("\n");
    for (int i = 0; i < rows; i++) // Recorremos todas las filas
    {
        division[i] = pivot[i] / higher[i]; // El cociente entre el pivote y el elemento mayor de la misma fila

        printf("%f/%f - %f", pivot[i], higher[i], division[i]); // Comprobación de los elementos que se dividen y sus resultados
        printf("\n");

        if (i > 0) // Si se trata de una fila distinta a la primera
        {
            if (division[i] > higher_division) // Comparamos si el cociente es mayor que el ya guardado
            {
                // Si el cociente es mayor
                higher_division = division[i]; // Reemplazamos los valores
                higher_pivot = pivot[i];
                pivot_row = i; // La fila pivote cambia
            }
            else if (division[i] == higher_division) // En el caso de que los cocientes sean iguales
            {
                if (pivot[i] > higher_pivot) // Comparamos que pivote es más alto
                {
                    // Si el pivote es mayor
                    higher_division = division[i]; // Reemplazamos los valores
                    higher_pivot = pivot[i];
                    pivot_row = i; // La fila pivote cambia
                }
            }
        }
        else // Si se trata de la primera fila
        {
            higher_division = division[i]; // Asignamos los valores iniciales (no hay guardados previamente)
            higher_pivot = pivot[i];
            pivot_row = i; // La fila pivote es la primera, pues es la actual
        }
    }

    printf("\n");
    printf("El pivote elegido es %f", higher_pivot); // Mensaje del pivote más alto
    printf("\n");
    printf("La fila de pivoteo va a ser la %d", (pivot_row + 1)); // Fila de pivoteo
    printf("\n");
    printf("\n");
    sleep(5); // Tiempo de delay en la impresión, para que no se solape el texto

    return pivot_row; // Devolvemos la fila que vamos a pivotear
}

void change_element(double matrix[rows][cols], int action, int row_a, int row_b, int postemp) // Función con los pasas que se usarán para llevar a cabo el pivotaje parcial escalado
{
    double temp = matrix[row_a][postemp]; // Número por el que se multiplicará o dividirá una fila de nuestra matriz (Es una posición específica)
    bool any_change = false;              // Boleano que lee si se ha producido algún cambio en la matriz

    if (temp != 0) // Si existe un elemento por el que multiplicaremos o dividiremos la fila
    {
        if (action == 1) // Acción 1: Dividiremos la fila entre el primer número no nulo de la misma
        {
            if (temp != 1) // Si el primer elemento no nulo de la fila es distinto a 1
            {
                printf("Dividimos la fila %d entre su primer elemento no nulo (%f): ", row_a + 1, temp); // Mostramos el mensaje de que se procederá a la división de la fila
                printf("\n");
            }
        }
        else // Acción 2: Restaremos la fila A a otra fila B multiplicada por el primer número de la fila B
        {
            printf("Restamos a la fila %d, la fila %d multiplicada por su primer elemento (%f): ", row_a + 1, row_b + 1, temp); // Mostramos el mensaje de que se procederá a la resta de la fila
            printf("\n");
        }

        for (int col = 0; col < cols; col++) // Recorremos las columnas de la fila
        {
            if (matrix[row_a][col] != 0) // Si el número no es nulo
            {
                if (action == 1) // Acción 1: Dividiremos la fila entre el primer número no nulo de la misma
                {
                    if (temp != 1) // Si el primer elemento no nulo de la fila es distinto a 1
                    {
                        matrix[row_a][col] = matrix[row_a][col] / temp; // Dividimos cada elemento de la fila por el primer número no nulo de la fila A
                        any_change = true;                              // Hemos realizado un cambio, dejamos constancia en la variable
                    }
                }
                else // Acción 2: Restaremos la fila A a otra fila B multiplicada por el primer número de la fila B
                {
                    matrix[row_a][col] = temp * matrix[row_b][col] - matrix[row_a][col]; // Restamos la fila A a otra fila B multiplicada por el primer número de la misma
                    any_change = true;                                                   // Hemos realizado un cambio, dejamos constancia en la variable
                }
            }
        }
        if (any_change) // Si se ha producido algún cambio
        {
            print_matrix(matrix); // Imprimimos la nueva matriz
        }
    }
}

void change_elements(double matrix[rows][cols]) // Función que se usará para llevar a cabo el pivotaje parcial escalado
{
    // Recorremos cada fila de la matriz
    for (int i = 0; i < rows; i++)
    {
        change_element(matrix, 1, i, i, i); // Acción 1: Dividiremos la fila entre el primer número no nulo de la misma
        for (int j = 1; j < rows; j++)      // Recorremos de nuevo las filas de la matriz
        {
            if (j + i < rows) // Para no sobrepasar los límites de filas
            {
                change_element(matrix, 2, j + i, i, i); // Acción 2: Restaremos la fila A a otra fila B multiplicada por el primer número de la fila B
            }
        }
    }
}

void main() // Función principal
{
    if (rows == cols) // Si la matriz es cuadrática (número de filas = número de columnas)
    {
        double matrix[rows][cols]; // Declaramos la matriz con las dimensiones indicadas
        double pivot[rows];        // Declaramos un array de los pivotes de cada fila
        double higher[rows];       // Declaramos un array de los números más altos de cada fila

        create_matrix(matrix); // Función que crea una matriz
        print_matrix(matrix);  // Función que imprime una matriz

        search_pivot(matrix, pivot);   // Función que busca el pivote de cada fila de la matriz para moverlo a la primera fila
        search_higher(matrix, higher); // Función que busca el elemento más grande en cada una de las filas de la matriz

        int pivot_row = search_pivot_row(matrix, pivot, higher); // Función que busca la mejor fila pivote (para colocarlo en la primera posición)

        if (pivot_row != 0) // Si la fila pivote es distinta a la primera
        {
            // Mensaje que nos indica que se realizará un cambio de filas
            printf("Cambiamos la fila %d por la fila 1, y por lo tanto, la nueva matriz es la siguiente: ", pivot_row + 1);
            printf("\n");
            printf("\n");
            swap_rows(matrix, 0, pivot_row); // Función que cambia una fila de nuestra matriz por otra ya existente
        }

        check_matrix(matrix);    // Función que comprueba que se puede realizar el pivotaje parcial escalado correctamente y cambia alguna fila si es necesario
        change_elements(matrix); // Función que se usará para llevar a cabo el pivotaje parcial escalado
        printf("Pivoteo parcial escalado completado");
    }
    else
    {
        // Mensaje de error, debido a que la matriz no se trata de una cuadrática
        printf("Debes de introducir una matriz cuadrática para que el programa funcione correctamente, las columnas y filas deben de ser iguales (filas %d) (columnas %d)", rows, cols);
    }
}