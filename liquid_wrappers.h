#ifndef LIQUID_WRAPPERS_H_
#define LIQUID_WRAPPERS_H_

#include <complex>
#include <vector>

#include "liquid/liquid.h"

namespace liquid {

class AGC {
 public:
  AGC(float bw, float initial_gain);
  ~AGC();
  std::complex<float> execute(std::complex<float> s);
  float getGain();

 private:
  agc_crcf object_;
};

class FIRFilter {
 public:
  FIRFilter(int len, float fc, float As = 60.0f, float mu = 0.0f);
  ~FIRFilter();
  void push(std::complex<float> s);
  std::complex<float> execute();
  float getGroupDelayAt(float f);

 private:
  firfilt_crcf object_;
};

class NCO {
 public:
  NCO(float freq);
  ~NCO();
  std::complex<float> mixDown(std::complex<float> s);
  std::complex<float> mixUp(std::complex<float> s);
  void mixBlockDown(std::complex<float>* x, std::complex<float>* y,
      int n);
  void step();
  void setPLLBandwidth(float);
  void setFrequency(float);
  void setPhase(float);
  void stepPLL(float dphi);
  float getFrequency();
  float getPhase();
  std::complex<float> getComplex();

 private:
  nco_crcf object_;
};

class WDelay {
 public:
  WDelay(int k);
  ~WDelay();
  void push(std::complex<float> x);
  std::complex<float> read();

 private:
  wdelaycf object_;
};

class SymSync {
 public:
  SymSync(liquid_firfilt_type ftype, unsigned k, unsigned m,
          float beta, unsigned num_filters);
  ~SymSync();
  void setBandwidth(float);
  void setOutputRate(unsigned);
  std::vector<std::complex<float>> execute(std::complex<float> in);

 private:
  symsync_crcf object_;
};

class Modem {
 public:
  Modem(modulation_scheme scheme);
  ~Modem();
  unsigned int demodulate(std::complex<float> sample);
  float getPhaseError();

 private:
  modem object_;
};

}  // namespace liquid

#endif // LIQUID_WRAPPERS_H_
