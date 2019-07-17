// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	Connect();

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AMyActor::Connect()
{
	UE_LOG(LogTemp, Log, TEXT("Connect start"));
#if MACTOR_WITH_LIBMONGO_C
	
	const char *uri_string = "mongodb://localhost:27017";
	
	// Required to initialize libmongoc's internals	
	mongoc_init();

	// Stores any error that might appear during the connection
	bson_error_t error;

	// Safely create a MongoDB URI object from the given string
	//FString Uri = TEXT("mongodb://") + ServerIp + TEXT(":") + FString::FromInt(ServerPort);
	uri = mongoc_uri_new_with_error(uri_string, &error);
	if (!uri)
	{
		UE_LOG(LogTemp, Error, TEXT("%s::%d Err.:%s"),
			*FString(__func__), __LINE__, *uri_string, *FString(error.message));
		return false;
	}

	// Create a new client instance
	client = mongoc_client_new_from_uri(uri);
	if (!client)
	{
		return false;
	}

	// Register the application name so we can track it in the profile logs on the server
	mongoc_client_set_appname(client, "trajectory");

	// Get a handle on the database "db_name" and collection "coll_name"
	database = mongoc_client_get_database(client, "SemLogVis421");
	collection = mongoc_client_get_collection(client, "SemLogVis421", "t1");

	UE_LOG(LogTemp, Log, TEXT("Connect successfully111"));
	
	//Insert record
	UE_LOG(LogTemp, Log, TEXT("Connect successfully111"));
	bson_oid_t oid;
	bson_t *doc;

	doc = bson_new();
	bson_oid_init(&oid, NULL);
	BSON_APPEND_OID(doc, "_id", &oid);
	BSON_APPEND_UTF8(doc, "hello", "world");
	if (!mongoc_collection_insert_one(
		collection, doc, NULL, NULL, &error)) {
		fprintf(stderr, "%s\n", error.message);
	}
	bson_destroy(doc);

	//query
	/*UE_LOG(LogTemp, Log, TEXT("start query1"));
	const bson_t * doc;
	bson_t * query;
	mongoc_cursor_t *cursor;
	char * str;
	bson_oid_t oid;
	FString JsonRaw;

	bson_oid_init_from_string(&oid, "5d1f4f07dd3ffb49c0000f55");
	query = BCON_NEW("_id", BCON_OID(&oid));

	cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
	
	while (mongoc_cursor_next(cursor, &doc)) {
		str = bson_as_canonical_extended_json(doc, NULL);
		JsonRaw = FString(str);
		UE_LOG(LogTemp, Log, TEXT("%s"), *FString(str));
		bson_free(str);
	}

	bson_destroy(query);
	mongoc_cursor_destroy(cursor);


	TSharedPtr<FJsonObject> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonRaw);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		FString ExampleString = JsonParsed->GetObjectField("_id")->GetStringField("$oid");
		UE_LOG(LogTemp, Log, TEXT("%s"), *ExampleString);
	}*/
	

	return true;
#else
	return false;

#endif // MACTOR_WITH_LIBMONGO_C

	
}

void AMyActor::Query()
{

}