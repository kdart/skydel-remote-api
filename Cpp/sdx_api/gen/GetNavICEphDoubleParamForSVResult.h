#pragma once

#include <memory>
#include "command_result.h"
#include "command_result_factory.h"
#include "sdx_optional.h"
#include <string>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Result of GetNavICEphDoubleParamForSV.
    ///
    /// Name        Type            Description
    /// ----------- --------------- -------------------------------------------------------------------------------------------
    /// SvId        int             Satellite SV ID 1..14, or use 0 to apply new value to all satellites
    /// ParamName   string          Parameter name (see table above for accepted names)
    /// Val         double          Parameter value (see table above for unit)
    /// DataSetName optional string Optional name of the data set to use. If no value is provided, the active data set is used.
    ///

    class GetNavICEphDoubleParamForSVResult;
    typedef std::shared_ptr<GetNavICEphDoubleParamForSVResult> GetNavICEphDoubleParamForSVResultPtr;
    typedef GetNavICEphDoubleParamForSVResult GetNavICEphemerisDoubleParamResult;
    typedef std::shared_ptr<GetNavICEphemerisDoubleParamResult> GetNavICEphemerisDoubleParamResultPtr;
    
    class GetNavICEphDoubleParamForSVResult : public CommandResult
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      GetNavICEphDoubleParamForSVResult();

      GetNavICEphDoubleParamForSVResult(CommandBasePtr relatedCommand, int svId, const std::string& paramName, double val, const Sdx::optional<std::string>& dataSetName = {});
  
      static GetNavICEphDoubleParamForSVResultPtr create(CommandBasePtr relatedCommand, int svId, const std::string& paramName, double val, const Sdx::optional<std::string>& dataSetName = {});
      static GetNavICEphDoubleParamForSVResultPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;


      // **** svId ****
      int svId() const;
      void setSvId(int svId);


      // **** paramName ****
      std::string paramName() const;
      void setParamName(const std::string& paramName);


      // **** val ****
      double val() const;
      void setVal(double val);


      // **** dataSetName ****
      Sdx::optional<std::string> dataSetName() const;
      void setDataSetName(const Sdx::optional<std::string>& dataSetName);
    };
    REGISTER_COMMAND_RESULT_TO_FACTORY_DECL(GetNavICEphDoubleParamForSVResult);
  }
}

