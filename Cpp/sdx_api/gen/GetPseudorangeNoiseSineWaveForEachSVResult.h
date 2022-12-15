#pragma once

#include <memory>
#include "command_result.h"
#include "command_result_factory.h"
#include <string>
#include <vector>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Result of GetPseudorangeNoiseSineWaveForEachSV.
    ///
    /// Name      Type         Description
    /// --------- ------------ ----------------------------------------------------------------
    /// System    string       "GPS", "GLONASS", "Galileo", "BeiDou", "SBAS", "QZSS" or "NavIC"
    /// SineWave  int          Sine wave number (0 or 1)
    /// Enabled   array bool   If true, sine wave is enabled
    /// Amplitude array double Sine wave amplitude in meters
    /// Period    array int    sine wave period in seconds
    /// Offset    array double Phase offset in radians
    ///

    class GetPseudorangeNoiseSineWaveForEachSVResult;
    typedef std::shared_ptr<GetPseudorangeNoiseSineWaveForEachSVResult> GetPseudorangeNoiseSineWaveForEachSVResultPtr;
    typedef GetPseudorangeNoiseSineWaveForEachSVResult GetAllSatellitesPseudorangeNoiseSineWaveResult;
    typedef std::shared_ptr<GetAllSatellitesPseudorangeNoiseSineWaveResult> GetAllSatellitesPseudorangeNoiseSineWaveResultPtr;
    
    class GetPseudorangeNoiseSineWaveForEachSVResult : public CommandResult
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      GetPseudorangeNoiseSineWaveForEachSVResult();

      GetPseudorangeNoiseSineWaveForEachSVResult(CommandBasePtr relatedCommand, const std::string& system, int sineWave, const std::vector<bool>& enabled, const std::vector<double>& amplitude, const std::vector<int>& period, const std::vector<double>& offset);
  
      static GetPseudorangeNoiseSineWaveForEachSVResultPtr create(CommandBasePtr relatedCommand, const std::string& system, int sineWave, const std::vector<bool>& enabled, const std::vector<double>& amplitude, const std::vector<int>& period, const std::vector<double>& offset);
      static GetPseudorangeNoiseSineWaveForEachSVResultPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;


      // **** system ****
      std::string system() const;
      void setSystem(const std::string& system);


      // **** sineWave ****
      int sineWave() const;
      void setSineWave(int sineWave);


      // **** enabled ****
      std::vector<bool> enabled() const;
      void setEnabled(const std::vector<bool>& enabled);


      // **** amplitude ****
      std::vector<double> amplitude() const;
      void setAmplitude(const std::vector<double>& amplitude);


      // **** period ****
      std::vector<int> period() const;
      void setPeriod(const std::vector<int>& period);


      // **** offset ****
      std::vector<double> offset() const;
      void setOffset(const std::vector<double>& offset);
    };
    REGISTER_COMMAND_RESULT_TO_FACTORY_DECL(GetPseudorangeNoiseSineWaveForEachSVResult);
  }
}

