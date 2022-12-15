#pragma once

#include <memory>
#include "command_result.h"
#include "command_result_factory.h"
#include <string>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Result of GetVehicleTrajectory.
    ///
    /// Name Type   Description
    /// ---- ------ -----------------------------------------------------------------------
    /// Type string Trajectory type ("Fix", "Circular", "HIL", "Track", "Route" or "Orbit")
    ///

    class GetVehicleTrajectoryResult;
    typedef std::shared_ptr<GetVehicleTrajectoryResult> GetVehicleTrajectoryResultPtr;
    
    
    class GetVehicleTrajectoryResult : public CommandResult
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      GetVehicleTrajectoryResult();

      GetVehicleTrajectoryResult(CommandBasePtr relatedCommand, const std::string& type);
  
      static GetVehicleTrajectoryResultPtr create(CommandBasePtr relatedCommand, const std::string& type);
      static GetVehicleTrajectoryResultPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;


      // **** type ****
      std::string type() const;
      void setType(const std::string& type);
    };
    REGISTER_COMMAND_RESULT_TO_FACTORY_DECL(GetVehicleTrajectoryResult);
  }
}

