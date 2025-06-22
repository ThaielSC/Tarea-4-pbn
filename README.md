ICC3102 - Programación de Bajo Nivel 2025-10

# Tarea 4
## Colisiones con fricción

**Entrega: viernes 27 de junio a las 21:00 hrs.**

### 1. Motivación
Los lenguajes de alto nivel existen, entre otras cosas, para facilitar el trabajo del programador y aumentar su productividad. Los más comunes y desarrollados ofrecen una enorme variedad de librerías que permiten hacer, en pocas líneas de código, trabajos altamente complejos que finalmente significan muchas líneas de código compilado.

Para algunas de esas aplicaciones, la velocidad es fundamental. Eso implica que cualquier optimización en el desempeño puede ser un aporte: desde mejoras a los algoritmos a paralelización. Si el lenguaje además es interpretado — como Python —, existe la posibilidad de optimizar escribiendo las librerías en un lenguaje distinto: los lenguajes interpretados pueden ser varias veces más lentos que el código de máquina para hacer lo mismo. Existen formas de escribir librerías en C o C++, compilarlas, y usarlas desde otro lenguaje (como Python).

Diversas razones pueden hacer necesaria la escritura de librerías nuevas: p.ej. que se trate de algo muy específico, o que por la aplicación concreta se haga conveniente alguna optimización específica que no está presente en las librerías existentes.

En esta tarea se busca aplicar conocimientos de física y programación para simular interacciones entre cuerpos en movimiento rectilíneo, considerando la fricción cinética y las colisiones elásticas. Estas simulaciones deben implementarse utilizando C++ y el paradigma de programación orientada a objetos. Además se requiere que la librería resultante pueda ser utilizada desde Python.

### 2. Modelo Físico
Se consideran dos esferas que se mueven en línea recta con fricción cinética. El modelo asume:

* Movimiento rectilíneo uniforme desacelerado debido a fricción:
    $a = -\mu_k g$
* Colisión perfectamente elástica (conservación de cantidad de movimiento y energía cinética).
* Posiciones y velocidades iniciales dadas.
* Se ignora el tamaño de las esferas salvo para detectar colisiones (se asume contacto puntual).
* Todas las magnitudes físicas se deben expresar en unidades del Sistema Internacional (SI).
* Por simplicidad, las esferas deben moverse en direcciones opuestas (una hacia la otra) para que exista posibilidad de colisión. Si ambas se mueven en la misma dirección, no debe considerarse que hubo colisión.

### 3. Cálculos requeridos

* **Distancia máxima sin colisión:** Sea $\mu_k$ el coeficiente de fricción cinética entre cada esfera y la superficie, y $g$ la aceleración de la gravedad (por ejemplo, $g = 9.81 m/s^2$). Si una esfera se lanza con velocidad inicial $v_0$, entonces puede recorrer como máximo:
    $$d_{\text{máx}} = \frac{v_0^2}{2\mu_k g}$$
    donde $d_{\text{máx}}$ es la distancia máxima antes de detenerse debido a la fricción.

* **Verificación de colisión:** Sean $x_{A0}$ y $x_{B0}$ las posiciones iniciales de las esferas A y B, respectivamente. Definimos la distancia entre ellas al inicio como:
    $$D = |x_{B0} - x_{A0}|$$
    Entonces, sea $d_{A,\text{max}}$ la distancia máxima que puede recorrer la esfera A, y $d_{B,\text{max}}$ la correspondiente para B. Si la suma de esas distancias es mayor o igual a D, entonces eventualmente colisionarán:
    $$d_{A,\text{max}} + d_{B,\text{max}} \ge D$$

* **Tiempo y posición de colisión (si ocurre):** Sean $v_{A0}$ y $v_{B0}$ las velocidades iniciales (incluyendo el signo) de las esferas A y B, respectivamente, si asumimos que ambas se mueven una hacia la otra, bajo fricción. Entonces el tiempo que tarda en ocurrir la colisión es:
    $$t_c = \frac{x_{B0} - x_{A0}}{v_{A0} - v_{B0}}$$
    donde $t_c$ es válido si $v_{A0} - v_{B0} > 0$ y si ambas esferas siguen en movimiento.
    Luego, el tiempo que tarda cada esfera en detenerse por fricción es:
    $$t_{f,i} = \frac{v_{i0}}{\mu_k g}$$
    donde $i = A \text{ o } B$.
    Y entonces, la colisión sólo ocurre si $t_c \le \min(t_{f,A}, t_{f,B})$. Con esto, la posición de colisión $x_c$ se logra calcular con:
    $$x_c = x_{A0} + v_{A0}t_c - \frac{1}{2}\mu_k g t_c^2$$

* **Velocidades después del choque:** Sea $m_A$ y $m_B$ la masa de las esferas A y B. Luego del choque elástico, las velocidades finales $v'_A$ y $v'_B$ se obtienen con:
$$
v'_A = \frac{m_A - m_B}{m_A + m_B}v_{A0} + \frac{2m_B}{m_A + m_B}v_{B0}
, \quad v'_B = \frac{2m_A}{m_A + m_B}v_{A0} + \frac{m_B - m_A}{m_A + m_B}v_{B0}
$$

* **Distancia recorrida post-colisión:** Finalmente, considerando que si una esfera queda con velocidad $v'$ después del choque, su distancia final antes de detenerse se calcula tal que:
    $$d = \frac{(v')^2}{2\mu_k g}$$
    donde d es la distancia adicional recorrida tras el choque, bajo fricción, hasta detenerse.

### 4. Interfaz esperada
La librería en C++ debe definir al menos las siguientes clases y métodos:

* **Esfera**, con atributos:
    * `double masa`
    * `double x0` (posición inicial)
    * `double v0` (velocidad inicial, positiva o negativa)

* **Simulador**, con métodos:
    * `Simulador(double mu, double g)`: constructor con fricción y gravedad.
    * `bool colisiona(Esfera a, Esfera b)`: indica si hay colisión.
    * `double tiempo_colision(Esfera a, Esfera b)`: retorna el tiempo de colisión.
    * `double posicion_colision(Esfera a, Esfera b)`: retorna posición de colisión.
    * `std::pair<double, double> velocidades_post(Esfera a, Esfera b)`: retorna velocidades después del choque.
    * `double distancia_final(Esfera e)`: retorna distancia hasta detenerse tras colisión.

* **Importante:** Para evitar errores de precisión acumulados, **no se debe redondear ningún valor intermedio durante los cálculos**. Todas las operaciones deben realizarse manteniendo la mayor precisión posible usando variables tipo `double`. Solo se permite redondear para efectos de visualización final si fuera necesario.

### 5. Uso desde Python
La librería debe ser compilada utilizando algún generador de *wrappers* como `pybind` o `SWIG`. El nombre del módulo debe ser `colisiones`. Un ejemplo de uso es:
```python
from colisiones import *

s = Simulador(0.2, 9.81)
a = Esfera(2, 0, 5)
b = Esfera(1, 10, -3)

if s.colisiona(a, b):
    print("Colisión!")
    print("Ocurre en t =", s.tiempo_colision(a, b), "s")
    print("Posición:", s.posicion_colision(a, b), "m")
    va, vb = s.velocidades_post(a, b)
    print("Velocidades luego del choque:")
    print("A:", va, "m/s")
    print("B:", vb, "m/s")
    print("Distancias finales:")
    print("A:", s.distancia_final(Esfera(2, 0, va)), "m")
    print("B:", s.distancia_final(Esfera(1, 10, vb)), "m")
else:
    print("No colisionan")
```

#### 5.1. Ejemplo de salida
```
Colisión!
Ocurre en t = 1.25 s
Posición: 4.717 m
Velocidades luego del choque:
A: -0.33 m/s
B: 7.66 m/s
Distancias finales:
A: 0.0283
B: 14.953
```

### 6. Evaluación y Entrega
Formato de entrega: Subir un solo archivo comprimido con todo el código fuente de su programa al módulo de tareas de la página del curso, con el nombre de archivo "NOMBRE_APELLIDO.tar.gz", que deberá contener los archivos de código fuente en C++ (archivos `.cpp` y `.h`, de ser necesario). Los archivos compilados no serán tomados en cuenta, si se llega a subir solo un archivo compilado, este será ignorado, y será evaluado con nota 1.

Como parte de su tarea, deberá escribir e incluir un `Makefile` que genere la librería `colisiones` automáticamente y que incluya los siguientes *flags*:

`-std=c++11 -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self`

Al compilar deberá generar una librería de Python llamada "colisiones", con todos los archivos intermedios requeridos. Si este paso falla y se debe realizar la compilación de forma manual, o la librería no se llama como se indica se procederá a descontar 1 punto de la nota obtenida.

Aquellas tareas que no compilen de la forma normal serán evaluadas con nota 1. Las que compilen, pero se caigan durante la ejecución, serán evaluadas con nota máxima 3.

Su programa podrá ser evaluado con múltiples casos de prueba y deberá ser capaz de ejecutarlos todos de manera correcta. De fallar en algún caso de prueba serán descontados los puntos correspondientes a dicho caso.

### 7. Consideraciones de Trabajo
El trabajo en las tareas debe ser hecho individualmente, por lo que cuide su tarea para que no sea copiada parcial o íntegramente por otros. Todas las tareas entregadas serán comparadas por un sistema automático de detección de plagios. Cualquier copia será penalizada, recibiendo el mismo castigo tanto quien copia como quien permite que le copien. También es considerada copia cualquier ayuda externa recibida directamente en la tarea, sin importar si proviene de un alumno del curso, de la universidad, o de otro lugar. El castigo será establecido por el Consejo de la Facultad, siendo como mínimo un 1,0 de promedio en el curso.
