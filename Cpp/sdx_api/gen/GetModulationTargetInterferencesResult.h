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
    /// Result of GetModulationTargetInterferences.
    ///
    /// Name        Type            Description
    /// ----------- --------------- -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /// Output      int             Output index (zero based)
    /// MinRate     int             Minimum sampling rate (12500000, 25000000, 50000000, 60000000, 100000000)
    /// MaxRate     int             Maximum sampling rate (12500000, 25000000, 50000000. 60000000, 100000000)
    /// Group       int             Interference group number [1..16] or 0 for no group
    /// CentralFreq double          Central frequency (Hz). Put 0.0 and complete signal list to let Skydel choose automaticly the central frequency.
    /// Gain        int             The gain associated to this output (dB). As of today, accepted values are 0, 20, 40, 60 and 80. Values at 40 and under are not recommended. Use a negative value to use the default value (60).
    /// Id          string          Target identifier
    /// Signal      optional string Comma separated signal keys if you want to match central frequency and sampling rate with a particular list of signals. Accepted signal keys: "L1CA", "L1C", "L1P", "L1ME", "L1MR", "L2C", "L2P", "L2ME", "L2MR", "L5", "G1", "G2", "E1", "E5a", "E5b", "B1", "B2", "B1C", "B2a", "SBASL1", "QZSSL1CA", "QZSSL1CB", "QZSSL1C", "QZSSL2C", "QZSSL5", "QZSSL1S", "QZSSL5S", "NAVICL5"
    ///

    class GetModulationTargetInterferencesResult;
    typedef std::shared_ptr<GetModulationTargetInterferencesResult> GetModulationTargetInterferencesResultPtr;
    
    
    class GetModulationTargetInterferencesResult : public CommandResult
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      GetModulationTargetInterferencesResult();

      GetModulationTargetInterferencesResult(CommandBasePtr relatedCommand, int output, int minRate, int maxRate, int group, double centralFreq, int gain, const std::string& id, const Sdx::optional<std::string>& signal = {});
  
      static GetModulationTargetInterferencesResultPtr create(CommandBasePtr relatedCommand, int output, int minRate, int maxRate, int group, double centralFreq, int gain, const std::string& id, const Sdx::optional<std::string>& signal = {});
      static GetModulationTargetInterferencesResultPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;


      // **** output ****
      int output() const;
      void setOutput(int output);


      // **** minRate ****
      int minRate() const;
      void setMinRate(int minRate);


      // **** maxRate ****
      int maxRate() const;
      void setMaxRate(int maxRate);


      // **** group ****
      int group() const;
      void setGroup(int group);


      // **** centralFreq ****
      double centralFreq() const;
      void setCentralFreq(double centralFreq);


      // **** gain ****
      int gain() const;
      void setGain(int gain);


      // **** id ****
      std::string id() const;
      void setId(const std::string& id);


      // **** signal ****
      Sdx::optional<std::string> signal() const;
      void setSignal(const Sdx::optional<std::string>& signal);
    };
    REGISTER_COMMAND_RESULT_TO_FACTORY_DECL(GetModulationTargetInterferencesResult);
  }
}

