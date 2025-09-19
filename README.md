# sistemas-operativos

# 🖥️ Simulador de Planificación MLFQ en C++

## 📌 Introducción
Este proyecto implementa un **simulador de planificación por colas multinivel con realimentación (MLFQ)** en C++.  
Permite probar distintas configuraciones de colas (Round Robin, SJF, STCF) y obtener métricas de rendimiento de procesos como:

- **WT** (Waiting Time)  
- **CT** (Completion Time)  
- **RT** (Response Time)  
- **TAT** (Turnaround Time)  

---

## ⚙️ Requisitos
- Compilador **C++** (recomendado **g++ 9.0+**).  
- Sistema operativo: Windows, Linux o macOS.  
- Archivos de entrada (`.txt`) con la lista de procesos.  

---

## 📂 Estructura del Proyecto
├── main.cpp

├── Process.h / Process.cpp

├── QueueMLFQ.h / QueueMLFQ.cpp

├── SchedulerMLFQ.h / SchedulerMLFQ.cpp

├── Utils.h / Utils.cpp

├── mlfq001.txt # Archivo de entrada de procesos

└── resultados/ # Carpeta donde se generan las salidas


---

## 📝 Formato de Entrada
El simulador recibe un archivo `.txt` con la siguiente estructura:

etiqueta; BT; AT; Q; Pr

A;6;0;1;5

B;9;0;1;4

C;10;0;2;3

D;15;0;2;3

E;8;0;3;2


- **etiqueta** → Nombre del proceso (ejemplo: A, B, P1).  
- **BT (Burst Time)** → Tiempo total de CPU requerido.  
- **AT (Arrival Time)** → Tiempo de llegada del proceso.  
- **Q (Queue)** → Número de la cola inicial (1 = más alta).  
- **Pr (Priority)** → Nivel de prioridad (mayor número = mayor prioridad).  

---

## ▶️ Ejecución

### 1. Compilar
En la terminal, dentro de la carpeta del proyecto:

```bash
g++ -o mlfq main.cpp Process.cpp QueueMLFQ.cpp SchedulerMLFQ.cpp Utils.cpp
```
Esto generará el ejecutable mlfq.

2. Ejecutar
   
mlfq.exe

## 📂 Archivos de Salida

El programa genera archivos como:

- `mlq001Out.txt`  
- `mlq002Out.txt`  
- `mlq003Out.txt`  

Cada archivo contiene:

etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT

A;6;0;1;5;5;11;0;11

B;9;0;1;4;6;15;1;15

C;10;0;2;3;24;34;15;34

D;15;0;2;3;25;40;18;40

E;8;0;3;2;40;48;40;48

WT=20.0; CT=29.6; RT=14.8; TAT=29.6;


---

## 🔧 Configuración de Colas

El archivo `main.cpp` contiene las configuraciones de colas.

Ejemplo:

```cpp
// Configuración 1
std::vector<std::pair<std::string,int>> config1 = {
    {"RR",1}, {"RR",3}, {"RR",4}, {"SJF",0}
};

// Configuración 2
std::vector<std::pair<std::string,int>> config2 = {
    {"RR",2}, {"RR",3}, {"RR",4}, {"STCF",0}
};

// Configuración 3
std::vector<std::pair<std::string,int>> config3 = {
    {"RR",3}, {"RR",5}, {"RR",6}, {"RR",20}
};
```

📊 Métricas Calculadas

WT (Waiting Time) → Tiempo total en espera.

CT (Completion Time) → Momento en que el proceso terminó.

RT (Response Time) → Tiempo desde llegada hasta primera ejecución.

TAT (Turnaround Time) → Tiempo total desde llegada hasta terminación.

Se muestran tanto por proceso como promedios al final del archivo.

💡 Ejemplo de Uso

Entrada (mlfq001.txt):

A;6;0;1;5

B;9;0;1;4

C;10;0;2;3

D;15;0;2;3

E;8;0;3;2


Salida (mlq001Out.txt):

A;6;0;1;5;5;11;0;11

B;9;0;1;4;6;15;1;15

C;10;0;2;3;24;34;15;34

D;15;0;2;3;25;40;18;40

E;8;0;3;2;40;48;40;48

WT=20.0; CT=29.6; RT=14.8; TAT=29.6;

