#pragma once

#include "digest.hpp"

namespace Hash {

namespace Sha1Internal {

typedef std::array<uint8_t, 64> Chunk;
typedef std::array<uint32_t, 16> WordChunk;
typedef std::array<uint32_t, 5> HValues;

static constexpr const HValues defaultHValues{
        0x67452301U,
        0xEFCDAB89U,
        0x98BADCFEU,
        0x10325476U,
        0xC3D2E1F0U,
};

static constexpr const std::array<uint32_t, 4> defaultRoundValues{
        0x5A827999U,
        0x6ED9EBA1U,
        0x8F1BBCDCU,
        0xCA62C1D6U,
};

//round from 0 to 3, not 4
template<std::size_t round>
inline uint32_t Box(uint32_t b [[maybe_unused]], uint32_t c [[maybe_unused]], uint32_t d [[maybe_unused]]) {
    static_assert(round <= 3);
    return -1;
}

template<>
inline uint32_t Box<0>(uint32_t b, uint32_t c, uint32_t d) { return (b & c) | (~b & d); }

template<>
inline uint32_t Box<1>(uint32_t b, uint32_t c, uint32_t d) { return b ^ c ^ d; }

template<>
inline uint32_t Box<2>(uint32_t b, uint32_t c, uint32_t d) { return (b & c) | (b & d) | (c & d); }

template<>
inline uint32_t Box<3>(uint32_t b, uint32_t c, uint32_t d) { return b ^ c ^ d; }

template<bool doRotl = false>
class Sha1Base: public LengthPaddedDigest<uint32_t, 64, std::size_t> {
  public:
    Sha1Base()
            : hValues(Sha1Internal::defaultHValues) {}

  protected:
    virtual std::vector<uint8_t> FinalInternal() override {
        Pad();
        Reset();

        auto ret = SplitUintView<std::endian::big, uint32_t>({hValues.data(), hValues.size()});
        hValues = Sha1Internal::defaultHValues;

        return ret;
    }

    virtual void ProcessWordChunk(WordChunkType &wChunk) override {
        uint32_t a = hValues[0];
        uint32_t b = hValues[1];
        uint32_t c = hValues[2];
        uint32_t d = hValues[3];
        uint32_t e = hValues[4];

        Round<0, 0>(wChunk, a, b, c, d, e);
        Round<0, 1>(wChunk, e, a, b, c, d);
        Round<0, 2>(wChunk, d, e, a, b, c);
        Round<0, 3>(wChunk, c, d, e, a, b);
        Round<0, 4>(wChunk, b, c, d, e, a);
        Round<0, 5>(wChunk, a, b, c, d, e);
        Round<0, 6>(wChunk, e, a, b, c, d);
        Round<0, 7>(wChunk, d, e, a, b, c);
        Round<0, 8>(wChunk, c, d, e, a, b);
        Round<0, 9>(wChunk, b, c, d, e, a);
        Round<0, 10>(wChunk, a, b, c, d, e);
        Round<0, 11>(wChunk, e, a, b, c, d);
        Round<0, 12>(wChunk, d, e, a, b, c);
        Round<0, 13>(wChunk, c, d, e, a, b);
        Round<0, 14>(wChunk, b, c, d, e, a);
        Round<0, 15>(wChunk, a, b, c, d, e);
        Round<0, 16>(wChunk, e, a, b, c, d);
        Round<0, 17>(wChunk, d, e, a, b, c);
        Round<0, 18>(wChunk, c, d, e, a, b);
        Round<0, 19>(wChunk, b, c, d, e, a);
        Round<1, 20>(wChunk, a, b, c, d, e);
        Round<1, 21>(wChunk, e, a, b, c, d);
        Round<1, 22>(wChunk, d, e, a, b, c);
        Round<1, 23>(wChunk, c, d, e, a, b);
        Round<1, 24>(wChunk, b, c, d, e, a);
        Round<1, 25>(wChunk, a, b, c, d, e);
        Round<1, 26>(wChunk, e, a, b, c, d);
        Round<1, 27>(wChunk, d, e, a, b, c);
        Round<1, 28>(wChunk, c, d, e, a, b);
        Round<1, 29>(wChunk, b, c, d, e, a);
        Round<1, 30>(wChunk, a, b, c, d, e);
        Round<1, 31>(wChunk, e, a, b, c, d);
        Round<1, 32>(wChunk, d, e, a, b, c);
        Round<1, 33>(wChunk, c, d, e, a, b);
        Round<1, 34>(wChunk, b, c, d, e, a);
        Round<1, 35>(wChunk, a, b, c, d, e);
        Round<1, 36>(wChunk, e, a, b, c, d);
        Round<1, 37>(wChunk, d, e, a, b, c);
        Round<1, 38>(wChunk, c, d, e, a, b);
        Round<1, 39>(wChunk, b, c, d, e, a);
        Round<2, 40>(wChunk, a, b, c, d, e);
        Round<2, 41>(wChunk, e, a, b, c, d);
        Round<2, 42>(wChunk, d, e, a, b, c);
        Round<2, 43>(wChunk, c, d, e, a, b);
        Round<2, 44>(wChunk, b, c, d, e, a);
        Round<2, 45>(wChunk, a, b, c, d, e);
        Round<2, 46>(wChunk, e, a, b, c, d);
        Round<2, 47>(wChunk, d, e, a, b, c);
        Round<2, 48>(wChunk, c, d, e, a, b);
        Round<2, 49>(wChunk, b, c, d, e, a);
        Round<2, 50>(wChunk, a, b, c, d, e);
        Round<2, 51>(wChunk, e, a, b, c, d);
        Round<2, 52>(wChunk, d, e, a, b, c);
        Round<2, 53>(wChunk, c, d, e, a, b);
        Round<2, 54>(wChunk, b, c, d, e, a);
        Round<2, 55>(wChunk, a, b, c, d, e);
        Round<2, 56>(wChunk, e, a, b, c, d);
        Round<2, 57>(wChunk, d, e, a, b, c);
        Round<2, 58>(wChunk, c, d, e, a, b);
        Round<2, 59>(wChunk, b, c, d, e, a);
        Round<3, 60>(wChunk, a, b, c, d, e);
        Round<3, 61>(wChunk, e, a, b, c, d);
        Round<3, 62>(wChunk, d, e, a, b, c);
        Round<3, 63>(wChunk, c, d, e, a, b);
        Round<3, 64>(wChunk, b, c, d, e, a);
        Round<3, 65>(wChunk, a, b, c, d, e);
        Round<3, 66>(wChunk, e, a, b, c, d);
        Round<3, 67>(wChunk, d, e, a, b, c);
        Round<3, 68>(wChunk, c, d, e, a, b);
        Round<3, 69>(wChunk, b, c, d, e, a);
        Round<3, 70>(wChunk, a, b, c, d, e);
        Round<3, 71>(wChunk, e, a, b, c, d);
        Round<3, 72>(wChunk, d, e, a, b, c);
        Round<3, 73>(wChunk, c, d, e, a, b);
        Round<3, 74>(wChunk, b, c, d, e, a);
        Round<3, 75>(wChunk, a, b, c, d, e);
        Round<3, 76>(wChunk, e, a, b, c, d);
        Round<3, 77>(wChunk, d, e, a, b, c);
        Round<3, 78>(wChunk, c, d, e, a, b);
        Round<3, 79>(wChunk, b, c, d, e, a);

        hValues[0] += a;
        hValues[1] += b;
        hValues[2] += c;
        hValues[3] += d;
        hValues[4] += e;
    }

  private:
    std::array<uint32_t, 5> hValues;

    template<std::size_t round, std::size_t i = 0>
    static inline void Round(WordChunkType &chunk, uint32_t a, uint32_t &b, uint32_t c, uint32_t d, uint32_t &e) {
        static_assert(round <= 3);

        uint32_t fk = Sha1Internal::defaultRoundValues[round] + Sha1Internal::Box<round>(b, c, d);
        uint32_t wi;
        if constexpr(i < 16)
            wi = chunk[i];
        else
            wi = Schedule(i, chunk);

        uint32_t temp = std::rotl(a, 5) + fk + wi; //+e
        e += temp;
        b = std::rotl(b, 30);
    }

    static inline uint32_t Schedule(std::size_t i, WordChunkType &chunk) {
        if constexpr (doRotl) {
            chunk[i % 16] = std::rotl(chunk[(i + 13) % 16] ^
                                      chunk[(i + 8) % 16] ^
                                      chunk[(i + 2) % 16] ^
                                      chunk[i % 16], 1);
        } else {
            chunk[i % 16] = chunk[(i + 13) % 16] ^
                            chunk[(i + 8) % 16] ^
                            chunk[(i + 2) % 16] ^
                            chunk[i % 16];
        }
        return chunk[i % 16];
    }

};

}

typedef Sha1Internal::Sha1Base<false> Sha0;
typedef Sha1Internal::Sha1Base<true> Sha1;

}
