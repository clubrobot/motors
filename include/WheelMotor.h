//
// Created by Romain Pouvreau on 15/04/2026.
//

#ifndef MOTORS_WHEELMOTOR_H
#define MOTORS_WHEELMOTOR_H

#include "AbstractMotors.h"

/**
* @class WheelMotor
* @brief Implémentation concrète d'un moteur DC standard.
* * Cette classe permet de définir les limites physiques d'un moteur
* et de le lier à un canal spécifique d'un AbstractDriver.
*/
class WheelMotor : public AbstractMotor
{
public:
    /**
     * @brief Constructeur par défaut.
     * @param maxVelocity Vitesse maximale autorisée (généralement 1.0f pour 100%).
     */
    explicit WheelMotor(float maxVelocity = 1.0f);

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

    //!Renvoie la constante du moteur paramétrée
    /*!
        \return constante : (60 * reduction_ratio / velocity_constant_in_RPM) / supplied_voltage_in_V
    */
    float getConstant   () const {return m_constant;}

    //!Renvoie rayon de la roue du moteur
    /*
        \return rayon en mm
    */
    float getWheelRadius() const {return m_wheelRadius;}

    //!Paramètre le rayon de la roue liée au moteur
    /*!
        \param wheelRadius rayon en mm
    */
    void setWheelRadius(float wheelRadius);

    //!Envoie une commande de vitesse au moteur
    /*!
        \param velocity vitesse de commande en mm/s
    */
    void setVelocity(float velocity) override;


    //!Paramètre la constante du moteur
    /*!
        \param constant constante en rad/s/Volt
    */
    void setConstant   (float constant);

private:
    float m_maxVelocity; ///< Limite de vitesse pour ce moteur.
    float m_wheelRadius; //!<  in mm
    float m_constant; //!<  (60 * reduction_ratio / velocity_constant_in_RPM) / supplied_voltage_in_V
};


#endif //MOTORS_WHEELMOTOR_H
