#pragma once

#include "digest.hpp"

namespace Hash {

namespace Sha2Internal {

static constexpr const std::array<uint32_t, 8> defaultHValues256{
        0x6a09e667U,
        0xbb67ae85U,
        0x3c6ef372U,
        0xa54ff53aU,
        0x510e527fU,
        0x9b05688cU,
        0x1f83d9abU,
        0x5be0cd19U,
};

static constexpr const std::array<uint32_t, 8> defaultHValues224{
        0xc1059ed8U,
        0x367cd507U,
        0x3070dd17U,
        0xf70e5939U,
        0xffc00b31U,
        0x68581511U,
        0x64f98fa7U,
        0xbefa4fa4U,
};

static constexpr const std::array<uint32_t, 64> defaultRoundValues256{
        0x428a2f98U, 0x71374491U, 0xb5c0fbcfU, 0xe9b5dba5U, 0x3956c25bU, 0x59f111f1U, 0x923f82a4U, 0xab1c5ed5U,
        0xd807aa98U, 0x12835b01U, 0x243185beU, 0x550c7dc3U, 0x72be5d74U, 0x80deb1feU, 0x9bdc06a7U, 0xc19bf174U,
        0xe49b69c1U, 0xefbe4786U, 0x0fc19dc6U, 0x240ca1ccU, 0x2de92c6fU, 0x4a7484aaU, 0x5cb0a9dcU, 0x76f988daU,
        0x983e5152U, 0xa831c66dU, 0xb00327c8U, 0xbf597fc7U, 0xc6e00bf3U, 0xd5a79147U, 0x06ca6351U, 0x14292967U,
        0x27b70a85U, 0x2e1b2138U, 0x4d2c6dfcU, 0x53380d13U, 0x650a7354U, 0x766a0abbU, 0x81c2c92eU, 0x92722c85U,
        0xa2bfe8a1U, 0xa81a664bU, 0xc24b8b70U, 0xc76c51a3U, 0xd192e819U, 0xd6990624U, 0xf40e3585U, 0x106aa070U,
        0x19a4c116U, 0x1e376c08U, 0x2748774cU, 0x34b0bcb5U, 0x391c0cb3U, 0x4ed8aa4aU, 0x5b9cca4fU, 0x682e6ff3U,
        0x748f82eeU, 0x78a5636fU, 0x84c87814U, 0x8cc70208U, 0x90befffaU, 0xa4506cebU, 0xbef9a3f7U, 0xc67178f2U
};

static constexpr const std::array<uint64_t, 8> defaultHValues512{
        0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL,
};

static constexpr const std::array<uint64_t, 8> defaultHValues384{
        0xcbbb9d5dc1059ed8ULL, 0x629a292a367cd507ULL, 0x9159015a3070dd17ULL, 0x152fecd8f70e5939ULL,
        0x67332667ffc00b31ULL, 0x8eb44a8768581511ULL, 0xdb0c2e0d64f98fa7ULL, 0x47b5481dbefa4fa4ULL,
};

static constexpr const std::array<uint64_t, 80> defaultRoundValues512{
        0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL,
        0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
        0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL,
        0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
        0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL,
        0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
        0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL,
        0x53380d139d95b3dfULL, 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
        0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL,
        0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
        0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL,
        0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
        0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL,
        0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
        0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL,
        0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL,
};

//256 functions:

inline uint32_t Sum0_256(uint32_t x) { return std::rotr(x, 2) ^ std::rotr(x, 13) ^ std::rotr(x, 22); }

inline uint32_t Sum1_256(uint32_t x) { return std::rotr(x, 6) ^ std::rotr(x, 11) ^ std::rotr(x, 25); }

inline uint32_t Sig0_256(uint32_t x) { return std::rotr(x, 7) ^ std::rotr(x, 18) ^ (x >> 3); }

inline uint32_t Sig1_256(uint32_t x) { return std::rotr(x, 17) ^ std::rotr(x, 19) ^ (x >> 10); }

//512 functions:

inline uint64_t Sum0_512(uint64_t x) { return std::rotr(x, 28) ^ std::rotr(x, 34) ^ std::rotr(x, 39); }

inline uint64_t Sum1_512(uint64_t x) { return std::rotr(x, 14) ^ std::rotr(x, 18) ^ std::rotr(x, 41); }

inline uint64_t Sig0_512(uint64_t x) { return std::rotr(x, 1) ^ std::rotr(x, 8) ^ (x >> 7); }

inline uint64_t Sig1_512(uint64_t x) { return std::rotr(x, 19) ^ std::rotr(x, 61) ^ (x >> 6); }

//common:

template<std::size_t i, typename Word, typename Chunk>
requires (std::is_same_v<Word, uint32_t> || std::is_same_v<Word, uint64_t>)
static inline Word Scheduled(Chunk &wChunk) {
    constexpr Chunk chunkTemp{};
    if constexpr (i < chunkTemp.size()) {
        return wChunk[i];
    } else {
        const Word s0 = std::is_same_v<Word, uint32_t> ? Sig0_256(wChunk[(i + 1) % 16]) : Sig0_512(wChunk[(i + 1) % 16]);
        const Word s1 = std::is_same_v<Word, uint32_t> ? Sig1_256(wChunk[(i + 14) % 16]) : Sig1_512(wChunk[(i + 14) % 16]);
        wChunk[i % 16] = s0 + s1 + wChunk[i % 16] + wChunk[(i + 9) % 16];
        return wChunk[i % 16];
    }
}

template<std::size_t i, typename Word, typename Chunk>
requires (std::is_same_v<Word, uint32_t> || std::is_same_v<Word, uint64_t>)
static inline void Round(Chunk &w, Word &a, Word &b, Word &c, Word &d, Word &e, Word &f, Word &g, Word &h) {
    const Word s1 = std::is_same_v<Word, uint32_t> ? Sum1_256(e) : Sum1_512(e);
    const Word ch = (e & f) ^(~e & g);
    const Word k = std::is_same_v<Word, uint32_t> ? defaultRoundValues256[i] : defaultRoundValues512[i];
    const Word temp1 = h + s1 + ch + k + Scheduled<i, Word>(w);

    const Word s0 = std::is_same_v<Word, uint32_t> ? Sum0_256(a) : Sum0_512(a);
    const Word maj = (a & b) ^(a & c) ^(b & c);
    const Word temp2 = s0 + maj;

    d += temp1;
    h = temp1 + temp2;
}

class DigestBase256: public LengthPaddedDigest<uint32_t, 64, std::size_t> {
  public:
    virtual ~DigestBase256() override = default;

    explicit DigestBase256(const std::array<uint32_t, 8> &hValues)
            : defHValues(hValues)
            , hValues(hValues) {}

  protected:
    virtual std::vector<uint8_t> FinalInternal() override {
        Pad();
        Reset();

        auto ret = SplitUintView<std::endian::big, uint32_t>({hValues.data(), hValues.size()});
        hValues = defHValues;

        return ret;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
    virtual void ProcessWordChunk(WordChunkType &wChunk) override {
        uint32_t a = hValues[0];
        uint32_t b = hValues[1];
        uint32_t c = hValues[2];
        uint32_t d = hValues[3];
        uint32_t e = hValues[4];
        uint32_t f = hValues[5];
        uint32_t g = hValues[6];
        uint32_t h = hValues[7];

        /*for (std::size_t i = 16; i < 64; i++) {
            uint32_t s0 = std::rotr(wChunk[i - 15], 7) ^std::rotr(wChunk[i - 15], 18) ^(wChunk[i - 15] >> 3);
            uint32_t s1 = std::rotr(wChunk[i - 2], 17) ^std::rotr(wChunk[i - 2], 19) ^(wChunk[i - 2] >> 10);
            wChunk[i] = s0 + s1 + wChunk[i - 16] + wChunk[i - 7];
        }*/

        /*for (std::size_t i = 0; i < 64; i++) {
           uint32_t s1 = std::rotr(e, 6) ^std::rotr(e, 11) ^std::rotr(e, 25);
           uint32_t ch = (e & f) ^(~e & g);
           uint32_t temp1 = h + s1 + ch + defaultRoundValues256[i] + wChunk[i];

           uint32_t s0 = std::rotr(a, 2) ^std::rotr(a, 13) ^std::rotr(a, 22);
           uint32_t maj = (a & b) ^(a & c) ^(b & c);
           uint32_t temp2 = s0 + maj;

           h = g;
           g = f;
           f = e;
           e = d + temp1;
           d = c;
           c = b;
           b = a;
           a = temp1 + temp2;
       }*/

        //unrolling is faster :^)

        Round<0>(wChunk, a, b, c, d, e, f, g, h);
        Round<1>(wChunk, h, a, b, c, d, e, f, g);
        Round<2>(wChunk, g, h, a, b, c, d, e, f);
        Round<3>(wChunk, f, g, h, a, b, c, d, e);
        Round<4>(wChunk, e, f, g, h, a, b, c, d);
        Round<5>(wChunk, d, e, f, g, h, a, b, c);
        Round<6>(wChunk, c, d, e, f, g, h, a, b);
        Round<7>(wChunk, b, c, d, e, f, g, h, a);
        Round<8>(wChunk, a, b, c, d, e, f, g, h);
        Round<9>(wChunk, h, a, b, c, d, e, f, g);
        Round<10>(wChunk, g, h, a, b, c, d, e, f);
        Round<11>(wChunk, f, g, h, a, b, c, d, e);
        Round<12>(wChunk, e, f, g, h, a, b, c, d);
        Round<13>(wChunk, d, e, f, g, h, a, b, c);
        Round<14>(wChunk, c, d, e, f, g, h, a, b);
        Round<15>(wChunk, b, c, d, e, f, g, h, a);
        Round<16>(wChunk, a, b, c, d, e, f, g, h);
        Round<17>(wChunk, h, a, b, c, d, e, f, g);
        Round<18>(wChunk, g, h, a, b, c, d, e, f);
        Round<19>(wChunk, f, g, h, a, b, c, d, e);
        Round<20>(wChunk, e, f, g, h, a, b, c, d);
        Round<21>(wChunk, d, e, f, g, h, a, b, c);
        Round<22>(wChunk, c, d, e, f, g, h, a, b);
        Round<23>(wChunk, b, c, d, e, f, g, h, a);
        Round<24>(wChunk, a, b, c, d, e, f, g, h);
        Round<25>(wChunk, h, a, b, c, d, e, f, g);
        Round<26>(wChunk, g, h, a, b, c, d, e, f);
        Round<27>(wChunk, f, g, h, a, b, c, d, e);
        Round<28>(wChunk, e, f, g, h, a, b, c, d);
        Round<29>(wChunk, d, e, f, g, h, a, b, c);
        Round<30>(wChunk, c, d, e, f, g, h, a, b);
        Round<31>(wChunk, b, c, d, e, f, g, h, a);
        Round<32>(wChunk, a, b, c, d, e, f, g, h);
        Round<33>(wChunk, h, a, b, c, d, e, f, g);
        Round<34>(wChunk, g, h, a, b, c, d, e, f);
        Round<35>(wChunk, f, g, h, a, b, c, d, e);
        Round<36>(wChunk, e, f, g, h, a, b, c, d);
        Round<37>(wChunk, d, e, f, g, h, a, b, c);
        Round<38>(wChunk, c, d, e, f, g, h, a, b);
        Round<39>(wChunk, b, c, d, e, f, g, h, a);
        Round<40>(wChunk, a, b, c, d, e, f, g, h);
        Round<41>(wChunk, h, a, b, c, d, e, f, g);
        Round<42>(wChunk, g, h, a, b, c, d, e, f);
        Round<43>(wChunk, f, g, h, a, b, c, d, e);
        Round<44>(wChunk, e, f, g, h, a, b, c, d);
        Round<45>(wChunk, d, e, f, g, h, a, b, c);
        Round<46>(wChunk, c, d, e, f, g, h, a, b);
        Round<47>(wChunk, b, c, d, e, f, g, h, a);
        Round<48>(wChunk, a, b, c, d, e, f, g, h);
        Round<49>(wChunk, h, a, b, c, d, e, f, g);
        Round<50>(wChunk, g, h, a, b, c, d, e, f);
        Round<51>(wChunk, f, g, h, a, b, c, d, e);
        Round<52>(wChunk, e, f, g, h, a, b, c, d);
        Round<53>(wChunk, d, e, f, g, h, a, b, c);
        Round<54>(wChunk, c, d, e, f, g, h, a, b);
        Round<55>(wChunk, b, c, d, e, f, g, h, a);
        Round<56>(wChunk, a, b, c, d, e, f, g, h);
        Round<57>(wChunk, h, a, b, c, d, e, f, g);
        Round<58>(wChunk, g, h, a, b, c, d, e, f);
        Round<59>(wChunk, f, g, h, a, b, c, d, e);
        Round<60>(wChunk, e, f, g, h, a, b, c, d);
        Round<61>(wChunk, d, e, f, g, h, a, b, c);
        Round<62>(wChunk, c, d, e, f, g, h, a, b);
        Round<63>(wChunk, b, c, d, e, f, g, h, a);

        hValues[0] += a;
        hValues[1] += b;
        hValues[2] += c;
        hValues[3] += d;
        hValues[4] += e;
        hValues[5] += f;
        hValues[6] += g;
        hValues[7] += h;
    }
#pragma clang diagnostic pop

  private:
    std::array<uint32_t, 8> defHValues{};
    std::array<uint32_t, 8> hValues{};
};

class DigestBase512: public LengthPaddedDigest<uint64_t, 128, /*_ExtInt(128)*/ __uint128_t> {
  public:
    explicit DigestBase512(const std::array<uint64_t, 8> defHValues)
            : defHValues(defHValues)
            , hValues(defHValues) {}

    virtual ~DigestBase512() = default;

  protected:
    virtual std::vector<uint8_t> FinalInternal() override {
        Pad();
        Reset();

        auto ret = SplitUintView<std::endian::big, uint64_t>({hValues.data(), hValues.size()});
        hValues = defHValues;

        return ret;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
    virtual void ProcessWordChunk(WordChunkType &wChunk) override {
        uint64_t a = hValues[0];
        uint64_t b = hValues[1];
        uint64_t c = hValues[2];
        uint64_t d = hValues[3];
        uint64_t e = hValues[4];
        uint64_t f = hValues[5];
        uint64_t g = hValues[6];
        uint64_t h = hValues[7];

        Round<0>(wChunk, a, b, c, d, e, f, g, h);
        Round<1>(wChunk, h, a, b, c, d, e, f, g);
        Round<2>(wChunk, g, h, a, b, c, d, e, f);
        Round<3>(wChunk, f, g, h, a, b, c, d, e);
        Round<4>(wChunk, e, f, g, h, a, b, c, d);
        Round<5>(wChunk, d, e, f, g, h, a, b, c);
        Round<6>(wChunk, c, d, e, f, g, h, a, b);
        Round<7>(wChunk, b, c, d, e, f, g, h, a);
        Round<8>(wChunk, a, b, c, d, e, f, g, h);
        Round<9>(wChunk, h, a, b, c, d, e, f, g);
        Round<10>(wChunk, g, h, a, b, c, d, e, f);
        Round<11>(wChunk, f, g, h, a, b, c, d, e);
        Round<12>(wChunk, e, f, g, h, a, b, c, d);
        Round<13>(wChunk, d, e, f, g, h, a, b, c);
        Round<14>(wChunk, c, d, e, f, g, h, a, b);
        Round<15>(wChunk, b, c, d, e, f, g, h, a);
        Round<16>(wChunk, a, b, c, d, e, f, g, h);
        Round<17>(wChunk, h, a, b, c, d, e, f, g);
        Round<18>(wChunk, g, h, a, b, c, d, e, f);
        Round<19>(wChunk, f, g, h, a, b, c, d, e);
        Round<20>(wChunk, e, f, g, h, a, b, c, d);
        Round<21>(wChunk, d, e, f, g, h, a, b, c);
        Round<22>(wChunk, c, d, e, f, g, h, a, b);
        Round<23>(wChunk, b, c, d, e, f, g, h, a);
        Round<24>(wChunk, a, b, c, d, e, f, g, h);
        Round<25>(wChunk, h, a, b, c, d, e, f, g);
        Round<26>(wChunk, g, h, a, b, c, d, e, f);
        Round<27>(wChunk, f, g, h, a, b, c, d, e);
        Round<28>(wChunk, e, f, g, h, a, b, c, d);
        Round<29>(wChunk, d, e, f, g, h, a, b, c);
        Round<30>(wChunk, c, d, e, f, g, h, a, b);
        Round<31>(wChunk, b, c, d, e, f, g, h, a);
        Round<32>(wChunk, a, b, c, d, e, f, g, h);
        Round<33>(wChunk, h, a, b, c, d, e, f, g);
        Round<34>(wChunk, g, h, a, b, c, d, e, f);
        Round<35>(wChunk, f, g, h, a, b, c, d, e);
        Round<36>(wChunk, e, f, g, h, a, b, c, d);
        Round<37>(wChunk, d, e, f, g, h, a, b, c);
        Round<38>(wChunk, c, d, e, f, g, h, a, b);
        Round<39>(wChunk, b, c, d, e, f, g, h, a);
        Round<40>(wChunk, a, b, c, d, e, f, g, h);
        Round<41>(wChunk, h, a, b, c, d, e, f, g);
        Round<42>(wChunk, g, h, a, b, c, d, e, f);
        Round<43>(wChunk, f, g, h, a, b, c, d, e);
        Round<44>(wChunk, e, f, g, h, a, b, c, d);
        Round<45>(wChunk, d, e, f, g, h, a, b, c);
        Round<46>(wChunk, c, d, e, f, g, h, a, b);
        Round<47>(wChunk, b, c, d, e, f, g, h, a);
        Round<48>(wChunk, a, b, c, d, e, f, g, h);
        Round<49>(wChunk, h, a, b, c, d, e, f, g);
        Round<50>(wChunk, g, h, a, b, c, d, e, f);
        Round<51>(wChunk, f, g, h, a, b, c, d, e);
        Round<52>(wChunk, e, f, g, h, a, b, c, d);
        Round<53>(wChunk, d, e, f, g, h, a, b, c);
        Round<54>(wChunk, c, d, e, f, g, h, a, b);
        Round<55>(wChunk, b, c, d, e, f, g, h, a);
        Round<56>(wChunk, a, b, c, d, e, f, g, h);
        Round<57>(wChunk, h, a, b, c, d, e, f, g);
        Round<58>(wChunk, g, h, a, b, c, d, e, f);
        Round<59>(wChunk, f, g, h, a, b, c, d, e);
        Round<60>(wChunk, e, f, g, h, a, b, c, d);
        Round<61>(wChunk, d, e, f, g, h, a, b, c);
        Round<62>(wChunk, c, d, e, f, g, h, a, b);
        Round<63>(wChunk, b, c, d, e, f, g, h, a);
        Round<64>(wChunk, a, b, c, d, e, f, g, h);
        Round<65>(wChunk, h, a, b, c, d, e, f, g);
        Round<66>(wChunk, g, h, a, b, c, d, e, f);
        Round<67>(wChunk, f, g, h, a, b, c, d, e);
        Round<68>(wChunk, e, f, g, h, a, b, c, d);
        Round<69>(wChunk, d, e, f, g, h, a, b, c);
        Round<70>(wChunk, c, d, e, f, g, h, a, b);
        Round<71>(wChunk, b, c, d, e, f, g, h, a);
        Round<72>(wChunk, a, b, c, d, e, f, g, h);
        Round<73>(wChunk, h, a, b, c, d, e, f, g);
        Round<74>(wChunk, g, h, a, b, c, d, e, f);
        Round<75>(wChunk, f, g, h, a, b, c, d, e);
        Round<76>(wChunk, e, f, g, h, a, b, c, d);
        Round<77>(wChunk, d, e, f, g, h, a, b, c);
        Round<78>(wChunk, c, d, e, f, g, h, a, b);
        Round<79>(wChunk, b, c, d, e, f, g, h, a);

        hValues[0] += a;
        hValues[1] += b;
        hValues[2] += c;
        hValues[3] += d;
        hValues[4] += e;
        hValues[5] += f;
        hValues[6] += g;
        hValues[7] += h;
    }
#pragma clang diagnostic pop

  private:
    std::array<uint64_t, 8> defHValues{};
    std::array<uint64_t, 8> hValues{};
};

}

class Sha256: public Sha2Internal::DigestBase256 {
  public:
    virtual ~Sha256() override = default;

    Sha256()
            : Sha2Internal::DigestBase256(Sha2Internal::defaultHValues256) {}
};

class Sha224: public Sha2Internal::DigestBase256 {
  public:
    virtual ~Sha224() override = default;

    Sha224()
            : Sha2Internal::DigestBase256(Sha2Internal::defaultHValues224) {}

  protected:
    virtual std::vector<uint8_t> FinalInternal() override {
        auto vec = DigestBase256::FinalInternal();
        vec.erase(vec.end() - 4, vec.end());
        return vec;
    }
};


class Sha512: public Sha2Internal::DigestBase512 {
  public:
    virtual ~Sha512() override = default;

    Sha512()
            : DigestBase512(Sha2Internal::defaultHValues512) {}
};

class Sha384: public Sha2Internal::DigestBase512 {
  public:
    virtual ~Sha384() override = default;

    Sha384()
            : DigestBase512(Sha2Internal::defaultHValues384) {}

  protected:
    virtual std::vector<uint8_t> FinalInternal() override {
        auto vec = DigestBase512::FinalInternal();
        vec.erase(vec.end() - 16, vec.end());
        return vec;
    }
};

}
