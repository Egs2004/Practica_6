# Practica_6

Este repositorio contiene la implementación de una máquina de estados para el microcontrolador STM32 (NUCLEO-F103RB) utilizando una arquitectura modular de alto nivel.

## Arquitectura del Proyecto
El sistema se divide en capas para aislar la lógica del hardware, cumpliendo el principio de un modulo por responsabilidad:
* **Módulo LED:** Controla el estado del pin físico sin exponer registros.
* **Módulo Timer:** Genera y administra la base de tiempo mediante interrupciones hardware (TIM2), evitando bloqueos por `HAL_Delay`.
* **Módulo UART:** Maneja la transmisión de mensajes de estado por comunicación serial.
* **Lógica Principal:** Coordina los módulos y ejecuta una máquina de estados que altera la frecuencia del sistema cada 5 segundos.

## Flujo de Trabajo (Git/GitHub)
El desarrollo se coordinó mediante un sistema ágil:
1. Seguimiento mediante **Issues** y **GitHub Projects**.
2. Desarrollo aislado en **Branches** independientes.
3. Integración mediante **Pull Requests** y **Code Reviews** rigurosos antes del **Merge**.

## Requisitos de Compilación
* STM32CubeMX
* CMake + Ninja
* Compilador ARM GCC
