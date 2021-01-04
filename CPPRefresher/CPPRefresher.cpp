/* A C++ Refresher of: 
*
* - Pointers
* - References, LValue and RValue References
* - DeReferenced Pointers
* - LValues
* - RValues
* 
* - Excuse the variable names. Just helps me with refreshing. I would not use these in a real world application.
*/


#include <iostream>

void WaitConsole()
{
#ifdef _WIN32
    system("pause");
#endif
}

int ReturnIntRValue()
{
    return 25;
}

class BaseClassExample
{
public:
    virtual void ShowMessage()
    {
        std::cout << "Showing Message from BaseClassExample!" << "\n \n";
    }

    virtual std::string ReturnSlicingString() const
    {
        return "Slicing: Called from the BaseClassExample!";
    }
};

class DerivedFromBaseClassExample : public BaseClassExample
{
public:
    void ShowMessage()
    {
        std::cout << "Showing Message from DerivedFromBaseClassExample!" << "\n \n";
    }

    virtual std::string ReturnSlicingString() const
    {
        return "Slicing: Called from DerivedFromBaseClassExample!";
    }
};

void SlicingTest_NoReference(BaseClassExample paramBaseClass)
{
    std::cout << paramBaseClass.ReturnSlicingString() << "\n \n";
}

void SlicingTest_Reference(const BaseClassExample& paramBaseClass)
{
    std::cout << paramBaseClass.ReturnSlicingString() << "\n \n";
}

/*
* - So am assuming the reaon for being able to reference the TempIntLValueLiteral memory address,
* - is because it has been referenced outside of the ReturnTemporyIntLValue scope, thus keeping 
* - the memory address allocated and not returned to the heap.
* 
* - Nope. Compiler throws: Warning	C4172	returning address of local variable or temporary: tempIntLValueLiteral	CPPRefresher	E:\Github Projects\C++ Refresher\CPPRefresher\CPPRefresher.cpp	66	

* 
* 
int& ReturnTemporaryIntLValueReference()
{
    int tempIntLValueLiteral = 10;

    int& tempIntLValueReference_01 = tempIntLValueLiteral;

    return tempIntLValueReference_01;
}
*/


void ShowPolymorphismAtRunTime(BaseClassExample& paramBaseClassExample)
{
    paramBaseClassExample.ShowMessage();
}

void ShowLValueReferenceTests_Literals()
{
    std::cout << "----- Literal Tests -------" << "\n \n";

    int myLValueIntWithRValueLiteral = 5;

    int& myLValueIntWithRValueLiteralReference_01 = myLValueIntWithRValueLiteral;

    //int& myLValueIntWithRValueLiteralReference_02 = 5; // - Will not work, as a C++ LValue Reference assignment must be a LValue, not an RValue Literal

    std::cout << "myLValueIntWithRValueLiteral: " << myLValueIntWithRValueLiteral << "\n \n"; //Should output 5

    std::cout << "myLValueIntWithRValueLiteralReference_01: " << myLValueIntWithRValueLiteralReference_01 << "\n \n"; //Should reference the LValue and grab the value from its memory address?

    myLValueIntWithRValueLiteralReference_01 = 10; //This should change the value of myLValueIntWithRValueLiteral as myLValueIntWithRValueLiteralReference_01 is referencing myLValueIntWithRValueLiteral memory address.

    std::cout << "myLValueIntWithRValueLiteral: " << myLValueIntWithRValueLiteral << "\n \n"; //Should output 10, as the value at myLValueIntWithRValueLiteralReference memory location was changed through myLValueIntWithRValueLiteralReference_01' reference.

    std::cout << "myLValueIntWithRValueLiteralReference_01: " << myLValueIntWithRValueLiteralReference_01 << "\n \n"; //Should reference the LValue and grab the value from its memory address?

    //int& myLValueIntWithRValueLiteralReference_02 = ReturnIntRValue(); //Hmm didn't show a compiler warning until I hit start debug. Won't work as ReturnIntRValue is returning a RValue literal, and we all know a LValue Reference needs a memory address, which is through an LValue

    //int& myAssumedAccessViolationLValueReference = ReturnTemporaryIntLValueReference();

    //std::cout << "myAssumedAccessViolationLValueReference: " << myAssumedAccessViolationLValueReference << "\n \n";

    //myAssumedAccessViolationLValueReference = 11;
    
    //std::cout << "myAssumedAccessViolationLValueReference: " << myAssumedAccessViolationLValueReference << "\n \n";

    std::cout << "----- End Literal Tests -------" << "\n \n";
}

void ShowReferenceClassTests()
{
    BaseClassExample baseClass;

    DerivedFromBaseClassExample derivedClass;

    std::cout << "------ Class Tests ------" << "\n \n";

    baseClass.ShowMessage();

    derivedClass.ShowMessage();

    std::cout << "Slicing: Following message should be from derived class: " << "\n";
    SlicingTest_NoReference(derivedClass);

    std::cout << "Slicing: Following message should be from derived class: " << "\n";
    SlicingTest_Reference(derivedClass);

    std::cout << "Poly: " << "\n";
    ShowPolymorphismAtRunTime(baseClass);
    ShowPolymorphismAtRunTime(derivedClass);

    std::cout << "------ Class Tests End ------" << "\n \n";
}

int main()
{
    std::cout << "Pointers, References, LValues and RValues refresher! \n\n";
    std::cout << "By Aaron Thompson \n \n";

    ShowLValueReferenceTests_Literals();
 
    ShowReferenceClassTests();

    WaitConsole();
}
