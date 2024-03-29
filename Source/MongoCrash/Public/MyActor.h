// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#if MACTOR_WITH_LIBMONGO_C
THIRD_PARTY_INCLUDES_START
#if PLATFORM_WINDOWS
	#include "Windows/AllowWindowsPlatformTypes.h"
	#include <mongoc/mongoc.h>
	#include "Windows/HideWindowsPlatformTypes.h"
#else
	#include <mongoc/mongoc.h>
#endif // #if PLATFORM_WINDOWS
THIRD_PARTY_INCLUDES_END
#endif // MACTOR_WITH_LIBMONGO_C

#include "MyActor.generated.h"


UCLASS()
class MONGOCRASH_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	bool Connect();

	void Query();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
#if MACTOR_WITH_LIBMONGO_C
	// Server uri
	mongoc_uri_t* uri;

	// MongoC connection client
	mongoc_client_t* client;

	// Database to access
	mongoc_database_t* database;
	
	// Database collection
	mongoc_collection_t* collection;

#endif // MACTOR_WITH_LIBMONGO_C
};
