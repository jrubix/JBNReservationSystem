#pragma once

#include <any>
#include <memory>    // unique_ptr
#include <stdexcept> // runtime_error
#include <string>
#include <vector>

namespace Domain::Hotel
{

  class HotelHandler
  {
  public:
    virtual std::string addCostHotel() = 0;
    virtual std::string checkoutHotel() = 0;
    virtual std::string printAllRooms(std::string onlyavail) = 0;
    virtual std::string reserveHotelRoom(const std::string name, const std::string credentials, const std::vector<std::string> &args) = 0;
    virtual std::string unassignHotelRoom(const std::vector<std::string> &args) = 0;
    virtual std::string assignHotelRoom(const std::string name, const std::string number) = 0;
    virtual std::string getprice(std::string name) = 0;
    virtual std::string askAvailableRoom(std::string credentials, const std::vector<std::string> &args) = 0;

    virtual ~HotelHandler() noexcept = 0;
    static std::unique_ptr<HotelHandler> createHotel();

  private:
  };

} // namespace Domain::Hotel
