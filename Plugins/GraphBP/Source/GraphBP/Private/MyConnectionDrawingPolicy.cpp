#include "MyConnectionDrawingPolicy.h"

FMyConnectionDrawingPolicy::FMyConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj)
	:FConnectionDrawingPolicy(InBackLayerID,InFrontLayerID,InZoomFactor,InClippingRect,InDrawElements)
	,EdGraphObj(InGraphObj)
{

}

static const FLinearColor DefaultWiringColor(1.0f, 0.0f, 0.0f);
void FMyConnectionDrawingPolicy::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params)
{
	Params.WireThickness = 5.5f;
	Params.WireColor = DefaultWiringColor;

	if (HoveredPins.Num() > 0)
	{
		ApplyHoverDeemphasis(OutputPin, InputPin, Params.WireThickness, Params.WireColor);
	}
}

