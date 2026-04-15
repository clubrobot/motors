//
// Created by Romain Pouvreau on 15/04/2026.
//

#ifndef MOTORS_DCMOTOR_H
#define MOTORS_DCMOTOR_H

#include "AbstractMotors.h"

/**
* @class DCMotor
* @brief Implémentation concrète d'un moteur DC standard.
* * Cette classe permet de définir les limites physiques d'un moteur
* et de le lier à un canal spécifique d'un AbstractDriver.
*/
class DCMotor : public AbstractMotor
{
public:
    /**
     * @brief Constructeur par défaut.
     * @param maxVelocity Vitesse maximale autorisée (généralement 1.0f pour 100%).
     */
    explicit DCMotor(float maxVelocity = 1.0f);

    /**
     * @brief Retourne la vitesse maximale configurée.
     * @return float Vitesse max.
     */
    [[nodiscard]] float getMaxVelocity() const override;

    /**
     * @brief Modifie la vitesse maximale (limitation logicielle).
     * @param maxVelocity Nouvelle vitesse max.
     */
    void setMaxVelocity(float maxVelocity);

private:
    float m_maxVelocity; ///< Limite de vitesse pour ce moteur.
};


#endif //MOTORS_DCMOTOR_H
