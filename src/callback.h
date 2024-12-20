#ifndef RAFT_CALLBACK_DEFINITIONS
#define RAFT_CALLBACK_DEFINITIONS

#include <functional>

namespace raft {

// Common
typedef struct {
    int64_t term;
    bool success;
} rep_t;

// Request Vote
typedef std::function<void(int64_t, bool)> client_rv_t;
typedef std::function<rep_t(int64_t, const std::string&)> service_rv_t;

// Append Entries (TODO: add more params)
typedef std::function<void(int64_t, bool)> client_ae_t;
typedef std::function<rep_t(int64_t, const std::string&)> service_ae_t;

} // namespace raft

#endif // RAFT_CALLBACK_DEFINITIONS
