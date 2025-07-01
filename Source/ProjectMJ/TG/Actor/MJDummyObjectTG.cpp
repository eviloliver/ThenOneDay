
#include "TG/Actor/MJDummyObjectTG.h"

AMJDummyObjectTG::AMJDummyObjectTG()
{
}

void AMJDummyObjectTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMJDummyObjectTG::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
