#ifndef __MEMINFO_GETTER_HPP__
#define __MEMINFO_GETTER_HPP__

#include "json.hpp"

typedef struct meminfo {
  int MemTotal, MemFree, MemAvailable, Buffers, Cached, SwapCached, Active,
      Inactive, Active_anon, Inactive_anon, Active_file_, Inactive_file,
      Unevictable, Mlocked, SwapTotal, SwapFree, Dirty, Writeback, AnonPages,
      Mapped, Shmem, KReclaimable, Slab, SReclaimable, SUnreclaim, KernelStack,
      PageTables, NFS_Unstable, Bounce, WritebackTmp, CommitLimit, Committed_AS,
      VmallocTotal, VmallocUsed, VmallocChunk, Percpu, HugePages_Total,
      HugePages_Free, HugePages_Rsvd, HugePages_Surp, Hugepagesize, Hugetlb;
} MEMINFO;

nlohmann::json meminfo_getter();

#endif