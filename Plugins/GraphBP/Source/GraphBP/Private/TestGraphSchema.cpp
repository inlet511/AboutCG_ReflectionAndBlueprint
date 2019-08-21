#include "TestGraphSchema.h"
#include "TestNode_HelloWorld.h"

#define LOCTEXT_NAMESPACE "TestGraphSchema"

UEdGraphNode* FTestGraphSchemaAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UEdGraphNode*  UEdResultNode = nullptr;
	if (NodeHelloWorld != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("FF", "HelloNewNode"));

		ParentGraph->Modify();

		if (FromPin != nullptr)
		{
			FromPin->Modify();
		}

		NodeHelloWorld->Rename(nullptr, ParentGraph);

		ParentGraph->AddNode(NodeHelloWorld, true, bSelectNewNode);

		NodeHelloWorld->CreateNewGuid();
		NodeHelloWorld->PostPlacedNewNode();
		NodeHelloWorld->AllocateDefaultPins();
		NodeHelloWorld->AutowireNewNode(FromPin);

		NodeHelloWorld->NodePosX = Location.X;
		NodeHelloWorld->NodePosY = Location.Y;

		NodeHelloWorld->SetFlags(RF_Transactional);

		UEdResultNode = NodeHelloWorld;
	}
	return UEdResultNode;
}

void UTestGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FTestGraphSchemaAction> NewNodeAction(new
		FTestGraphSchemaAction(
			LOCTEXT("GroupName", "TestGroup"),
			LOCTEXT("NodeName", "TestNode"),
			LOCTEXT("Desc", "Add a Node"),
			0));
	NewNodeAction->NodeHelloWorld = NewObject<UTestNode_HelloWorld>(ContextMenuBuilder.OwnerOfTemporaries);
	ContextMenuBuilder.AddAction(NewNodeAction);
}

