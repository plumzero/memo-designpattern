
#include "diag_message.h"
#include <iostream>

int main()
{
  const uint8_t cProtocolVersion{0x02};
  const uint8_t cSourceAddress{0x0001};
  const uint8_t cTargetAddress{0x0002};
  const std::vector<uint8_t> cUserData{0xab, 0xcd, 0xef};

  DiagMessage _message(cProtocolVersion, cSourceAddress, cTargetAddress, cUserData);
  std::vector<uint8_t> _actualResult;
  _message.Serialize(_actualResult);

  std::cout << std::hex;
  for (const auto elem : _actualResult) {
    std::cout << static_cast<int>(elem) << " ";
  }
  std::cout << std::endl;

  return 0;
}