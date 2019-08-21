#pragma once 

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "TestNode_HelloWorld.generated.h"

//图表中的一个节点类
UCLASS(MinimalAPI)
class UTestNode_HelloWorld :public UEdGraphNode
{
	GENERATED_BODY()

public:
	UTestNode_HelloWorld();

	//分配节点接口
	virtual void AllocateDefaultPins() override;

	//节点标题
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};