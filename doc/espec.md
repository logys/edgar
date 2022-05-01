# Objetivo principal

**Dispositivo para ayudar a realizar trayectorias bien definidas en el 
movimiento de los brazos**

# Características

- Eficiente
- Responsivo
- Inalámbrico
- Preciso
- Trayectorias configurables
- Potente

## Descripción de la característica Preciso

- As a user
- I want smooth movements
- So that the trajectories are precises

### Controlador dinámico

Historias

- Al recibir el commando start, se inicia el bucle y sus respectivas variables,
no se cambia el estado de las variables, solo se inicia el bucle.
-- Dado que el controlador esta detenido,
-- Cuando se recibe ala señal
-- El controlador se inicia

-- Dado que el controlador esta corriendo
-- Cuando se recibe la señal
-- No pasa nada

- Al recibir el commando stop, se detiene el bucle, igualmente no se cambia el
estado.
-- Dado que el controlador esta encendido
-- Cuando se recibe la señal
-- El loop se detiene y detiene los motores

-- Dado que el controlador esta apagado
-- Cuando se recibe la señal
-- No hace nada

- Al recibir el commando reinit, se reinician todas las variables de estado.
-- Dado que el controlador fue configurado
-- Cuando se recibe la señal
-- El estado se restablece al inicial

- Al recibir el commando kp acompañado de un dato, se cambia el valor del 
controlador kp
-- Dado que el controlador fue configurado con un kp inicial
-- Al recibir el commando
-- El valor de inicial de kp es reemplazado

- Al recibir el commando ki acompañado de un dato, se cambia el valor del 
controlador ki
--
- Al recibir el commando kd acompañado de un dato, se cambia el valor del 
controlador kd
--
- La velocidad se actualiza en un solo comando, siendo especificadas las
velocidades angular y lineal y calculándose la velocidad de cada rueda.
-- Dadas las velocidades configuradas inicialmente
-- Cuando se recibe el commando
-- Las velocidades se actualizan

### Controlador de puntos
## Metas
- Diseñar un controlador de tal forma que 
