#pragma once
#include "motor_ctl.hpp"
#include "us_ctl.hpp"

/// Primary Mission-Control
class PMC {
  public: 
    /*********************************************************/
    /*                Initialization Section                 */
    /*********************************************************/
    
    /// Defualt contructor
    PMC(); 

    /// Contructor that automatically starts setup
    PMC(const char* Name, int MissionType, int MarkerID, int RoomNumber, int Tx_Pin, int Rx_Pin);

    /// Sets up the basic connections (i.e. WiFi, sends test message, etc.)
    void Init(const char* Name, int MissionType, int MarkerID, int RoomNumber, int Tx_Pin, int Rx_Pin); 

    /// Runs through the final code (from start to finish)
    void RunMission(); 

    /*********************************************************/
    /*                 Motor Control Section                 */
    /*********************************************************/

    /// Stop wheel movement of the OTV (keeps it locked)
    void Stop(); 

    /// Releases the control of the wheels to move freely (use at the end of a run to prevent damage)
    void ReleaseWheels(bool free = true, unsigned int Motors = FrontRight | FrontLeft | RearRight | RearLeft);

    /// Set the motor speed of the given motor
    void SetMotorSpeed(unsigned int Motors, float Speed); 

    /// Goes to a specific point on a 2D plane (in the arena)
    void GoToPosition(const Point& p); 

    /// Turn to a specific theta (in radians) on the given axis
    void TurnTo(float Theta, unsigned int Axis = Center | Turn);

    /// Set the motors to drive on the given axis (including strafing)
    void Drive(float Speed, unsigned int Axis = Forward);

    /*********************************************************/
    /*                Sensor Control Section                 */
    /*********************************************************/

    /// Get the distance reading from the given direction
    float GetUSReading(unsigned int Direction); 

    float GetTheta(); 

  protected: 
    /// Motor list
    Motor FR{}, FL{}, RR{}, RL{}; 

    /// Ultrasonic sensors
    UltraSonicSensor ForwardUS{}, RightUS{}, LeftUS{}; 

    /// Helper function that turns the OTV around its center
    void TurnAboutCenter(float Theta);

    /// Helper function that turns the OTV about some other axis (or together different directions to make an axis)
    void TurnAboutCorner(float Theta, unsigned int Axis); 

  private: 
    /// Define if this is initialized and ready to run yet
    bool bInitialized = false; 

    /// The or-ed together bits that specify the arena setup
    unsigned int mArragement = 0; 
};





















