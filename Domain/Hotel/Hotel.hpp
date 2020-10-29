#pragma once
#include "Domain/Hotel/HotelHandler.hpp"

namespace Domain::Hotel
{

  class HotelBase : public Domain::Hotel::HotelHandler {
    public:
    std::string addCostHotel() override;
    std::string checkoutHotel() override;
    std::string unassignHotelRoom() override;
    std::string assignHotelRoom() override;
    std::string getprice(std::string name) override;
    std::string askAvailableRoom(std::string credentials, const std::vector<std::string>& args) override;
    HotelBase();
    ~HotelBase() noexcept override;

    private:
      std::vector<std::vector<std::string>> roominfo;
  };

}
