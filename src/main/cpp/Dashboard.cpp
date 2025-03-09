// Dashboard.cpp

#include "Dashboard.h"

Dashboard::Dashboard() {
    auto ntInstance = nt::NetworkTableInstance::GetDefault();
    m_table = ntInstance.GetTable("Dashboard");
}

void Dashboard::UpdateJoystick(double leftX, double leftY, double rightX, double rightY) {
    m_table->PutNumber("LeftX", leftX);
    m_table->PutNumber("LeftY", leftY);
    m_table->PutNumber("RightX", rightX);
    m_table->PutNumber("RightY", rightY);
}

void Dashboard::SendNotification(elastic::NotificationLevel level, const std::string& title, const std::string& description, units::millisecond_t displayTime, int width, int height) {
    elastic::Notification notification;
    notification.level = level;
    notification.title = title;
    notification.description = description;
    notification.displayTime = displayTime;
    notification.width = width;
    notification.height = height;
    elastic::SendNotification(notification);
}

void Dashboard::PutNumber(const std::string& key, double value) {
    m_table->PutNumber(key, value);
}

void Dashboard::PutBoolean(const std::string& key, bool value) {
    m_table->PutBoolean(key, value);
}

void Dashboard::PutString(const std::string& key, const std::string& value) {
    m_table->PutString(key, value);
}

double Dashboard::GetNumber(const std::string& key, double defaultValue) const {
    return m_table->GetNumber(key, defaultValue);
}

bool Dashboard::GetBoolean(const std::string& key, bool defaultValue) const {
    return m_table->GetBoolean(key, defaultValue);
}

std::string Dashboard::GetString(const std::string& key, const std::string& defaultValue) const {
    return m_table->GetString(key, defaultValue);
}

