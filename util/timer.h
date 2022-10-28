#ifndef QJOIN_UTIL_TIMER_H__
#define QJOIN_UTIL_TIMER_H__
#include <chrono>

namespace qjoin {

time_t GetEpoch();

class Timer {
 private:
  bool activate_;
  // std::chrono::high_resolution_clock::time_point start_point_;
  // std::chrono::high_resolution_clock::duration duration_;
  std::chrono::steady_clock::time_point start_point_;
  double duration_;

 public:
  Timer(){};
  virtual ~Timer(){};
  void Start() {
    activate_ = true;
    start_point_ = std::chrono::steady_clock::now();
  }

  void Stop() {
    if (activate_) {
      duration_ += std::chrono::duration_cast<std::chrono::duration<double>>(
                       std::chrono::steady_clock::now() - start_point_)
                       .count();
      start_point_ = std::chrono::steady_clock::time_point();
      activate_ = false;
    }
  }

  void Pause() { Stop(); }

  void Reset() {
    start_point_ = std::chrono::steady_clock::time_point();
    duration_ = 0.0;
    activate_ = false;
  }

  void UpdateDuration() {
    Stop();
    Start();
  }

  double Seconds() { return duration_; }

  // double MilliSeconds() {
  //   return static_cast<double>(
  //       std::chrono::duration_cast<std::chrono::milliseconds>(duration_)
  //           .count());
  // }

  // double MicroSeconds() {
  //   return static_cast<double>(
  //       std::chrono::duration_cast<std::chrono::microseconds>(duration_)
  //           .count());
  // }
};
}  // namespace qjoin

#endif  // QJOIN_UTIL_TIMER_H__