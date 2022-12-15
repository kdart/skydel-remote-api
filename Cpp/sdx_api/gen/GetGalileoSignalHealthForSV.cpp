
#include "gen/GetGalileoSignalHealthForSV.h"

#include "command_factory.h"
#include "command_result_factory.h"
#include "parse_json.hpp"

///
/// Definition of GetGalileoSignalHealthForSV
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const GetGalileoSignalHealthForSV::CmdName = "GetGalileoSignalHealthForSV";
    const char* const GetGalileoSignalHealthForSV::Documentation = "Get Galileo signal health for I/NAV and F/NAV message";

    REGISTER_COMMAND_FACTORY(GetGalileoSignalHealthForSV);


    GetGalileoSignalHealthForSV::GetGalileoSignalHealthForSV()
      : CommandBase(CmdName)
    {}

    GetGalileoSignalHealthForSV::GetGalileoSignalHealthForSV(int svId, const std::string& component, const Sdx::optional<std::string>& dataSetName)
      : CommandBase(CmdName)
    {

      setSvId(svId);
      setComponent(component);
      setDataSetName(dataSetName);
    }


    GetGalileoSignalHealthForSVPtr GetGalileoSignalHealthForSV::create(int svId, const std::string& component, const Sdx::optional<std::string>& dataSetName)
    {
      return std::make_shared<GetGalileoSignalHealthForSV>(svId, component, dataSetName);
    }

    GetGalileoSignalHealthForSVPtr GetGalileoSignalHealthForSV::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<GetGalileoSignalHealthForSV>(ptr);
    }

    bool GetGalileoSignalHealthForSV::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<int>::is_valid(m_values["SvId"])
          && parse_json<std::string>::is_valid(m_values["Component"])
          && parse_json<Sdx::optional<std::string>>::is_valid(m_values["DataSetName"])
        ;

    }

    std::string GetGalileoSignalHealthForSV::documentation() const { return Documentation; }


    int GetGalileoSignalHealthForSV::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }


    int GetGalileoSignalHealthForSV::svId() const
    {
      return parse_json<int>::parse(m_values["SvId"]);
    }

    void GetGalileoSignalHealthForSV::setSvId(int svId)
    {
      m_values.AddMember("SvId", parse_json<int>::format(svId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::string GetGalileoSignalHealthForSV::component() const
    {
      return parse_json<std::string>::parse(m_values["Component"]);
    }

    void GetGalileoSignalHealthForSV::setComponent(const std::string& component)
    {
      m_values.AddMember("Component", parse_json<std::string>::format(component, m_values.GetAllocator()), m_values.GetAllocator());
    }



    Sdx::optional<std::string> GetGalileoSignalHealthForSV::dataSetName() const
    {
      return parse_json<Sdx::optional<std::string>>::parse(m_values["DataSetName"]);
    }

    void GetGalileoSignalHealthForSV::setDataSetName(const Sdx::optional<std::string>& dataSetName)
    {
      m_values.AddMember("DataSetName", parse_json<Sdx::optional<std::string>>::format(dataSetName, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
