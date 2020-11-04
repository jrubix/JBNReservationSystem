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

  //roles under the assumption users only have one role
  // std::any reserveRoom(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  // {
  //   std::string results = hotelControl->reserveHotelRoom(session._credentials.userName, session._credentials.roles[0], args);
  //   session._logger << results;
  //   return results;
  // }
  // //done
  // std::any askAvailableRoom(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  // {
  //   std::string room = hotelControl->askAvailableRoom(session._credentials.roles[0], args);
  //   session._logger << "Available Rooms:\n\n" + room;
  //   return room;
  // }

  // std::any signOff(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  // {

  //   std::string results = "signed off successfully by " + args[0];
  //   session._logger << "Signing off:  " + results;
  //   return results;
  // }
  // /////checking out//////////////
  // std::any UnassignRoom(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  // {
  //   auto results = hotelControl->unassignHotelRoom(args);
  //   return {results};
  // }

  // std::any addAdditionalCost(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  // {
  //   std::string itemprice = hotelControl->getPrice("");
  //   int cost = stoi(itemprice) * stoi(args[1]);
  //   std::string result = "Adding extra cost: for " + args[1] + " " + args[0] + " is " + std::to_string(cost);
  //   return {result};
  // }

  // std::any makepayment(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  // {
  //   //TOBE REPLACE BY CALL TO PAYMENT SERVICE
  //   std::string results = "Payment success by " + args[0];
  //   session._logger << "making payment result:  " + results;
  //   return results;
  // }

  // std::any ProceedToCheckOut(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  // {
  //   std::string result = hotelControl->checkoutHotel(args[0]);
  //   return {result};
  // }
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
    // std::vector<std::string> availableCommands;
    // availableCommands.reserve(_startingCommands.size());

    // for (const auto &[command, function] : _startingCommands)
    //   availableCommands.emplace_back(command);

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

    //std::cout << args[0];

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
    // _commandDispatch = {
    //     {"Ask Available Room", askAvailableRoom},
    //     {"Reserve Room", reserveRoom},
    //     {"Make Payment", makepayment},
    //     {"Help", Help},
    //     {"Sign Off", signOff}};
    // _startingCommands = {
    //     {"Ask Available Room", askAvailableRoom},
    //     {"Reserve Room", reserveRoom},
    //     {"Make Payment", makepayment},
    //     {"Help", Help},
    //     {"Sign Off", signOff},
    // };
    _commandList = {"Ask available room",
                    "Reserve room",
                    "Pay",
                    "Sign Off",
                    "Help"};
  }

  ///////////////////////////Receptionist/////////////////////
  ReceptionistSession::ReceptionistSession(const UserCredentials &credentials) : SessionBase("Receptionist", credentials)
  {
    // _commandDispatch = {
    //     {"Assign room", assignRoom},
    //     {"Unassign room", UnassignRoom},
    //     {"Help", Help},
    //     {"Sign Off", signOff},
    //     {"Add extra cost", addAdditionalCost},
    //     {"Make Payment", makepayment},
    //     {"Proceed to check out", ProceedToCheckOut}};

    // _startingCommands = {
    //     {"Assign room", assignRoom},
    //     {"Unassign room", UnassignRoom},
    //     {"Help", Help},
    //     {"Sign Off", signOff},
    // };
    _commandList = {"Assign room",
                    "Unassign room",
                    "Pay",
                    "Add additional cost", "Sign Off",
                    "Help"};
  }

} // namespace Domain::Session
