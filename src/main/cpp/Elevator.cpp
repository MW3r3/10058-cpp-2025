#include "Elevator.h"

Elevator::Elevator() {}

bool Elevator::IsAtBottom() const {
    return m_hallBottom.GetAverageVoltage() > m_ThresholdBottom;
}

bool Elevator::IsAtMid() const {
    return m_hallMid.GetAverageVoltage() > m_ThresholdMid;
}

bool Elevator::IsAtTop() const {
    return m_hallTop.GetAverageVoltage() > m_ThresholdTop;
}

void Elevator::Periodic() {
    // Update thresholds from SmartDashboard
    m_ThresholdBottom = g_dashboard.GetNumber("Elevator Bottom Threshold", m_ThresholdBottom);
    m_ThresholdMid    = g_dashboard.GetNumber("Elevator Mid Threshold", m_ThresholdMid);
    m_ThresholdTop    = g_dashboard.GetNumber("Elevator Top Threshold", m_ThresholdTop);

    // Publish values to SmartDashboard
    g_dashboard.PutNumber("Elevator Bottom Threshold", m_ThresholdBottom);
    g_dashboard.PutNumber("Elevator Mid Threshold", m_ThresholdMid);
    g_dashboard.PutNumber("Elevator Top Threshold", m_ThresholdTop);
    g_dashboard.PutNumber("Hall Bottom Voltage", m_hallBottom.GetAverageVoltage());
    g_dashboard.PutBoolean("Elevator Bottom", IsAtBottom());
    g_dashboard.PutNumber("Hall Mid Voltage", m_hallMid.GetAverageVoltage());
    g_dashboard.PutBoolean("Elevator Mid", IsAtMid());
    g_dashboard.PutNumber("Hall Top Voltage", m_hallTop.GetAverageVoltage());
    g_dashboard.PutBoolean("Elevator Top", IsAtTop());
}