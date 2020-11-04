#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <any>

#include "Domain/Hotel/Hotel.hpp"

namespace Domain::Hotel
{

  HotelBase::HotelBase() : _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())
  {
    roomInfo = {{"120", "Queen", "Available", ""},
                {"121", "King", "Occupied", "Rebecca Gamble"},
                {"122", "Two Queens", "Available", ""},
                {"123", "Suite", "Occupied", "Julie Straw"},
                {"124", "Suite", "Available", ""},
                {"125", "King", "Occupied", "Sam Smith"},
                {"126", "Queen", "Occupied", "John Doe"}};

    pricing = {{"Coke can", 5}, {"Queen", 89}, {"Two Queens", 130}, {"Suite", 189}, {"King", 90}};

    _commandDispatch["Unassign room"] = &HotelBase::unassignHotelRoom;
    _commandDispatch["Add additional cost"] = &HotelBase::addCostHotel;
    _commandDispatch["Pay"] = &HotelBase::pay;
    _commandDispatch["Ask available room"] = &HotelBase::askAvailableRoom;
    _commandDispatch["Reserve room"] = &HotelBase::reserveHotelRoom;

    _logger << "Hotel being used and has been successfully initialized";
  }
  std::any HotelBase::addCostHotel(const std::vector<std::string> &args)
  {
    std::string result;
    result = args[2] + " x " + args[1] + " added to room " + args[0] + ". Subtotal: $" + std::to_string(getPrice(args[1]) * stoi(args[2]));
    return {result};
  }

  double HotelBase::getPrice(std::string name)
  {
    auto result = pricing.find(name);

    return result->second;
  }

  std::any HotelBase::executeCommand(const std::string &command, const std::vector<std::string> &args)
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

    auto results = (*this.*(it->second))(args);
    if (results.has_value())
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>(results) + '"';
    }

    return results;
  }

  std::any HotelBase::pay(const std::vector<std::string> &args)
  {
    std::string result = "Payment of $" + args[2] + " for room " + args[0] + " by " + args[1] + " received successfully.";
    return {result};
  }

  std::string HotelBase::checkoutHotel(const std::string number)
  {
    int vecsize = roomInfo.size() - 1;
    for (int i = 0; i < vecsize; i++)
    {
      if (roomInfo[i][0] == number)
      {
        if (roomInfo[i][2] == "Available" && roomInfo[i][3] == "")
        {
          std::string succ = "Checking out room " + number + " Successful";
          return succ;
        }
        else
          return "Failed to checkout";
      }
    }
    return "Failed to checkout";
  }

  //unassigns hotel room
  std::any HotelBase::unassignHotelRoom(const std::vector<std::string> &args)
  {
    int vecsize = roomInfo.size() - 1;
    std::string result;
    for (int i = 0; i < vecsize; i++)
    {
      if (roomInfo[i][0] == args[0])
      {
        if (roomInfo[i][2] == "Available")
        {
          result = "Room " + args[0] + " is not occupied. Request canceled.";
          return result;
        }
        roomInfo[i][2] = "Available";
        roomInfo[i][3] = "";
        result = "Checking out room " + args[0] + "... Successful";
        return {result};
      }
    }

    result = "Unsuccessful";

    return {result};
  }

  std::string HotelBase::assignHotelRoom(const std::string name, const std::string number)
  {
    int vecsize = roomInfo.size() - 1;
    std::string assigncomp;
    for (int i = 0; i < vecsize; i++)
    {
      if (roomInfo[i][0] == number)
      {
        roomInfo[i][2] = "Occupied";
        roomInfo[i][3] = name;
        assigncomp = "Room assignment successful\n";
        return assigncomp;
      }
      else
        assigncomp = "Room assignment failed\n";
    }
    return assigncomp;
  }

  //if onlyavail == Y print only available rooms otherwise all
  //generic print all room functions and occupants
  std::string HotelBase::printAllRooms(std::string onlyavail)
  {
    std::string rinfo;
    int vecsize = roomInfo.size() - 1;
    for (int i = 0; i < vecsize; i++)
    {
      if (onlyavail == "Y" && roomInfo[i][2] == "Occupied")
        continue;
      //direct access second vector, change if additional fields
      rinfo += roomInfo[i][0] + "   " + roomInfo[i][1] + "   " + roomInfo[i][2] + "  " + roomInfo[i][3] + "\n";
    }
    return rinfo;
  }
  //reserves the room and updates the room log and returns success
  //removes the room from available
  std::any HotelBase::reserveHotelRoom(const std::vector<std::string> &args)
  {
    //arg[0] = roomtype arg[1] = room number
    int vecsize = roomInfo.size() - 1;
    std::string reservesuccess;
    for (int i = 0; i < vecsize; i++)
    {
      if (roomInfo[i][0] == args[1] && roomInfo[i][1] == args[0])
      {
        if (roomInfo[i][2] == "Available")
        {
          std::string completed = assignHotelRoom(roomInfo[i][3], roomInfo[i][0]);
          reservesuccess = "Room " + roomInfo[i][0] + " - " + roomInfo[i][1] + " reserved by " + args[2];
          return reservesuccess;
        }
        else
        {
          reservesuccess = "That room is unavailable.\n";
        }
      }
      else
      {
        reservesuccess = "That room was not found.\n";
      }
    }
    return reservesuccess;
  }

  //checks for available rooms with date and prices
  std::any HotelBase::askAvailableRoom(const std::vector<std::string> &args)
  {

    std::string rinfo;

    int vecsize = roomInfo.size() - 1;
    for (int i = 0; i < vecsize; i++)
    {
      if (roomInfo[i][2] == "Occupied")
        continue;
      //direct access second vector, change if additional fields
      rinfo += roomInfo[i][0] + "-" + roomInfo[i][1] + " " + roomInfo[i][2];
      rinfo += " Room for checking date \"" + args[0] + "\" for \"" + args[1] + "\" night(s) and for \"" + args[2] + "\" hotel guest(s) at: $" + std::to_string(stoi(args[1]) * getPrice(roomInfo[i][1])) + "\n";
    }
    return {rinfo};
  }

  HotelBase::~HotelBase() noexcept
  {
    _logger << "Hotel shutdown successfully";
  }

} // namespace Domain::Hotel
