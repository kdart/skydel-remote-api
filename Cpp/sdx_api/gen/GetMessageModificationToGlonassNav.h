#pragma once

#include <memory>
#include "command_base.h"

#include <string>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Get infos about the GLONASS NAV message modification with this ID.
    ///
    /// Name Type   Description
    /// ---- ------ ------------------------------
    /// Id   string Unique identifier of the event
    ///

    class GetMessageModificationToGlonassNav;
    typedef std::shared_ptr<GetMessageModificationToGlonassNav> GetMessageModificationToGlonassNavPtr;
    
    
    class GetMessageModificationToGlonassNav : public CommandBase
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;


      GetMessageModificationToGlonassNav();

      GetMessageModificationToGlonassNav(const std::string& id);
  
      static GetMessageModificationToGlonassNavPtr create(const std::string& id);
      static GetMessageModificationToGlonassNavPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;

      virtual int executePermission() const override;


      // **** id ****
      std::string id() const;
      void setId(const std::string& id);
    };
    
  }
}

