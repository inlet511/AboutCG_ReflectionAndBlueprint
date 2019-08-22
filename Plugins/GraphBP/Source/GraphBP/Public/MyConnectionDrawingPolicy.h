#pragma once 
#include "ConnectionDrawingPolicy.h"

//在Build.cs中包含模块"GraphEditor"
//绘制规则
class FMyConnectionDrawingPolicy :public FConnectionDrawingPolicy
{
public:

	FMyConnectionDrawingPolicy(
		int32 InBackLayerID,							//连接线的ID
		int32 InFrontLayerID,							//箭头的ID
		float InZoomFactor,								//右上角的Zoom级别
		const FSlateRect& InClippingRect,				//当前视口的范围
		class FSlateWindowElementList& InDrawElements,	//绘制的元素
		class UEdGraph* InGraphObj);					//当前Graph

	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;

	virtual void DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params) override;


protected:
	//在哪个Graph中建立连线
	UEdGraph* EdGraphObj;

	//哪个GraphNode建立这个连接
	TMap<UEdGraphNode*, int32> EdNodeWidgetMap;
};