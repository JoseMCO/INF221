# Análisis Tarea 2

## Problema 1 - El Accionista
El algoritmo implementado corresponde a la solución del problema de "Suma Máxima Contigua".

Para calcular la suma máxima en una lista de valores, primero se calcula la suma máxima de cada una de sus mitades (S<sub>1</sub> y S<sub>2</sub>). La solución del problema corresponderá al max { S<sub>1</sub>, S<sub>2</sub>, S<sub>1</sub>+2<sub>r</sub> }. Para calcular las sumas de las mitades se aplica el mismo método recursivamente.

Como para la resolución se necesita dividir el problema en dos mitades iguales, la complejidad del "Divide" corresponde a 2T(n/2). Por otro lado, la etapa de "Conquer/Combine" es T(n), ya que debe sumar linealmente las soluciones de ambas mitades. Finalmente, la complejidad queda:

T(n) = 2T(n/2) + T(n)

lo que de acuerdo al Teorema maestro equivale a T(nLogn).

Otra posible solución a este problema es el "Algoritmo de Kadane", el que hace uso de la técnica de programación dinámica y tiene una complejidad O(n)

## Problema 2 - Árboles Binarios de Búsqueda Óptimos
Para la solución de este problema se irá calculando paso a paso el costo mínimo al ir uniendo los n árboles que inicialmente tienen un solo elemento (n<sub>i</sub>). En cada paso se calculará el árbol de costo mínimo que se genera al unir dos árboles adyacentes n<sub>j</sub> y n <sub>j+1</sub>. Para esto se busca el mínimo entre el costo del árbol creado usando a n<sub>j</sub> como raíz y el creado usando a n<sub>j+1</sub>
