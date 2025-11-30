// Fill out your copyright notice in the Description page of Project Settings.


#include "UIScreenBase.h"

void UUIScreenBase::OnShow()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UUIScreenBase::OnHide()
{
	SetVisibility(ESlateVisibility::Hidden);
}
