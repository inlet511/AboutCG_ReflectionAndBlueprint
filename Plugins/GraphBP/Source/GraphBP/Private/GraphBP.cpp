// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GraphBP.h"
#include "GraphBPStyle.h"
#include "GraphBPCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphSchema.h"
#include "GraphEditor.h"
#include "TestGraphSchema.h"

static const FName GraphBPTabName("GraphBP");

#define LOCTEXT_NAMESPACE "FGraphBPModule"

void FGraphBPModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGraphBPStyle::Initialize();
	FGraphBPStyle::ReloadTextures();

	FGraphBPCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGraphBPCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FGraphBPModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FGraphBPModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FGraphBPModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GraphBPTabName, FOnSpawnTab::CreateRaw(this, &FGraphBPModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FGraphBPTabTitle", "GraphBP"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FGraphBPModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FGraphBPStyle::Shutdown();

	FGraphBPCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GraphBPTabName);
}

TSharedRef<SDockTab> FGraphBPModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	GraphObject = NewObject<UEdGraph>();
	GraphObject->Schema = UTestGraphSchema::StaticClass();
	GraphObject->AddToRoot();
	GraphEditorSlate = SNew(SGraphEditor)
		.GraphToEdit(GraphObject);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				GraphEditorSlate.ToSharedRef()
			]
		];
}

void FGraphBPModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(GraphBPTabName);
}

void FGraphBPModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FGraphBPCommands::Get().OpenPluginWindow);
}

void FGraphBPModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FGraphBPCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGraphBPModule, GraphBP)