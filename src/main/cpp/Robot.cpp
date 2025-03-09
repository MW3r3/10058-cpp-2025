#include <frc/TimedRobot.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/XboxController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Drivetrain.h"
#include "Elevator.h"
#include "Dashboard.h"
#include "DashboardSingleton.h"

class Robot : public frc::TimedRobot {
public:
    // Use XboxController for the F310 in XInput mode on USB port 0
    frc::XboxController m_f310Controller{0};

    void RobotInit() override {
		// Publish a notification to the dashboard
		g_dashboard.PutString("Drive Mode", "Tank");
		g_dashboard.SendNotification(elastic::NotificationLevel::INFO, "Robot Init", "Robot has been initialized.");
    }

    void RobotPeriodic() override {
        frc2::CommandScheduler::GetInstance().Run();
    }

	void TeleopInit() override {
		// Publish a notification to the dashboard
		g_dashboard.SendNotification(elastic::NotificationLevel::INFO, "Teleop Init", "Teleop mode has been initialized.");
	}

    void TeleopPeriodic() override {
        double maxSpeed = frc::SmartDashboard::GetNumber("Max Speed", 1.0);

        // Get axis values using the XboxController methods
        double leftX   = m_f310Controller.GetLeftX();
        double leftY   = m_f310Controller.GetLeftY();
        double rightX  = m_f310Controller.GetRightX();
        double rightY  = m_f310Controller.GetRightY();

		// Publish joystick values to NetworkTables
		g_dashboard.UpdateJoystick(leftX, leftY, rightX, rightY);

        g_dashboard.GetString("Drive Mode", "Tank") == "Tank" ?
			m_drivetrain.TankDrive(leftY, rightY, maxSpeed) :
			m_drivetrain.ArcadeDrive(leftY, rightX, maxSpeed);
    }

private:
    Drivetrain m_drivetrain;
    Elevator m_elevator;
};

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<Robot>();
}
#endif