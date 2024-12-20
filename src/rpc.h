#ifndef RAFT_RPC
#define RAFT_RPC

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <grpcpp/grpcpp.h>

#include "callback.h"
#include "raft.grpc.pb.h"

using grpc::CallbackServerContext;
using grpc::ServerUnaryReactor;

namespace raft {

class Rpc {
public:
    Rpc(const std::string& address, int timeout) 
        : address(address)
        , timeout(timeout) {}
    ~Rpc() {
        server->Shutdown();
        delete service;
    }

    // start gRPC server
    void start(service_rv_t rv_cb, service_ae_t ae_cb);
    // clear all stubs (when node converts to follower)
    void clear();

    // rpc frontend api
    void request_vote(const std::string& peer, 
                    const int64_t term, 
                    client_rv_t callback);
    void append_entries(const std::string& peer,
                    const int64_t term,
                    client_ae_t callback);

private:
    // Impl Wrappers for Client and Server Implementation.
    // ClientImpl allows for state to be contained.
    // ServerImpl allows for the Rpc class to store service information.
    class ClientImpl {
    public:
        ClientImpl(std::unique_ptr<RaftService::Stub> stub, const int timeout)
            : stub(std::move(stub))
            , timeout(timeout) {}

        void RequestVote(VoteRequest request, client_rv_t callback);
        void AppendEntries(AppendRequest request, client_ae_t callback);

    private:
        // context
        const int timeout;
        std::unique_ptr<RaftService::Stub> stub;
        grpc::ClientContext context;

        // responses
        VoteResponse vr;
        AppendResponse ar;
    };

    class ServerImpl: public RaftService::CallbackService {
    public:
        ServerImpl(service_rv_t rv_clbk, service_ae_t ae_clbk)
            : rv_clbk(std::move(rv_clbk))
            , ae_clbk(std::move(ae_clbk)) {}

        ServerUnaryReactor* RequestVote(CallbackServerContext* context,
                                        const VoteRequest* request,
                                        VoteResponse* response) override;

        ServerUnaryReactor* AppendEntries(CallbackServerContext* context,
                                        const AppendRequest* request,
                                        AppendResponse* response) override;
    
    private:
        service_rv_t rv_clbk;
        service_ae_t ae_clbk;
    };

private:
    // configs
    const std::string address;
    const int timeout;

    // peer channels. Use get_stub() internally to access cached stubs.
    std::mutex channel_mutex;
    std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> channels;
    std::unique_ptr<RaftService::Stub> get_stub(const std::string& peer);

    // server
    ServerImpl * service;
    std::unique_ptr<grpc::Server> server;
};

} // namespace rafe

#endif // RAFT_RPC
