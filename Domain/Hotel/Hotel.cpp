#include "Domain/Hotel/Hotel.hpp"
#include <string>
#include <iostream>
namespace Domain::Hotel
{

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
    return price;
  }

  HotelBase::~HotelBase() noexcept {
    std::cout<<"Deconstructed";
  }

}
