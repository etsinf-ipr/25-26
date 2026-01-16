# Simulador de tráfico.

## 1. Contexto
Esta actividad se realizará en una sesión en línea de 90 minutos, trabajando en grupos de 3–4 personas. El objetivo es aplicar de forma integrada los contenidos vistos en la asignatura: estructuras, arrays, bucles, selección y funciones en C
No se espera que todos los grupos lleguen al mismo punto. El ejercicio está diseñado con un núcleo mínimo común y una serie de ampliaciones opcionales e independientes.
## 2. Objetivo general
Implementar una simulación discreta por turnos de tráfico en una rejilla 2D que represente carreteras y coches, mostrando la evolución del sistema paso a paso por pantalla
## 3. Núcleo mínimo común (obligatorio)
Esta sección define exactamente el comportamiento esperado del simulador básico. Cualquier otra situación a las que aparecen más abajo no se debe asumir y se tratará como una ampliación.
La rejilla
    • Tiene un tamaño fijo de 10x10
    • Cada celda puede contener un único elemento: estar vacía, ser una carretera o contener un coche
    • Las carreteras ocupan celdas completas y se representan como líneas rectas continuas de extremo a extremo
    • Se recomienda usar constantes simbólicas:
'''
#define VACIO '.'
#define CARRETERA '-'
#define COCHE 'C'
'''

Las calles
    • Todas las calles son bidireccionales.
    • No existe sentido obligatorio de circulación.
    • Las calles pueden ser horizontales o verticales.
    • En el núcleo mínimo, las calles pueden ser fijas (por ejemplo, una cruz siempre en las mismas coordenadas).
El coche
    • Debe representarse mediante una estructura con, al menos
        ◦ fila
        ◦ columna
        ◦ dirección (`0=arriba, 1=derecha, 2=abajo, 3=izquierda`)
    • La dirección indica hacia dónde intenta moverse el coche en el siguiente turno.
    • Se colocará inicialmente en el extremo de cualquier carretera
Movimiento del coche
En cada turno:
    1. El coche intenta avanzar una celda en su dirección actual.
    2. El movimiento solo se realiza si la celda destino está dentro del mapa y es una carretera.
    3. Si no puede avanzar porque la celda está ocupada por otro coche o fuera de la carretera, el coche permanece detenido.
    4. Si el coche llega al extremo del grid en su dirección de movimiento, desaparece del mapa.
    5. No existe aceleración, frenado ni movimiento parcial.

Intersecciones
    • Una intersección es una celda que pertenece a una calle horizontal y a una vertical.
    • En el núcleo mínimo, el coche NO gira en las intersecciones. El giro en intersecciones se considera una ampliación opcional.
 ## 4. Simulación
 La simulación avanza por turnos discretos.
 En cada turno:
    1. Se actualiza la posición del coche actual.
    2. Se genera un coche nuevo según el parámetro X si aplica.
    3. Se muestra el estado completo del mapa por pantalla.
 El número de turnos es fijo (por ejemplo, 20).
## 5. Criterio de completitud
La actividad se considera completa con estas funcionalidades:
    • inicialización correcta del mapa,
    • movimiento coherente de los coches uno a uno,
    • desaparición al llegar al extremo,
    • visualización clara.

## Ampliaciones opcionales ("cartas")
Cada grupo puede elegir una o dos ampliaciones. No son dependientes entre sí.
### Carta A – Calles aleatorias
    • Generar aleatoriamente 2 calles horizontales y 2 verticales completas.
    • Deben estar separadas por una distancia mínima (al menos una diferencia de 2)
    • Los coches pueden salir de cualquiera de los extremos de las carreteras

### Carta B – Semáforos coordinados
    • Añadir semáforos en los cruces.
    • Estados globales:
        ◦ Verde horizontal / rojo vertical
        ◦ Rojo horizontal / verde vertical
    • Cambian cada cierto número de turnos.

### Carta C – Múltiples coches
    • Mantener un array de coches.
    • Se mueven por turnos.
    • No pueden ocupar la misma celda
C
### arta D – Cambios de dirección
    • En intersecciones, los coches pueden seguir recto o girar
    • Posibilidades: 
        ◦ regla simple fija
        ◦ decisión aleatoria del coche al llegar al cruce

### Carta E – Generación periódica de coches
    • Cada X turnos, aparece un coche nuevo en la entrada
    • Pueden aparecer a un ritmo fijo o variable (aleatorio)


## Ficheros
- trafico_plantilla.c: plantilla inicial con el esqiueleto del programa
- trafico.c            núcleo básico del simalor de tráfico
- trafico_cartaA.c     ampliación A: calles aleatorias
- trafico_cartaB.c     ampliación B: semáforos   
- trafico_cartaC.c     ampliación C: múltiples coches simultáneos
- trafico_cartaD.c     ampliación D: cambios de dirección
- trafico_cartaE.c     ampliación E: cambios en la tasa de entradas de coches       
- trafico_cartaAD.c    combinación de las ampliaciones A y D  
- trafico_cartaBE.c    combinación de las ampliaciones B y E      
- trafico_comp.c.      simulador con todas las ampliaciones integradas          
- trafico_variable.c.  simulador extendido con mejoras adicionales
- trafico_obras.c      función extra: generación de obras que bloquean el tráfico       
     