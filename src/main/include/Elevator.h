#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AnalogInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "DashboardSingleton.h"

class Elevator : public frc2::SubsystemBase {
public:
    Elevator();

    bool IsAtBottom() const;
    bool IsAtMid() const;
    bool IsAtTop() const;

    void Periodic() override;

private:
    frc::AnalogInput m_hallBottom{0};
    frc::AnalogInput m_hallMid{1};
    frc::AnalogInput m_hallTop{2};

    double m_ThresholdBottom = 2.5;
    double m_ThresholdMid    = 2.5;
    double m_ThresholdTop    = 2.5;
};