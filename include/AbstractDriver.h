//
// Created by awing on 29/03/2026.
//

#ifndef MOTORS_ABSTRACTDRIVER_H
#define MOTORS_ABSTRACTDRIVER_H

#define MAX_MOTOR_IN_DRIVER 2

#include <cstdint>

class AbstractMotor;


/**
 * This class represent an Abstract Driver.
 */
class AbstractDriver {
public:
    virtual ~AbstractDriver() = default;

    /**
     * Attach a motor to the first empty channel available
     * @param motor the motor to attach
     * @return the id of the motor
     */
    virtual int attach(AbstractMotor* motor) = 0;

    /**
     * Attach a motor to the specified id
     * @param motor the motor to attach
     * @param id the channel id
     * @return -1 if it failed, the motor's id else
     */
    virtual int attach(AbstractMotor* motor, uint8_t id) = 0;

    /**
     * Detach the motor at this id
     * @param id the id at which the motor is
     */
    virtual void detach(const int id) {
        m_motors[id] = nullptr;
    }

    /**
     * set the velocity of the motor at the specified id
     * @param velocity the velocity to be set
     * @param id the motor id
     */
    virtual void setVelocity(float velocity, uint8_t id) = 0;

    /**
     * get the velocity from the motor at the specified id
     * @param id the motor id
     * @return the velocity
     */
    virtual float getVelocity(uint8_t id) const = 0;

    /**
     * return a pointer to the motor at the specified id
     * @param id the motor id
     * @return a pointer to the motor, nullptr if it doesn't exist
     */
    AbstractMotor* getMotor(const int id) const {
        if (id < 0 || id >= MAX_MOTOR_IN_DRIVER) return nullptr;
        return m_motors[id];
    }
protected:
    AbstractMotor* m_motors[MAX_MOTOR_IN_DRIVER] = {};
};

#endif //MOTORS_ABSTRACTDRIVER_H
