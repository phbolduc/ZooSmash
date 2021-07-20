// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAICharacter.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
protected void AMyAICharacter::Tick(float DeltaTime)
{
	try {
		Super::Tick(DeltaTime);
	}
	catch (...) {
		UKismetSystemLibrary::PrintString(this, FString("Tick don't work???"), true, true, FLinearColor(0, 0.66, 1.0, 1.0), 20);
	}
}

// Called to bind functionality to input
void AMyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
