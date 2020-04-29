#include <iostream>
#include <array>
#include "common_defines.h"
#include "dihedralgeneric.h"
#include "dihedralrotation.h"
#include "dihedralreflection.h"

static const int NUMBER_OF_SIDES = 4;
static const int TRANSITION_COUNT = NUMBER_OF_SIDES * 2;
static const int REFLECTION_START_INDEX = NUMBER_OF_SIDES;
static const int ROTATION_ANGLE_PER_SIDES = 360/NUMBER_OF_SIDES;
static const int REFLECTION_ANGLE_PER_SIDES = 360/(NUMBER_OF_SIDES * 2);


//Data for Triangle
/*#define SEQUENCE 0,1,2,3,4,5
using TransitionRow = std::array<int,TRANSITION_COUNT>;

static const std::array <TransitionRow,TRANSITION_COUNT> transition_matrices {{
	{1, 2, 3, 4, 5, 6},
	{2, 3, 1, 6, 4, 5},
	{3, 1, 2, 5, 6, 4},
	{4, 5, 6, 1, 2, 3},
	{5, 6, 4, 3, 1, 2},
	{6, 4, 5, 2, 3, 1}
}};*/

//Data for Sqaure
#define SEQUENCE 0,1,2,3,4,5,6,7
using TransitionRow = std::array<int,TRANSITION_COUNT>;

static const std::array <TransitionRow,TRANSITION_COUNT> transition_matrices {{
	{1,2,3,4,5,6,7,8},
	{2,3,4,1,8,5,6,7},
	{3,4,1,2,7,8,5,6},
	{4,1,2,3,6,7,8,5},
	{5,6,7,8,1,2,3,4},
	{6,7,8,5,4,1,2,3},
	{7,8,5,6,3,4,1,2},
	{8,5,6,7,2,3,4,1}
}};

//Data for Pentagon
/*#define SEQUENCE 0,1,2,3,4,5,6,7,8,9
using TransitionRow = std::array<int,TRANSITION_COUNT>;

static const std::array <TransitionRow,TRANSITION_COUNT> transition_matrices {{
	{1,2,3,4,5,6,7,8,9,10},
	{2,3,4,5,1,10,6,7,8,9},
	{3,4,5,1,2,9,10,6,7,8},
	{4,5,1,2,3,8,9,10,6,7},
	{5,1,2,3,4,7,8,9,10,6},
	{6,7,8,9,10,1,2,3,4,5},
	{7,8,9,10,6,5,1,2,3,4},
	{8,9,10,6,7,4,5,1,2,3},
	{9,10,6,7,8,3,4,5,1,2},
	{10,6,7,8,9,2,3,4,5,1}
}};*/

template <int N, int K >
using conditionChecker = typename std::enable_if<(K<=2*N),IDihedralGenericPtr>::type;

template<int N>
class Dihedral {
public:
    template<int K>
    conditionChecker<N,K> getRotation() {
        double angle = ROTATION_ANGLE(N,K);
        return std::make_shared<DihedralRotation>(angle);
    }
    template<int K>
    conditionChecker<N,K> getReflection() {
        double angle = REFLECTION_ANGLE(N,K);
        return std::make_shared<DihedralReflection>(angle);
    }
};

void printResult(const int& row, const int& column, const int& output, bool result)
{
    if(result)
    {
        std::cout << "TEST ("<<row+1<< ") then ("<< column+1
                  << ") = ("<< output <<") :: PASSED"<<std::endl;
    }
    else
    {
        std::cout << "TEST ("<< row+1 << ") then ("<< column+1
                  << ") = ("<< output <<") :: FAILED"<<std::endl;
    }
}

int getDihedralStateID(IDihedralGenericPtr obj)
{
    int dihedralStateID {-1};
    if(obj->isRotation())
    {
    	dihedralStateID = (obj->getAngle()/ROTATION_ANGLE_PER_SIDES) + 1;
    }
    else
    {
    	dihedralStateID = REFLECTION_START_INDEX + obj->getAngle()/REFLECTION_ANGLE_PER_SIDES + 1;
    }
    return dihedralStateID;
}

template <int row, int column>
void testRotationTransition()
{
    Dihedral<NUMBER_OF_SIDES> dihedral;
    bool bStatus{false};
    const int& transition_result = transition_matrices[row][column];
    int dihedralStateID;

    if(column < REFLECTION_START_INDEX)
    {
    	dihedralStateID = getDihedralStateID(dihedral.getRotation<row>()->then(dihedral.getRotation<column>()));
        bStatus = (transition_result == dihedralStateID);
    }
    else
    {
        constexpr int reflection_column_index = column - REFLECTION_START_INDEX;
        dihedralStateID = getDihedralStateID(dihedral.getRotation<row>()->then(dihedral.getReflection<reflection_column_index>()));

        bStatus = (transition_result == dihedralStateID);
    }
    printResult(row, column, dihedralStateID, bStatus);
}

template <int row, int column>
void testReflectionTransition()
{
	constexpr int reflection_row_transition_index = row - REFLECTION_START_INDEX;
    int dihedralStateID;

    Dihedral<NUMBER_OF_SIDES> dihedral;
    bool bStatus{false};
    const int& transition_result = transition_matrices[row][column];

    if(column < REFLECTION_START_INDEX)
    {
    	dihedralStateID = getDihedralStateID(
    			dihedral.getReflection<reflection_row_transition_index>()->then(dihedral.getRotation<column>()));
        bStatus = (transition_result == dihedralStateID);
    }
    else
    {
    	constexpr int reflection_column_transition_index = column - REFLECTION_START_INDEX;
        dihedralStateID = getDihedralStateID(
        		dihedral.getReflection<reflection_row_transition_index>()->then(dihedral.getReflection
        				<reflection_column_transition_index>()));

        bStatus = (transition_result == dihedralStateID);
    }
    printResult(row, column, dihedralStateID, bStatus);
}

template<class none = void>
void testDihedralGeneric()
{
	//end of looping via var..
}

template <int last_row>
void testDihedralGeneric() {
    std::cout <<"--------- END "<<last_row + 1 <<"------"<<std::endl;
}

template <int row, int column, int... var2>
void testDihedralGeneric()
{
    if(row < REFLECTION_START_INDEX)
    {
        testRotationTransition<row,column>();
    }
    else
    {
        testReflectionTransition<row,column>();
    }
    testDihedralGeneric<row, var2...>();
}

template<class none = void>
void testDihedral()
{
	//end of looping via var..
}

template <int row, int... var2>
void testDihedral()
{
    testDihedralGeneric<row, SEQUENCE>();
    testDihedral<var2...>();
}

int main()
{
    std::cout << "By Default Calculation is for SQUARE" << std::endl;
    std::cout << "Test data avaiable for Triangle and Pentagon too\n\
To check Traingle and Pentagon,\
change the value of NUMBER_OF_SIDES to 3 or 5 in main.cpp \
and uncomment the respective testdata" << std::endl;

    std::cout << "-----------START TEST----------------"<<std::endl;

    testDihedral<SEQUENCE>();

    std::cout << "-----------END TEST----------------"<<std::endl;
    return 0;
}
