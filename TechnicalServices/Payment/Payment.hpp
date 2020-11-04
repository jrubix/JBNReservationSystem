#pragma once
#include "TechnicalServices/Payment/PaymentHandler.hpp"

namespace TechnicalServices::Payment
{

  class PaymentBase : public TechnicalServices::Payment::PaymentHandler {
    public:
      std::string payHotel() override;
      ~PaymentBase() noexcept override;

    private:
  };

}
