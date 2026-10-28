# MonitorFrigorifico

## Descripción
MonitorFrigorifico es un proyecto electrónico que utiliza un ESP32 para controlar la temperatura y el estado de la puerta de un frigorífico. Su objetivo es detectar temperaturas elevadas y puertas abiertas durante demasiado tiempo, activando una alarma para avisar al usuario.

## Funciones principales
- Medición de temperatura mediante un sensor DS18B20.
- Detección de apertura y cierre de la puerta mediante un Reed Switch.
- Activación de una alarma sonora cuando la temperatura supera el límite establecido.
- Aviso cuando la puerta permanece abierta durante más de un minuto.
- Visualización de información en una pantalla LCD de 16x2.
- Conexión Wi-Fi para consultar los datos desde una aplicación.

## Componentes
- ESP32.
- Sensor de temperatura DS18B20.
- Reed Switch.
- Buzzer.
- Pantalla LCD 16x2 con módulo I2C.
- Placa de circuito impreso (PCB).
- Cables y alimentación eléctrica.

## Archivos del proyecto
- `frigorifico.ino`: código del programa para el ESP32.
- `Vigistain 3D.stl`: modelo tridimensional de la caja para imprimir en 3D.
- `proyecto ref`: carpeta con archivos de referencia del proyecto.

## Funcionamiento
El ESP32 recibe los datos del sensor de temperatura y del Reed Switch. Si detecta una temperatura superior al límite configurado o una puerta abierta durante demasiado tiempo, activa el buzzer. La pantalla LCD muestra información sobre la temperatura y el estado de la puerta. Mediante Wi-Fi, los datos también pueden consultarse desde una aplicación compatible.

## Objetivo
Desarrollar un sistema electrónico que permita supervisar las condiciones de un frigorífico y alertar al usuario ante situaciones que puedan afectar su funcionamiento.

## Instalación y uso
1. Conectar los componentes al ESP32 según el circuito diseñado.
2. Abrir `frigorifico.ino` en el IDE de Arduino.
3. Configurar las credenciales de la red Wi-Fi en el código.
4. Seleccionar la placa ESP32 y el puerto correspondiente.
5. Cargar el programa en el ESP32.
6. Encender el sistema y comprobar el funcionamiento de los sensores, la pantalla y la alarma.

## Modelo 3D
El archivo `Vigistain 3D.stl` contiene el diseño de la caja, preparado para utilizarse en un programa de laminado e impresión 3D. Antes de imprimir, se recomienda verificar las dimensiones y la ubicación de los componentes.

## Autores
Proyecto realizado por Agustin Vigistain y Bautista Fusi, como trabajo final de Taller de 5.º año.
