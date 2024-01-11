Proyecto Luis Osvaldo Cerna Copado
Licenciatura en Computación Matemática
13 de Diciembre de 2020

Se puede jugar desde el .exe

Explicación del juego.

Todo el juego funciona usando únicamente el ratón. Durante los menús sólo está disponible el click izquierdo 
y durante el juego están disponibles el izquierdo y el derecho (el click derecho pausa el juego y te lleva al menú de pausa).
Lo primero que aparece en pantalla es el menú de inicio, este te da dos opciones, "Play" o "Load Game" el primero inicia el juego
con el acomodo inicial del ajedrez como lo conocemos. El segundo te inicializa el juego con el acomodo de piezas que se dejó anteriormente,
esto con la finalidad de poder dejar una partida a medias y regresar después a terminarla. El estado del tablero se guarda constantemente,
de forma que no necesitas guardar la partida, solo salir y cargarla con este botón la siguiente vez que se desea jugar.

Dando click izquierdo en cualquiera de las dos opciones mencionadas anteriormente se inicia el juego, en este punto dispones del
click izquierdo para seleccionar piezas y para moverlas. En el momento en el que das click en una pieza se dibuja el borde de esa
casilla para puntualizar que esta seleccionada (dando click izquierdo nuevamente sobre la misma pieza la podemos deseleccionar).
Una vez seleccionada una pieza podemos dar click sobre cualquier otra casilla para moverla. El juego no tiene movimientos limitados
todas las piezas se pueden mover a cualquier casilla del tablero, incluso a aquellas casillas que ya contienen una pieza. Si esto último ocurre,
en caso de invadir la casilla de una pieza de color contrario, la primera "comerá" a la segunda de la forma en que ya conocemos de los juegos de ajedrez
la pieza de color contrario desaparece y la otra toma su lugar. En caso de invadir la casilla de una pieza del mismo color las imagenes se 
sobrepondran y de seleccionarla nuevamente, se elegirá a aquella con número más pequeño, las piezas dentro del código se enumeraron del 0 al 31
comenzando con la torre blanca (izquierda) el 0 y terminando con la torre negra (derecha) el 31. También cabe mencionar que si a la hora de seleccionar, 
el usario da click en una casilla que no contiene ninguna pieza, no se seleccionará nada y el juego no reaccionará de ninguna manera, sólo en caso de 
encontrar una pieza se selecciona.

Por último, si tú presionas el click derecho en cualquier parte de la pantalla durante el juego accederás al menú de pausa, el cual te da como opción
tres botones distintos. El primero de ellos "Play" solo quita la pausa y te regresa al juego exactamente como estaba. El segundo, con imagen de una 
flechita retornando te permite regresar un movimiento, es decir, regresa el juego con el estado inmediato anterior en el que estuvo. Cabe aclarar que 
solo es posible regresar un movimiento y que si se regresa desde un estado de seleccionado, te regresará nuevamente con ese estado, pero es sencillo
cambiar de pieza si es que no se deseaba elegir esa, solo se vuelve a dar click en la pieza para quitar la selección como habiamos mencionado antes. 
Con esto llegamos al tercer y último botón cuya finalidad es terminar el juego, se sale del ciclo y te presenta la última pantalla de despedida.
La ventana se cierra sola después de dos segundos de esto.
