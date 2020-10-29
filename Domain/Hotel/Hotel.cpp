#include "Domain/Hotel/Hotel.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <array>

namespace Domain::Hotel
{

  HotelBase::HotelBase(){
    roominfo = {{"120","Queen","Available"},
                {"121","King","Occupied"},
                {"122","2 Queens","Available"},
                {"123","Suite","Occupied"},
                {"124","Suite","Available"},
                {"125","King","Occupied"},
                {"126","Queen","Occupied"}};
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

  std::string HotelBase::askAvailableRoom(std::string credentials, const std::vector<std::string>& args){

    std::string rinfo;
    //std::vector<std::vector<std::string>>::iterator row;
    //std::vector<std::string>::iterator col;
    int vecsize = roominfo.size()-1;
    for(int i = 0; i < vecsize; i++){
      if(roominfo[i][2] == "Occupied" && credentials == "HotelGuest" ) continue;
      for(int j = 0; j < 3; j++){
         rinfo += roominfo[i][j] + " ";
      }
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
