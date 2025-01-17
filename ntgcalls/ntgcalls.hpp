//
// Created by Laky64 on 22/08/2023.
//

#include <cstdint>
#include "client.hpp"
#include "models/media_description.hpp"

namespace ntgcalls {

    class NTgCalls {
    private:
        std::shared_ptr<DispatchQueue> dispatchUpdates;
        std::map<int64_t, std::shared_ptr<Client>> connections;
        wrtc::synchronized_callback<int64_t, Stream::Type> onEof;
        wrtc::synchronized_callback<int64_t, MediaState> onChangeStatus;

        bool exists(int64_t chatId);

        std::shared_ptr<Client> safeConnection(int64_t chatId);

    public:
        NTgCalls();

        ~NTgCalls();

        std::string createCall(int64_t chatId, MediaDescription media);

        void connect(int64_t chatId, std::string params);

        void changeStream(int64_t chatId, MediaDescription media);

        bool pause(int64_t chatId);

        bool resume(int64_t chatId);

        bool mute(int64_t chatId);

        bool unmute(int64_t chatId);

        void stop(int64_t chatId);

        uint64_t time(int64_t chatId);

        static std::string ping();

        void onUpgrade(std::function<void(int64_t, MediaState)> callback);

        void onStreamEnd(std::function<void(int64_t, Stream::Type)> callback);

        std::map<int64_t, Stream::Status> calls();
    };

} // ntgcalls

