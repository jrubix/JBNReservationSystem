#include "TechnicalServices/Payment/Payment.hpp"
#include "TechnicalServices/Payment/PaymentHandler.hpp"
namespace TechnicalServices::Payment
{
  PaymentHandler::~PaymentHandler() noexcept = default;
  std::unique_ptr<PaymentHandler> PaymentHandler::createPayment()
  {
    return std::unique_ptr<PaymentHandler>();
  }
}
