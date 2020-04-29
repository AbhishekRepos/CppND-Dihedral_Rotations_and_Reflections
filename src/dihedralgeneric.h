#ifndef DIHEDRALGENERIC_H
#define DIHEDRALGENERIC_H

#include<iostream>
#include <memory>

class IDihedralGeneric;
using IDihedralGenericPtr = std::shared_ptr<IDihedralGeneric>;

class IDihedralGeneric
{
public:
    virtual ~IDihedralGeneric() {}

    virtual bool isRotation() const noexcept = 0;
    virtual bool isReflection() const noexcept = 0;
    virtual double getAngle() const noexcept = 0;
    virtual IDihedralGenericPtr then(IDihedralGenericPtr) const noexcept = 0;
    virtual IDihedralGenericPtr inv() const noexcept = 0;
};


#endif // DIHEDRALGENERIC_H
