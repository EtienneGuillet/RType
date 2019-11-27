#ifndef R_TYPE_ENTITIESSTATE_HPP
#define R_TYPE_ENTITIESSTATE_HPP

#include <map>

namespace rtype {

    class EntitiesState {

        public:

        EntitiesState();

        ~EntitiesState() = default;

        void setPos(int x, int y, int z);

        const std::map<std::string, int> &getPos() const;

        void setRot(int x, int y);

        const std::map<std::string, int> &getRot() const;

        void setScale(int x, int y);

        const std::map<std::string, int> &getScale() const;

        void setId(int id);

        [[nodiscard]] int getId() const;

        void setType(int type);

        [[nodiscard]] int getType() const;

        private:

        int _id;
        int _type;
        int _posX;
        int _posY;
        int _posZ;
        int _rotX;
        int _rotY;
        int _scaleX;
        int _scaleY;
    };
}

#endif //R_TYPE_ENTITIESSTATE_HPP
