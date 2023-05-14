#ifndef LIGHTING_TECHNIQUE_H
#define	LIGHTING_TECHNIQUE_H
// Методы освящения
#include "technique.h"
#include "math_3d.h"

// Базовое освящение
struct BaseLight
{
    Vector3f Color; // Цвет
    float AmbientIntensity; // Внешняя интенсивность 
    float DiffuseIntensity; // Интенсивность рассеивания

    BaseLight()
    {
        Color = Vector3f(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }
};

// Направленное освящение 
struct DirectionalLight : public BaseLight
{
    Vector3f Direction; // Направление

    DirectionalLight()
    {
        Direction = Vector3f(0.0f, 0.0f, 0.0f);
    }
};

// Точечное освящение
struct PointLight : public BaseLight
{
    Vector3f Position; // Позиция точки освящения

    // Коэфициенты затухания
    struct
    {
        float Constant;
        float Linear;
        float Exp;
    } Attenuation;

    PointLight()
    {
        Position = Vector3f(0.0f, 0.0f, 0.0f);
        Attenuation.Constant = 1.0f;
        Attenuation.Linear = 0.0f;
        Attenuation.Exp = 0.0f;
    }
};

// Структура для описывания прожектора
struct SpotLight : public PointLight
{
    Vector3f Direction;
    float Cutoff;

    SpotLight()
    {
        Direction = Vector3f(0.0f, 0.0f, 0.0f);
        Cutoff = 0.0f;
    }
};

// Методы освящения
class LightingTechnique : public Technique
{
public:
    static const unsigned int MAX_POINT_LIGHTS = 2;
    static const unsigned int MAX_SPOT_LIGHTS = 2;

    LightingTechnique();
    virtual bool Init(); // Создание шейдеров вызывает методы добавления шейдеров и линковки с проверкой

    // Настройка мировых координат
    void SetWVP(const Matrix4f& WVP);
    void SetLightWVP(const Matrix4f& LightWVP);
    // Функция для отправления матрицы мировых преобразований
    void SetWorldMatrix(const Matrix4f& WVP);
    // Настройка текстур
    void SetColorTextureUnit(unsigned int TextureUnit);
    void SetShadowMapTextureUnit(unsigned int TextureUnit);
    void SetNormalMapTextureUnit(unsigned int TextureUnit);
    // Функция назначает параметры направленного света в шейдере
    // Ещё нужна для вектора направления и интенсивности рассеивания
    void SetDirectionalLight(const DirectionalLight& Light);

    // Настройка положения глаза
    void SetEyeWorldPos(const Vector3f& EyeWorldPos);
    // Настройка интенсивности отражения
    void SetMatSpecularIntensity(float Intensity);
    // Настройка коэфициента материала
    void SetMatSpecularPower(float Power);

    // Устанавливает точки света
    void SetPointLights(unsigned int NumLights, const PointLight* pLights);
    void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);

private:
    GLuint m_WVPLocation; // Система координат камеры
    GLuint m_LightWVPLocation;
    GLuint m_WorldMatrixLocation; // Матрица мировых преобразований
    GLuint m_shadowMapLocation;
    GLuint m_normalMapLocation;
    GLuint m_colorMapLocation;

    GLuint m_eyeWorldPosLocation; // Позиция галаз
    GLuint m_matSpecularIntensityLocation; // Интенсивность освящения
    GLuint m_matSpecularPowerLocation; // Коэфициент материала
    GLuint m_numPointLightsLocation; // Расположения точек света
    GLuint m_numSpotLightsLocation; // Расположение прожектор

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } m_dirLightLocation; // Структура, описывывающая направленный свет

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_pointLightsLocation[MAX_POINT_LIGHTS];  // Структура, описывающая точечный свет

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Direction;
        GLuint Cutoff;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_spotLightsLocation[MAX_SPOT_LIGHTS]; // Описывает прожектор
};

#endif	/* LIGHTING_TECHNIQUE_H */