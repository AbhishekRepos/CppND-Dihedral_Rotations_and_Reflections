#ifndef DIHEDRALREFLECTION_H
#define DIHEDRALREFLECTION_H

#include "dihedralgeneric.h"

class DihedralReflection: public IDihedralGeneric {

public:
    DihedralReflection(double angle):
        is_rotation_(false),
        is_reflection_(true),
        angle_(angle) {}

    virtual ~DihedralReflection() override {}

    bool isRotation() const noexcept override
    {
    	return is_rotation_;
    }

    bool isReflection() const noexcept override
    {
    	return is_reflection_;
    }

    double getAngle() const noexcept override
    {
    	return angle_;
    }

    IDihedralGenericPtr then(IDihedralGenericPtr operation_object) const noexcept override;
    IDihedralGenericPtr inv() const noexcept override;
    static IDihedralGenericPtr getObject(const double& angle);

private:
    bool is_rotation_;
    bool is_reflection_;
    double angle_;
};
#endif // DIHEDRALREFLECTION_H
