//
// Created by Romain Pouvreau on 23/04/2026.
//

#include "I2CDCDriver.h"

#include "AbstractMotors.h"

I2CDCDriver::I2CDCDriver(int sda, int scl, int addr, int m1_fwd_port, int m1_bck_port, int m1_pwm, int m2_fwd_port, int m2_bck_port, int m2_pwm, int stdby_port) : m_currentVelocity(0.0f)
{
    // Initialisation du tableau de moteurs hérité de AbstractDriver
    for (auto & m_motor : m_motors)
    {
        m_motor = nullptr;
    }

    m_m1_fwd_port = m1_fwd_port;
    m_m1_bck_port = m1_bck_port;
    m_m2_fwd_port = m2_fwd_port;
    m_m2_bck_port = m2_bck_port;
    m_stdby_port = stdby_port;
    m_addr = addr;
    m_scl = scl;
    m_sda = sda;
    m_m1_pwm = m1_pwm;
    m_m2_pwm = m2_pwm;
}

void I2CDCDriver::init()
{
#ifdef ARDUINO
#elif ESP_PLATFORM

    // Initialise i2c
    m_dev.cfg.sda_io_num = static_cast<gpio_num_t>(m_sda);
    m_dev.cfg.scl_io_num = static_cast<gpio_num_t>(m_scl);
    m_dev.cfg.sda_pullup_en = GPIO_PULLUP_ENABLE;
    m_dev.cfg.scl_pullup_en = GPIO_PULLUP_ENABLE;

    ESP_ERROR_CHECK(pca9685_init_desc(&m_dev, m_addr, I2C_NUM_0, static_cast<gpio_num_t>(m_sda), static_cast<gpio_num_t>(m_scl)));
    ESP_ERROR_CHECK(pca9685_init(&m_dev));
    ESP_ERROR_CHECK(pca9685_restart(&m_dev));

    ESP_ERROR_CHECK(pca9685_set_pwm_frequency(&m_dev, 1526));

    ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_stdby_port, PCA9685_HIGH));
#endif
}

int I2CDCDriver::attach(AbstractMotor* motor)
{
    if(m_motors[0] == nullptr)
        return attach(motor, 0);
    else if(m_motors[1] == nullptr)
        return attach(motor, 1);
    return -1;
}

int I2CDCDriver::attach(AbstractMotor* motor, uint8_t id)
{
    if (id >= 2 || id >= MAX_MOTOR_IN_DRIVER)
    {
        return -1;
    }
    m_motors[id] = motor;

    m_motors[id]->m_driver = this;
    m_motors[id]->m_driverId = id;
    return id;
}

void I2CDCDriver::setVelocity(float velocity, uint8_t id)
{
    if (m_motors[id] == nullptr)
    {
        return;
    };

    m_currentVelocity = velocity;

    float absSpeed = fabsf(velocity);
    absSpeed = saturate(absSpeed, 0 ,1);

    int pwmValue = static_cast<int>(absSpeed * PCA9685_HIGH);

#ifdef ARDUINO
#elif ESP_PLATFORM

    if (id == 0)
    {
        ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_m1_pwm, pwmValue));

        ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_m1_fwd_port, velocity >= 0 ? PCA9685_HIGH : PCA9685_LOW));
        ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_m1_bck_port, velocity >= 0 ? PCA9685_LOW : PCA9685_HIGH));

    }else
    {
        ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_m2_pwm, pwmValue));

        ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_m2_fwd_port, velocity >= 0 ? PCA9685_HIGH : PCA9685_LOW));
        ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_m2_bck_port, velocity >= 0 ? PCA9685_LOW : PCA9685_HIGH));
    }

#endif
}

float I2CDCDriver::getVelocity(uint8_t id) const
{
    return (id == 0) ? m_currentVelocity : 0.0f;
}

bool I2CDCDriver::isFaulty() const
{
    return false;
}

void I2CDCDriver::setSleep(bool active)
{
#ifdef ARDUINO

#elif ESP_PLATFORM
        ESP_ERROR_CHECK(pca9685_set_pwm_value(&m_dev, m_stdby_port, active ? PCA9685_HIGH : PCA9685_LOW));
#endif

}
