# Comando para compilar desde terminal

1. --- comando cuando el archivo .cpp esta en la raiz
g++ -g -I./include -L./lib bresemham.cpp src/glad.c -lglfw3dll -o bresemham.exe

2. --- comando cuando el archivo .cpp esta en la en la carpeta src
g++ -g -I./include -L./lib src/GraficaBresemham.cpp src/glad.c -lglfw3dll -o Grafica.exe


NOTA:
se tiene que tener la comfigurado las variables de entorno para el compilador de c++






