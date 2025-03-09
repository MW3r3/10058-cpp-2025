#pragma once

#include <string>
#include <networktables/NetworkTableInstance.h>
#include "util/elasticlib.h"

class Dashboard {
public:
    Dashboard();

    void UpdateJoystick(double leftX, double leftY, double rightX, double rightY);
        void SendNotification(elastic::NotificationLevel level, 
                          const std::string& title, 
                          const std::string& description,
                          units::millisecond_t displayTime = 3000_ms,
                          int width = 400,                              
                          int height = 300);   
    void PutNumber(const std::string& key, double value);
    void PutBoolean(const std::string& key, bool value);
    void PutString(const std::string& key, const std::string& value);

    double GetNumber(const std::string& key, double defaultValue) const;
    bool GetBoolean(const std::string& key, bool defaultValue) const;
    std::string GetString(const std::string& key, const std::string& defaultValue) const;

private:
    std::shared_ptr<nt::NetworkTable> m_table;
};