#pragma once


#include <string>
#include <vector>

namespace Domain::Hotel
{

  class HotelHandler {
    public:

      virtual std::string addCostHotel() = 0;
      virtual std::string checkoutHotel() = 0;
      virtual std::string unassignHotelRoom() = 0;
      virtual std::string assignHotelRoom() = 0;
      virtual std::string getprice(std::string name) = 0;
      virtual std::string askAvailableRoom(std::string credentials, const std::vector<std::string>& args) = 0;

      virtual ~HotelHandler() noexcept = 0;
      static std::unique_ptr<HotelHandler> createHotel();

    private:
  };

}
