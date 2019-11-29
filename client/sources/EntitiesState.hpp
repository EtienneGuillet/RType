#ifndef R_TYPE_ENTITIESSTATE_HPP
#define R_TYPE_ENTITIESSTATE_HPP

#include <map>
#include <chrono>
#include "maths/Vectors.hpp"

/*!
 * @namespace rtype
 * @brief A generic namespace for the rtype project
 */
namespace rtype {

    /*!
     * @class EntitiesState
     * @brief Used to store information of a entity for graphical and network purpose.
     */
    class EntitiesState {

        public:

        /*!
         * @brief Ctor.
         */
        EntitiesState();

        /*!
         * @brief Dtor.
         */
        ~EntitiesState() = default;

        /*!
         * @brief Set the position vector of the entity.
         * @param x X position on screen.
         * @param y Y position on screen.
         * @param z Z position on screen.
         */
        void setPos(std::uint32_t x, std::uint32_t y, std::uint32_t z);

        /*!
         * @brief Get the position of the entity.
         * @return The 3D position vector of the entity.
         */
        b12software::maths::Vector3D getPos() const;

        /*!
         * @brief Set the rotation of the entity.
         * @param x X rotation axe on screen.
         * @param y Y rotation axe on screen.
         */
        void setRot(std::uint32_t x, std::uint32_t y);

        /*!
         * @brief Get the rotation of the entity.
         * @return The 2D rotation vector of the entity.
         */
        b12software::maths::Vector2D getRot() const;

        /*!
         * @brief Set the scale of the entity.
         * @param x X scale index on screen.
         * @param y Y scale index on screen.
         */
        void setScale(std::uint32_t x, std::uint32_t y);

        /*!
         * @brief Get the scale of the entity.
         * @return The 2D scale vector of the entity.
         */
        b12software::maths::Vector2D getScale() const;

        /*!
         * @brief Set the id of the entity.
         * @param id The id to set.
         */
        void setId(std::uint32_t id);

        /*!
         * @brief Get the id of the entity.
         * @return The id of the entity.
         */
        std::uint32_t getId() const;

        /*!
         * @brief Set the type of the entity.
         * @param id The type to set.
         */
        void setType(std::uint32_t type);

        /*!
         * @brief Get the type of the entity.
         * @return The type of the entity.
         */
        std::uint32_t getType() const;

        /*!
         * @brief Get the last display update
         * @return the last display update
         */
        const std::chrono::high_resolution_clock::time_point &getLastDisplayUpdate() const;
        /*!
         * @brief Set the last display update time point
         * @param lastDisplayUpdate new timepoint
         */
        void setLastDisplayUpdate(const std::chrono::high_resolution_clock::time_point &lastDisplayUpdate);
        /*!
         * @brief Get the last update
         * @return the last update
         */
        const std::chrono::high_resolution_clock::time_point &getLastUpdate() const;
        /*!
         * @brief Get the last update time point
         * @return the last update time point
         */
        void setLastUpdate(const std::chrono::high_resolution_clock::time_point &lastUpdate);

    private:

        std::uint32_t _id;
        std::uint32_t _type;
        std::uint32_t _posX;
        std::uint32_t _posY;
        std::uint32_t _posZ;
        std::uint32_t _rotX;
        std::uint32_t _rotY;
        std::uint32_t _scaleX;
        std::uint32_t _scaleY;
        std::chrono::high_resolution_clock::time_point _lastDisplayUpdate;
        std::chrono::high_resolution_clock::time_point _lastUpdate;
    };
}

#endif //R_TYPE_ENTITIESSTATE_HPP
