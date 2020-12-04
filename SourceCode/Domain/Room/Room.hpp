#pragma once

#include <string>

namespace Domain::Room
{

  class Room
  {
  public:
    Room(int rnum, std::string chin_, std::string chout_, std::string avail_):
      roomNumber(rnum), checkin(chin_), checkout(chout_), availability(avail_) {}

    virtual ~Room() = 0;

  protected:
    int roomNumber;
    std::string checkin, checkout, availability;

  };

}// namespace Domain::Room
