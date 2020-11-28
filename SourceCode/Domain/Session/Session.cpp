#include "Domain/Session/Session.hpp"

//#include "Domain/Hotel/Hotel.hpp"
#include <string>
#include <any>
#include <vector>

namespace // anonymous (private) working area
{
// 1)  First define all system events (commands, actions, requests, etc.)
#define STUB(functionName)                                                                                     \
  std::any functionName(Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/) \
  {                                                                                                            \
    return {};                                                                                                 \
  } // Stubbed for now

  

  STUB(Help)
  STUB(assignRoom)
  STUB(shutdown)

  std::any signOff(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  {
    std::string results = "signed off successfully by " + args[0];
    session._logger << "Signing off:  " + results;
    return results;
  }

} // namespace

namespace Domain::Session
{
  SessionBase::SessionBase(const std::string &description, const UserCredentials &credentials) : _credentials(credentials), _name(description), _hotelPtr(Domain::Hotel::HotelHandler::createHotel())
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
		
  }

  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }

  std::vector<std::string> SessionBase::getCommands()
  {
	  /*std::vector<std::string> availableCommands;
	  availableCommands.reserve(_commandList.size());

	 for (const auto& [command] : _commandList)
		  availableCommands.emplace_back(command);*/

	  return _commandList;
  }

  std::any SessionBase::executeCommand(const std::string &command, const std::vector<std::string> &args)
  {
	  std::vector<std::string> argument;
	  argument = args;
    std::string parameters;
    for (const auto &arg : args)
      parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find(command);
    if (it == _commandDispatch.end())
    {
		//no command from session.. have to find in hotel..
		auto results = _hotelPtr->executeCommand(command, argument);

		///fialure in finding commands...
		if (!(results.has_value()) && it == _commandDispatch.end())
		{
			std::string message = __func__;
			message += " attempt to execute \"" + command + "\" failed, no such command";

			_logger << message;
			throw BadCommand(message);
		}
		else if (results.has_value())
		{
			// The type of result depends on function called.  Let's assume strings for now ...
			_logger << "Responding with: \"" + std::any_cast<const std::string&>(results) + '"';
		}
		return results;
    }

	//for session functions.. execution call
	else if (it != _commandDispatch.end())
	{
		auto results = it->second(*this, args);
		if (results.has_value())
		{
			// The type of result depends on function called.  Let's assume strings for now ...
			_logger << "Responding with: \"" + std::any_cast<const std::string&>(results) + '"';
		}
		return results;
	}

  }

  /////////////////////Hotel Guest//////////////////////////////////
  HotelGuestSession::HotelGuestSession(const UserCredentials &credentials) : SessionBase("HotelGuest", credentials)
  {
	  //inheritent the getCommands() and executeCommand() functions from sessionbase//
    _commandDispatch = {
        {"Sign Off", signOff}};

    _commandList = {"Ask available room",
                    "Reserve room",
                    "Pay",
                    "Sign Off",
                    "Help"};
  }

  ///////////////////////////Receptionist/////////////////////
  ReceptionistSession::ReceptionistSession(const UserCredentials &credentials) : SessionBase("Receptionist", credentials)
  {
	  //inheritent the getCommands() and executeCommand() functions from sessionbase//
	  _commandDispatch = {
        {"Sign Off", signOff}};

    _commandList = {"Assign room",
                    "Unassign room",
                    "Pay",
                    "Add additional cost", "Sign Off",
                    "Help"};
  }

} // namespace Domain::Session
