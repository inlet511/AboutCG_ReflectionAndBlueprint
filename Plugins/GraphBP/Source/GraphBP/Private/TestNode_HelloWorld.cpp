#include "TestNode_HelloWorld.h"

UTestNode_HelloWorld::UTestNode_HelloWorld()
{

}

void UTestNode_HelloWorld::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "HelloNodeInput1", FName(), TEXT("In1"));
	CreatePin(EGPD_Input, "HelloNodeInput2", FName(), TEXT("In2"));
	CreatePin(EGPD_Input, "HelloNodeInput3", FName(), TEXT("In3"));
	CreatePin(EGPD_Input, "HelloNodeInput4", FName(), TEXT("In4"));
	CreatePin(EGPD_Input, "HelloNodeInput5", FName(), TEXT("In5"));
	CreatePin(EGPD_Input, "HelloNodeInput6", FName(), TEXT("In6"));

	CreatePin(EGPD_Output, "HelloNodeOutput1", FName(), TEXT("Out1"));
	CreatePin(EGPD_Output, "HelloNodeOutput2", FName(), TEXT("Out2"));
	CreatePin(EGPD_Output, "HelloNodeOutput3", FName(), TEXT("Out3"));
	CreatePin(EGPD_Output, "HelloNodeOutput4", FName(), TEXT("Out4"));
	CreatePin(EGPD_Output, "HelloNodeOutput5", FName(), TEXT("Out5"));
	CreatePin(EGPD_Output, "HelloNodeOutput6", FName(), TEXT("Out6"));


}

FText UTestNode_HelloWorld::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("HelloWorld");
}

