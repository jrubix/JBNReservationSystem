#include "Domain/Session/Session.hpp"
#include "Domain/Hotel/HotelHandler.hpp"
#include "Domain/Hotel/Hotel.hpp"
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

  ////////////////////////////////////////
  //pointer to HotelBase
  Domain::Hotel::HotelHandler *hotelControl;
  ///////////////////////////////////////////////////////

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
  SessionBase::SessionBase(const std::string &description, const UserCredentials &credentials) : _credentials(credentials), _name(description)
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }

  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }

  std::vector<std::string> SessionBase::getCommands()
  {
    return _commandList;
  }

  std::any SessionBase::executeCommand(const std::string &command, const std::vector<std::string> &args)
  {

    std::string parameters;
    for (const auto &arg : args)
      parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find(command);
    if (it == _commandDispatch.end())
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand(message);
    }

    auto results = it->second(*this, args);
    if (results.has_value())
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>(results) + '"';
    }

    return results;
  }

  /////////////////////Hotel Guest//////////////////////////////////
  HotelGuestSession::HotelGuestSession(const UserCredentials &credentials) : SessionBase("HotelGuest", credentials)
  {
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
    _commandDispatch = {
        {"Sign Off", signOff}};

    _commandList = {"Assign room",
                    "Unassign room",
                    "Pay",
                    "Add additional cost", "Sign Off",
                    "Help"};
  }

} // namespace Domain::Session
