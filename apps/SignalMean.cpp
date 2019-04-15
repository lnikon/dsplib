#include <iostream>
#include <cmath>

#define SIG_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];

double calc_signal_mean(double *sig_src_arr, 
                        int sig_length);

double calc_signal_variance(double *sig_src_arr, 
                            double sig_mean,
                            int sig_length);

double calc_signal_std(double sig_variance);

int main() {
  double signal_mean = calc_signal_mean(InputSignal_f32_1kHz_15kHz, SIG_LENGTH);
  std::cout << "signal_mean = " << signal_mean << std::endl;

  double signal_variance = calc_signal_variance(InputSignal_f32_1kHz_15kHz, signal_mean, SIG_LENGTH);

  std::cout << "signal_variance = " << signal_variance << std::endl;

  double signal_std = calc_signal_std(signal_variance);
  std::cout << "signal_std = " << signal_std << std::endl;

  return 0;
}

double calc_signal_mean(double *sig_src_arr,
                        int sig_length)
{
  double _mean = .0;
  for(int i = 0; i < sig_length; i++)
  {
    _mean += *(sig_src_arr + i);
  }

  _mean /= (double)sig_length;

  return _mean;
}

double calc_signal_variance(double *sig_src_arr, 
                            double sig_mean,
                            int sig_length) 
{
  double _variance = .0;

  for(int i = 0; i < sig_length; i++)
  {
    _variance = _variance + pow((sig_src_arr[i] - sig_mean), 2);
  }

  _variance = _variance / (sig_length - 1);

  return _variance;
}

double calc_signal_std(double sig_variance) 
{
  double _std = sqrt(sig_variance);

  return _std;
}
