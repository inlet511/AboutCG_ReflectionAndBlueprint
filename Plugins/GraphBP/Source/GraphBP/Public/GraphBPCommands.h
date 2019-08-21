// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GraphBPStyle.h"

class FGraphBPCommands : public TCommands<FGraphBPCommands>
{
public:

	FGraphBPCommands()
		: TCommands<FGraphBPCommands>(TEXT("GraphBP"), NSLOCTEXT("Contexts", "GraphBP", "GraphBP Plugin"), NAME_None, FGraphBPStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};