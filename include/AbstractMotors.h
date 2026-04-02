//
// Created by awing on 29/03/2026.
//

#ifndef MOTORS_ABSTRACTMOTORS_H
#define MOTORS_ABSTRACTMOTORS_H

#include <cstdint>
#include "AbstractDriver.h"

class AbstractMotor
{
public:
    /**
     * @brief Constructeur d'AbstractMotor.
     *
     * Méthode à implémenter.
     */
    virtual ~AbstractMotor() = default;
    /**
     * @brief Charge une nouvelle vitesse.
     *
     * Change la vitesse du moteur par celle passée en parametre. Méthode à implémenter.
     *
     * @param velocity Nouvelle vitesse.
     */
    virtual void setVelocity(float velocity) {
        this->m_driver->setVelocity(velocity, this->m_driverId);
    };

    /**
     * @brief Retourne vitesse max
     *
     * Retourne la vitesse max du moteur pour son intégration dans les calculs de DifferentialController.
     *
     * @return virtual float
     */
    [[nodiscard]] virtual float getMaxVelocity() const = 0;

protected:
    AbstractDriver* m_driver = nullptr;
    uint8_t m_driverId = 255;

};
#endif //MOTORS_ABSTRACTMOTORS_H