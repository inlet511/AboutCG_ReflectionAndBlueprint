#include "TestGraphSchema.h"
#include "TestNode_HelloWorld.h"
#include "ScopedTransaction.h"
#include "EdGraph/EdGraph.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Images/SImage.h"
#include "MyConnectionDrawingPolicy.h"

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

void UTestGraphSchema::GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const
{
	MenuBuilder->BeginSection(TEXT("Hall"));
	{

		MenuBuilder->AddWidget(
			SNew(SImage),
			LOCTEXT("ImageTest","Just Image Test")
		);

		MenuBuilder->AddEditableText(
			LOCTEXT("A", "Just a Hello"),
			LOCTEXT("B", "BBB"),
			FSlateIcon(),
			LOCTEXT("TTT", "just a TTT")			
		);
	}
	MenuBuilder->EndSection();
}

class FConnectionDrawingPolicy* UTestGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	return new FMyConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

