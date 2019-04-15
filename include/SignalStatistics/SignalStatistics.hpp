#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <cmath>

template <class SignalType>
struct SignalStatistics final {
    SignalStatistics() = default;
    SignalStatistics(const SignalStatistics&) = default;
    SignalStatistics& operator=(const SignalStatistics&) = default;
    SignalStatistics(SignalStatistics&&) = default;
    SignalStatistics& operator=(SignalStatistics&&) = default;
    ~SignalStatistics() = default;

    SignalStatistics(const std::vector<SignalType>& signalSource);

    void setSignalSource(const std::vector<SignalType>& signalSource);

    std::optional<SignalType> mean(); 
    std::optional<SignalType> variance();
    std::optional<SignalType> standardDeviation() const;

    private:
    std::vector<SignalType> m_signalSource;

    std::optional<SignalType> meanHelper();
    std::optional<SignalType> varianceHelper();
    std::optional<SignalType> standardDeviationHelper() const;
};

    template <class SignalType>
SignalStatistics<SignalType>::SignalStatistics(const std::vector<SignalType>& signalSource) 
    : m_signalSource{signalSource} { }

    template <class SignalType>
    void SignalStatistics<SignalType>::setSignalSource(const std::vector<SignalType>& signalSource) {
        m_signalSource = signalSource;
    }

template <class SignalType>
std::optional<SignalType> SignalStatistics<SignalType>::mean() {
    return meanHelper();
}

template <class SignalType>
std::optional<SignalType> SignalStatistics<SignalType>::meanHelper() {
    using SigSrcIt = typename decltype(m_signalSource)::iterator;

    const auto signalSourceSize = m_signalSource.size();
    const auto divideFactor = 2;

    // How much long length of each block should be,
    // if the number of block equals to 2^divideFactor
    long long blockSize = signalSourceSize >> divideFactor;

    // Determine the beginning of the signal source
    auto signalSourceBegin { std::begin(m_signalSource) };

    // In our case, number of the blocks is explicitly 
    // set to the 4, therefore number of iterators
    // pointing to the blocks should be 4 too :)
    auto beginFirstBlock  { SigSrcIt{} };
    auto beginSecondBlock { SigSrcIt{} };
    auto beginThirdBlock  { SigSrcIt{} };
    auto beginFourthBlock { SigSrcIt{} };

    // Sum of blocks
    auto sum  = SignalType{};
    while(blockSize != 0) {
        beginFirstBlock  = signalSourceBegin++;
        beginSecondBlock = signalSourceBegin++;
        beginThirdBlock  = signalSourceBegin++;
        beginFourthBlock = signalSourceBegin++;

        sum += *beginFirstBlock;
        sum += *beginSecondBlock;
        sum += *beginThirdBlock;
        sum += *beginFourthBlock;

        --blockSize;
    }

    // Sum of the items from rest of the
    // signal source, which is has been not included
    // in last block
    blockSize = signalSourceSize % 0x4;

    while(blockSize != 0) {
        sum += *signalSourceBegin++;
        blockSize--;
    }
    auto result = std::optional<SignalType>{};
    if(signalSourceSize != 0) {
        auto mean = sum / static_cast<SignalType>(signalSourceSize);
        result = mean;
    } else {
        result = std::nullopt;
    }

    return result;
}

template <class SignalType>
std::optional<SignalType> SignalStatistics<SignalType>::variance() {
    return varianceHelper();
}

template <class SignalType>
std::optional<SignalType> SignalStatistics<SignalType>::varianceHelper() {
    using SigSrcIt = typename decltype(m_signalSource)::iterator;

    auto resultOptional = std::optional<SignalType>{};

    const auto signalSourceSize = m_signalSource.size();
    const auto divideFactor = 2;

    // How much long length of each block should be,
    // if the number of block equals to 2^divideFactor
    long long blockSize = signalSourceSize >> divideFactor;

    // Determine the beginning of the signal source
  auto signalSourceBegin { std::begin(m_signalSource) };

  // In our case, number of the blocks is explicitly 
  // set to the 4, therefore number of iterators
  // pointing to the blocks should be 4 too :)
  auto beginFirstBlock  { SigSrcIt{} };
  auto beginSecondBlock { SigSrcIt{} };
  auto beginThirdBlock  { SigSrcIt{} };
  auto beginFourthBlock { SigSrcIt{} };

  // Sum of blocks
  auto sum = SignalType{};
  while(blockSize > 0) {
    beginFirstBlock  = signalSourceBegin++;
    beginSecondBlock = signalSourceBegin++;
    beginThirdBlock  = signalSourceBegin++;
    beginFourthBlock = signalSourceBegin++;

    sum += *beginFirstBlock;
    sum += *beginSecondBlock;
    sum += *beginThirdBlock;
    sum += *beginFourthBlock;

    --blockSize;
  }

  blockSize = signalSourceSize % 0x4;
  while(blockSize > 0) {
    sum += *signalSourceBegin++;
    --blockSize;
  }

  auto fmean = SignalType{};
  if(signalSourceSize != 0) {
    fmean = sum / (double)signalSourceSize;
  } else {
    resultOptional = std::nullopt;
    return resultOptional;
  }

  signalSourceBegin = std::begin(m_signalSource);

  blockSize = signalSourceSize >> divideFactor;
  auto fvalue = SignalType{};
  auto fsum = SignalType{};
  while(blockSize > 0) {
    fvalue = *signalSourceBegin++ - fmean;
    fsum += fvalue * fvalue;

    fvalue = *signalSourceBegin++ - fmean;
    fsum += fvalue * fvalue;

    fvalue = *signalSourceBegin++ - fmean;
    fsum += fvalue * fvalue;

    fvalue = *signalSourceBegin++ - fmean;
    fsum += fvalue * fvalue;

    --blockSize;
  }

  blockSize = signalSourceSize % 0x4;
  while(blockSize > 0) {
    fvalue = *signalSourceBegin++ - fmean;
    blockSize--;
  }

  if(signalSourceSize >= 2) {
    resultOptional = fsum / static_cast<SignalType>(signalSourceSize - 1);
    return resultOptional;
  } 
    
  return std::nullopt;
}

template <class SignalType>
std::optional<SignalType> SignalStatistics<SignalType>::standardDeviation() const {
    return standardDeviationHelper();
}

template <class SignalType>
std::optional<SignalType> SignalStatistics<SignalType>::standardDeviationHelper() const
{
  const auto blkSize = m_signalSource.size();
  if(blkSize == 1) {
      return std::nullopt;
  }

  auto stdDeviation = std::optional<SignalType>{};

  auto sum = SignalType{};
  auto sumOfSqrs = SignalType{};
  auto it = m_signalSource.begin();
  auto in = SignalType{};

  auto blkCnt{0u};

  auto meanOfSquares = SignalType{};
  auto mean = SignalType{};
  auto squareOfMean = SignalType{}; 

  blkCnt = blkSize >> 2;

  while(blkCnt > 0)
  {
    in += *it++;
    sum += in;
    sumOfSqrs += in * in;

    in += *it++;
    sum += in;
    sumOfSqrs += in * in;

    in += *it++;
    sum += in;
    sumOfSqrs += in * in;

    in += *it++;
    sum += in;
    sumOfSqrs += in * in;

    blkCnt--;
  }

  blkCnt = blkSize % 0x4;

  while(blkCnt > 0) {
    in += *it++;
    sum += in;
    sumOfSqrs += in * in;
    blkCnt--;
  }

  meanOfSquares = sumOfSqrs / ((double)blkSize - 1.0);
  mean = sum / (double)blkSize;

  squareOfMean = (mean * mean) * (blkSize / (double)blkSize - 1.0);

  stdDeviation = sqrt(meanOfSquares - squareOfMean);

  return stdDeviation;
}
