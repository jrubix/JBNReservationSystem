
#include "Domain/Room/RoomSpecification.hpp"

namespace Domain::Room
{
  float RoomSpecification::getRoomPrice(){ return price; }
  std::string RoomSpecification::getRoomType(){ return type; }
  std::string RoomSpecification::getRoomDesc(){ return description; }
  int RoomSpecification::getRoomOccu(){ return occupancy; }

  void RoomSpecification::setRoomPrice(float temp){ price = temp; }
  void RoomSpecification::setRoomType(std::string temp){ type = temp; }
  void RoomSpecification::setRoomDesc(std::string temp){ description = temp; }
  void RoomSpecification::setRoomOccu(int temp){ occupancy = temp; }

  RoomSpecification::RoomSpecification(float rnum, std::string type_, std::string desc_, int occ_, std::vector<int> rtype){
    price = rnum;
    type = type_;
    description = desc_;
    occupancy = occ_;
    for(int i=0; i<rtype.size()-1; i++){
      roomnums.push_back(rtype[i]);
    }
  }

} // namespace Domain::Room
