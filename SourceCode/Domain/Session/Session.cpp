#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  STUB( askAvailableRoom )
  STUB( reserveRoom  )
  STUB( makepayment  )
  STUB( Help  )
  STUB( UnassignRoom     )
  STUB(addAdditionalCost)
  STUB(ProceedToCheckOut)
  STUB( signOff )
  STUB( shutdown     )


  // anonymous (private) working area

}







namespace Domain::Session
{
  SessionBase::SessionBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }




  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }




  std::vector<std::string> SessionBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }




  std::any SessionBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }








  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
 /* AdministratorSession::AdministratorSession( const UserCredentials & credentials ) : SessionBase( "Administrator", credentials )
  {
    _commandDispatch = { {"Help",            help        },
                         {"Reset Account",   resetAccount},
                         {"Shutdown System", shutdown    } };
  }*/




  HotelGuestSession::HotelGuestSession( const UserCredentials & credentials ) : SessionBase( "HotelGuest", credentials )
  {
    _commandDispatch = {
                         {"Ask Available Room",          askAvailableRoom        },
						 {"Reserve Room",         reserveRoom       },
						 {"Make Payment",          makepayment        },
						 {"Help",          Help        },
						  {"Sign Off",         signOff         }
					   };
  }




  ReceptionistSession::ReceptionistSession( const UserCredentials & credentials ) : SessionBase( "Receptionist", credentials )
  {
    _commandDispatch = { 
						 {"unassigning room",          UnassignRoom      },
						 {"add additional cost",        addAdditionalCost       },
						 {"Proceed To CheckOut",          ProceedToCheckOut        },
						  {"Make Payment",          makepayment        },
						   {"Help",          Help        },
						  {"Sign Off",         signOff         }
					  };
  }




 /* ManagementSession::ManagementSession( const UserCredentials & credentials ) : SessionBase( "Management", credentials )
  {
    _commandDispatch = { {"Bug People", bugPeople},
                         {"Help",       help} };
  }*/
}    // namespace Domain::Session
