
#pragma once

#include <vector>
#include <cstdint>

static const std::size_t cByteOffset{8};
static const uint8_t cByteMask{0xff};

template <typename T>
void ToByteVector(T unsignedInteger, std::vector<uint8_t> &vector)
{
  const auto cCastedByteOffset{static_cast<T>(cByteOffset)};
  const std::size_t cUnsignedIntegerSize{sizeof(T)};

  for (std::size_t i = 0; i < cUnsignedIntegerSize; ++i)
  {
    auto _byte{static_cast<uint8_t>(unsignedInteger & cByteMask)};
    vector.insert(vector.begin(), _byte);
    unsignedInteger = unsignedInteger >> cCastedByteOffset;
  }
}

using PayloadType = uint16_t;

class Message
{
private:
  uint8_t mProtocolVersion;
  const PayloadType mPayloadType;

protected:
  Message(PayloadType payloadType) noexcept : mPayloadType{payloadType} {}

  explicit Message(uint8_t protocolVersion,
          PayloadType payloadType) noexcept : mProtocolVersion{protocolVersion},
                                              mPayloadType{payloadType} {}

  virtual void GetPayload(std::vector<uint8_t> &payload) const = 0;
  // virtual bool TrySetPayload( const std::vector<uint8_t> &payload, uint32_t payloadLength) = 0;

public:
  void Serialize(std::vector<uint8_t> &serializedMessage) const
  {
    GetPayload(serializedMessage);

    auto _payloadLength{static_cast<uint32_t>(serializedMessage.size())};
    ToByteVector<uint32_t>(_payloadLength, serializedMessage);

    auto _payloadTypeInt{static_cast<uint16_t>(mPayloadType)};
    ToByteVector<uint16_t>(_payloadTypeInt, serializedMessage);

    auto _inverseProtocolVersion{static_cast<uint8_t>(~mProtocolVersion)};
    serializedMessage.insert(serializedMessage.begin(), _inverseProtocolVersion);

    serializedMessage.insert(serializedMessage.begin(), mProtocolVersion);
  }

  virtual ~Message() noexcept = default;
};
