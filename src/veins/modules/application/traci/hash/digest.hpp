#pragma once

#include <bit>
#include <boost/endian.hpp>
#include <climits>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

#include <span>
#include <vector>

static_assert(CHAR_BIT == 8, "CHAR_BIT must == 8");
static_assert(boost::endian::little != boost::endian::big, "platforms with no endianness is not supported");
static_assert(boost::endian::native == boost::endian::little || boost::endian::native == boost::endian::big,
        "platforms with mixed endianness is not supported");

namespace Hash {

class Digest {
  public:
    virtual ~Digest() = default;

    std::string Final() {
        auto vec = FinalInternal();

        std::ostringstream oss;
        for (auto i : vec)
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(i);

        return oss.str();
    }

    void Update(const char *str) {
        Update({str, strlen(str)});
    }

  protected:
    virtual void UpdateInternal(uint8_t* view) = 0;

    virtual std::vector<uint8_t> FinalInternal() = 0;

    template<boost::endian endianness, typename T>
    requires (std::is_integral_v<T> && std::is_unsigned_v<T>)
    static std::vector<uint8_t> SplitUintView(std::basic_string<T> data) {
        std::vector<uint8_t> ret;
        ret.reserve(sizeof(T) * data.size());

        constexpr std::size_t maxShift = (sizeof(T) - 1) * 8;
        for (const auto i : data) {
            for (std::size_t shift = 0; shift <= maxShift; shift += 8) {
                (void) ret.emplace_back(static_cast<uint8_t>((i >> (endianness == boost::endian::little ? shift : maxShift - shift)) & 0xFF));
            }
        }

        return ret;
    }

};

template<typename WordType, std::size_t chunkSize, boost::endian endianness = boost::endian::big, std::size_t wordChunkExtend = 0> requires (std::is_integral_v<WordType> && std::is_unsigned_v<WordType> && (chunkSize % sizeof(WordType) == 0))
class ChunkedDigest: public Digest {
  public:
    virtual ~ChunkedDigest() override = default;

    static constexpr const std::size_t wordChunkSize = chunkSize / sizeof(WordType);
    typedef std::array<uint8_t, chunkSize> ChunkType;
    typedef std::array<WordType, wordChunkSize + wordChunkExtend> WordChunkType;

    ChunkedDigest()
            : chunkIter(chunk.begin()) {}

  protected:
    virtual void ProcessWordChunk(WordChunkType &wChunk) = 0;

    static void GetWordChunk(WordChunkType &wChunk, const ChunkType &chunk) {
        for (std::size_t i = 0; i < wordChunkSize; i++) {
            WordType temp = 0;
            std::size_t shift = 0;
            for (std::size_t j = 0; j < sizeof(WordType); j++) {
                const auto idx = (endianness == boost::endian::big) ? (sizeof(WordType) - 1) - j : j;
                temp |= static_cast<WordType>(chunk[sizeof(WordType) * i + idx]) << shift;
                shift += 8;
            }
            wChunk[i] = temp;
        }
    }

    std::basic_string<uint8_t> GetChunkView() {
        return {chunk.cbegin(), chunkIter};
    }

    std::size_t GetChunkCounter() {
        return chunkCounter;
    }

    virtual void UpdateInternal(std::basic_string<uint8_t> view) override {
        auto digestIter = view.cbegin();

        while (digestIter != view.cend()) { //could recurse but we can't count on tail call to avoid stack overflows all the time
            std::size_t toCopy = std::min(std::distance(digestIter, view.cend()), std::distance(chunkIter, chunk.end()));
            chunkIter = std::copy(digestIter, digestIter + toCopy, chunkIter);
            digestIter += toCopy;

            if (chunkIter == chunk.end())
                FeedChunk();
        }
    }

    void Fill(std::size_t n, uint8_t val) {
        std::size_t filled = 0;
        while (n > filled) {
            std::size_t toFill = std::min(
                    static_cast<std::size_t>(std::distance(chunkIter, chunk.end())),
                    n - filled);

            chunkIter = std::fill_n(chunkIter, toFill, val);
            filled += toFill;

            if (chunkIter == chunk.end())
                FeedChunk();
        }
    }

    void Reset() {
        chunkCounter = 0;
        chunkIter = chunk.begin();
    }

  private:
    ChunkType chunk{};
    typename ChunkType::iterator chunkIter;
    WordChunkType wChunk{};

    std::size_t chunkCounter{0};

    void FeedChunk() {
        ++chunkCounter;
        chunkIter = chunk.begin();
        GetWordChunk(wChunk, chunk);
        ProcessWordChunk(wChunk);
    }

};

template<typename WordType, std::size_t chunkSize, typename LengthContainer, boost::endian endianness = boost::endian::big, std::size_t wordChunkExtend = 0>
class LengthPaddedDigest: public ChunkedDigest<WordType, chunkSize, endianness, wordChunkExtend> {
  public:
    virtual ~LengthPaddedDigest() override = default;

  protected:
    void Pad() {
        namespace endian = boost::endian;

        std::size_t mlBytes = this->GetChunkCounter() * chunkSize + this->GetChunkView().size();
        Digest::Update("\200");

        constexpr std::size_t expected = chunkSize - sizeof(LengthContainer);
        std::size_t mod = (mlBytes + 1) % chunkSize;
        std::size_t zeroAppend = (mod <= expected) ? expected - mod : (chunkSize - mod) + expected;
        this->Fill(zeroAppend, 0x00U);

        //std::size_t mlBits = endian::native_to_big(mlBytes * 8);
        //this->Update({reinterpret_cast<uint8_t *>(&mlBits), sizeof(mlBits)});

        LengthContainer mlBits{mlBytes};
        mlBits *= LengthContainer{8};
        std::span < uint8_t > bitSpan;
        bitSpan = {reinterpret_cast<uint8_t *>(&mlBits), sizeof(LengthContainer)}; ///FIXME: ugly ugly ugly

        if constexpr (boost::endian::native != endianness)
            std::reverse(bitSpan.begin(), bitSpan.end());

        this->Update({bitSpan.data(), bitSpan.size()});
    }

  private:
};

}
