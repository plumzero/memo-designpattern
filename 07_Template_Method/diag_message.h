
#pragma once

#include "message.h"

class DiagMessage : public Message
{
private:
  static const PayloadType cPayloadType{0x8001};

  uint16_t mSourceAddress;
  uint16_t mTargetAddress;
  std::vector<uint8_t> mUserData;

protected:
  void GetPayload(std::vector<uint8_t> &payload) const override
  {
    payload.insert(payload.begin(), mUserData.cbegin(), mUserData.cend());
    ToByteVector<uint16_t>(mTargetAddress, payload);
    ToByteVector<uint16_t>(mSourceAddress, payload);
  }
  // virtual bool TrySetPayload(const std::vector<uint8_t> &payload, uint32_t payloadLength) override;

public:
  DiagMessage() : Message(cPayloadType) {}

  DiagMessage(
      uint8_t protocolVersion,
      uint16_t sourceAddress,
      uint16_t targetAddress,
      const std::vector<uint8_t> &userData) : Message(protocolVersion, cPayloadType),
                                              mSourceAddress{sourceAddress},
                                              mTargetAddress{targetAddress},
                                              mUserData{userData} {}

  DiagMessage(
      uint8_t protocolVersion,
      uint16_t sourceAddress,
      uint16_t targetAddress,
      std::vector<uint8_t> &&userData) : Message(protocolVersion, cPayloadType),
                                          mSourceAddress{sourceAddress},
                                          mTargetAddress{targetAddress},
                                          mUserData{std::move(userData)} {}
};
