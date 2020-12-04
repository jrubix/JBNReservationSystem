#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>


#include "Domain/Session/SessionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"





namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  :
    _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() )
  {
    _logger << "Simple UI being used and has been successfully initialized";
  }




  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }


  void SimpleUI::logo(){
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
    Domain::Session::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

    do
    {
      std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

      logo();

      std::cout << "  Username: ";
      std::getline( std::cin, credentials.userName );

      std::cout << "  Password: ";
      std::getline( std::cin, credentials.passPhrase );

	  /*std::cout << "  Role: ";
      std::getline( std::cin, selectedRole );*/


      unsigned menuSelection;
      do
      {
        for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
        std::cin  >> menuSelection;
      } while( menuSelection >= roleLegalValues.size() );

      selectedRole = roleLegalValues[menuSelection];


      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::Session::SessionHandler::createSession( credentials );
      if( sessionControl != nullptr )
      {
        _logger << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
        break;
      }

      std::cout << "** Login failed\n";
      _logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";

    } while( true );


    // 4) Fetch functionality options for this role
    do
    {
      auto        commands = sessionControl->getCommands();
      std::string selectedCommand;
      unsigned    menuSelection;

      do
      {
        for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
        std::cout << std::setw( 2 ) << commands.size() << " - " << "Quit\n";

        std::cout << "  action (0-" << commands.size() << "): ";
        std::cin >> menuSelection;
      } while( menuSelection > commands.size() );

      if( menuSelection == commands.size() ) break;

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
      if( selectedCommand == "Ask Available Room" )
      {
        std::vector<std::string> parameters( 3 );

        std::cout << " Enter check_in_date:  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << " Enter night: ";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        std::cout << " Enter hotelguest number:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );

        auto results = sessionControl->executeCommand( selectedCommand, parameters );

        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }

	  ////////////////////for Reserving room/////////////////
      else if( selectedCommand == "Reserve Room" )

	  {
		std::vector<std::string> parameters( 2 );

        std::cout << " Room Type:  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << " Room number: ";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
       // std::cout << " Reservation_guest_name:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );

        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
	  }

	  ///////////////////making payment...in...reserveroom scenario////////////
	  else if (selectedCommand == "Make Payment")

	  {
		  std::vector<std::string> parameters(1);

		  std::cout << " payment done by:  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[0]);

		  auto results = sessionControl->executeCommand(selectedCommand, parameters);
		  if (results.has_value()) _logger << "Received reply: \"" + std::any_cast<const std::string&>(results) + '"';

	  }

	  ///////////////////////////////
	  else if (selectedCommand == "Sign Off")

	  {
		  std::vector<std::string> parameters(1);

		  parameters[0] = credentials.userName;
		  auto results = sessionControl->executeCommand(selectedCommand, parameters);
		  if (results.has_value()) _logger << "Received reply: \"" + std::any_cast<const std::string&>(results) + '"';
	  }

	  ////////////////////for checking out......................//
	  /////////////for unassign room....................//
      else if (selectedCommand == "Unassign room")
      {
        std::vector<std::string> parameters(2);

        std::cout << " Enter room's number:  ";
        std::cin >> std::ws;
        std::getline(std::cin, parameters[0]);

		std::string roomnumber = parameters[0];
        auto results = sessionControl->executeCommand(selectedCommand, parameters);
        if (results.has_value())
          _logger << "Received reply: \"" + std::any_cast<const std::string &>(results) + '"';
        unsigned selection;
        int totalAmount = 0;
        do
        {

          std::cout << "0 - Add extra cost\n1 - Pay\n2 - Proceed to check out\n action (0 - 2): ";
          std::cin >> selection;
          if (selection == 0)
          {
            std::vector<std::string> params(2);
            std::cout << " Enter item name: ";
            std::cin >> std::ws;
            std::getline(std::cin, params[0]);
            std::cout << " Enter quantity: ";
            std::cin >> std::ws;
            std::getline(std::cin, params[1]);

            int price = std::stoi(params[1]);
            //totalAmount = totalAmount + price * 5;
            std::cout << "Price: " << price << std::endl;

			////////////////////////////////adding extra cost
            auto res = sessionControl->executeCommand("Add extra cost", params);
            // logger << "Total amount: " << totalAmount;
           // _logger << "Total amount: " + std::to_string(totalAmount);
          }
          else if (selection == 1)
          {
			  //std::vector<std::string> parameters(1);
			  parameters[1] = std::to_string(totalAmount);
            //std::vector<std::string> params = {std::to_string(totalAmount)};
			  std::cout << " payment done by:  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[0]);

			/////////////////making payment..............//////////
            auto res = sessionControl->executeCommand("Make Payment", parameters);
          }
          else if (selection == 2)
          {
            std::vector<std::string> params = {roomnumber};
            auto res = sessionControl->executeCommand("Proceed to check out", params);
            break;
          }

        } while (selection < 3);
      }

    } while( true );

    _logger << "Ending session and terminating";
  }
}
