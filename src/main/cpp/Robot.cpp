// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/XboxController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <rev/CANSparkMax.h>
#include <frc/Joystick.h>
#include <frc/PS4Controller.h>

#include <wpi/deprecated.h>
WPI_IGNORE_DEPRECATED

class Robot : public frc::TimedRobot {
 public:
  Robot() {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_rightForward.SetInverted(true);
    m_robotDrive.SetExpiration(100_ms);
    m_timer.Start();
  }

  void AutonomousInit() override { m_timer.Restart(); }

  void AutonomousPeriodic() override {
    // Drive for 2 seconds
    if (m_timer.Get() < 2_s) {
      // Drive forwards half speed, make sure to turn input squaring off
      m_robotDrive.ArcadeDrive(0.5, 0.0, false);
    } else {
      // Stop robot
      m_robotDrive.ArcadeDrive(0.0, 0.0, false);
    }
  }

  void TeleopInit() override {}

  void TeleopPeriodic() override {
    // Drive with arcade style (use right stick to steer)
    m_robotDrive.ArcadeDrive(m_ps4.GetLeftY()*0.75,
                             m_ps4.GetLeftX()*0.75); 

    // This is our shooter code. This should accelerate the Note into the top motor for a shot
        if( m_joystick.GetRawButton(1)){
            m_shooterBack.Set(0.85);
            m_shooterForward.Set(0.85);

        } else{ m_shooterBack.Set(0);
                m_shooterForward.Set(0);
        }

    // This is our intake code
        if( m_joystick.GetRawButton(2)){
            m_shooterForward.Set(-0.30);
            m_shooterBack.Set(-0.30);
    
      } else{ m_shooterForward.Set(0);
            m_shooterBack.Set(0);
         }
  }

  void TestInit() override {}

  void TestPeriodic() override {}

 private:
  // Robot drive sysyemy
  rev::CANSparkMax m_leftForward{21, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_rightForward{11, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_leftBack{20, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_rightBack{10, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_shooterForward{30, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  rev::CANSparkMax m_shooterBack{31, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
  frc::DifferentialDrive m_robotDrive{m_leftForward, m_rightForward};

  //frc::XboxController m_controller{0};
  frc::Timer m_timer;
  frc::Joystick m_joystick{1};
  frc::PS4Controller m_ps4{0};
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
