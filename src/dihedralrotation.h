#ifndef DIHEDRALROTATION_H
#define DIHEDRALROTATION_H

#include "dihedralgeneric.h"

class DihedralRotation: public IDihedralGeneric {

public:
    DihedralRotation(double angle):
        is_rotation_(true),
        is_reflection_(false),
        angle_(angle) {}

    virtual ~DihedralRotation() override {}

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

#endif // DIHEDRALROTATION_H
