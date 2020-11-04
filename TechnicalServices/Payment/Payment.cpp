#include "TechnicalServices/Payment/Payment.hpp"
#include <string>
#include <iostream>
namespace TechnicalServices::Payment
{

  std::string PaymentBase::payHotel(){
    return "Success";
  }

  PaymentBase::~PaymentBase() noexcept {
    std::cout<<"Payment Services Shutdown";
  }

}
