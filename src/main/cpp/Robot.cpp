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
		g_dashboard.PutNumber("Max Speed", 1.0);
		g_dashboard.PutNumber("Tolerance", 0.1);
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
        // Get axis values using the XboxController methods
        // Get raw joystick values
		double leftY  = m_f310Controller.GetLeftY();
		double rightY = m_f310Controller.GetRightY();

		// Apply nonlinear mapping; adjust the exponent as needed (e.g., 2.0 for quadratic mapping)
		double mappedLeftY  = m_drivetrain.NonlinearMap(leftY, 2.0);
		double mappedRightY = m_drivetrain.NonlinearMap(rightY, 2.0);

		// Now use the mapped values for assisted tank drive:
		double tolerance = g_dashboard.GetNumber("Tolerance", 0.1);
		double maxSpeed = g_dashboard.GetNumber("Max Speed", 1.0);
		
		g_dashboard.GetString("Drive Mode", "Tank") == "Tank" ?
			m_drivetrain.AssistedTankDrive(mappedLeftY, mappedRightY, maxSpeed, tolerance) :
			m_drivetrain.ArcadeDrive(mappedLeftY, m_f310Controller.GetRightX(), maxSpeed);
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