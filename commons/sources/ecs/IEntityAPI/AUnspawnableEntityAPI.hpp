//
// Created by Lilian on 29/11/2019.
//

#ifndef R_TYPE_AUnspawnableEntityAPI_HPP
#define R_TYPE_AUnspawnableEntityAPI_HPP

#include "IEntityAPI.hpp"

namespace ecs {
    class AUnspawnableEntityAPI : public ecs::IEntityAPI {
    public:
        bool isSpawnable() const override;
    };
}

#endif //R_TYPE_AUnspawnableEntityAPI_HPP
