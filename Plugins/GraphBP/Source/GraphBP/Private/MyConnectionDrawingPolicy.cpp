#include "MyConnectionDrawingPolicy.h"
#include "Rendering/DrawElements.h"

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

void FMyConnectionDrawingPolicy::DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params)
{
	const FVector2D Delta = End - Start;
	const FVector2D DirDelta = Delta.GetSafeNormal();

	FSlateDrawElement::MakeDrawSpaceSpline(
		DrawElementsList,
		LayerId,
		Start,DirDelta,
		End,DirDelta,
		Params.WireThickness,
		ESlateDrawEffect::None,
		Params.WireColor
	);
}

