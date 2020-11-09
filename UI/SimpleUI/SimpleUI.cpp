#include "UI/SimpleUI/SimpleUI.hpp"

#include <any>      // any_cast()
#include <iomanip>  // setw()
#include <iostream> // streamsize
#include <limits>   // numeric_limits
#include <memory>   // unique_ptr, make_unique<>()
#include <string>   // string, getline()
#include <vector>

#include "Domain/Session/SessionHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "Domain/Hotel/HotelHandler.hpp"

namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
      : _hotelPtr(Domain::Hotel::HotelHandler::createHotel()),
        _loggerPtr(TechnicalServices::Logging::LoggerHandler::create()),
        _persistentData(TechnicalServices::Persistence::PersistenceHandler::instance())

  {
    _logger << "Simple UI being used and has been successfully initialized";
  }

  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }

  //company logo
  void SimpleUI::logo()
  {
    std::cout << "\n\n"
              << "         ██╗██████╗ ███╗   ███╗   \n"
              << "         ██║██╔══██╗████╗ ████║   \n"
              << "         ██║██████╔╝██╔████╔██║   \n"
              << "    ██   ██║██╔══██╗██║╚██╔╝██║   \n"
              << "    ╚█████╔╝██████╔╝██║ ╚═╝ ██║   \n"
              << "     ╚════╝ ╚═════╝ ╚═╝     ╚═╝   \n"
              << "      Hotel Reservation Systems   \n\n\n";
    return;
  }

  // Operations
  void SimpleUI::launch()
  {
    //// 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();

    // 2) Present login screen to user and get username, password, and valid role
    Domain::Session::UserCredentials credentials = {"", "", {""}}; // ensures roles[0] exists
    auto &selectedRole = credentials.roles[0];                     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;
    int shutdown = 0;
    do
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      logo();

      std::cout << "  Username: ";
      std::getline(std::cin, credentials.userName);

      std::cout << "  Password: ";
      std::getline(std::cin, credentials.passPhrase);

      /*std::cout << "  Role: ";
      std::getline( std::cin, selectedRole );*/

      unsigned menuSelection;
      do
      {
        for (unsigned i = 0; i != roleLegalValues.size(); ++i)
          std::cout << std::setw(2) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size() - 1 << "): ";
        std::cin >> menuSelection;
      } while (menuSelection >= roleLegalValues.size());

      selectedRole = roleLegalValues[menuSelection];

      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::Session::SessionHandler::createSession(credentials);
      if (sessionControl != nullptr)
      {
        _logger << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
        // break;

        // 4) Fetch functionality options for this role
        do
        {
          auto commands = sessionControl->getCommands();
          std::string selectedCommand;
          unsigned menuSelection;

          do
          {
            for (unsigned i = 0; i != commands.size(); ++i)
              std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
            std::cout << std::setw(2) << commands.size() << " - "
                      << "Quit\n";

            std::cout << "  action (0-" << commands.size() << "): ";
            std::cin >> menuSelection;
          } while (menuSelection > commands.size());

          if (menuSelection == commands.size())
          {
            shutdown = -1;
            break;
          }

          selectedCommand = commands[menuSelection];
          _logger << "Command selected \"" + selectedCommand + '"';

      /******************************************************************************************************************************
      **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
      **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
      **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
      **     parameters.
      ******************************************************************************************************************************/

          ///////////for Manange Reservation................//
          /////////////////For Room Avaiability.......//
          if (selectedCommand == "Ask available room")
          {
            std::vector<std::string> parameters(3);

            std::cout << " Enter check_in_date:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[0]);
            std::cout << " Enter # of nights: ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[1]);
            std::cout << " Enter # of hotel guest's:   ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[2]);

            auto results = _hotelPtr->executeCommand(selectedCommand, parameters);

            if (results.has_value())
              _logger << "Received reply:\n \"" + std::any_cast<const std::string &>(results) + '"';
          }

          ////////////////////for Reserving room/////////////////
          else if (selectedCommand == "Reserve room")
          {
            std::vector<std::string> parameters(3);

            parameters[2] = credentials.userName;
            std::cout << " Room Type:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[0]);
            std::cout << " Room number: ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[1]);
            // std::cout << " Reservation_guest_name:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );

            auto results = _hotelPtr->executeCommand(selectedCommand, parameters);
            if (results.has_value())
              _logger << "Received reply: \"" + std::any_cast<const std::string &>(results) + '"';
          }

          //signoff
          else if (selectedCommand == "Sign Off")
          {
            std::vector<std::string> parameters(1);

            parameters[0] = credentials.userName;
            auto results = sessionControl->executeCommand(selectedCommand, parameters);
            if (results.has_value())
              _logger << "Received reply: \"" + std::any_cast<const std::string &>(results) + '"';
            break;
          }

          ////////////////////for checking out......................//
          /////////////for unassign room....................//
          else if (selectedCommand == "Unassign room")
          {
            std::vector<std::string> parameters(1);

            std::cout << " Enter room's number:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[0]);

            auto results = _hotelPtr->executeCommand(selectedCommand, parameters);
            if (results.has_value())
              _logger << "Received reply: \"" + std::any_cast<const std::string &>(results) + '"';
          }
          //or adding additional costs
          else if (selectedCommand == "Add additional cost")
          {
            std::vector<std::string> parameters(3);

            std::cout << " Enter room's number:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[0]);
            std::cout << " Enter item's name:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[1]);
            std::cout << " Enter quantity:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[2]);

            auto results = _hotelPtr->executeCommand(selectedCommand, parameters);
            if (results.has_value())
              _logger << "Received reply: \"" + std::any_cast<const std::string &>(results) + '"';
          }

          //for pay function
          else if (selectedCommand == "Pay")
          {
            std::vector<std::string> parameters(3);

            std::cout << " Enter room's number:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[0]);
            std::cout << " Enter payment method:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[1]);
            std::cout << " Enter amount:  ";
            std::cin >> std::ws;
            std::getline(std::cin, parameters[2]);

            auto results = _hotelPtr->executeCommand(selectedCommand, parameters);
            if (results.has_value())
              _logger << "Received reply: \"" + std::any_cast<const std::string &>(results) + '"';
          }

        } while (true);
      }

      else
      {
        std::cout << "** Login failed\n";
        _logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
      }

    } while (true && shutdown != -1);
    _logger << "Ending session and terminating";
  }
} // namespace UI
