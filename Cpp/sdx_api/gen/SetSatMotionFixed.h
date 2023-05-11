#pragma once

#include <memory>
#include "command_base.h"

#include <string>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// If IsFixed is set to true, the satellite will not move during the simulation and keep its initial position calculated at the beginning of the simulation.
    ///
    /// Name    Type   Description
    /// ------- ------ --------------------------------------------------------------------------------------------------------------
    /// System  string "GPS", "Galileo", "BeiDou", "QZSS" or "NavIC"
    /// SvId    int    The satellite's SV ID.
    /// IsFixed bool   If true, the satellite relative position is fixed, if false, the satellite motion follows a normal trajectory.
    ///

    class SetSatMotionFixed;
    typedef std::shared_ptr<SetSatMotionFixed> SetSatMotionFixedPtr;
    
    
    class SetSatMotionFixed : public CommandBase
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      SetSatMotionFixed();

      SetSatMotionFixed(const std::string& system, int svId, bool isFixed);

      static SetSatMotionFixedPtr create(const std::string& system, int svId, bool isFixed);
      static SetSatMotionFixedPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;

      virtual int executePermission() const override;


      // **** system ****
      std::string system() const;
      void setSystem(const std::string& system);


      // **** svId ****
      int svId() const;
      void setSvId(int svId);


      // **** isFixed ****
      bool isFixed() const;
      void setIsFixed(bool isFixed);
    };
    
  }
}

