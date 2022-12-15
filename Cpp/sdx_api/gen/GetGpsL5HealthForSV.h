#pragma once

#include <memory>
#include "command_base.h"

#include "sdx_optional.h"
#include <string>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Get GPS L5 health (used with CNAV and CNAV2)
    ///
    /// Name        Type            Description
    /// ----------- --------------- -------------------------------------------------------------------------------------------
    /// SvId        int             Satellite's SV ID 1..32, or use 0 to apply new value to all satellites.
    /// DataSetName optional string Optional name of the data set to use. If no value is provided, the active data set is used.
    ///

    class GetGpsL5HealthForSV;
    typedef std::shared_ptr<GetGpsL5HealthForSV> GetGpsL5HealthForSVPtr;
    
    
    class GetGpsL5HealthForSV : public CommandBase
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      GetGpsL5HealthForSV();

      GetGpsL5HealthForSV(int svId, const Sdx::optional<std::string>& dataSetName = {});
  
      static GetGpsL5HealthForSVPtr create(int svId, const Sdx::optional<std::string>& dataSetName = {});
      static GetGpsL5HealthForSVPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;

      virtual int executePermission() const override;


      // **** svId ****
      int svId() const;
      void setSvId(int svId);


      // **** dataSetName ****
      Sdx::optional<std::string> dataSetName() const;
      void setDataSetName(const Sdx::optional<std::string>& dataSetName);
    };
    
  }
}

