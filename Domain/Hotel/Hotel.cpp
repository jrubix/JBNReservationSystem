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
    roominfo = {{"120", "Queen", "Available", ""},
                {"121", "King", "Occupied", "Rebecca Gamble"},
                {"122", "2 Queens", "Available", ""},
                {"123", "Suite", "Occupied", "Julie Straw"},
                {"124", "Suite", "Available", ""},
                {"125", "King", "Occupied", "Sam Smith"},
                {"126", "Queen", "Occupied", "John Doe"}};
    _commandDispatch = {
        {"Unassign room", pay}};
    // _commandDispatch["Unassign room"] = pay;
    _logger << "Hotel being used and has been successfully initialized";
  }
  std::any HotelBase::addCostHotel()
  {
    return "Success";
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

    auto results = it->second(*this, args);
    if (results.has_value())
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>(results) + '"';
    }

    return results;
  }

  std::any pay(const std::vector<std::string> &abc)
  {
    return "success";
  }

  std::string HotelBase::checkoutHotel(const std::string number)
  {
    int vecsize = roominfo.size() - 1;
    for (int i = 0; i < vecsize; i++)
    {
      if (roominfo[i][0] == number)
      {
        if (roominfo[i][2] == "Available" && roominfo[i][3] == "")
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
  std::string HotelBase::unassignHotelRoom(const std::vector<std::string> &args)
  {
    int vecsize = roominfo.size() - 1;
    for (int i = 0; i < vecsize; i++)
    {
      if (roominfo[i][0] == args[0])
      {
        roominfo[i][2] = "Available";
        roominfo[i][3] = "";
        std::string succ = "Checking out room " + args[0] + "... Successful";
        return succ;
      }
    }
    return "Unsuccessful";
  }

  std::string HotelBase::assignHotelRoom(const std::string name, const std::string number)
  {
    int vecsize = roominfo.size() - 1;
    std::string assigncomp;
    for (int i = 0; i < vecsize; i++)
    {
      if (roominfo[i][0] == number)
      {
        roominfo[i][2] = "Occupied";
        roominfo[i][3] = name;
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
    int vecsize = roominfo.size() - 1;
    for (int i = 0; i < vecsize; i++)
    {
      if (onlyavail == "Y" && roominfo[i][2] == "Occupied")
        continue;
      //direct access second vector, change if additional fields
      rinfo += roominfo[i][0] + "   " + roominfo[i][1] + "   " + roominfo[i][2] + "  " + roominfo[i][3] + "\n";
    }
    return rinfo;
  }
  //reserves the room and updates the room log and returns success
  //removes the room from available
  std::string HotelBase::reserveHotelRoom(const std::string name, const std::string credentials, const std::vector<std::string> &args)
  {
    //arg[0] = roomtype arg[1] = room number
    int vecsize = roominfo.size() - 1;
    std::string reservesuccess;
    for (int i = 0; i < vecsize; i++)
    {
      if (roominfo[i][0] == args[1] && roominfo[i][1] == args[0])
      {
        if (roominfo[i][2] == "Available")
        {
          std::string completed = assignHotelRoom(roominfo[i][3], roominfo[i][0]);
          reservesuccess = "Room " + roominfo[i][0] + " - " + roominfo[i][1] + " reserved by " + name + "\n";
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
  std::string HotelBase::askAvailableRoom(std::string credentials, const std::vector<std::string> &args)
  {

    std::string rinfo;
    //std::vector<std::vector<std::string>>::iterator row;
    //std::vector<std::string>::iterator col;
    int vecsize = roominfo.size() - 1;
    for (int i = 0; i < vecsize; i++)
    {
      if (roominfo[i][2] == "Occupied" && credentials == "HotelGuest")
        continue;
      //direct access second vector, change if additional fields
      rinfo += roominfo[i][0] + "   " + roominfo[i][1] + "   " + roominfo[i][2];
      rinfo += "- Room avialable for checking date \"" + args[0] + "\" for \"" + args[1] + "\" night(s) and for \"" + args[2] + "\" hotel guest(s) at: $" + std::to_string(stoi(args[1]) * stoi(getprice(roominfo[i][1]))) + "\n";
    }
    return rinfo;
  }

  std::string HotelBase::getprice(std::string name)
  {
    std::string price;
    ///getting extra item price::
    if (name == "coke")
    {
      return "5";
    }

    //getting the price for room type
    if (name == "Queen")
    {
      return "89";
    }
    if (name == "2 Queens")
    {
      return "130";
    }
    if (name == "Suite")
    {
      return "189";
    }
    if (name == "King")
    {
      return "90";
    }

    return price;
  }

  HotelBase::~HotelBase() noexcept
  {
    std::cout << "Deconstructed";
  }

} // namespace Domain::Hotel
