#include "common_defines.h"
#include "dihedralrotation.h"
#include "dihedralreflection.h"

IDihedralGenericPtr DihedralRotation::then(IDihedralGenericPtr operation_object) const noexcept
{
    double transition_angle {0.0};
    IDihedralGenericPtr transition_object = nullptr;
    if(operation_object->isRotation())
    {
        transition_angle = operation_object->getAngle() + this->getAngle();
        if(transition_angle >= FULL_CIRCLE) //simplify the angle
        {
            transition_angle -= FULL_CIRCLE;
        }
        transition_object = DihedralRotation::getObject(transition_angle);
    }
    else
    {
        double this_rotate_to_reflection_angle = angle_/INT_TWO;
        transition_angle = operation_object->getAngle() - this_rotate_to_reflection_angle;

        if(transition_angle < MIN_ANGLE)//simplify the angle
        {
            transition_angle =  HALF_CIRCLE + transition_angle;
        }
        transition_object = DihedralReflection::getObject(transition_angle);
    }
    return transition_object;
}

IDihedralGenericPtr DihedralRotation::inv() const noexcept
{
    IDihedralGenericPtr transition_object = nullptr;
    double inv_transition_rotate_angle = (angle_ == 0.0)? angle_ : (FULL_CIRCLE - angle_);
    transition_object = DihedralRotation::getObject(inv_transition_rotate_angle);
    return transition_object;
}

IDihedralGenericPtr DihedralRotation::getObject(const double& angle)
{
    IDihedralGenericPtr transition_object = nullptr;
    try {
        transition_object = std::make_shared<DihedralRotation>(angle);
    } catch (std::bad_alloc& error) {
        std::cout<< error.what()<< std::endl;
    }
    return transition_object;
}
