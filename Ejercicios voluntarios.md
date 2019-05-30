# Respuestas ejercicios voluntarios

- [Respuestas ejercicios voluntarios](#respuestas-ejercicios-voluntarios)
	- [¿Cúantos 8086 caben en un Core i9-9900K? Compara rendimiento n8086/CPU/GPU](#%C2%BFc%C3%BAantos-8086-caben-en-un-core-i9-9900k-compara-rendimiento-n8086cpugpu)
	- [IOMMU](#iommu)
	- [Coste del cambio de contexto](#coste-del-cambio-de-contexto)
	- [Implementación de la práctica ping/pong con colas de mensajes y socket](#implementaci%C3%B3n-de-la-pr%C3%A1ctica-pingpong-con-colas-de-mensajes-y-socket)
	- [Tipos de monitores. ¿De cual de los dos tipos es std::condition_variable?](#tipos-de-monitores-%C2%BFde-cual-de-los-dos-tipos-es-stdconditionvariable)
		- [Hoare](#hoare)
		- [Mesa](#mesa)
	- [Futex](#futex)
	- [Memoria transaccional](#memoria-transaccional)

## ¿Cúantos 8086 caben en un Core i9-9900K? Compara rendimiento n8086/CPU/GPU  
~~Un _8086_ tiene una velocidad de 5 MHz y el _Core i9-9900K_ tiene una velocidad de 3,6 GHz. Teniendo esto en cuenta, podemos decir que en el _i9_ caben 720 _8086_.~~  
~~El _8086_ tiene una arquitectura del mismo nombre, con transistores de 3 µm y tamaño de palabra de 16 bits. No puede ejecutar gráficos.~~  
~~El _Core i9-9900K_ tiene una arquitectura _Coffee Lake_, con transistores de 14 nm y un tamaño de palabra de 64 bits. En gráficos tiene una memoria de 64 GiB y una frecuencia de 350 MHz para una resolución máxima de 4K.~~  
## IOMMU
Una IOMMU es una unidad de gestión de memoria que conecta un bus de E/S con capacidad de acceso directo a memoria principal. Al igual que una MMU tradicional, que traduce direcciones virtuales visibles de CPU a direcciones físicas, IOMMU correlaciona direcciones virtuales visibles de dispositivo a direcciones físicas.  
Las ventajas de tener una IOMMU incluyen:
- Se pueden asignar grandes regiones de memoria sin la necesidad de que sean contiguas en la memoria física.
- Los dispositivos que no admiten direcciones de memoria lo suficientemente largas como para direccionar toda la memoria física aún pueden direccionar toda la memoria a través de la IOMMU.
- La memoria está protegida contra los dispositivos maliciosos.
- La paginación de la memoria periférica puede ser apoyada por un IOMMU.

Las desventajas son:
- Degradación del rendimiento por sobrecarga de traducción.
- Consumo de memoria física para las tablas página E/S añadidas.

## Coste del cambio de contexto
En el sistema operativo Linux, con la versión del kernel 2.6, un cambio de contexto toma de media entre 1 y 2 µs.  
En el sistema operativo macOS, con la versión 10.14.3, menos de 10 µs (no he encontrado información más precisa).  

## Implementación de la práctica ping/pong con colas de mensajes y socket
- [Colas de mensajes](https://github.com/jesusjimsa/Arquitectura-de-Sistemas-UGR/blob/master/Práctica%204/ping-pong/ping.pong.mq.cc)
- [Socket](https://github.com/jesusjimsa/Arquitectura-de-Sistemas-UGR/blob/master/Práctica%204/ping-pong/ping.pong.socket.cc)

## Tipos de monitores. ¿De cual de los dos tipos es std::condition_variable?
### Hoare
En la definición original de Hoare, el thread que ejecuta `cond_signal` le cede el monitor al thread que esperaba. El monitor toma entonces el lock y se lo entrega al thread durmiente, que reanuda la ejecución. Más tarde cuando el monitor quede libre nuevamente el thread que cedió el lock volverá a ejecutar.

### Mesa
El thread que ejecuta `cond_signal` sobre una variable de condición continúa con su ejecución dentro del monitor. Si hay otro thread esperando en esa variable de condición, se lo despierta y deja como listo. Podrá intentar entrar el monitor cuando éste quede libre, aunque puede suceder que otro thread logre entrar antes. Este nuevo thread puede cambiar la condición por la cual el primer thread estaba durmiendo. Cuando reanude la ejecución el durmiente, debería verificar que la condición efectivamente es la que necesita para seguir ejecutando. En el proceso que durmió, por lo tanto, es necesario cambiar la instrucción `if` por `while`, para que al despertar compruebe nuevamente la condición, y de no ser cierta vuelva a llamar a `cond_wait`.  
Este es el que usa `std::condition_variable`

## Futex
En computación, un futex es una llamada al sistema del kernel que los programadores pueden usar para implementar el bloqueo básico, o como un bloque de construcción para abstracciones de bloqueo de alto nivel como semáforos y exclusión mutua POSIX o variables de condición.

Un futex consiste en una cola de espera del espacio de kernel que se adjunta a un entero atómico en el espacio de usuario. Múltiples procesos o hebras operan en el entero completamente en el espacio de usuario, y solo recurren a llamadas del sistema relativamente caras para solicitar operaciones en la cola de espera. Un bloqueo basado en futex debidamente programado no utilizará llamadas al sistema, excepto cuando se oponga el bloqueo; dado que la mayoría de las operaciones no requieren arbitraje entre procesos, esto no ocurrirá en la mayoría de los casos.

## Memoria transaccional
La memoria transaccional es un mecanismo de control de concurrencia análogo a las transacciones de base de datos para controlar el acceso a la memoria compartida en la computación concurrente. Es una alternativa a la sincronización basada en bloqueo. La memoria transaccional es una estrategia implementada en software, en lugar de como un componente de hardware. Una transacción en este contexto ocurre cuando un fragmento de código ejecuta una serie de lecturas y escrituras en la memoria compartida. Estas lecturas y escrituras ocurren lógicamente en un solo instante en el tiempo; Los estados intermedios no son visibles a otras transacciones.
