#pragma once

#include <string>
#include <vector>

namespace Domain::Room
{

  class RoomSpecification
  {
  public:

    virtual float getRoomPrice() = 0;
    virtual std::string getRoomType() = 0;
    virtual std::string getRoomDesc() = 0;
    virtual int getRoomOccu() = 0;

    virtual void setRoomPrice(float temp) = 0;
    virtual void setRoomType(std::string temp) = 0;
    virtual void setRoomDesc(std::string temp) = 0;
    virtual void setRoomOccu(int temp) = 0;

    virtual ~RoomSpecification() noexcept = 0;

  private:
    float price;
    std::string type, description;
    int occupancy;
    //std::vector<int> roomnums;
  };

}// namespace Domain::Room
