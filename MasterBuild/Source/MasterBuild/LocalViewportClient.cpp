// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalViewportClient.h"

bool ULocalViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	if (bGamepad)
	{
		// Map the gamepad to the next player index (so 1st controller is player index 1, etc.)
		return Super::InputKey(Viewport, ControllerId + 1, Key, EventType, AmountDepressed, bGamepad);
	}
	else
	{
		return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
	}
}

bool ULocalViewportClient::InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if (bGamepad)
	{
		// Map the gamepad to the next player index (so 1st controller is player index 1, etc.)
		return Super::InputAxis(Viewport, ControllerId + 1, Key, Delta, DeltaTime, NumSamples, bGamepad);
	}
	else
	{
		return Super::InputAxis(Viewport, ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
	}
}


