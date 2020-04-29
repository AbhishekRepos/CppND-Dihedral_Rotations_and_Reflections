#include "common_defines.h"
#include "dihedralreflection.h"
#include "dihedralrotation.h"

IDihedralGenericPtr DihedralReflection::then(IDihedralGenericPtr operation_object) const noexcept
{
    double transition_angle {0.0};
    IDihedralGenericPtr transition_object = nullptr;
    if(operation_object->isRotation())
    {
        //convert rotate angle to reflection angle
        double operation_object_rotate_to_reflection_angle = operation_object->getAngle()/INT_TWO;
        transition_angle = angle_ +  operation_object_rotate_to_reflection_angle; //rotate reflection angle then operation_object angle

        if(transition_angle >= HALF_CIRCLE) //simplify the angle
        {
            transition_angle = transition_angle - HALF_CIRCLE;
        }
        transition_object = DihedralReflection::getObject(transition_angle);
    }
    else
    {
        double operation_object_reflection_to_rotate_angle = INT_TWO * operation_object->getAngle();
        double this_reflection_to_rotate_angle = INT_TWO * this->angle_;
        transition_angle = (operation_object_reflection_to_rotate_angle - this_reflection_to_rotate_angle);

        if(transition_angle < MIN_ANGLE)
        {
            transition_angle =  FULL_CIRCLE + transition_angle; // convert negative angle in positive direction
        }
        transition_object = DihedralRotation::getObject(transition_angle);
    }
    return transition_object;
}

IDihedralGenericPtr DihedralReflection::inv() const noexcept
{
    IDihedralGenericPtr transition_object = nullptr;
    transition_object = DihedralReflection::getObject(angle_);
    return transition_object;
}

IDihedralGenericPtr DihedralReflection::getObject(const double& angle)
{
    IDihedralGenericPtr transition_object = nullptr;
    try {
        transition_object = std::make_shared<DihedralReflection>(angle);
    } catch (std::bad_alloc& error) {
        std::cout<< error.what()<< std::endl;
    }
    return transition_object;
}
