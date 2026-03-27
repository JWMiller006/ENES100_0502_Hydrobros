#pragma once
#include "motor_ctl.hpp"

/// Primary Mission-Control
class PMC {
  public: 
    /// Defualt contructor
    PMC(); 

    /// Contructor that automatically starts setup
    PMC(const char* Name, int MissionType, int MarkerID, int RoomNumber, int Tx_Pin, int Rx_Pin);

    /// Sets up the basic connections (i.e. WiFi, sends test message, etc.)
    void Init(const char* Name, int MissionType, int MarkerID, int RoomNumber, int Tx_Pin, int Rx_Pin); 

    /// Runs through the final code (from start to finish)
    void RunMission(); 

    void Stop(); 

    void SetMotorSpeed(unsigned int Motors, float Speed); 

    void GoToPosition(Point p); 

  protected: 
    /// Motor list
    Motor FR{}, FL{}, RR{}, RL{}; 

  private: 
    /// Define if this is initialized and ready to run yet
    bool bInitialized = false; 

    /// The or-ed together bits that specify the arena setup
    unsigned int mArragement = 0; 
};