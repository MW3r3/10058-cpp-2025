#include "Drivetrain.h"

Drivetrain::Drivetrain() {
    // Configure SparkMax controllers for the right side

    // Global configuration: set a smart current limit and use brake mode
    rev::spark::SparkMaxConfig GlobalConfig;
    GlobalConfig.SmartCurrentLimit(50).SetIdleMode(rev::spark::SparkMaxConfig::IdleMode::kCoast);

    // Create individual configurations for the right side motors
    rev::spark::SparkMaxConfig RightLeaderConfig;
    rev::spark::SparkMaxConfig RightFollowerConfig;

    // Invert the leader and set the follower to follow the leader
    RightFollowerConfig.Apply(GlobalConfig).Follow(m_rightLeadMotor);

    // Apply configurations to the SparkMax controllers
    m_rightLeadMotor.Configure(RightLeaderConfig,
                               rev::spark::SparkMax::ResetMode::kResetSafeParameters,
                               rev::spark::SparkMax::PersistMode::kPersistParameters);
    m_rightFollowMotor.Configure(RightFollowerConfig,
                                 rev::spark::SparkMax::ResetMode::kResetSafeParameters,
                                 rev::spark::SparkMax::PersistMode::kPersistParameters);
}

void Drivetrain::Periodic() {
    g_dashboard.PutNumber("Left Lead Motor Output", m_leftLeadMotor.Get());
    g_dashboard.PutNumber("Right Lead Motor Output", m_rightLeadMotor.GetAppliedOutput());
}

void Drivetrain::AssistedTankDrive(double leftSpeed, double rightSpeed, double maxSpeed, double tolerance) {
    // Clamp speeds to the maximum speed
    leftSpeed = std::clamp(leftSpeed, -maxSpeed, maxSpeed);
    rightSpeed = std::clamp(rightSpeed, -maxSpeed, maxSpeed);

    // If the difference between left and right speeds is less than the tolerance,
    // set both speeds to the average, allowing for straighter driving.
    if (std::abs(leftSpeed - rightSpeed) < tolerance) {
        double avgSpeed = (leftSpeed + rightSpeed) / 2.0;
        leftSpeed = avgSpeed;
        rightSpeed = avgSpeed;
    }

    m_drive.TankDrive(leftSpeed, rightSpeed);
}

void Drivetrain::ArcadeDrive(double leftSpeed, double rightSpeed, double maxSpeed) {
    double forward = (leftSpeed + rightSpeed) / 2.0;
    double rotation = (leftSpeed - rightSpeed) / 2.0;
    forward = std::clamp(forward, -maxSpeed, maxSpeed); 
    rotation = std::clamp(rotation, -maxSpeed, maxSpeed);
    m_drive.ArcadeDrive(forward, rotation);
}

double Drivetrain::NonlinearMap(double input, double exponent) {
    double sign = (input >= 0.0) ? 1.0 : -1.0;
    return sign * std::pow(std::abs(input), exponent);
}

