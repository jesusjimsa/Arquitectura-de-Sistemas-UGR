bien  : número de mensajes correctos  
mal   : número de mensajes incorrectos  
total : bien + mal  
hebras: número de hebras que han impreso al menos un mensaje  
real  : tiempo de pared en segundos  
user  : tiempo de usuario en segundos  
sys   : tiempo de sistema en segundos  
tiempo: user + sys  
ratio : bien / tiempo --> número de mensajes correctos por segundo  

| programa  | bien |   mal | total hebras |  real  | user  |  sys | tiempo | ratio |
| ----------|-----|--------|--------------|--------|-------|------|--------|-------|
| atomic |  22832 |      0 |  22832 |      3 |   1.00 |   0.69 |   0.03 |    .72 |  31711 |
| cerrojo |  26405 |     0 |  26405 |      1 |   1.00 |   0.87 |   0.04 |    .91 |  29016 |
| lamport |  27773 |     4 |  27777 |      6 |   1.00 |   0.88 |   0.03 |    .91 |  30519 |
| lock_guard | 289770 |  0 | 289770 |     16 |   1.00 |   0.33 |   0.34 |    .67 | 432492 |
| mensaje | 114214 |    75 | 114289 |     16 |   1.00 |   0.18 |   0.21 |    .39 | 292856 |
| mutex | 176715 |       0 | 176715 |     16 |   1.02 |   0.26 |   0.18 |    .44 | 401625 |
| secuencial | 190449 |  0 | 190449 |      1 |   1.00 |   0.18 |   0.24 |    .42 | 453450 |
| tas |          7783 |  0 |   7783 |      1 |   1.01 |   0.40 |   0.02 |    .42 |  18530 |
| tasb |  10644 |        0 |  10644 |      1 |   1.02 |   0.48 |   0.02 |    .50 |  21288 |
| ticketlock |   7313 |  0 |   7313 |     16 |   1.00 |   0.04 |   0.17 |    .21 |  34823 |
| ttas |   9227 |        0 |   9227 |      1 |   1.00 |   0.39 |   0.03 |    .42 |  21969 |
