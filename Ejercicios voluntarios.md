# Respuestas ejercicios voluntarios
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
