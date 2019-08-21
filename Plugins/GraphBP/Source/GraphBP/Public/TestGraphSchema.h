#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "TestGraphSchema.generated.h"

/*
FEdGraphSchemaAction 蓝图框架中的"动作"
*/
USTRUCT()
struct FTestGraphSchemaAction :public FEdGraphSchemaAction
{
	GENERATED_BODY()
public:
	FTestGraphSchemaAction()
	{}
	FTestGraphSchemaAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, FText InKeywords = FText(), int32 InSectionID = 0)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, InKeywords, InSectionID)
	{}

	//点击某个环境菜单选项要执行的操作
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;

	//环境菜单中的一个选项
	class UTestNode_HelloWorld*  NodeHelloWorld;
};

/*
UEdGraphSchema 整个蓝图的框架
*/

UCLASS(MinimalAPI)
class UTestGraphSchema :public UEdGraphSchema
{
	GENERATED_BODY()

public:

	
	//在Schema中右键的环境菜单	
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	//选择一个已经创建的节点右键的环境菜单
	virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;

	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT("Not implemented by this schema"));
	}
};