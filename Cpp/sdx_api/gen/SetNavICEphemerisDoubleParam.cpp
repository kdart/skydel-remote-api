
#include "gen/SetNavICEphemerisDoubleParam.h"

#include "command_factory.h"
#include "command_result_factory.h"
#include "parse_json.hpp"

///
/// Definition of SetNavICEphemerisDoubleParam
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const SetNavICEphemerisDoubleParam::CmdName = "SetNavICEphemerisDoubleParam";
    const char* const SetNavICEphemerisDoubleParam::Documentation = "Please note the command SetNavICEphemerisDoubleParam is deprecated since 21.3. You may use SetNavICEphDoubleParamForSV.\n\nSet various parameters in the NavIC ephemeris\n\n  ParamName         Unit\n  \"ClockBias\"       sec\n  \"ClockDrift\"      sec/sec\n  \"ClockDriftRate\"  sec/sec^2\n  \"Crs\"             meter\n  \"Crc\"             meter\n  \"Cis\"             rad\n  \"Cic\"             rad\n  \"Cus\"             rad\n  \"Cuc\"             rad\n  \"DeltaN\"          rad/sec\n  \"M0\"              rad\n  \"Eccentricity\"    -\n  \"SqrtA\"           sqrt(meter)\n  \"BigOmega\"        rad\n  \"I0\"              rad\n  \"LittleOmega\"     rad\n  \"BigOmegaDot\"     rad/sec\n  \"Idot\"            rad/sec\n  \"Accuracy\"        meter\n  \"Adot\"            meters/sec\n  \"DeltaN0dot\"      rad/sec^2\n  \"Tgd\"             sec";

    REGISTER_COMMAND_FACTORY(SetNavICEphemerisDoubleParam);


    SetNavICEphemerisDoubleParam::SetNavICEphemerisDoubleParam()
      : CommandBase(CmdName)
    {}

    SetNavICEphemerisDoubleParam::SetNavICEphemerisDoubleParam(int svId, const std::string& paramName, double val, const Sdx::optional<std::string>& dataSetName)
      : CommandBase(CmdName)
    {

      setSvId(svId);
      setParamName(paramName);
      setVal(val);
      setDataSetName(dataSetName);
    }


    SetNavICEphemerisDoubleParamPtr SetNavICEphemerisDoubleParam::create(int svId, const std::string& paramName, double val, const Sdx::optional<std::string>& dataSetName)
    {
      return std::make_shared<SetNavICEphemerisDoubleParam>(svId, paramName, val, dataSetName);
    }

    SetNavICEphemerisDoubleParamPtr SetNavICEphemerisDoubleParam::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<SetNavICEphemerisDoubleParam>(ptr);
    }

    bool SetNavICEphemerisDoubleParam::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<int>::is_valid(m_values["SvId"])
          && parse_json<std::string>::is_valid(m_values["ParamName"])
          && parse_json<double>::is_valid(m_values["Val"])
          && parse_json<Sdx::optional<std::string>>::is_valid(m_values["DataSetName"])
        ;

    }

    std::string SetNavICEphemerisDoubleParam::documentation() const { return Documentation; }


    int SetNavICEphemerisDoubleParam::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }


    int SetNavICEphemerisDoubleParam::svId() const
    {
      return parse_json<int>::parse(m_values["SvId"]);
    }

    void SetNavICEphemerisDoubleParam::setSvId(int svId)
    {
      m_values.AddMember("SvId", parse_json<int>::format(svId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::string SetNavICEphemerisDoubleParam::paramName() const
    {
      return parse_json<std::string>::parse(m_values["ParamName"]);
    }

    void SetNavICEphemerisDoubleParam::setParamName(const std::string& paramName)
    {
      m_values.AddMember("ParamName", parse_json<std::string>::format(paramName, m_values.GetAllocator()), m_values.GetAllocator());
    }



    double SetNavICEphemerisDoubleParam::val() const
    {
      return parse_json<double>::parse(m_values["Val"]);
    }

    void SetNavICEphemerisDoubleParam::setVal(double val)
    {
      m_values.AddMember("Val", parse_json<double>::format(val, m_values.GetAllocator()), m_values.GetAllocator());
    }



    Sdx::optional<std::string> SetNavICEphemerisDoubleParam::dataSetName() const
    {
      return parse_json<Sdx::optional<std::string>>::parse(m_values["DataSetName"]);
    }

    void SetNavICEphemerisDoubleParam::setDataSetName(const Sdx::optional<std::string>& dataSetName)
    {
      m_values.AddMember("DataSetName", parse_json<Sdx::optional<std::string>>::format(dataSetName, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
