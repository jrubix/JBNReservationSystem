#include "Domain/Hotel/Hotel.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <array>

namespace Domain::Hotel
{

  HotelBase::HotelBase(){
    roominfo = {{"120","Queen","Available",""},
                {"121","King","Occupied","Rebecca Gamble"},
                {"122","2 Queens","Available",""},
                {"123","Suite","Occupied","Julie Straw"},
                {"124","Suite","Available",""},
                {"125","King","Occupied","Sam Smith"},
                {"126","Queen","Occupied","John Doe"}};
  }
  std::string HotelBase::addCostHotel(){
    return "Success";
  }

  std::string HotelBase::checkoutHotel(){
    return "Success";
  }

  std::string HotelBase::unassignHotelRoom(){
    return "Success";
  }

  std::string HotelBase::assignHotelRoom(){
    return "Success";
  }

//if onlyavail == Y print only available rooms otherwise all
//generic print all room functions and occupants
  std::string HotelBase::printAllRooms(std::string onlyavail){
    std::string rinfo;
    int vecsize = roominfo.size()-1;
    for(int i = 0; i < vecsize; i++){
      if(onlyavail == "Y" && roominfo[i][2] == "Occupied") continue;
      //direct access second vector, change if additional fields
      rinfo += roominfo[i][0] + "   " + roominfo[i][1] + "   " +roominfo[i][2] + "  " + roominfo[i][3] +"\n";
    }
    return rinfo;
  }
//reserves the room and updates the room log and returns success
  std::string HotelBase::reserveHotelRoom(const std::string name, const std::string credentials, const std::vector<std::string>& args){
    //arg[0] = roomtype arg[1] = room number
    int vecsize = roominfo.size()-1;
    std::string reservesuccess;
    for(int i = 0; i < vecsize; i++){
      if(roominfo[i][0] == args[1] && roominfo[i][1] == args[0]){
        if(roominfo[i][2] == "Available"){
          roominfo[i][2] = "Occupied";
          roominfo[i][3] = name;
          reservesuccess = "Room "+ roominfo[i][0] +" - "+roominfo[i][1]+" reserved by "+name+"\n";
          return reservesuccess;
        }
        else {
          reservesuccess = "That room is unavailable.\n";
        }
      }
      else{
        reservesuccess = "That room was not found.\n";
      }
    }
   return reservesuccess;
  }

//checks for available rooms with date and prices
  std::string HotelBase::askAvailableRoom(std::string credentials, const std::vector<std::string>& args){

    std::string rinfo;
    //std::vector<std::vector<std::string>>::iterator row;
    //std::vector<std::string>::iterator col;
    int vecsize = roominfo.size()-1;
    for(int i = 0; i < vecsize; i++){
      if(roominfo[i][2] == "Occupied" && credentials == "HotelGuest" ) continue;
//direct access second vector, change if additional fields
      rinfo += roominfo[i][0] + "   " + roominfo[i][1] + "   " +roominfo[i][2];
      rinfo += "- Room avialable for checking date \"" + args[0]
            + "\" for \"" + args[1] + "\" night(s) and for \"" + args[2]
            + "\" hotel guest(s) at: $" + std::to_string(stoi(args[1]) * stoi(getprice(roominfo[i][1]))) +"\n";

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

  HotelBase::~HotelBase() noexcept {
    std::cout<<"Deconstructed";
  }

}
