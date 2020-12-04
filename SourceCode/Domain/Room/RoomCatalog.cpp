#pragma once

#include "Domain/Room/RoomCatalog.hpp"

namespace Domain::Room
{
    //test
    void RoomCatalog::printall(){
      for (int i=0; i<roomList.size()-1; i++){
        std::cout << roomList[i].getRoomNumber();
      }
    }


    RoomCatalog::RoomCatalog(){
      //int rnum, std::string chin_, std::string chout_, std::string avail_

      // # | checkin | checkout | availability | price | occupancy |
      roomList.push_back(Room(120, "n/a", "n/a", "Available"));
      roomList.push_back(Room(121, "n/a", "n/a", "Available"));
      roomList.push_back(Room(122, "n/a", "n/a", "Available"));
      roomList.push_back(Room(123, "n/a", "n/a", "Available"));
      roomList.push_back(Room(124, "n/a", "n/a", "Available"));
      roomList.push_back(Room(125, "n/a", "n/a", "Available"));
      roomList.push_back(Room(126, "n/a", "n/a", "Available"));
      roomList.push_back(Room(127, "n/a", "n/a", "Available"));
      roomList.push_back(Room(128, "n/a", "n/a", "Available"));
      roomList.push_back(Room(129, "n/a", "n/a", "Available"));
      roomList.push_back(Room(130, "n/a", "n/a", "Available"));
      /*
      ** 120 = king     121 = king      122 = queen     123 = queen
      ** 124 = king     125 = queen     126 = 2 king    127 = 2 king
      ** 128 = suite    129 = suite     130 = suite
      */
      std::vector<int> kings = {120, 121, 124};
      std::vector<int> queens = {122, 123, 125};
      std::vector<int> suite = {128, 129, 130};
      std::vector<int> dking = {126, 127};

      roomCatalog.push_back(RoomSpecification(129.99, "King", "standard", 2, kings));
      roomCatalog.push_back(RoomSpecification(109.99, "Queen", "standard", 2, queens));
      roomCatalog.push_back(RoomSpecification(169.99, "Suite", "VIP", 2, suite));
      roomCatalog.push_back(RoomSpecification(149.99, "Double King", "Two Kings - standard", 2, dking));

    }
    RoomCatalog::~RoomCatalog(){}

}// namespace Domain::Room
