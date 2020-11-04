#pragma once

#include <string>
#include <memory>

namespace TechnicalServices::Payment
{

  class PaymentHandler
  {
  public:
    virtual std::string payHotel() = 0;
    virtual ~PaymentHandler() noexcept = 0;
    static std::unique_ptr<PaymentHandler> createPayment();

  private:
  };

} // namespace TechnicalServices::Payment
