#ifndef R_TYPE_OMEGATRONSYSTEM_HPP
#define R_TYPE_OMEGATRONSYSTEM_HPP

#include "ecs/ASystem/ASystem.hpp"
#include "ecs/Version/Version.hpp"

class OmegatronSystem : public ecs::ASystem {

    public:

    OmegatronSystem();

    ~OmegatronSystem() override  = default;

    void start() override;

    void stop() override;

    void tick(long deltatime) override;

    const ecs::Version &getType() const override;

    private:

    bool _isRunning;
    static const ecs::Version Version;
};

#endif //R_TYPE_OMEGATRONSYSTEM_HPP
