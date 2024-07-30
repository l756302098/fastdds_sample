#pragma once

#include <glog/logging.h>
#ifndef SLOG
#define SLOG(MODE) LOG(MODE) << "[SDK] [DDS] "
#endif

#ifndef DLOG
#define DSLOG(MODE) DLOG(MODE) << "[SDK] [DDS] "
#endif
