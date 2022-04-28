#pragma once

#include "digest.hpp"

namespace Hash {

namespace Md5Internal {

static constexpr const std::array<uint8_t, 64> roundShifts{
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

//floor(232 × abs (sin(i + 1)))
static constexpr const std::array<uint32_t, 64> kValues{
        0xd76aa478U, 0xe8c7b756U, 0x242070dbU, 0xc1bdceeeU,
        0xf57c0fafU, 0x4787c62aU, 0xa8304613U, 0xfd469501U,
        0x698098d8U, 0x8b44f7afU, 0xffff5bb1U, 0x895cd7beU,
        0x6b901122U, 0xfd987193U, 0xa679438eU, 0x49b40821U,
        0xf61e2562U, 0xc040b340U, 0x265e5a51U, 0xe9b6c7aaU,
        0xd62f105dU, 0x02441453U, 0xd8a1e681U, 0xe7d3fbc8U,
        0x21e1cde6U, 0xc33707d6U, 0xf4d50d87U, 0x455a14edU,
        0xa9e3e905U, 0xfcefa3f8U, 0x676f02d9U, 0x8d2a4c8aU,
        0xfffa3942U, 0x8771f681U, 0x6d9d6122U, 0xfde5380cU,
        0xa4beea44U, 0x4bdecfa9U, 0xf6bb4b60U, 0xbebfbc70U,
        0x289b7ec6U, 0xeaa127faU, 0xd4ef3085U, 0x04881d05U,
        0xd9d4d039U, 0xe6db99e5U, 0x1fa27cf8U, 0xc4ac5665U,
        0xf4292244U, 0x432aff97U, 0xab9423a7U, 0xfc93a039U,
        0x655b59c3U, 0x8f0ccc92U, 0xffeff47dU, 0x85845dd1U,
        0x6fa87e4fU, 0xfe2ce6e0U, 0xa3014314U, 0x4e0811a1U,
        0xf7537e82U, 0xbd3af235U, 0x2ad7d2bbU, 0xeb86d391U,
};

}

class Md5: public LengthPaddedDigest<uint32_t, 64, std::size_t, std::endian::little, 0> {
  public:
    virtual ~Md5() override = default;

  protected:
    virtual std::vector<uint8_t> FinalInternal() override {
        Pad();
        Reset();

        auto ret = SplitUintView<std::endian::little, uint32_t>({hValues.data(), hValues.size()});
        hValues = defaultHValues;

        return ret;
    }

    virtual void ProcessWordChunk(WordChunkType &wChunk) override {
        uint32_t a = hValues[0];
        uint32_t b = hValues[1];
        uint32_t c = hValues[2];
        uint32_t d = hValues[3];

        RoundCaller(wChunk, a, b, c, d);

        hValues[0] += a;
        hValues[1] += b;
        hValues[2] += c;
        hValues[3] += d;
    }

  private:
    const std::array<uint32_t, 4> defaultHValues{0x67452301U, 0xefcdab89U, 0x98badcfeU, 0x10325476U};
    std::array<uint32_t, 4> hValues{defaultHValues};

    ///FIXME: unrolling would be faster than variable shifting but eh i am too lazy for that right now
    template<std::size_t i = 0>
    requires (i < 64)
    static void RoundCaller(const WordChunkType &wChunk, uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d) {
        Round<i>(wChunk, a, b, c, d);
        if constexpr (i < 63)
            RoundCaller<i + 1>(wChunk, a, b, c, d);
    }

    template<std::size_t i>
    requires (i <= 63)
    static void Round(const WordChunkType &wChunk, uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d) {
        uint32_t f;
        uint32_t g;

        if constexpr (i < 16) {
            f = (b & c) | ((~b) & d);
            g = i;
        } else if constexpr (i < 32) {
            f = (b & d) | ((~d) & c);
            g = (5 * i + 1) % 16;
        } else if constexpr (i < 48) {
            f = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        } else {
            f = c ^ (b | (~d));
            g = (7 * i) % 16;
        }

        f += a + Md5Internal::kValues[i] + wChunk[g];

        a = d;
        d = c;
        c = b;
        b += std::rotl(f, Md5Internal::roundShifts[i]);
    }
};

}
