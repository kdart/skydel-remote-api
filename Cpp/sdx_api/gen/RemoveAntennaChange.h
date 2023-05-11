#pragma once

#include <memory>
#include "command_base.h"

#include <string>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Removes an antenna change.
    ///
    /// Name Type   Description
    /// ---- ------ -------------------------------------
    /// Id   string Unique identifier (see AntennaChange)
    ///

    class RemoveAntennaChange;
    typedef std::shared_ptr<RemoveAntennaChange> RemoveAntennaChangePtr;
    
    
    class RemoveAntennaChange : public CommandBase
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      RemoveAntennaChange();

      RemoveAntennaChange(const std::string& id);

      static RemoveAntennaChangePtr create(const std::string& id);
      static RemoveAntennaChangePtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;

      virtual int executePermission() const override;


      // **** id ****
      std::string id() const;
      void setId(const std::string& id);
    };
    
  }
}

