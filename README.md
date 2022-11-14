# Comando para compilar desde terminal

1. --- comando cuando el archivo .cpp esta en la raiz
g++ -g -I./include -L./lib HelloTriangulo.cpp src/glad.c -lglfw3dll -o HelloTriangulo.exe

2. --- comando cuando el archivo .cpp esta en la en la carpeta src
g++ -g -I./include -L./lib src/GraficaBresemham.cpp src/glad.c -lglfw3dll -o Grafica.exe


NOTA:
se tiene que tener la comfigurado las variables de entorno para el compilador de c++



# opengl-cpp-template

Opengl c++ template for vscode ide

This template is source code for this article https://medium.com/@vivekjha92/setup-opengl-with-vs-code-82852c653c43

Requirements for this template to work
1.  To run this template you should have GCC C++ compiler and the C/C++ extension for VS Code.
    To setup both, follow this https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites

