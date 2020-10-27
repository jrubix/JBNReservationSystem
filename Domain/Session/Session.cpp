#include "Domain/Session/Session.hpp"

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

  STUB(bugPeople)
  STUB(collectFines)
  STUB(help)
  STUB(openArchives)
  STUB(payFines)
  STUB(resetAccount)
  STUB(returnBook)
  STUB(shutdown)

  STUB(signOff)
  STUB(assignRoom)

  // anonymous (private) working area

  std::any unassignRoom(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  {
    std::string results = "Checking out room " + args[0] + "...";

    // unsigned option;

    // do
    // {
    //   std::cout << results + "\n action(0 - 2): ";
    //   std::cin >> option;

    //   if (option == 0)
    //   {
    //     std::vector<std::string> parameters(2);

    //     std::cout << "What is the item: ";
    //     std::cin >> std::ws;
    //     std::getline(std::cin, parameters[0]);
    //     std::cout << "What is the quantity: ";
    //     std::cin >> std::ws;
    //     std::getline(std::cin, parameters[1]);

    //     std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

    //     auto abc = sessionControl->executeCommand("Add additional cost", parameters);
    //   }

    // } while (option < 2);

    // // std::vector<std::string> parameters(2);

    // // std::cout << " Enter book's number:  ";
    // // std::cin >> std::ws;
    // // std::getline(std::cin, parameters[0]);

    // // auto results = sessionControl->executeCommand(selectedCommand, parameters);
    // // if (results.has_value())
    // //   _logger << "Received reply: \"" + std::any_cast<const std::string &>(results) + '"';
    // std::string result = "Back to main menu!";
    return {results};
  }

  std::any addCost(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  {
    std::string result = "Adding extra cost: " + args[1] + " x " + args[0];
    return {result};
  }

  std::any pay(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  {
    std::string result = "Payment success";
    return {result};
  }

  std::any checkout(Domain::Session::SessionBase &session, const std::vector<std::string> &args)
  {
    std::string result = "Room " + args[0] + " checked out successfully";
    return {result};
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
    std::vector<std::string> availableCommands;
    availableCommands.reserve(_startingCommands.size());

    for (const auto &[command, function] : _startingCommands)
      availableCommands.emplace_back(command);

    return availableCommands;
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

  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  AdministratorSession::AdministratorSession(const UserCredentials &credentials) : SessionBase("Administrator", credentials)
  {
    _commandDispatch = {{"Help", help},
                        {"Reset Account", resetAccount},
                        {"Shutdown System", shutdown}};
  }

  HotelGuestSession::HotelGuestSession(const UserCredentials &credentials) : SessionBase("User", credentials)
  {
    _commandDispatch = {
        {"Help", help}};
  }

  ReceptionistSession::ReceptionistSession(const UserCredentials &credentials) : SessionBase("Receptionist", credentials)
  {
    _commandDispatch = {
        {"Assign room", assignRoom},
        {"Unassign room", unassignRoom},
        {"Help", help},
        {"Sign off", signOff},
        {"Add extra cost", addCost},
        {"Pay", pay},
        {"Proceed to check out", checkout}};

    _startingCommands = {
        {"Assign room", assignRoom},
        {"Unassign room", unassignRoom},
        {"Help", help},
        {"Sign off", signOff},
    };
  }

  ManagementSession::ManagementSession(const UserCredentials &credentials) : SessionBase("Management", credentials)
  {
    _commandDispatch = {{"Bug People", bugPeople},
                        {"Help", help}};
  }
} // namespace Domain::Session
