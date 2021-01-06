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

/*
*  - Todo -
*  -
*  - 1) Add a RemoveNode function to the LinkedList
*  - 2) Add a FindNode function to the LinkedList
*/

struct LinkedList
{
public:

    LinkedList(const std::string& string)
    {
        this->SetData(string);
    }

   inline bool operator==(const LinkedList& rhs)
    {
       if ((Data == rhs.Data) && (_internal_incrementor == rhs._internal_incrementor) && (GetNextNode() == rhs.GetNextNode()) && (GetRootNode() == rhs.GetRootNode()))
       {
           return true;
       }

       return false;
    }

    LinkedList* Next()
    {
        if (this->Ptr == nullptr)
        {
            this->Ptr = this;

            return this->Ptr;
        }

        if (this->Ptr->GetNextNode() == nullptr)
        {
            return nullptr;
        }

        this->Ptr = this->Ptr->GetNextNode();

        return this->Ptr;
    }

    LinkedList* Previous()
    {
        if (this->Ptr == nullptr)
        {
            this->Ptr = this->End();

            return this->Ptr;
        }

        if (this->Ptr->GetPreviousNode() == nullptr)
        {
            return nullptr;
        }

        this->Ptr = this->Ptr->GetPreviousNode();

        return this->Ptr;
    }

    LinkedList* End()
    {
        LinkedList* temp;

        for (auto index = -1; index <= this->_internal_incrementor; index++)
        {
            if (this->Next() == nullptr)
            {
                temp = this->Ptr;

                return temp;
            }
        }

        return nullptr;
    }

    LinkedList* Begin()
    {
        this->Ptr = this;

        return this;
    }

    std::string& GetData()
    {
        if (this)
        {
            return Data;
        }

        return Data = "Invalid!";
    }

    LinkedList* GetPtr()
    {
        return Ptr;
    }

    LinkedList* GetRootNode() const
    {
        return root;
    }

    LinkedList* GetNextNode() const
    {
        return _Next;
    }

    LinkedList* GetPreviousNode() const
    {
        return _Previous;
    }

    void SetData(std::string const& paramData)
    {
        Data = paramData;
    }

    void SetRootNode(LinkedList* paramNode)
    {
        root = &*paramNode;
    }

    void SetNextNode(LinkedList* paramNode)
    {
        _Next = &*paramNode;
    }

    void SetPreviousNode(LinkedList* paramNode)
    {
        _Previous = &*paramNode;
    }

    void AddNode(LinkedList* paramNode)
    {
        if ((nullptr) == paramNode)
        {
            std::cout << "Warning: Tried to add a nulled node to linked list! \n \n";
            return;
        }

        if (this->Current == nullptr && this->GetNextNode() == nullptr && this->GetPreviousNode() == nullptr)
        {
            // 'this' must be root node

            paramNode->SetRootNode(this);
            paramNode->SetPreviousNode(this);

            this->SetNextNode(paramNode);
            this->Current = paramNode;
            paramNode->SetPreviousNode(this);

            Ptr = this;

            return;
        }

        if (this->GetRootNode() == paramNode)
        {
            std::cout << "Warning: Trying to add Root Node to the end of the list!" << "\n \n";
            return;
        }

        paramNode->SetRootNode(this);
        paramNode->SetPreviousNode(this->Current);

        this->Current->SetNextNode(paramNode);
        this->Current = paramNode;

        this->_internal_incrementor++;

        return;
    }

private:
    LinkedList* Ptr = nullptr;

    LinkedList* root = nullptr;
    LinkedList* _Previous = nullptr;
    LinkedList* _Next = nullptr;

    LinkedList* Current = nullptr;

    int _internal_incrementor = 0;

    std::string Data;
};

class BaseClassExample
{
public:
    virtual void ShowPolyMessage()
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
    void ShowPolyMessage()
    {
        std::cout << "Showing Message from DerivedFromBaseClassExample!" << "\n \n";
    }

    virtual std::string ReturnSlicingString() const
    {
        return "Slicing: Called from DerivedFromBaseClassExample!";
    }
};

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
* - Nope. Compiler throws: Warning	C4172	returning address of local variable or temporary: tempIntLValueLiteral	CPPRefresher

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
    paramBaseClassExample.ShowPolyMessage();
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

void ShowClassTests()
{
    BaseClassExample baseClass;

    DerivedFromBaseClassExample derivedClass;

    std::cout << "------ Class Tests ------" << "\n \n";

    baseClass.ShowPolyMessage();

    derivedClass.ShowPolyMessage();

    std::cout << "Slicing: Following message should be from derived class: " << "\n";
    SlicingTest_NoReference(derivedClass);

    std::cout << "Slicing: Following message should be from derived class: " << "\n";
    SlicingTest_Reference(derivedClass);

    std::cout << "Poly: " << "\n";
    ShowPolymorphismAtRunTime(baseClass);
    ShowPolymorphismAtRunTime(derivedClass);

    std::cout << "------ Class Tests End ------" << "\n \n";
}

void PassAddress(int* inPtr)
{
    std::cout << "PassAddress: inPtr = " << *inPtr << "\n \n";
}

void PassPtr(int* inPtr)
{
    std::cout << "PassPtr: inPtr = " << *inPtr << "\n \n";
}

int main()
{
    std::cout << "Pointers, References, LValues and RValues refresher! \n\n";
    std::cout << "By Aaron Thompson \n \n";

    ShowLValueReferenceTests_Literals();

    ShowClassTests();

    int myInt = 100;

    int* pIntMemAddress = &myInt;

    std::cout << "pIntMemAddress = " << *pIntMemAddress << "\n \n";

    PassAddress(&myInt);
    PassPtr(pIntMemAddress);

    LinkedList Root("My Names Root!");

    LinkedList One("My names One!");
    LinkedList Two("My Names Two!");
    LinkedList Three("My Names Three!");
    LinkedList Four("My Names Four!");
    LinkedList Five("My Names Five!");
    LinkedList Six("My Names Six!");
    LinkedList Seven("My Names Seven!");

    Root.AddNode(&One);
    Root.AddNode(&Two);
    Root.AddNode(&Three);
    Root.AddNode(&Four);
    Root.AddNode(&Five);
    Root.AddNode(&Six);
    Root.AddNode(&Seven);

    //LinkedList Forward
    for (auto index = Root.Begin(); index != nullptr; index = Root.Next())
    {
        if (index != nullptr)
        {
            std::cout << index->GetData() << "\n \n";
        }
    }

    //LinkedList Reverse
    for (auto index = Root.End(); index != nullptr; index = Root.Previous())
    {
        if (index != nullptr)
        {
            std::cout << index->GetData() << "\n \n";
        }
    }

    //operator== overload for comparison of LinkedLists
    LinkedList L1("Hello My Friend!");
    LinkedList L2("Goodbye My Friend!");

    if (L1 == L2 || L2 == L1)
    {
        std::cout << "L1 == L2 || L2 == L1" << "\n \n";
    }
    else
    {
        std::cout << "L1 != L2 || L2 != L1" << "\n \n";
    }

    WaitConsole();
}
