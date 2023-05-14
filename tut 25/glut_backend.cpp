#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "glut_backend.h"

static ICallbacks* s_pCallbacks = NULL;

// Матрёшка нужна для использования в функциях обратного вызова glut
static void SpecialKeyboardCB(int Key, int x, int y) {
    s_pCallbacks->SpecialKeyboardCB(Key, x, y);
}

static void KeyboardCB(unsigned char Key, int x, int y) {
    s_pCallbacks->KeyboardCB(Key, x, y);
}

static void PassiveMouseCB(int x, int y) {
    s_pCallbacks->PassiveMouseCB(x, y);
}

static void RenderSceneCB() {
    s_pCallbacks->RenderSceneCB();
}

static void IdleCB() {
    s_pCallbacks->IdleCB();
}

// Инициализация функций обратного вызова glut
static void InitCallbacks() {
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(IdleCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
    glutKeyboardFunc(KeyboardCB);
}

// Инициализация glut
void GLUTBackendInit(int argc, char** argv) {
    glutInit(&argc, argv); // Инициализация glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Настройка отображения
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); // Настройка опций glut
}

// Создание экрана
bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, unsigned int bpp, bool isFullScreen, const char* pTitle) {
    if (isFullScreen) { // Если флаг полного экрана, то полный экран
        char ModeString[64] = { 0 };
        snprintf(ModeString, sizeof(ModeString), "%dx%d@%d", Width, Height, bpp);
        glutGameModeString(ModeString);
        glutEnterGameMode();
    }
    else { // Иначе по обычному
        glutInitWindowSize(Width, Height);
        glutCreateWindow(pTitle);
    }

    // Создание и проверка glew
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return false;
    }

    return true;
}

// Запуск бекэнда glut и настройка цветов и текстуры
void GLUTBackendRun(ICallbacks* pCallbacks) {
    if (!pCallbacks) {
        fprintf(stderr, "%s : callbacks not specified!\n", __FUNCTION__);
        return;
    }

    // Глубина
    glEnable(GL_DEPTH_TEST);

    // Цвет и улучшение текстуры
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Инициализация функций обратного вызова
    s_pCallbacks = pCallbacks;
    InitCallbacks();
    // Основной цикл glut
    glutMainLoop();
}