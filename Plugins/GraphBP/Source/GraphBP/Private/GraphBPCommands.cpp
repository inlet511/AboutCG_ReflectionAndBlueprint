// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GraphBPCommands.h"

#define LOCTEXT_NAMESPACE "FGraphBPModule"

void FGraphBPCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "GraphBP", "Bring up GraphBP window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
