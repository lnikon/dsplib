#include <iostream>

#include "SignalStatistics.hpp"
// #include "Waveforms.hpp"

int main() {
  SignalStatistics<float> ss;
  auto InputSignal_f32_1kHz_15kHz = std::vector<float> {};
  ss.setSignalSource(InputSignal_f32_1kHz_15kHz);

  auto mean = ss.mean();
  if(mean.has_value()) {
    auto meanValue = mean.value();
    std::cout << "mean: " << meanValue << std::endl;
  }

  auto variance = ss.variance();
  if(variance.has_value()) {
    auto varianceValue = variance.value();
    std::cout << "mean: " << varianceValue << std::endl;
  }

  return 0;
}

