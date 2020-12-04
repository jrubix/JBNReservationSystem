#pragma once
#include <iostream>
#include <vector>
#include "Domain/Room/Room.hpp"
#include "Domain/Room/RoomSpecification.hpp"


namespace Domain::Room
{
  class RoomCatalog
  {
  public:

    //test
    void printall();

    RoomCatalog();
    ~RoomCatalog();

  private:
    std::vector<RoomSpecification> roomCatalog;
    std::vector<Room> roomList;

  };
}// namespace Domain::Room
