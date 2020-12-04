#include <iostream>
#include "Domain/Room/RoomSpecification.hpp"

namespace Domain::Room
{
  //add king, queen, double
  class King : public RoomSpecification{

    float getRoomPrice() override { return price; }
    std::string getRoomType() override { return type; }
    std::string getRoomDesc() override { return description; }
    int getRoomOccu() override { return occupancy; }

    void setRoomPrice(float temp) override { price = temp; }
    void setRoomType(std::string temp) override { type = temp; }
    void setRoomDesc(std::string temp) override { description = temp; }
    void setRoomOccu(int temp) override { occupancy = temp; }

    King(float rnum, std::string type_, std::string desc_, int occ_)
      :price(rnum), type(type_), description(desc_),occupancy(occ_){}

    ~King(){}
  };

  class Queen : public RoomSpecification{
    float getRoomPrice() override { return price; }
    std::string getRoomType() override { return type; }
    std::string getRoomDesc() override { return description; }
    int getRoomOccu() override { return occupancy; }

    void setRoomPrice(float temp) override { price = temp; }
    void setRoomType(std::string temp) override { type = temp; }
    void setRoomDesc(std::string temp) override { description = temp; }
    void setRoomOccu(int temp) override { occupancy = temp; }

    Queen(float rnum, std::string type_, std::string desc_, int occ_)
      :price(rnum), type(type_), description(desc_),occupancy(occ_){}

    ~Queen(){}
  };

  class Suite : public RoomSpecification{
    float getRoomPrice() override { return price; }
    std::string getRoomType() override { return type; }
    std::string getRoomDesc() override { return description; }
    int getRoomOccu() override { return occupancy; }

    void setRoomPrice(float temp) override { price = temp; }
    void setRoomType(std::string temp) override { type = temp; }
    void setRoomDesc(std::string temp) override { description = temp; }
    void setRoomOccu(int temp) override { occupancy = temp; }

    Suite(float rnum, std::string type_, std::string desc_, int occ_)
      :price(rnum), type(type_), description(desc_),occupancy(occ_){}

    ~Suite(){}
  };

  class DoubleKing : public RoomSpecification{
    float getRoomPrice() override { return price; }
    std::string getRoomType() override { return type; }
    std::string getRoomDesc() override { return description; }
    int getRoomOccu() override { return occupancy; }

    void setRoomPrice(float temp) override { price = temp; }
    void setRoomType(std::string temp) override { type = temp; }
    void setRoomDesc(std::string temp) override { description = temp; }
    void setRoomOccu(int temp) override { occupancy = temp; }

    DoubleKing(float rnum, std::string type_, std::string desc_, int occ_)
      :price(rnum), type(type_), description(desc_),occupancy(occ_){}

    ~DoubleKing(){}
  };
  
} // namespace Domain::Room
