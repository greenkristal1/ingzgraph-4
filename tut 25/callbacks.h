#pragma once
// Инкапсулирование всех функций обратного вызова, используемых в glut-функциях, в один класс
class ICallbacks // Класс-интерфейс
{
public:
    // Функция для обратного вызова, обрабатывающая нажатие клаивиши на клавиатуре
    // Принимает занчение клавиши и координаты мыши в момент нажатия клавиши
    virtual void SpecialKeyboardCB(int Key, int x, int y) = 0;
    // Для завершения программы
    virtual void KeyboardCB(unsigned char Key, int x, int y) = 0;
    // Для отслеживания мыши
    virtual void PassiveMouseCB(int x, int y) = 0;
    // Рендер сцены
    virtual void RenderSceneCB() = 0;
    // Просто функция, которая хранит дргую функцию - RenderSceneCB
    virtual void IdleCB() = 0;
    virtual ~ICallbacks() {};
};