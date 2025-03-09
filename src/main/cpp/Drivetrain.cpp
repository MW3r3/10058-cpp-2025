#include "Drivetrain.h"

Drivetrain::Drivetrain() {
    // Configure SparkMax controllers for the right side

    // Global configuration: set a smart current limit and use brake mode
    rev::spark::SparkMaxConfig GlobalConfig;
    GlobalConfig.SmartCurrentLimit(50).SetIdleMode(rev::spark::SparkMaxConfig::IdleMode::kBrake);

    // Create individual configurations for the right side motors
    rev::spark::SparkMaxConfig RightLeaderConfig;
    rev::spark::SparkMaxConfig RightFollowerConfig;

    // Invert the leader and set the follower to follow the leader
    RightLeaderConfig.Apply(GlobalConfig).Inverted(true);
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

void Drivetrain::TankDrive(double leftSpeed, double rightSpeed) {
    m_drive.TankDrive(leftSpeed, rightSpeed);
}

void Drivetrain::ArcadeDrive(double forward, double rotation) {
    m_drive.ArcadeDrive(forward, rotation);
}