#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/Talon.h>
#include <rev/SparkMax.h>
#include <rev/config/SparkMaxConfig.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include "DashboardSingleton.h"




class Drivetrain : public frc2::SubsystemBase {
public:
    Drivetrain();

    /**
     * Periodic method for diagnostics.
     */
    void Periodic() override;

    /**
     * Drives the robot using tank drive control.
     *
     * @param leftSpeed  The speed for the left side.
     * @param rightSpeed The speed for the right side.
     */
    void TankDrive(double leftSpeed, double rightSpeed);

    /**
     * Drives the robot using arcade drive control.
     *
     * @param forward  The forward speed command.
     * @param rotation The rotation command.
     */
    void ArcadeDrive(double forward, double rotation);

private:
    // Left side motors (using Talon controllers)
    frc::Talon m_leftLeadMotor{0};
    frc::Talon m_leftFollowMotor{1};

    // Right side motors (using SparkMax controllers)
    rev::spark::SparkMax m_rightLeadMotor{12, rev::spark::SparkMax::MotorType::kBrushed};
    rev::spark::SparkMax m_rightFollowMotor{13, rev::spark::SparkMax::MotorType::kBrushed};

    // Grouping motors on each side (ensure left motors use left controllers, etc.)
    frc::MotorControllerGroup m_leftMotors{m_rightLeadMotor, m_rightFollowMotor};
    frc::MotorControllerGroup m_rightMotors{m_leftLeadMotor, m_leftFollowMotor};

    // Differential drive to control the robot's movement
    frc::DifferentialDrive m_drive{m_leftMotors, m_rightMotors};
};