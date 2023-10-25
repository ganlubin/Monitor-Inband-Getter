#include "tools.hpp"
#include <iostream>
#include <proc/readproc.h>
#include <stdio.h>
#include <string.h>
#include <typeinfo>


std::string create(const proc_t &);

int procps(const std::string &file) {

  // check if cached file existed
  int r = check_file_exist_delete(file);
  if (r < 0) {
    std::cerr << "something wrong in the deleting..." << std::endl;
    return -1;
  }

  PROCTAB *proc = openproc(PROC_FILLMEM | PROC_FILLSTAT);

  proc_t proc_info;
  memset(&proc_info, 0, sizeof(proc_info));
  while (readproc(proc, &proc_info) != NULL) {
    if (proc_info.cmd == NULL) {
      continue;
    }

    std::string s = create(proc_info);
    write_to_file(s + '\n', file, 'a');
  }
  std::cout << "Over" << std::endl;
  closeproc(proc); // 关闭进程表
  return 0;
}

std::string create(const proc_t &t) {
  std::string res = "";
  res += "tid: " + std::to_string(t.tid) + '\n';
  res += "ppid: " + std::to_string(t.ppid) + '\n';
  res += "maj_delta: " + std::to_string(t.maj_delta) + '\n';
  res += "min_delta: " + std::to_string(t.min_delta) + '\n';
  res += "pcpu: " + std::to_string(t.pcpu) + '\n';
  res += "state: " + std::to_string(t.state) + '\n';
  res += "utime: " + std::to_string(t.utime) + '\n';
  res += "stime: " + std::to_string(t.stime) + '\n';
  res += "cutime: " + std::to_string(t.cutime) + '\n';
  res += "cstime: " + std::to_string(t.cstime) + '\n';
  res += "start_time: " + std::to_string(t.start_time) + '\n';
  //   res + "signal: " + std::to_string(t.signal) + '\n';
  //   res + "blocked: " + std::to_string(t.blocked) + '\n';
  //   res + "sigignore: " + std::to_string(t.sigignore) + '\n';
  //   res + "sigcatch: " + t.sigcatch + '\n';
  //   res + "_sigpnd: " + t._sigpnd + '\n';
  res += "start_code: " + std::to_string(t.start_code) + '\n';
  res += "end_code: " + std::to_string(t.end_code) + '\n';
  res += "start_stack: " + std::to_string(t.start_stack) + '\n';
  res += "kstk_esp: " + std::to_string(t.kstk_esp) + '\n';
  res += "kstk_eip: " + std::to_string(t.kstk_eip) + '\n';
  res += "wchan: " + std::to_string(t.wchan) + '\n';
  res += "priority: " + std::to_string(t.priority) + '\n';
  res += "nice: " + std::to_string(t.nice) + '\n';
  res += "rss: " + std::to_string(t.rss) + '\n';
  res += "alarm: " + std::to_string(t.alarm) + '\n';
  res += "size: " + std::to_string(t.size) + '\n';
  res += "resident: " + std::to_string(t.resident) + '\n';
  res += "share: " + std::to_string(t.share) + '\n';
  res += "trs: " + std::to_string(t.trs) + '\n';
  res += "lrs: " + std::to_string(t.lrs) + '\n';
  res += "drs: " + std::to_string(t.drs) + '\n';
  res += "dt: " + std::to_string(t.dt) + '\n';
  res += "vm_size: " + std::to_string(t.vm_size) + '\n';
  res += "vm_lock: " + std::to_string(t.vm_lock) + '\n';
  res += "vm_rss: " + std::to_string(t.vm_rss) + '\n';
  res += "vm_rss_anon: " + std::to_string(t.vm_rss_anon) + '\n';
  res += "vm_rss_shared: " + std::to_string(t.vm_rss_shared) + '\n';
  res += "vm_data: " + std::to_string(t.vm_data) + '\n';
  res += "vm_stack: " + std::to_string(t.vm_stack) + '\n';
  res += "vm_swap: " + std::to_string(t.vm_swap) + '\n';
  res += "vm_exe: " + std::to_string(t.vm_exe) + '\n';
  res += "vm_lib: " + std::to_string(t.vm_lib) + '\n';
  res += "rtprio: " + std::to_string(t.rtprio) + '\n';
  res += "sched: " + std::to_string(t.sched) + '\n';
  res += "vsize: " + std::to_string(t.vsize) + '\n';
  res += "rss_rlim: " + std::to_string(t.rss_rlim) + '\n';
  res += "flags: " + std::to_string(t.flags) + '\n';
  res += "maj_flt: " + std::to_string(t.maj_flt) + '\n';
  res += "min_flt: " + std::to_string(t.min_flt) + '\n';
  res += "cmaj_flt: " + std::to_string(t.cmaj_flt) + '\n';
  res += "cmin_flt: " + std::to_string(t.cmin_flt) + '\n';
  //   res + "euser: " + t.euser + '\n';
  //   res + "ruser: " + t.ruser + '\n';
  //   res + "suser: " + t.suser + '\n';
  //   res + "fuser: " + t.fuser + '\n';
  //   res + "rgroup: " + t.rgroup + '\n';
  //   res + "egroup: " + t.egroup + '\n';
  //   res + "sgroup: " + t.sgroup + '\n';
  //   res + "fgroup: " + t.fgroup + '\n';
  //   res + "cmd: " + std::to_string(t.cmd) + '\n';
  res += "cmd: ";
  res.append(t.cmd), res + '\n';
  res += "pgrp: " + std::to_string(t.pgrp) + '\n';
  res += "session: " + std::to_string(t.session) + '\n';
  res += "nlwp: " + std::to_string(t.nlwp) + '\n';
  res += "tgid: " + std::to_string(t.tgid) + '\n';
  res += "tty: " + std::to_string(t.tty) + '\n';
  res += "euid: " + std::to_string(t.euid) + '\n';
  res += "egid: " + std::to_string(t.egid) + '\n';
  res += "ruid: " + std::to_string(t.ruid) + '\n';
  res += "rgid: " + std::to_string(t.rgid) + '\n';
  res += "suid: " + std::to_string(t.suid) + '\n';
  res += "sgid: " + std::to_string(t.sgid) + '\n';
  res += "fuid: " + std::to_string(t.fuid) + '\n';
  res += "fgid: " + std::to_string(t.fgid) + '\n';
  res += "tpgid: " + std::to_string(t.tpgid) + '\n';
  res += "exit_signal: " + std::to_string(t.exit_signal) + '\n';
  res += "processor: " + std::to_string(t.processor) + '\n';
  res += "oom_score: " + std::to_string(t.oom_score) + '\n';
  res += "oom_adj: " + std::to_string(t.oom_adj) + '\n';

  return res;
}