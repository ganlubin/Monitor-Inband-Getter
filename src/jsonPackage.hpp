#ifndef JSONPACKAGE_HPP
#define JSONPACKAGE_HPP
#include "json.hpp"
using json = nlohmann::json;

#include <iostream>

typedef struct proc {
  std::string USER;
  int PID;
  float CPU;
  float MEM;
  int VSZ;
  int RSS;
  std::string TTY;
  std::string STAT;
  std::string START;
  std::string TIME;
  std::string COMMAND;

  int ppid;
  unsigned long maj_delta, min_delta;
  unsigned int pcpu;
  char state;
  unsigned long long utime, stime, cutime, cstime, start_time;
  unsigned long start_code, end_code, start_stack, kstk_esp,
      kstk_eip;
  unsigned long wchan;
  long priority, nice, rss, alarm;
  long size, resident, share, trs, lrs, drs, dt;
  long vm_size, vm_lock, vm_rss, vm_rss_anon, vm_rss_shared, vm_data, vm_stack,
      vm_swap, vm_exe, vm_lib;
  long rtprio, sched, vsize, rss_rlim, flags, maj_flt, min_flt, cmaj_flt,
      cmin_flt;
  std::string cmd;
  int pgrp, session, nlwp, tgid, tty, euid, egid, ruid, rgid, suid, sgid, fuid,
      fgid, tpgid;
  int exit_signal, processor, oom_socre, oom_adj;

} PROC_INFO;

int create_info_json();

#endif