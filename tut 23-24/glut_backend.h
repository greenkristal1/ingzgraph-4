#pragma once
// инициализация и настройка glut
#include "callbacks.h"

// Инициализация glut
void GLUTBackendInit(int argc, char** argv);

// Создания окна
bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, unsigned int bpp, bool isFullScreen, const char* pTitle);

// Запуск обратных вызовов glut
void GLUTBackendRun(ICallbacks* pCallbacks);